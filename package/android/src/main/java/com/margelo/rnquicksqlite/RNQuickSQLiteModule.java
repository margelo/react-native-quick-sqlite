package com.margelo.rnquicksqlite;

import androidx.annotation.NonNull;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;

class RNQuickSQLiteModule extends ReactContextBaseJavaModule {
    public static final String NAME = "RNQuickSQLite";

    private native void setDocPath(String docPath);

    public RNQuickSQLiteModule(ReactApplicationContext context) {
        super(context);
        final String path =  context.getFilesDir().getAbsolutePath();
        setDocPath(path);
    }

    @NonNull
    @Override
    public String getName() {
        return NAME;
    }
}