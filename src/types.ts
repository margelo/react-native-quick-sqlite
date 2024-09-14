export enum ColumnType {
  BOOLEAN,
  NUMBER,
  INT64,
  TEXT,
  ARRAY_BUFFER,
  NULL_VALUE,
}

/**
 * Represents a value that can be stored in a SQLite database
 */
export type SQLiteValue =
  | boolean
  | number
  | bigint
  | string
  | ArrayBuffer
  | undefined

export type SQLiteItem = Record<string, SQLiteValue>

export interface QueryResult<Data extends SQLiteItem = SQLiteItem> {
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

export type SQLiteQueryParams = SQLiteValue[]

export type ExecuteQuery = <Data extends SQLiteItem = SQLiteItem>(
  query: string,
  params?: SQLiteQueryParams
) => QueryResult<Data>

export type ExecuteAsyncQuery = <Data extends SQLiteItem = SQLiteItem>(
  query: string,
  params?: SQLiteQueryParams
) => Promise<QueryResult<Data>>

export interface Transaction {
  commit(): QueryResult
  rollback(): QueryResult
  execute: ExecuteQuery
  executeAsync: ExecuteAsyncQuery
}

/**
 * Allows the execution of bulk of sql commands
 * inside a transaction
 * If a single query must be executed many times with different arguments, its preferred
 * to declare it a single time, and use an array of array parameters.
 */
export interface BatchQueryCommand {
  query: string
  params?: SQLiteQueryParams | SQLiteQueryParams[]
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
