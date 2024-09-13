import { HybridObject } from 'react-native-nitro-modules'
import {
  BatchQueryResult,
  FileLoadResult,
  BatchQueryCommand,
  SQLiteValue,
} from '../types'
import { NativeQueryResult } from './NativeQueryResult.nitro'

export interface QuickSQLite
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  open(dbName: string, location?: string): void
  close(dbName: string): void
  drop(dbName: string, location?: string): void
  attach(
    mainDbName: string,
    dbNameToAttach: string,
    alias: string,
    location?: string
  ): void
  detach(mainDbName: string, alias: string): void
  execute(
    dbName: string,
    query: string,
    params?: SQLiteValue[]
  ): NativeQueryResult
  executeAsync(
    dbName: string,
    query: string,
    params?: SQLiteValue[]
  ): Promise<NativeQueryResult>
  executeBatch(dbName: string, commands: BatchQueryCommand[]): BatchQueryResult
  executeBatchAsync(
    dbName: string,
    commands: BatchQueryCommand[]
  ): Promise<BatchQueryResult>
  loadFile(dbName: string, location: string): FileLoadResult
  loadFileAsync(dbName: string, location: string): Promise<FileLoadResult>
}
