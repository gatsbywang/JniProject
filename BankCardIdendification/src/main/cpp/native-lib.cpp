//
// Created by 花歹 on 2018/7/2.
//
#include <jni.h>
#include <android/log.h>
#include <syslog.h>
#include <string>
#include "BitmapMatUtils.h"
#include "cardocr.h"
#include <vector>


using namespace std;
extern "C"
JNIEXPORT jstring

JNICALL
Java_com_demo_jni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



extern "C"
JNIEXPORT jstring JNICALL
Java_com_demo_card_BankCardOcr_cardOcr(JNIEnv *env, jclass type, jobject bitmap) {

    // TODO
        //1、bitmap -> mat
    Mat mat;
    BitmapMatUtils::bitmap2mat(env,bitmap,mat);


    //轮廓增强
    Rect card_area;
    co1::find_card_area(mat,card_area);

    //对过滤到的银行卡区域进行裁剪
    Mat card_mat(mat,card_area);


    //截取卡号区域
    Rect card_number_area;
    co1::find_card_number_area(card_mat,card_number_area);
    Mat card_number_mat(card_mat,card_number_area);

    //获取数字
    vector<Mat> numbers;
    co1::find_card_numbers(card_number_mat, numbers);

    __android_log_print(ANDROID_LOG_ERROR, "TAG", "%d,%d,%d,%d", mat.cols, mat.rows, mat.type(),CV_8UC4);
    return env->NewStringUTF("622848");
}