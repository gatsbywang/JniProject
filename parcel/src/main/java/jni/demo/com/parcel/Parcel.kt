package jni.demo.com.parcel

/**
 * Created by 花歹 on 2018/5/1.
 * Email:   gatsbywang@126.com
 * Description:
 * Thought:
 */

public class Parcel {

    private var mNativePtr: Long = 0

    init {
        System.load("native-lib")

        mNativePtr = nativeCreate()
    }

    fun writeInt(value: Int) {
        nativeWriteInt(mNativePtr, value);
    }

    fun readInt(): Int {
        return nativeReadInt(mNativePtr);
    }


    fun setDataPosition(dataPost: Int) {
        nativeSetDataPosition(mNativePtr, dataPost);
    }

    //C层构建一个Parcel.cpp对象
    private external fun nativeCreate(): Long

    private external fun nativeWriteInt(nativePtr: Long, value: Int)

    //写完后重新设置偏移位置
    private external fun nativeSetDataPosition(nativePtr: Long, dataPost: Int)

    private external fun nativeReadInt(nativePtr: Long): Int
}