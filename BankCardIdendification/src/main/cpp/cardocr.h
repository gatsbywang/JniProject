//
// Created by 花歹 on 2018/8/1.
//

#ifndef JNIPROJECT_CARDOCR_H
#define JNIPROJECT_CARDOCR_H


#include "opencv2/opencv.hpp"
#include <vector>

using namespace cv;

//会针对不同的场景，做不同的事情
namespace co1{

    /**
     * 找到银行卡区域
     * @param mat 图片的mat
     * @param area  卡号区域
     * @return 是否成功 0为成功，其他失败
     */
    int find_card_area(const Mat &mat,Rect &area);

    /**
     * 通过银行卡区域 截取到卡号区域
     * @param mat  银行卡的mat
     * @param area 存放截取区域
     * @return  是否成功 0为成功，其他失败
     */
    int find_card_number_area(const Mat &mat,Rect &area);

    /**
     * 找到所有数字
     * @param mat 银行卡号区域
     * @param numbers   存放所有数字
     * @return  是否成功
     */
    int find_card_numbers(const Mat &mat,std::vector<Mat> numbers);

    /**
     * 字符串进行粘连处理
     * @param mat
     * @return  粘连的那一列
     */
    int find_split_cols_pos(Mat mat);
}

/**
 * 备选方案
 */
namespace co2{

}

class cardocr {


};


#endif //JNIPROJECT_CARDOCR_H
