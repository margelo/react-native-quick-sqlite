import { sqlite3Worker1Promiser } from '@sqlite.org/sqlite-wasm';
import {
  ISQLite,
  PendingTransaction,
  QueryResult,
  QuickSQLiteConnection,
  SQLBatchTuple,
  Transaction,
} from 'src/types';

// import init from '@sqlite.org/sqlite-wasm';

// // init().then((sqlite3) => {
// //   console.log({ sqlite3 });
// // });

const log = (...args) => console.log(...args);
const error = (...args) => console.error(...args);

type PromiserMethods = {
  'open': {
    args: {
      filename: string
    }
    response: {
      dbId: string
    }
  }
  'close': {
    args: {
      dbId: string
    }
    response: {}
  }
  'exec': {
    dbId: string
  }
  'config-get' : {
    args: {}
    response: {
      result: {
        version: {
          libVersion}}
    }
  }
}

type PromiserMethodName = keyof PromiserMethods;
let promiser: <Method extends PromiserMethodName>(operation: Method, args: PromiserMethods[Method]['args']) => Promise<PromiserMethods[Method]['response']>;

(async () => {
  try {
    log('Loading and initializing SQLite3 module...');

    promiser = await new Promise((resolve) => {
      const _promiser = sqlite3Worker1Promiser({
        onready: () => {
          resolve(_promiser);
        },
      });
    });

    log('Done initializing. Running demo...');

    let response;

    response = await promiser('config-get', {});
    log('Running SQLite3 version', response.result.version.libVersion);
  } catch (err) {
    if (!(err instanceof Error)) {
      err = new Error(err.result.message);
    }
    error(err.name, err.message);
  }
})();



export const openAsync = async (options: {
  name: string;
  location?: string;
}): Promise<QuickSQLiteConnection => {
  const response = await promiser('open', {
    filename: `file:${name}.sqlite3?vfs=opfs`,
  });

  response

  const { dbId } = response;
  log(
    'OPFS is available, created persisted database at',
    response.result.filename.replace(/^file:(.*?)\?vfs=opfs$/, '$1')
  );

  const close = () => promiser('close', { dbId });

  return {
    close,
    delete: () => QuickSQLite.delete(options.name, options.location),
    attach: (dbNameToAttach: string, alias: string, location?: string) =>
      QuickSQLite.attach(options.name, dbNameToAttach, alias, location),
    detach: (alias: string) => QuickSQLite.detach(options.name, alias),
    transaction: (fn: (tx: Transaction) => Promise<void> | void) =>
      QuickSQLite.transaction(options.name, fn),
    execute: (query: string, params?: any[] | undefined): QueryResult =>
      QuickSQLite.execute(options.name, query, params),
    executeAsync: (
      query: string,
      params?: any[] | undefined
    ): Promise<QueryResult> =>
      QuickSQLite.executeAsync(options.name, query, params),
    executeBatch: (commands: SQLBatchTuple[]) =>
      QuickSQLite.executeBatch(options.name, commands),
    executeBatchAsync: (commands: SQLBatchTuple[]) =>
      QuickSQLite.executeBatchAsync(options.name, commands),
    loadFile: (location: string) =>
      QuickSQLite.loadFile(options.name, location),
    loadFileAsync: (location: string) =>
      QuickSQLite.loadFileAsync(options.name, location),
  };
};
