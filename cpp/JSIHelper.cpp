#include "JSIHelper.h"

// void jsiQueryArgumentsToSequelParam(jsi::Runtime &rt, jsi::Value const &params, vector<QuickValue> *target)
// {
//  if (params.isNull() || params.isUndefined())
//  {
//    return;
//  }

//  jsi::Array values = params.asObject(rt).asArray(rt);

//  for (int ii = 0; ii < values.length(rt); ii++)
//  {

//    jsi::Value value = values.getValueAtIndex(rt, ii);
//    if (value.isNull() || value.isUndefined())
//    {
//      target->push_back(createNullQuickValue());
//    }
//    else if (value.isBool())
//    {
//      target->push_back(createBooleanQuickValue(value.getBool()));
//    }
//    else if (value.isNumber())
//    {
//      double doubleVal = value.asNumber();
//      int intVal = (int)doubleVal;
//      long long longVal = (long)doubleVal;
//      if (intVal == doubleVal)
//      {
//        target->push_back(createIntegerQuickValue(intVal));
//      }
//      else if (longVal == doubleVal)
//      {
//        target->push_back(createInt64QuickValue(longVal));
//      }
//      else
//      {
//        target->push_back(createDoubleQuickValue(doubleVal));
//      }
//    }
//    else if (value.isString())
//    {
//      string strVal = value.asString(rt).utf8(rt);
//      target->push_back(createTextQuickValue(strVal));
//    }
//    else if (value.isObject())
//    {
//      auto obj = value.asObject(rt);
//      if (obj.isArrayBuffer(rt))
//      {
//        auto buf = obj.getArrayBuffer(rt);
//        target->push_back(createArrayBufferQuickValue(buf.data(rt), buf.size(rt)));
//      }
//    }
//    else
//    {
//      target->push_back(createNullQuickValue());
//    }
//  }
// }
