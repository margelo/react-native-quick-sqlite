module.exports = {
  root: true,
  extends: [
    '@react-native',
    'plugin:@typescript-eslint/recommended-type-checked',
    'plugin:@typescript-eslint/stylistic-type-checked',
    'plugin:prettier/recommended',
  ],
  plugins: ['@typescript-eslint', 'prettier'],
  parser: '@typescript-eslint/parser',
  parserOptions: {
    tsconfigRootDir: __dirname,
    project: ['./tsconfig.json'],
    ecmaFeatures: {
      jsx: true,
    },
    ecmaVersion: 2018,
    sourceType: 'module',
  },
  ignorePatterns: ['node_modules/', 'lib/'],
  rules: {
    'prettier/prettier': [
      'warn',
      {
        quoteProps: 'consistent',
        singleQuote: true,
        tabWidth: 2,
        trailingComma: 'es5',
        useTabs: false,
      },
    ],
    // eslint
    'semi': 'off',
    'curly': ['warn', 'multi-or-nest', 'consistent'],
    'no-mixed-spaces-and-tabs': ['warn', 'smart-tabs'],
    'no-async-promise-executor': 'warn',
    'require-await': 'warn',
    'no-return-await': 'warn',
    'no-await-in-loop': 'warn',
    'comma-dangle': 'off', // prettier already detects this
    'no-restricted-syntax': [
      'error',
      {
        selector: 'TSEnumDeclaration',
        message:
          "Enums have various disadvantages, use TypeScript's union types instead.",
      },
    ],
    // prettier
    'prettier/prettier': ['warn'],
    // typescript
    '@typescript-eslint/no-use-before-define': 'off',
    '@typescript-eslint/no-unused-vars': [
      'error',
      {
        vars: 'all',
        args: 'after-used',
        ignoreRestSiblings: false,
        varsIgnorePattern: '^_',
        argsIgnorePattern: '^_',
      },
    ],
    '@typescript-eslint/no-namespace': 'off',
    '@typescript-eslint/ban-ts-comment': 'off',
    '@typescript-eslint/no-unsafe-assignment': 'error',
    '@typescript-eslint/no-floating-promises': 'off',
    // react plugin
    'react/no-unescaped-entities': 'off',
    // react native plugin
    'react-native/no-unused-styles': 'warn',
    'react-native/split-platform-components': 'off',
    'react-native/no-inline-styles': 'warn',
    'react-native/no-color-literals': 'off',
    'react-native/no-raw-text': 'off',
    'react-native/no-single-element-style-arrays': 'warn',
    '@typescript-eslint/strict-boolean-expressions': [
      'error',
      {
        allowString: false,
        allowNullableObject: false,
        allowNumber: false,
        allowNullableBoolean: true,
      },
    ],
    '@typescript-eslint/no-non-null-assertion': 'error',
    '@typescript-eslint/no-unnecessary-condition': 'error',
    '@typescript-eslint/consistent-type-imports': 'warn',

    // react hooks
    'react-hooks/exhaustive-deps': [
      'error',
      {
        additionalHooks:
          '(useDerivedValue|useAnimatedStyle|useAnimatedProps|useWorkletCallback|useFrameProcessor|useSkiaFrameProcessor)',
      },
    ],
  },
}