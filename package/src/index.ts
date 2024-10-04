import { transaction } from './transaction'
import { HybridQuickSQLite } from './nitro'
import type {
  QueryResult,
  QuickSQLiteConnection,
  BatchQueryCommand,
  Transaction,
  SQLiteItem,
  SQLiteQueryParams,
  QuickSQLiteConnectionOptions,
} from './types'
import * as Operations from './operations'
import QuickSQLiteOnLoad from './specs/NativeQuickSQLiteOnLoad'

export * from './types'
export { typeORMDriver } from './typeORM'

export const onInitialized = new Promise<void>((resolve) => {
  QuickSQLiteOnLoad.onReactApplicationContextReady(resolve)
})

export function open(
  options: QuickSQLiteConnectionOptions
): QuickSQLiteConnection {
  Operations.open(options.name, options.location)

  return {
    close: () => Operations.close(options.name),
    delete: () => HybridQuickSQLite.drop(options.name, options.location),
    attach: (dbNameToAttach: string, alias: string, location?: string) =>
      HybridQuickSQLite.attach(options.name, dbNameToAttach, alias, location),
    detach: (alias: string) => HybridQuickSQLite.detach(options.name, alias),
    transaction: (fn: (tx: Transaction) => Promise<void> | void) =>
      transaction(options.name, fn),
    execute: <Data extends SQLiteItem = never>(
      query: string,
      params?: SQLiteQueryParams
    ): QueryResult<Data> => Operations.execute(options.name, query, params),
    executeAsync: <Data extends SQLiteItem = never>(
      query: string,
      params?: SQLiteQueryParams
    ): Promise<QueryResult<Data>> =>
      Operations.executeAsync(options.name, query, params),
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

export const QuickSQLite = {
  ...HybridQuickSQLite,
  onInitialized,
  open,
  transaction,
  execute: Operations.execute,
  executeAsync: Operations.executeAsync,
}
