package com.margelo.rnquicksqlite;

import android.util.Log;

import androidx.annotation.NonNull;
import com.facebook.react.bridge.ReactApplicationContext;

public class RNQuickSQLiteInitModule extends NativeQuickSQLiteInitSpec {
  public RNQuickSQLiteInitModule(ReactApplicationContext reactContext) {
    super(reactContext);
  }

  @Override
  @NonNull
  public String getName() {
    return NAME;
  }

  @Override
  public boolean install() {
    try {
      System.loadLibrary("RNQuickSQLite");
      QuickSQLiteBridge.instance.install(getReactApplicationContext());
      return true;
    } catch (Exception exception) {
      Log.e(NAME, "Failed to install JSI Bindings!", exception);
      return false;
    }
  }
}
