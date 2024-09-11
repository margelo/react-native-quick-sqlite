//   _________     _______  ______ ____  _____  __  __            _____ _____
//  |__   __\ \   / /  __ \|  ____/ __ \|  __ \|  \/  |     /\   |  __ \_   _|
//     | |   \ \_/ /| |__) | |__ | |  | | |__) | \  / |    /  \  | |__) || |
//     | |    \   / |  ___/|  __|| |  | |  _  /| |\/| |   / /\ \ |  ___/ | |
//     | |     | |  | |    | |___| |__| | | \ \| |  | |  / ____ \| |    _| |_
//     |_|     |_|  |_|    |______\____/|_|  \_\_|  |_| /_/    \_\_|   |_____|

import { transaction } from './transaction'
import { QuickSQLite } from './init'
import { QueryResult, SQLiteItem, SQLiteValue, Transaction } from './types'

// Enhance some host functions

// Add 'item' function to result object to allow the sqlite-storage typeorm driver to work
const enhanceQueryResult = <Data extends SQLiteItem = never>(
  result: QueryResult<Data>
): void => {
  // Add 'item' function to result object to allow the sqlite-storage typeorm driver to work
  // if (result.rows == null) {
  //   result.rows = {
  //     _array: [],
  //     length: 0,
  //     item: (idx: number) => result.rows._array[idx],
  //   };
  // } else {
  //   result.rows.item = (idx: number) => result.rows._array[idx];
  // }
}

/**
 * DO NOT USE THIS! THIS IS MEANT FOR TYPEORM
 * If you are looking for a convenience wrapper use `connect`
 */
export const typeORMDriver = {
  openDatabase: (
    options: {
      name: string
      location?: string
    },
    ok: (db: any) => void,
    fail: (msg: string) => void
  ): any => {
    try {
      QuickSQLite.open(options.name, options.location)

      const connection = {
        executeSql: async <Data extends SQLiteItem = never>(
          sql: string,
          params: SQLiteValue[] | undefined,
          ok: (res: QueryResult<Data>) => void,
          fail: (msg: string) => void
        ) => {
          try {
            let response = await QuickSQLite.executeAsync(
              options.name,
              sql,
              params
            )
            enhanceQueryResult(response)
            ok(response)
          } catch (e) {
            fail(e)
          }
        },
        transaction: (
          fn: (tx: Transaction) => Promise<void>
        ): Promise<void> => {
          return transaction(options.name, fn)
        },
        close: (ok: any, fail: any) => {
          try {
            QuickSQLite.close(options.name)
            ok()
          } catch (e) {
            fail(e)
          }
        },
        attach: (
          dbNameToAttach: string,
          alias: string,
          location: string | undefined,
          callback: () => void
        ) => {
          QuickSQLite.attach(options.name, dbNameToAttach, alias, location)

          callback()
        },
        detach: (alias, callback: () => void) => {
          QuickSQLite.detach(options.name, alias)

          callback()
        },
      }

      ok(connection)

      return connection
    } catch (e) {
      fail(e)
    }
  },
}
