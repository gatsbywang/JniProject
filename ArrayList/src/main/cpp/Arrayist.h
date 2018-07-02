//
// Created by 花歹 on 2018/7/2.
//

#ifndef JNIPROJECT_ARRAYIST_H
#define JNIPROJECT_ARRAYIST_H

template<class E>
class ArrayList {
    //长度，数组，当前角标
    E* arr; //当前
    int len =0;//数组大小
    int index =0; //当前角标

public:
    ArrayList();

    ArrayList(int len);

    void add(E e);

    E remove(int index);

    E get(int index);

    ~ArrayList();
};


#endif //JNIPROJECT_ARRAYIST_H
