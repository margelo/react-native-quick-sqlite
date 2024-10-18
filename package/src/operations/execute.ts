import { HybridQuickSQLite } from '../nitro'
import type { NativeQueryResult } from '../specs/NativeQueryResult.nitro'
import type { QueryResult, SQLiteItem, SQLiteQueryParams } from '../types'

export function execute<Data extends SQLiteItem = never>(
  dbName: string,
  query: string,
  params?: SQLiteQueryParams
): QueryResult<Data> {
  const nativeResult = HybridQuickSQLite.execute(dbName, query, params)
  const result = buildJsQueryResult<Data>(nativeResult)
  return result
}

export async function executeAsync<Data extends SQLiteItem = never>(
  dbName: string,
  query: string,
  params?: SQLiteQueryParams
): Promise<QueryResult<Data>> {
  const nativeResult = await HybridQuickSQLite.executeAsync(
    dbName,
    query,
    params
  )
  const result = buildJsQueryResult<Data>(nativeResult)
  return result
}

function buildJsQueryResult<Data extends SQLiteItem = never>({
  insertId,
  rowsAffected,
  results,
}: NativeQueryResult): QueryResult<Data> {
  const data = results as Data[]

  return {
    insertId,
    rowsAffected,
    rows: {
      _array: data,
      length: data.length,
      item: (idx: number) => data[idx],
    },
  }
}
