import { locks, HybridQuickSQLite } from '../nitro'
import { transaction } from './transaction'
import type {
  BatchQueryCommand,
  QuickSQLiteConnection,
  QuickSQLiteConnectionOptions,
  QueryResult,
  SQLiteItem,
  SQLiteQueryParams,
  Transaction,
} from '../types'
import { execute, executeAsync } from './execute'

export function open(
  options: QuickSQLiteConnectionOptions
): QuickSQLiteConnection {
  openDb(options.name, options.location)

  return {
    close: () => close(options.name),
    delete: () => HybridQuickSQLite.drop(options.name, options.location),
    attach: (dbNameToAttach: string, alias: string, location?: string) =>
      HybridQuickSQLite.attach(options.name, dbNameToAttach, alias, location),
    detach: (alias: string) => HybridQuickSQLite.detach(options.name, alias),
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
      HybridQuickSQLite.executeBatch(options.name, commands),
    executeBatchAsync: (commands: BatchQueryCommand[]) =>
      HybridQuickSQLite.executeBatchAsync(options.name, commands),
    loadFile: (location: string) =>
      HybridQuickSQLite.loadFile(options.name, location),
    loadFileAsync: (location: string) =>
      HybridQuickSQLite.loadFileAsync(options.name, location),
  }
}

export function openDb(dbName: string, location?: string) {
  HybridQuickSQLite.open(dbName, location)

  locks[dbName] = {
    queue: [],
    inProgress: false,
  }
}

export function close(dbName: string) {
  HybridQuickSQLite.close(dbName)
  delete locks[dbName]
}
