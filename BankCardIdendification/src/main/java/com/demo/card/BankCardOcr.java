package com.demo.card;

import android.graphics.Bitmap;

/**
 * Created by 花歹 on 2018/8/1.
 * Email:   gatsbywang@126.com
 * Description:
 * Thought:
 */

public class BankCardOcr {

    static {
        System.loadLibrary("native-lib");
    }

    public static native String cardOcr(Bitmap bitmap);

}
