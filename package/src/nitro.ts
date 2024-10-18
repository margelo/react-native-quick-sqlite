import { NitroModules } from 'react-native-nitro-modules'
import type { QuickSQLite as QuickSQLiteSpec } from './specs/QuickSQLite.nitro'
import type { PendingTransaction } from './operations/transaction'

export const HybridQuickSQLite =
  NitroModules.createHybridObject<QuickSQLiteSpec>('QuickSQLite')

export const locks: Record<
  string,
  { queue: PendingTransaction[]; inProgress: boolean }
> = {}
