import { transaction } from './operations/transaction'
import { HybridQuickSQLite } from './nitro'
import { open } from './operations/session'
import QuickSQLiteOnLoad from './specs/NativeQuickSQLiteOnLoad'
import { execute, executeAsync } from './operations/execute'

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
  open,
  transaction,
  execute,
  executeAsync,
}

export { open } from './operations/session'
