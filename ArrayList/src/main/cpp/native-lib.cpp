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
