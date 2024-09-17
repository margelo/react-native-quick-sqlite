package com.margelo.rnquicksqlite;

import androidx.annotation.Nullable;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.module.model.ReactModuleInfoProvider;
import com.facebook.react.TurboReactPackage;

import java.util.HashMap;

public class RNQuickSQLitePackage extends TurboReactPackage {
  static {
    System.loadLibrary("RNQuickSQLite");
  }

  @Nullable
  @Override
  public NativeModule getModule(String name, ReactApplicationContext reactContext) {
    return null;
  }

  public RNQuickSQLitePackage() {
  }

  @Override
  public ReactModuleInfoProvider getReactModuleInfoProvider() {
    return () -> {
      return new HashMap<>();
    };
  }
}
