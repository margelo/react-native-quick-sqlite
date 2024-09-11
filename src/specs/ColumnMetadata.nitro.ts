import { HybridObject } from 'react-native-nitro-modules'
import { ColumnType } from '../types'

/**
 * Column metadata
 * Describes a column in table fetched by a select query
 */
export interface ColumnMetadata
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  /** The name used for this column for this result set */
  name: string
  /** The declared column type for this column, when fetched directly from a table or a View resulting from a table column. "UNKNOWN" for dynamic values, like function returned ones. */
  type: ColumnType
  /** The index for this column for this result set */
  index: number
}
