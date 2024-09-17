#include <fbjni/fbjni.h>
#include <jni.h>
#include <jsi/jsi.h>
#include <typeinfo>
#include "HybridQuickSQLite.hpp"
#include "RNQuickSQLiteOnLoad.hpp"

using namespace margelo::nitro::rnquicksqlite;

extern "C"
JNIEXPORT void JNICALL
Java_com_margelo_rnquicksqlite_RNQuickSQLiteModule_setDocPath__Ljava_lang_String_2(JNIEnv *env,
                                                                                   jobject thiz,
                                                                                   jstring doc_path) {
    const char *nativeString = env->GetStringUTFChars(doc_path, nullptr);
    HybridQuickSQLite::docPath = std::string(nativeString);
    env->ReleaseStringUTFChars(doc_path, nativeString);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void*) {
    return margelo::nitro::rnquicksqlite::initialize(vm);
}

