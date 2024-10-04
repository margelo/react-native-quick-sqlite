#import "QuickSQLite.h"

#import <React/RCTBridge+Private.h>

#import <React/RCTUtils.h>
#import <ReactCommon/RCTTurboModule.h>
#import <jsi/jsi.h>

#import "../cpp/bindings.h"

@implementation QuickSQLite

RCT_EXPORT_MODULE(QuickSQLite)

@synthesize bridge = _bridge;

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(install) {
  NSLog(@"Installing QuickSQLite module...");

  RCTCxxBridge *cxxBridge = (RCTCxxBridge *)self.bridge;
  if (cxxBridge == nil) {
    return @false;
  }

  using namespace facebook;

  auto jsiRuntime = (jsi::Runtime *)cxxBridge.runtime;
  if (jsiRuntime == nil) {
    return @false;
  }
  auto &runtime = *jsiRuntime;
  auto callInvoker = cxxBridge.jsCallInvoker;

  // Get appGroupID value from Info.plist using key "AppGroup"
  NSString *appGroupID = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"ReactNativeQuickSQLite_AppGroup"];
  NSString *documentPath;

  if (appGroupID != nil) {
    // Get the app groups container storage url
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSURL *storeUrl = [fileManager containerURLForSecurityApplicationGroupIdentifier:appGroupID];

    if (storeUrl == nil) {
      NSLog(@"Invalid AppGroup ID provided (%@). Check the value of \"AppGroup\" in your Info.plist file", appGroupID);
      return @false;
    }
    NSLog(@"Configured with AppGroup ID: %@", appGroupID);

    documentPath = [storeUrl path];
  } else {
    // Get iOS app's document directory (to safely store database .sqlite3 file)
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, true);
    documentPath = [paths objectAtIndex:0];
  }

  osp::install(runtime, callInvoker, [documentPath UTF8String]);
  return @true;
}

- (void)invalidate {
  osp::clearState();
}


@end
