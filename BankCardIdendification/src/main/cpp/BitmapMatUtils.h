//
// Created by 花歹 on 2018/8/1.
//

#ifndef JNIPROJECT_BITMAPMATUTILS_H
#define JNIPROJECT_BITMAPMATUTILS_H


#include <jni.h>
#include "opencv2/opencv.hpp"

using namespace cv;

class BitmapMatUtils {

public:
    // c/c++ 开发项目增强，返回值一般作为是否成功，返回结果一般为参数
    // java 中是把想要的结果返回
    static int mat2bitmap(JNIEnv *env, jobject bitmap, Mat &mat);

    static int bitmap2mat(JNIEnv *env, jobject bitmap, Mat &mat);
};


#endif //JNIPROJECT_BITMAPMATUTILS_H
