import type { Spec as AndroidOnLoadTurboModuleSpec } from './NativeNitroSQLiteOnLoad.js'

export const noop: AndroidOnLoadTurboModuleSpec = {
  onReactApplicationContextReady: () => undefined,
}

export default noop
