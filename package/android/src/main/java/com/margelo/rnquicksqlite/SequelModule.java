package com.margelo.rnquicksqlite;

import androidx.annotation.NonNull;
import android.util.Log;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;

class SequelModule extends ReactContextBaseJavaModule {
  public static final String NAME = "QuickSQLite";

  public SequelModule(ReactApplicationContext context) {
    super(context);
  }

  @NonNull
  @Override
  public String getName() {
    return NAME;
  }

  @ReactMethod(isBlockingSynchronousMethod = true)
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

  @Override
  public void onCatalystInstanceDestroy() {
    try {
      QuickSQLiteBridge.instance.clearState();
    } catch (Exception exception) {
      Log.e(NAME, "Failed to clear state!", exception);
    }
  }
}
