import { SelectQueryResult } from './specs/SelectQueryResult.nitro'

/**
 * Object returned by SQL Query executions {
 *  insertId: Represent the auto-generated row id if applicable
 *  rowsAffected: Number of affected rows if result of a update query
 *  message: if status === 1, here you will find error description
 *  rows: if status is undefined or 0 this object will contain the query results
 * }
 *
 * @interface QueryResult
 */
export interface QueryResult {
  readonly queryType: QueryType
  insertId?: number
  rowsAffected: number

  selectQueryResult?: SelectQueryResult
}

export type QueryType = 'SELECT' | 'INSERT' | 'UPDATE' | 'DELETE' | 'OTHER'

export type ExecuteParam =
  | number
  | boolean
  | bigint
  | string
  | ArrayBuffer
  | undefined

export type ExecuteQuery = (
  query: string,
  params?: ExecuteParam[]
) => QueryResult

export type ExecuteAsyncQuery = (
  query: string,
  params?: ExecuteParam[]
) => Promise<QueryResult>

export interface Transaction {
  commit(): QueryResult
  rollback(): QueryResult
  execute: ExecuteQuery
  executeAsync: ExecuteAsyncQuery
}

export interface PendingTransaction {
  /*
   * The start function should not throw or return a promise because the
   * queue just calls it and does not monitor for failures or completions.
   *
   * It should catch any errors and call the resolve or reject of the wrapping
   * promise when complete.
   *
   * It should also automatically commit or rollback the transaction if needed
   */
  start: () => void
}

/**
 * Allows the execution of bulk of sql commands
 * inside a transaction
 * If a single query must be executed many times with different arguments, its preferred
 * to declare it a single time, and use an array of array parameters.
 */
export interface BatchQueryCommand {
  query: string
  params?: Array<ExecuteParam> | Array<Array<ExecuteParam>>
}

/**
 * status: 0 or undefined for correct execution, 1 for error
 * message: if status === 1, here you will find error description
 * rowsAffected: Number of affected rows if status == 0
 */
export interface BatchQueryResult {
  rowsAffected?: number
}

/**
 * Result of loading a file and executing every line as a SQL command
 * Similar to BatchQueryResult
 */
export interface FileLoadResult extends BatchQueryResult {
  commands?: number
}

export interface QuickSQLiteConnection {
  close(): void
  delete(): void
  attach(dbNameToAttach: string, alias: string, location?: string): void
  detach(alias: string): void
  transaction(fn: (tx: Transaction) => Promise<void> | void): Promise<void>
  execute: ExecuteQuery
  executeAsync: ExecuteAsyncQuery
  executeBatch(commands: BatchQueryCommand[]): BatchQueryResult
  executeBatchAsync(commands: BatchQueryCommand[]): Promise<BatchQueryResult>
  loadFile(location: string): FileLoadResult
  loadFileAsync(location: string): Promise<FileLoadResult>
}
