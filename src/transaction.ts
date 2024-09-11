import { execute, executeAsync } from '.'
import { locks, QuickSQLite } from './init'
import {
  PendingTransaction,
  QueryResult,
  SQLiteItem,
  SQLiteValue,
  Transaction,
} from './types'

export const transaction = async (
  dbName: string,
  fn: (tx: Transaction) => Promise<void> | void
): Promise<void> => {
  if (!locks[dbName]) {
    throw Error(`Quick SQLite Error: No lock found on db: ${dbName}`)
  }

  let isFinalized = false

  // Local transaction context object implementation
  const executeOnTransaction = <Data extends SQLiteItem = never>(
    query: string,
    params?: SQLiteValue[]
  ): QueryResult<Data> => {
    if (isFinalized) {
      throw Error(
        `Quick SQLite Error: Cannot execute query on finalized transaction: ${dbName}`
      )
    }
    return execute(dbName, query, params)
  }

  const executeAsyncOnTransaction = <Data extends SQLiteItem = never>(
    query: string,
    params?: SQLiteValue[]
  ): Promise<QueryResult<Data>> => {
    if (isFinalized) {
      throw Error(
        `Quick SQLite Error: Cannot execute query on finalized transaction: ${dbName}`
      )
    }
    return executeAsync(dbName, query, params)
  }

  const commit = () => {
    if (isFinalized) {
      throw Error(
        `Quick SQLite Error: Cannot execute commit on finalized transaction: ${dbName}`
      )
    }
    const result = QuickSQLite.execute(dbName, 'COMMIT')
    isFinalized = true
    return result
  }

  const rollback = () => {
    if (isFinalized) {
      throw Error(
        `Quick SQLite Error: Cannot execute rollback on finalized transaction: ${dbName}`
      )
    }
    const result = QuickSQLite.execute(dbName, 'ROLLBACK')
    isFinalized = true
    return result
  }

  async function run() {
    try {
      await QuickSQLite.executeAsync(dbName, 'BEGIN TRANSACTION')

      await fn({
        commit,
        execute: executeOnTransaction,
        executeAsync: executeAsyncOnTransaction,
        rollback,
      })

      if (!isFinalized) {
        commit()
      }
    } catch (executionError) {
      if (!isFinalized) {
        try {
          rollback()
        } catch (rollbackError) {
          throw rollbackError
        }
      }

      throw executionError
    } finally {
      locks[dbName].inProgress = false
      isFinalized = false
      startNextTransaction(dbName)
    }
  }

  return await new Promise((resolve, reject) => {
    const tx: PendingTransaction = {
      start: () => {
        run().then(resolve).catch(reject)
      },
    }

    locks[dbName].queue.push(tx)
    startNextTransaction(dbName)
  })
}

function startNextTransaction(dbName: string) {
  if (!locks[dbName]) {
    throw Error(`Lock not found for db: ${dbName}`)
  }

  if (locks[dbName].inProgress) {
    // Transaction is already in process bail out
    return
  }

  if (locks[dbName].queue.length) {
    locks[dbName].inProgress = true
    const tx = locks[dbName].queue.shift()
    setImmediate(() => {
      tx.start()
    })
  }
}
