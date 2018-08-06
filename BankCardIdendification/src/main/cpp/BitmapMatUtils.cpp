//
// Created by 花歹 on 2018/8/1.
//

#include "BitmapMatUtils.h"
#include <android/bitmap.h>

int BitmapMatUtils::bitmap2mat(JNIEnv *env, jobject bitmap, Mat &mat) {
    //1、锁定画布
    void* pixels;
    AndroidBitmap_lockPixels(env,bitmap,&pixels);

    //构建mat 对象，还要判断什么颜色通道
    // 获取 bitmap 的信息
    AndroidBitmapInfo bitmapInfo;
    AndroidBitmap_getInfo(env,bitmap,&bitmapInfo);

    //
    Mat createMat(bitmapInfo.height,bitmapInfo.width,CV_8UC4);
    if(bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888){ // 四颜色通道  CV_8UC4->argb
        Mat temp(bitmapInfo.height,bitmapInfo.width,CV_8UC4,pixels);
        //把CV_8UC4 转为 CV_8UC2
        temp.copyTo(createMat);
    } else if(bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGB_565){ //三颜色通道   CV_8UC2 -> rgb
        Mat temp(bitmapInfo.height,bitmapInfo.width,CV_8UC2,pixels);
        cvtColor(temp,createMat,COLOR_BGR5652BGRA);
    }

    createMat.copyTo(mat);
    //2、解锁画布
    AndroidBitmap_unlockPixels(env,bitmap);
}

int BitmapMatUtils::mat2bitmap(JNIEnv *env, jobject bitmap, Mat &mat) {}
