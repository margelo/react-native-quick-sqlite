#pragma once

#ifdef RCT_NEW_ARCH_ENABLED

#include <memory>
#include <string>

#include "RNQuickSQliteSpecJSI.h"

namespace facebook::react
{
    class RNQuickSQliteModule : public NativeRNQuickSQLiteCxxSpec<RNQuickSQliteModule>
    {
    public:
        RNQuickSQliteModule(std::shared_ptr<CallInvoker> jsInvoker);

        jsi::Object open(jsi::Runtime &runtime);
    };

} // namespace facebook::react

#endif
