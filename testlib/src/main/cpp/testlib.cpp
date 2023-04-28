#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_testlib_NativeLib_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    jclass tracetest = env->FindClass("com/tool/jnitrace/TraceTest");

    jmethodID md1 = env->GetStaticMethodID(tracetest, "test4", "(Ljava/lang/String;)I");

    env->CallStaticIntMethod(tracetest,md1,env->NewStringUTF("666"));
    return env->NewStringUTF(hello.c_str());
}