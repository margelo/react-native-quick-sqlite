#import <React/RCTBridgeModule.h>
#import <React/RCTInvalidating.h>

@interface QuickSQLite : NSObject <RCTBridgeModule, RCTInvalidating>

@property(nonatomic, assign) BOOL setBridgeOnMainQueue;

@end
