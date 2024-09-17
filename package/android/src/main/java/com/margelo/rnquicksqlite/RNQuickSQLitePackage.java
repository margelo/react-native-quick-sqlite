package com.margelo.rnquicksqlite;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.module.model.ReactModuleInfoProvider;
import com.facebook.react.TurboReactPackage;
import com.margelo.nitro.NitroModulesPackage;

import java.util.Collections;
import java.util.HashMap;
import java.util.List;

public class RNQuickSQLitePackage extends TurboReactPackage {
  static {
    System.loadLibrary("RNQuickSQLite");
  }

  private native static void setDocPathInJNI(String docPath);

  public static void setDocPath(ReactApplicationContext context) {
    final String path =  context.getFilesDir().getAbsolutePath();
    setDocPathInJNI(path);
  }

  @Nullable
  @Override
  public NativeModule getModule(String name, ReactApplicationContext reactContext) {return null;}

  public RNQuickSQLitePackage() {
    ReactApplicationContext context = NitroModulesPackage.getReactContext();
    setDocPath(context);
  }

  @Override
  public ReactModuleInfoProvider getReactModuleInfoProvider() {
    return () -> {
      return new HashMap<>();
    };
  }
}
