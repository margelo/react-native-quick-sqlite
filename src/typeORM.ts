//   _________     _______  ______ ____  _____  __  __            _____ _____
//  |__   __\ \   / /  __ \|  ____/ __ \|  __ \|  \/  |     /\   |  __ \_   _|
//     | |   \ \_/ /| |__) | |__ | |  | | |__) | \  / |    /  \  | |__) || |
//     | |    \   / |  ___/|  __|| |  | |  _  /| |\/| |   / /\ \ |  ___/ | |
//     | |     | |  | |    | |___| |__| | | \ \| |  | |  / ____ \| |    _| |_
//     |_|     |_|  |_|    |______\____/|_|  \_\_|  |_| /_/    \_\_|   |_____|

import {
  QueryResult,
  SQLiteItem,
  SQLiteQueryParams,
  Transaction,
} from './types'
import { open } from 'react-native-quick-sqlite'

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
      const db = open(options)

      const connection = {
        executeSql: async <RowData extends SQLiteItem = never>(
          sql: string,
          params: SQLiteQueryParams | undefined,
          okExecute: (res: QueryResult<RowData>) => void,
          failExecute: (msg: string) => void
        ) => {
          try {
            const result = await db.executeAsync<RowData>(sql, params)
            okExecute(result)
          } catch (e) {
            failExecute(e)
          }
        },
        transaction: (
          fn: (tx: Transaction) => Promise<void>
        ): Promise<void> => {
          return db.transaction(fn)
        },
        close: (okClose: any, failClose: any) => {
          try {
            db.close()
            okClose()
          } catch (e) {
            failClose(e)
          }
        },
        attach: (
          dbNameToAttach: string,
          alias: string,
          location: string | undefined,
          callback: () => void
        ) => {
          db.attach(dbNameToAttach, alias, location)
          callback()
        },
        detach: (alias, callback: () => void) => {
          db.detach(alias)
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
