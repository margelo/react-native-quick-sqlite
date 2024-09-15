import { transaction } from './transaction'
import { QuickSQLite, locks } from './init'
import {
  QueryResult,
  QuickSQLiteConnection,
  BatchQueryCommand,
  Transaction,
  SQLiteItem,
  SQLiteQueryParams,
} from './types'
import { enhanceQueryResult } from './typeORM'
import { NativeQueryResult } from './specs/NativeQueryResult.nitro'

export * from './types'
export { typeORMDriver } from './typeORM'

export function open(options: {
  name: string
  location?: string
}): QuickSQLiteConnection {
  openDb(options.name, options.location)

  return {
    close: () => close(options.name),
    delete: () => QuickSQLite.drop(options.name, options.location),
    attach: (dbNameToAttach: string, alias: string, location?: string) =>
      QuickSQLite.attach(options.name, dbNameToAttach, alias, location),
    detach: (alias: string) => QuickSQLite.detach(options.name, alias),
    transaction: (fn: (tx: Transaction) => Promise<void> | void) =>
      transaction(options.name, fn),
    execute: <Data extends SQLiteItem = never>(
      query: string,
      params?: SQLiteQueryParams
    ): QueryResult<Data> => execute(options.name, query, params),
    executeAsync: <Data extends SQLiteItem = never>(
      query: string,
      params?: SQLiteQueryParams
    ): Promise<QueryResult<Data>> => executeAsync(options.name, query, params),
    executeBatch: (commands: BatchQueryCommand[]) =>
      QuickSQLite.executeBatch(options.name, commands),
    executeBatchAsync: (commands: BatchQueryCommand[]) =>
      QuickSQLite.executeBatchAsync(options.name, commands),
    loadFile: (location: string) =>
      QuickSQLite.loadFile(options.name, location),
    loadFileAsync: (location: string) =>
      QuickSQLite.loadFileAsync(options.name, location),
  }
}

function openDb(dbName: string, location?: string) {
  QuickSQLite.open(dbName, location)

  locks[dbName] = {
    queue: [],
    inProgress: false,
  }
}

function close(dbName: string) {
  QuickSQLite.close(dbName)
  delete locks[dbName]
}

export function execute<Data extends SQLiteItem = never>(
  dbName: string,
  query: string,
  params?: SQLiteQueryParams
): QueryResult<Data> {
  const nativeResult = QuickSQLite.execute(dbName, query, params)
  const result = buildJsQueryResult<Data>(nativeResult)
  enhanceQueryResult(result)
  return result
}

export async function executeAsync<Data extends SQLiteItem = never>(
  dbName: string,
  query: string,
  params?: SQLiteQueryParams
): Promise<QueryResult<Data>> {
  const nativeResult = await QuickSQLite.executeAsync(dbName, query, params)
  const result = buildJsQueryResult<Data>(nativeResult)
  enhanceQueryResult(result)
  return result
}

function buildJsQueryResult<Data extends SQLiteItem = never>(
  nativeResult: NativeQueryResult
): QueryResult<Data> {
  const data = nativeResult.results as Data[]
  return {
    insertId: nativeResult.insertId,
    rowsAffected: nativeResult.rowsAffected,
    rows: {
      data,
      length: data.length,
      item: (idx: number) => data[idx],
    },
  }
}
