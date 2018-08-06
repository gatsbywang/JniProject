//
// Created by 花歹 on 2018/8/1.
//

#include "cardocr.h"
#include <vector>

using namespace std;

int co1::find_card_area(const Mat &mat, Rect &area) {

    //首先降噪
    Mat blur;
    GaussianBlur(mat, blur, Size(5, 5), BORDER_DEFAULT, BORDER_DEFAULT);

    //边缘梯度增强x,y,增强
    Mat gard_x, gard_y;

    Scharr(blur, gard_x, CV_32F, 1, 0);
    Scharr(blur, gard_y, CV_32F, 0, 1);

    Mat abs_gard_x, abs_gard_y;

    convertScaleAbs(gard_x, abs_gard_x);
    convertScaleAbs(gard_y, abs_gard_y);

    Mat gard;
    addWeighted(abs_gard_x, 0.5, abs_gard_y, 0.5, 0, gard);

//    Mat temp;
//    cvtColor(gard,temp,COLOR_BGR5652BGRA);
//
//    //写到内存
//    imwrite("/storage/emulated/0/ocr/gard_n.jpg",temp);

    //二值化,筛选轮廓
    Mat gray;
    cvtColor(gard, gray, COLOR_BGRA2GRAY);

    Mat binary;
    threshold(gray, binary, 40, 255, THRESH_BINARY);

    //图像过滤
    vector<vector<Point> > contours;//这里要有个空格
    findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (int i = 0; i < contours.size(); i++) {
        Rect rect = boundingRect(contours[i]);
        //过滤轮廓
        if (rect.width > mat.cols / 2 && rect.width != mat.cols && rect.height > mat.rows / 2) {
            //银行卡区域的高度和宽度 必须大于图片的一半
            area = rect; //调用拷贝构造函数
            break;
        }
    }



//    imwrite("/storage/emulated/0/ocr/gard_n.jpg",binary);

    //对返回值做处理，告诉调用者，有没有成功
    if (area.width == 0) {
        return -1;
    }
    //释放资源
    blur.release();
    gard_x.release();
    gard_y.release();
    abs_gard_x.release();
    abs_gard_y.release();
    gard.release();
    gray.release();
    binary.release();
    return 0;

}

int co1::find_card_number_area(const Mat &mat, Rect &area) {
    //两种方式
    //1、精确截取 2、粗略截取

    //粗略截取：高度1/2 到 3/4 ，宽度1/12 ~ 11/12

    //万一找不到，可以手动输入和修改。

    area.x = mat.cols / 12;
    area.y = mat.rows / 2;


    area.width = mat.cols * 5 / 6;
    area.height = mat.rows / 4;

    return 0;
}

int co1::find_card_numbers(const Mat &mat, std::vector<Mat> numbers) {
    //二值化 灰度处理
    //先灰度处理
    Mat gray;
    cvtColor(mat, gray, COLOR_BGRA2GRAY);

    //THRESH_OTSU 自己去找合适的值，这一步非常关键
    //二值化处理
    Mat binary;
    threshold(gray, binary, 39, 255, THRESH_BINARY);

    //去掉干扰过滤填充，找数字就是轮廓查询
    //查找轮廓，需要黑色的背景 ，白色数字
    //取反 白黑->黑白
    Mat binary_not = binary.clone();
    bitwise_not(binary_not, binary_not);

    //降噪过滤
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(binary_not, binary, MORPH_CLOSE, kernel);

    //轮廓过滤
    vector<vector<Point> > contours;//这里要有个空格
    findContours(binary_not, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    int mat_area = mat.rows * mat.cols;
    int min_h = mat.rows / 4;
    for (int i = 0; i < contours.size(); i++) {
        Rect rect = boundingRect(contours[i]);
        //多个条件
        //面积太小的过滤
        int area = rect.width * rect.height;
        if (area < mat_area / 200) {
            //小面积 填充为白色背景
            drawContours(binary, contours, i, Scalar(255), -1);
        } else if (rect.height < min_h) {
            drawContours(binary, contours, i, Scalar(255), -1);
        }

    }


    //binary_not 有噪点
    binary.copyTo(binary_not);
    bitwise_not(binary_not, binary_not);//取反，变为黑背景，白色字

    //先要把rect数组存起来，查找有可能出现循序错略，还有可能出现粘连字符
    contours.clear();
    findContours(binary_not, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    Rect rects[contours.size()];
    Mat contours_mat(binary.size(), CV_8UC1, Scalar(255));//单颜色通道,白色图片
    //判断粘连字符,记录最小宽度
    int min_w = mat.cols;
    for (int i = 0; i < contours.size(); i++) {
        rects[i] = boundingRect(contours[i]);
        drawContours(contours_mat, contours, i, Scalar(0), 1);
        min_w = min(rects[i].width, min_w);
    }

    //最小宽度的2倍
//    min_w *= 2;


    //进行排序，冒泡（最简单）,用轮廓的左上角的x值进行比较
    for (int i = 0; i < contours.size() - 1; ++i) {
        for (int j = 0; j < contours.size() - i - 1; ++j) {
            if (rects[j].x > rects[j + 1].x) {
                swap(rects[j], rects[j + 1]);
            }
        }
    }

    //裁剪
    numbers.clear();
    for (int i = 0; i < contours.size(); i++) {

        // 大于 最小宽度的2倍
        if (rects[i].width >= min_w * 2) {
            //处理粘连字符
            Mat mat(contours_mat, rects[i]);
            int cols_pos = co1::find_split_cols_pos(mat);

            Rect rect_left(0,0,cols_pos-1,mat.rows);
            numbers.push_back(Mat(mat,rect_left));
            Rect rect_right(cols_pos,0,mat.cols-cols_pos-1,mat.rows);
            numbers.push_back(Mat(mat,rect_right));

        } else {
            Mat number(contours_mat, rects[i]);
            numbers.push_back(number);
            //保存每个数字图片
            char name[50];
            sprintf(name, "/storage/emulated/0/ocr/card_number_%d.jpg", i);
            imwrite(name, number);
        }
    }


    gray.release();

    binary.release();

    binary_not.release();

    contours_mat.release();

    return 0;
}

int co1::find_split_cols_pos(Mat mat) {
    //对中心位置的左右 1/4 扫描，记录最少黑色像素点的列的位置，就当做我们的字符串的粘连的位置。
    int mx = mat.cols/2;
    int height =mat.rows;

    //围绕中心左右扫描1/4
    int start_x = mx-mx/2;
    int end_x = mx+mx/2;

    //刚开始先 等于中心点
    int cols_pos = mx;

    int c =0;

    int min_h_p = mat.rows;

    for (int col =start_x; col < end_x; ++col) {
        int total = 0;
        for (int row = 0; row < height; ++row) {
            //获取像素点
            c = mat.at<Vec3b>(row, col)[0];//单通道，取第0位置即可
            if(c==0){
                total++;
            }
        }

        if(total < min_h_p){
            min_h_p = total;
            cols_pos = col;
        }
    }

    return cols_pos;

}