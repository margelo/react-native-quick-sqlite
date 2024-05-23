#ifdef RCT_NEW_ARCH_ENABLED

#include "RNQuickSQLiteTurboModule.h"

namespace facebook::react
{
    RNQuickSQliteModule::RNQuickSQliteModule(std::shared_ptr<CallInvoker> jsInvoker)
        : NativeRNQuickSQLiteCxxSpec(std::move(jsInvoker)) {}

    jsi::Object RNQuickSQliteModule::open(jsi::Runtime &runtime)
    {
    }

} // namespace facebook::react

#endif
