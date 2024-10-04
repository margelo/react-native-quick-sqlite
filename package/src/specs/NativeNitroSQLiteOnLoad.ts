import type { Spec as AndroidOnLoadTurboModuleSpec } from './NativeNitroSQLiteOnLoad.android.ts'

export const noop: AndroidOnLoadTurboModuleSpec = {
  onReactApplicationContextReady: () => undefined,
}

export default noop
