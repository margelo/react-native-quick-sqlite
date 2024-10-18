import type { Spec as AndroidOnLoadTurboModuleSpec } from './NativeQuickSQLiteOnLoad'

export const noop: AndroidOnLoadTurboModuleSpec = {
  onReactApplicationContextReady: () => undefined,
}

export default noop
