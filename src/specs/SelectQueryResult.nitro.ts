import { HybridObject } from 'react-native-nitro-modules'
import { SQLiteValue } from '../types'
import { ColumnMetadata } from './ColumnMetadata.nitro'

export interface SelectQueryResult
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  /** Select query results */
  results: Record<string, SQLiteValue>[]
  /**
   * Table metadata
   * Describes some information about the table and it's columns fetched by the query
   * The index is the name of the column
   */
  metadata: Record<string, ColumnMetadata>
}
