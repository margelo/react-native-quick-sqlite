import {Buffer as CraftzdogBuffer} from '@craftzdog/react-native-buffer';

declare global {
  // eslint-disable-next-line no-var
  var Buffer: typeof CraftzdogBuffer;
  // eslint-disable-next-line no-var
  var process: {
    cwd: () => string;
    env: {NODE_ENV: string};
  };
}

globalThis.Buffer = CraftzdogBuffer;
globalThis.process.cwd = () => 'sxsx';
globalThis.process.env = {NODE_ENV: 'production'};
