import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';
import { ISQLite } from './types';

export type Spec = TurboModule & ISQLite;

export default TurboModuleRegistry.getEnforcing<Spec>(
  'RNQuickSQLite'
) as Spec | null;
