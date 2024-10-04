package com.margelo.rnnitrosqlite;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.module.model.ReactModuleInfo;
import com.facebook.react.module.model.ReactModuleInfoProvider;
import com.facebook.react.TurboReactPackage;

import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class RNNitroSQLitePackage extends TurboReactPackage {
  static {
    System.loadLibrary("RNNitroSQLite");
  }

  @Nullable
  @Override
  public NativeModule getModule(String name, ReactApplicationContext reactContext) {
    if (name.equals(RNNitroSQLiteOnLoadModule.NAME)) {
      return new RNNitroSQLiteOnLoadModule(reactContext);
    } else {
      return null;
    }
  }

  @Override
  public ReactModuleInfoProvider getReactModuleInfoProvider() {
    return () -> {
      final Map<String, ReactModuleInfo> moduleInfos = new HashMap<>();
      moduleInfos.put(
          RNNitroSQLiteOnLoadModule.NAME,
          new ReactModuleInfo(
              RNNitroSQLiteOnLoadModule.NAME,
              RNNitroSQLiteOnLoadModule.NAME,
              false,
              true,
              true,
              false,
              true));
      return moduleInfos;
    };
  }
}
