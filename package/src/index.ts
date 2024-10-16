import { transaction } from './transaction'
import { HybridNitroSQLite } from './nitro'
import * as Operations from './operations'
import NitroSQLiteOnLoad from './specs/NativeNitroSQLiteOnLoad'

export * from './types'
export { typeORMDriver } from './typeORM'

export const onInitialized = new Promise<void>((resolve) => {
  NitroSQLiteOnLoad.onReactApplicationContextReady(resolve)
})

export const NitroSQLite = {
  ...HybridNitroSQLite,
  native: HybridNitroSQLite,
  onInitialized,
  // Overwrite native functions with session-based JS implementations,
  // where the database name can be ommited once opened
  open: Operations.open,
  transaction,
  execute: Operations.execute,
  executeAsync: Operations.executeAsync,
}

export { open } from './operations'
