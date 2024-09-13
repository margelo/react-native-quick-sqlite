import { transaction } from './transaction'
import { QuickSQLite, locks } from './init'
import {
  SQLiteValue,
  QueryResult,
  QuickSQLiteConnection,
  BatchQueryCommand,
  Transaction,
  SQLiteItem,
  NativeQueryResult,
  ColumnType,
} from './types'
import { enhanceQueryResult } from './typeORM'

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
      params?: SQLiteValue[]
    ): QueryResult<Data> => execute(options.name, query, params),
    executeAsync: <Data extends SQLiteItem = never>(
      query: string,
      params?: SQLiteValue[]
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

function execute<Data extends SQLiteItem = never>(
  dbName: string,
  query: string,
  params?: SQLiteValue[]
): QueryResult<Data> {
  const nativeResult = QuickSQLite.execute(dbName, query, params)
  const result = buildJsQueryResult<Data>(nativeResult)
  enhanceQueryResult(result)
  return result
}

async function executeAsync<Data extends SQLiteItem = never>(
  dbName: string,
  query: string,
  params?: SQLiteValue[]
): Promise<QueryResult<Data>> {
  const nativeResult = await QuickSQLite.executeAsync(dbName, query, params)
  const result = buildJsQueryResult<Data>(nativeResult)
  enhanceQueryResult(result)
  return result
}

function buildJsQueryResult<Data extends SQLiteItem = never>(
  nativeResult: NativeQueryResult
): QueryResult<Data> {
  let result: QueryResult<Data> = {
    queryType: nativeResult.queryType,
    insertId: nativeResult.insertId,
    rowsAffected: nativeResult.rowsAffected,
  }

  if (nativeResult.selectQueryResult) {
    const results = nativeResult.selectQueryResult.results
    const metadata = nativeResult.selectQueryResult.metadata
    const data = results.map((row) => {
      let item = {}

      for (let key in row) {
        switch (metadata[key].type) {
          case ColumnType.BOOLEAN:
            item[key] = row[key] as boolean
            break
          case ColumnType.NUMBER:
            item[key] = row[key] as number
            break
          case ColumnType.INT64:
            item[key] = row[key] as bigint
            break
          case ColumnType.TEXT:
            item[key] = row[key] as string
            break
          case ColumnType.ARRAY_BUFFER:
            item[key] = row[key] as ArrayBuffer
            break
          case ColumnType.NULL_VALUE:
            item[key] = null
            break
          case ColumnType.UNKNOWN:
          default:
            item[key] = row[key] as unknown
        }
      }

      return item as Data
    })

    result.rows = {
      data: data,
      length: data.length,
      item: (idx: number) => result.rows.data[idx],
    }
  }

  return result
}
