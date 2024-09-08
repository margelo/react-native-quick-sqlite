import { HybridObject } from 'react-native-nitro-modules'
import {
  QueryResult,
  BatchQueryResult,
  FileLoadResult,
  BatchQueryCommand,
  Transaction,
  ExecuteParam,
} from '../types'

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
  transaction(
    dbName: string,
    fn: (tx: Transaction) => Promise<void> | void
  ): Promise<void>
  execute(dbName: string, query: string, params?: ExecuteParam[]): QueryResult
  executeAsync(
    dbName: string,
    query: string,
    params?: ExecuteParam[]
  ): Promise<QueryResult>
  executeBatch(dbName: string, commands: BatchQueryCommand[]): BatchQueryResult
  executeBatchAsync(
    dbName: string,
    commands: BatchQueryCommand[]
  ): Promise<BatchQueryResult>
  loadFile(dbName: string, location: string): FileLoadResult
  loadFileAsync(dbName: string, location: string): Promise<FileLoadResult>
}
