#ifdef RCT_NEW_ARCH_ENABLED
#import <RNQuickSQLite/RNQuickSQLite.h>

NS_ASSUME_NONNULL_BEGIN

@interface RNQuickSQLite : NSObject<NativeRNQuickSQLiteSpec>
#else
#import <React/RCTBridge.h>

@interface RNQuickSQLite : NSObject<RCTBridgeModule>
#endif

@property(nonatomic, assign) BOOL setBridgeOnMainQueue;

@end

#ifdef RCT_NEW_ARCH_ENABLED
NS_ASSUME_NONNULL_END
#endif
