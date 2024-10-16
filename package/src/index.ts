import { transaction } from './operations/transaction'
import { HybridNitroSQLite } from './nitro'
import { open } from './operations/session'
import NitroSQLiteOnLoad from './specs/NativeNitroSQLiteOnLoad'
import { execute, executeAsync } from './operations/execute'

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
  open,
  transaction,
  execute,
  executeAsync,
}

export { open } from './operations/session'
