import React, {useEffect, useState} from 'react';
import {ScrollView, Text} from 'react-native';
import {runTests} from '../tests/MochaSetup';
import {registerUnitTests} from '../tests/unitTests.spec';
import {ScreenStyles} from '../styles';

export const UnitTestScreen: React.FC = () => {
  const [results, setResults] = useState<any>([]);

  useEffect(() => {
    setResults([]);
    runTests(
      registerUnitTests,
      // registerTypeORMTests
    ).then(setResults);
  }, []);

  return (
    <ScrollView
      contentContainerStyle={[
        ScreenStyles.container,
        {alignItems: 'flex-start'},
      ]}>
      {results.map((r: any, i: number) => {
        if (r.type === 'grouping') {
          return (
            <Text key={i} className="mt-3 font-bold">
              {r.description}
            </Text>
          );
        }

        if (r.type === 'incorrect') {
          return (
            <Text key={i} className="mt-1">
              🔴 {r.description}: {r.errorMsg}
            </Text>
          );
        }

        return (
          <Text key={i} className="mt-1">
            🟢 {r.description}
          </Text>
        );
      })}
    </ScrollView>
  );
};
