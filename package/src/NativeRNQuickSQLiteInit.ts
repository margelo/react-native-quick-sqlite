import { TurboModuleRegistry, type TurboModule } from 'react-native'

export interface Spec extends TurboModule {
  install(): Promise<boolean>
}

export default TurboModuleRegistry.getEnforcing<Spec>('RNQuickSQLiteInit')
