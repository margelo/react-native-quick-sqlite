#pragma

#include <string>
#include <iostream>
#include <exception>

enum QuickSQLiteExceptionType {
  UnknownError,
  DatabaseCannotBeOpened,
  DatabaseNotOpen,
  UnableToAttachToDatabase,
  SqlExecutionError,
  CouldNotLoadFile,
  NoBatchCommandsProvided
};

std::unordered_map<QuickSQLiteExceptionType, std::string> exceptionTypeStrings = {
  {UnknownError, "UnknownError"},
  {DatabaseCannotBeOpened, "DatabaseCannotBeOpened"},
  {DatabaseNotOpen, "DatabaseNotOpen"},
  {UnableToAttachToDatabase, "UnableToAttachToDatabase"},
  {SqlExecutionError, "SqlExecutionError"},
  {CouldNotLoadFile, "CouldNotLoadFile"},
  {NoBatchCommandsProvided, "NoBatchCommandsProvided"}
};

std::string typeToString(QuickSQLiteExceptionType type) {
  return exceptionTypeStrings[type];
}

class QuickSQLiteException : public std::exception {
public:
  QuickSQLiteException(const char* message): QuickSQLiteException(QuickSQLiteExceptionType::UnknownError, message) {}
  QuickSQLiteException(std::string message): QuickSQLiteException(QuickSQLiteExceptionType::UnknownError, message) {}
  QuickSQLiteException(const QuickSQLiteExceptionType type, const char* message) : QuickSQLiteException(type, message) {}
  QuickSQLiteException(const QuickSQLiteExceptionType type, std::string message)
    : _exceptionString("[react-native-quick-sqlite] " + typeToString(type) + ": " + message) {}
  
private:
  const std::string _exceptionString;
  
public:
  const char* what() const noexcept override {
    return this->_exceptionString.c_str();
  }
  
  static QuickSQLiteException DatabaseNotOpen(std::string dbName) {
    return QuickSQLiteException(QuickSQLiteExceptionType::UnableToAttachToDatabase, dbName + " is not open");
  }
  
  static QuickSQLiteException SqlExecution(std::string errorMessage) {
    return QuickSQLiteException(QuickSQLiteExceptionType::SqlExecutionError, errorMessage);
  }
  
  static QuickSQLiteException DatabaseFileNotFound(std::string dbFilePath) {
    return QuickSQLiteException(QuickSQLiteExceptionType::SqlExecutionError, "Database file not found: " + dbFilePath);
  }
  
  static QuickSQLiteException CouldNotLoadFile(std::string fileLocation, std::optional<std::string> additionalLine = std::nullopt) {
    const auto message = "Could not load file: " + fileLocation + (additionalLine ? (". " + *additionalLine) : "");
    return QuickSQLiteException(QuickSQLiteExceptionType::CouldNotLoadFile, message);
  }
};
