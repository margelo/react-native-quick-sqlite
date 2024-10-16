import { transaction } from './transaction'
import { HybridQuickSQLite } from './nitro'
import * as Operations from './operations'
import QuickSQLiteOnLoad from './specs/NativeQuickSQLiteOnLoad'

export * from './types'
export { typeORMDriver } from './typeORM'

export const onInitialized = new Promise<void>((resolve) => {
  QuickSQLiteOnLoad.onReactApplicationContextReady(resolve)
})

export const QuickSQLite = {
  ...HybridQuickSQLite,
  native: HybridQuickSQLite,
  onInitialized,
  // Overwrite native functions with session-based JS implementations,
  // where the database name can be ommited once opened
  open: Operations.open,
  transaction,
  execute: Operations.execute,
  executeAsync: Operations.executeAsync,
}

export { open } from './operations'
