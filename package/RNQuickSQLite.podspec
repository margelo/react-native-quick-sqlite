require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

# TODO: Should be customizable in package.json.
# Used to create comparable benchmark results
performance_mode = 1

Pod::Spec.new do |s|
  s.name         = "RNQuickSQLite"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.homepage     = package["homepage"]
  s.license      = package["license"]
  s.authors      = package["author"]

  s.platforms    = { :ios => min_ios_version_supported, :visionos => "1.0" }
  s.source       = { :git => "https://github.com/margelo/react-native-quick-sqlite.git", :tag => "#{s.version}" }

  s.pod_target_xcconfig = {
    :GCC_PREPROCESSOR_DEFINITIONS => "HAVE_FULLFSYNC=1",
    :WARNING_CFLAGS => "-Wno-shorten-64-to-32 -Wno-comma -Wno-unreachable-code -Wno-conditional-uninitialized -Wno-deprecated-declarations",
    :USE_HEADERMAP => "No",
    'CLANG_CXX_LANGUAGE_STANDARD' => 'c++20',
    'CLANG_CXX_LIBRARY' => 'libc++'
  }

  # s.header_mappings_dir = "cpp"
  s.source_files = "ios/**/*.{h,hpp,m,mm}", "cpp/**/*.{h,hpp,c,cpp}"

  load 'nitrogen/generated/ios/RNQuickSQLite+autolinking.rb'
  add_nitrogen_files(s)

  if defined?(install_modules_dependencies())
    install_modules_dependencies(s)
  else
    s.dependency "React-callinvoker"
    s.dependency "React"
    s.dependency "React-Core"
  end

  optimizedCflags = '$(inherited) -DSQLITE_DQS=0 -DSQLITE_DEFAULT_MEMSTATUS=0 -DSQLITE_DEFAULT_WAL_SYNCHRONOUS=1 -DSQLITE_LIKE_DOESNT_MATCH_BLOBS=1 -DSQLITE_MAX_EXPR_DEPTH=0 -DSQLITE_OMIT_DEPRECATED=1 -DSQLITE_OMIT_PROGRESS_CALLBACK=1 -DSQLITE_OMIT_SHARED_CACHE=1 -DSQLITE_USE_ALLOCA=1'

  if performance_mode == '1' then
    log_message.call("Thread unsafe (1) performance mode enabled. Use only transactions! 🚀🚀")
    xcconfig[:OTHER_CFLAGS] = optimizedCflags + ' -DSQLITE_THREADSAFE=0 '
  end

  if performance_mode == '2' then
    log_message.call("Thread safe (2) performance mode enabled 🚀")
    xcconfig[:OTHER_CFLAGS] = optimizedCflags + ' -DSQLITE_THREADSAFE=1 '
  end

  if ENV['QUICK_SQLITE_USE_PHONE_VERSION'] == '1' then
    s.exclude_files = "cpp/sqlite3.c", "cpp/sqlite3.h"
    s.library = "sqlite3"
  end

end
