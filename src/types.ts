import { SelectQueryResult } from './specs/SelectQueryResult.nitro'

export enum QueryType {
  SELECT,
  INSERT,
  UPDATE,
  DELETE,
  OTHER,
}

export enum ColumnType {
  BOOLEAN,
  NUMBER,
  INT64,
  TEXT,
  ARRAY_BUFFER,
  NULL_VALUE,
  UNKNOWN,
}

/**
 * Represents a value that can be stored in a SQLite database
 */
export type SQLiteValue =
  | number
  | boolean
  | bigint
  | string
  | ArrayBuffer
  | undefined

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
export interface NativeQueryResult {
  readonly queryType: QueryType
  readonly insertId?: number
  readonly rowsAffected: number

  readonly selectQueryResult?: SelectQueryResult
}

export type SQLiteItem = Record<string, SQLiteValue>

export interface QueryResult<Data extends SQLiteItem = never> {
  readonly queryType: QueryType
  readonly insertId?: number
  readonly rowsAffected: number

  rows?: {
    /** Raw array with all dataset */
    data: Data[]
    /** The lengh of the dataset */
    length: number
    /** A convenience function to acess the index based the row object
     * @param idx the row index
     * @returns the row structure identified by column names
     */
    item: (idx: number) => Data
  }
}

export type ExecuteQuery = <Data extends SQLiteItem = never>(
  query: string,
  params?: SQLiteValue[]
) => QueryResult<Data>

export type ExecuteAsyncQuery = <Data extends SQLiteItem = never>(
  query: string,
  params?: SQLiteValue[]
) => Promise<QueryResult<Data>>

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
  params?: Array<SQLiteValue> | Array<Array<SQLiteValue>>
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
