import { transaction } from './transaction'
import { HybridNitroSQLite } from './nitro'
import type {
  QueryResult,
  NitroSQLiteConnection,
  BatchQueryCommand,
  Transaction,
  SQLiteItem,
  SQLiteQueryParams,
  NitroSQLiteConnectionOptions,
} from './types'
import * as Operations from './operations'
import NitroSQLiteOnLoad from './specs/NativeNitroSQLiteOnLoad'

export * from './types'
export { typeORMDriver } from './typeORM'

export const onInitialized = new Promise<void>((resolve) => {
  NitroSQLiteOnLoad.onReactApplicationContextReady(resolve)
})

export function open(
  options: NitroSQLiteConnectionOptions
): NitroSQLiteConnection {
  Operations.open(options.name, options.location)

  return {
    close: () => Operations.close(options.name),
    delete: () => HybridNitroSQLite.drop(options.name, options.location),
    attach: (dbNameToAttach: string, alias: string, location?: string) =>
      HybridNitroSQLite.attach(options.name, dbNameToAttach, alias, location),
    detach: (alias: string) => HybridNitroSQLite.detach(options.name, alias),
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
      HybridNitroSQLite.executeBatch(options.name, commands),
    executeBatchAsync: (commands: BatchQueryCommand[]) =>
      HybridNitroSQLite.executeBatchAsync(options.name, commands),
    loadFile: (location: string) =>
      HybridNitroSQLite.loadFile(options.name, location),
    loadFileAsync: (location: string) =>
      HybridNitroSQLite.loadFileAsync(options.name, location),
  }
}

export const NitroSQLite = {
  ...HybridNitroSQLite,
  onInitialized,
  open,
  transaction,
  execute: Operations.execute,
  executeAsync: Operations.executeAsync,
}
