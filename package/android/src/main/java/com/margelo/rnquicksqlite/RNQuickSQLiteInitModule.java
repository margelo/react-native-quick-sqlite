package com.margelo.rnquicksqlite;

import android.util.Log;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;

public class RNQuickSQLiteInitModule extends NativeRNQuickSQLiteInitSpec {
  public RNQuickSQLiteInitModule(ReactApplicationContext reactContext) {
    super(reactContext);
  }

  @Override
  @NonNull
  public String getName() {
    return NAME;
  }

  @Override
  public void install(Promise promise) {
    try {
      QuickSQLiteBridge.instance.install(getReactApplicationContext());
      promise.resolve(true);
    } catch (Exception exception) {
      Log.e(NAME, "Failed to install JSI Bindings!", exception);
      promise.resolve(false);
    }
  }
}
