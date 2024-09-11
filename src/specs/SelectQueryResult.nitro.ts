import { HybridObject } from 'react-native-nitro-modules'
import { SQLiteValue, TableMetadata } from '../types'

export interface SelectQueryResult
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  results: Record<string, SQLiteValue>[]
  /**
   * Query metadata, avaliable only for select query results
   */
  metadata: TableMetadata
}
