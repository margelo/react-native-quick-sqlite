import { HybridObject } from 'react-native-nitro-modules'
import { ColumnType, SQLiteValue } from '../types'

export interface SelectQueryResult
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  /** Select query results */
  results: Record<string, SQLiteValue>[]
  /** Table metadata */
  metadata: Record<string, ColumnMetadata>
}

export interface ColumnMetadata {
  /** The name used for this column for this result set */
  name: string
  /** The declared column type for this column, when fetched directly from a table or a View resulting from a table column. "UNKNOWN" for dynamic values, like function returned ones. */
  type: ColumnType
  /** The index for this column for this result set */
  index: number
}

/**
 * Table metadata
 * Describes some information about the table and it's columns fetched by the query
 * The index is the name of the column
 */
export type TableMetadata = Record<string, ColumnMetadata>
