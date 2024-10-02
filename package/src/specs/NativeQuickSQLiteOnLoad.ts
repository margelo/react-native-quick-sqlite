import type { Spec as AndroidOnLoadTurboModuleSpec } from './NativeQuickSQLiteOnLoad.android.ts'

export const noop: AndroidOnLoadTurboModuleSpec = {
  onReactApplicationContextReady: () => undefined,
}

export default noop
