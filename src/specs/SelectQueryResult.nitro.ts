import { HybridObject } from 'react-native-nitro-modules'

export interface SelectQueryResult
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  /**
   * Query metadata, avaliable only for select query results
   */
  metadata: ColumnMetadata[]

  getString(): string
  getNumber(): number
  getBoolean(): boolean
  getArrayBuffer(): ArrayBuffer
}

type ColumnType =
  | 'NULL_VALUE'
  | 'TEXT'
  | 'INTEGER'
  | 'INT64'
  | 'DOUBLE'
  | 'BOOLEAN'
  | 'ARRAY_BUFFER'
  | 'UNKNOWN'
// | 'null'
// | 'string'
// | 'number'
// | 'boolean'
// | 'ArrayBuffer';

/**
 * Column metadata
 * Describes some information about columns fetched by the query
 */
export interface ColumnMetadata {
  /** The name used for this column for this resultset */
  columnName: string
  /** The declared column type for this column, when fetched directly from a table or a View resulting from a table column. "UNKNOWN" for dynamic values, like function returned ones. */
  columnDeclaredType: ColumnType
  /**
   * The index for this column for this resultset*/
  columnIndex: number
}
