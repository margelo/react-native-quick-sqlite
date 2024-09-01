import { HybridObject } from 'react-native-nitro-modules';
import {
  BatchQueryResult,
  FileLoadResult,
  SQLBatchTuple,
  QueryResult,
  Transaction,
  ExecuteParams,
  QuickValue,
} from '../types';

export interface QuickSQLite
  extends HybridObject<{ ios: 'c++'; android: 'c++' }> {
  open(dbName: string, location?: string): void;
  close(dbName: string): void;
  delete(dbName: string, location?: string): void;
  attach(
    mainDbName: string,
    dbNameToAttach: string,
    alias: string,
    location?: string
  ): void;
  detach(mainDbName: string, alias: string): void;
  transaction(
    dbName: string,
    fn: (tx: Transaction) => Promise<void> | void
  ): Promise<void>;
  execute<RowData = QuickValue>(
    dbName: string,
    query: string,
    params?: ExecuteParams
  ): QueryResult;
  executeAsync<RowData = QuickValue>(
    dbName: string,
    query: string,
    params?: ExecuteParams
  ): Promise<QueryResult>;
  executeBatch(dbName: string, commands: SQLBatchTuple[]): BatchQueryResult;
  executeBatchAsync(
    dbName: string,
    commands: SQLBatchTuple[]
  ): Promise<BatchQueryResult>;
  loadFile(dbName: string, location: string): FileLoadResult;
  loadFileAsync(dbName: string, location: string): Promise<FileLoadResult>;
}
