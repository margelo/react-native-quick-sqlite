package com.margelo.rnquicksqlite;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.Callback;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import java.util.Map;
import java.util.HashMap;
import com.margelo.rnquicksqlite.NativeQuickSQLiteOnLoadSpec;

public class RNQuickSQLiteOnLoadModule extends NativeQuickSQLiteOnLoadSpec {
  private static ReactApplicationContext _reactContext;
  private Callback reactApplicationContextReadyCallback;

  public RNQuickSQLiteOnLoadModule(ReactApplicationContext reactContext) {
    super(reactContext);

    _reactContext = reactContext;
    setDocPath(reactContext);

    if (reactApplicationContextReadyCallback != null) {
      reactApplicationContextReadyCallback.invoke();
    }
  }

  public static void setDocPath(ReactApplicationContext context) {
    final String path = context.getFilesDir().getAbsolutePath();
    setDocPathInJNI(path);
  }

  @Override
  @NonNull
  public String getName() {
    return NAME;
  }

  @Override
  public void onReactApplicationContextReady(Callback callback) {
    if (_reactContext != null) {
      callback.invoke();
      return;
    }

    reactApplicationContextReadyCallback = callback;
  }

  public static ReactApplicationContext getReactContext() {
    return _reactContext;
  }

  private native static void setDocPathInJNI(String docPath);
}
