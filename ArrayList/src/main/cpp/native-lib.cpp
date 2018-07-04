//
// Created by 花歹 on 2018/7/2.
//
#include <jni.h>
#include "Arrayist.hpp"
#include <android/log.h>
#include <syslog.h>
#include <string>

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_demo_jni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {


    ArrayList<int> *list = new ArrayList<int>(4);

    for (int i = 0; i < 100; ++i) {
        list->add(i);
    }

    for (int i = 0; i < list->size(); ++i) {

        __android_log_print(LOG_ERR, "TAG", "i = %d", list->get(i));
    }

    delete (list);

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT void JNICALL
Java_com_demo_jni_arraylist_MainActivity_arraycopy(JNIEnv *env, jclass type, jobject src,
                                                   jint srcPos, jobject dest, jint destPos,
                                                   jint length) {

    // TODO
    //判断是不是数组
    //做一系列准备工作，如果有异常，程序会崩掉。
    //buggly so库报错，如果有抛java层异常，是可以try catch,但是很多情况下并不会抛java层的异常，
    // 如果没抛java层异常，try catch 无效。

    //src dest 都是java数组，需要转换
    jobjectArray src_array = reinterpret_cast<jobjectArray>(src);
    jobjectArray dest_array = reinterpret_cast<jobjectArray>(src);
    if (src_array != NULL && dest_array != NULL) {
        __android_log_print(ANDROID_LOG_ERROR, "TAG", "转换成功");

        for (int i = srcPos; i < srcPos + length; ++i) {
            jobject obj = env->GetObjectArrayElement(src_array, i);
            //放到新的数组里面
            env->SetObjectArrayElement(dest_array, i, obj);
        }


    }

}