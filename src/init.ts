import { NitroModules } from 'react-native-nitro-modules'
import { QuickSQLite as QuickSQLiteSpec } from './specs/QuickSQLite.nitro'
import { PendingTransaction } from './types'

export const QuickSQLite =
  NitroModules.createHybridObject<QuickSQLiteSpec>('QuickSQLite')

export const locks: Record<
  string,
  { queue: PendingTransaction[]; inProgress: boolean }
> = {}
