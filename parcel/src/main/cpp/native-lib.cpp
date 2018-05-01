#include <jni.h>
#include <stdlib.h>
#include <string>
#include "Parcel.h"

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_demo_jni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

//结构体和对象Parcel.cpp
class Parcel {
    char *mData;

    int mDataPos;

public:

    Parcel() {
        mData = (char *) malloc(1024);
        mDataPos = 0;
    }

    void writeInt(jint value) {
        *reinterpret_cast<int *>(mData + mDataPos) = value;
        mDataPos += sizeof(int);
    }

    void setDataPosition(jint position) {
        mDataPos = position;

    }

    jint readInt() {
        int result = *reinterpret_cast<int *>(mData + mDataPos);
        mDataPos += sizeof(int);
        return result;
    }
};


JNIEXPORT jlong JNICALL Java_jni_demo_com_parcel_nativeCreate
        (JNIEnv *, jobject) {
    Parcel *parcel = new Parcel();
    return (jlong) parcel;

}

JNIEXPORT void JNICALL Java_jni_demo_com_parcel_nativeWriteInt
        (JNIEnv *, jobject, jlong nativePtr, jint value) {

    Parcel *parcel = reinterpret_cast<Parcel *>(nativePtr);
    parcel->writeInt(value);
}


JNIEXPORT jint JNICALL Java_jni_demo_com_parcel_nativeReadInt
        (JNIEnv *, jobject, jlong nativePtr) {
    Parcel *parcel = reinterpret_cast<Parcel *>(nativePtr);
    return parcel->readInt();
}

JNIEXPORT void JNICALL Java_jni_demo_com_parcel_nativeSetDataPosition
        (JNIEnv *, jobject, jlong nativePtr, jint value) {
    Parcel *parcel = (Parcel *) nativePtr;
    parcel->setDataPosition(value);
}
