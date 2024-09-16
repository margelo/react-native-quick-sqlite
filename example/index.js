import {AppRegistry} from 'react-native';
import App from './src/App';
import {name as appName} from './app.json';

global.process.env = {NODE_ENV: 'production'};

AppRegistry.registerComponent(appName, () => App);
