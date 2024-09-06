//
//  JSIHelper.hpp
//  react-native-quick-sqlite
//
//  Created by Oscar on 13.03.22.
//

#ifndef JSIHelper_h
#define JSIHelper_h

#include <stdio.h>
#include <jsi/jsilib.h>
#include <jsi/jsi.h>
#include <vector>
#include <map>

using namespace facebook;

/**
 * Various structs to help with the results of the SQLite operations
 */
enum ResultType
{
  SQLiteOk,
  SQLiteError
};

struct SQLiteOPResult
{
  ResultType type;
  std::string errorMessage;
  int rowsAffected;
  double insertId;
};

struct SequelLiteralUpdateResult
{
  ResultType type;
    std::string message;
  int affectedRows;
};

struct SequelBatchOperationResult
{
  ResultType type;
    std::string message;
  int affectedRows;
  int commands;
};

#endif /* JSIHelper_h */
