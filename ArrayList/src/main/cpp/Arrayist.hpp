//
// Created by 花歹 on 2018/7/2.

//如果开发中涉及到模板类，声明和实现要写到同一个类中， hpp=h+cpp
//
#include <malloc.h>
#include <string.h>

#ifndef JNIPROJECT_ARRAYIST_H
#define JNIPROJECT_ARRAYIST_H

/*---------------------------------声明----------------------------------*/

template<class E>
class ArrayList {

private:
    //长度，数组，当前角标
    E *arr; //当前
    int len = 0;//数组大小
    int index = 0; //当前角标

public:
    ArrayList();

    ArrayList(int len);

    void add(E e);

    E remove(int index);

    E get(int index);

    int size();

    void ensureCapacityInternal(int minCapacity);

    void grow(int minCapacity);

    ~ArrayList();
};
/*---------------------------------实现----------------------------------*/

//每次实现方法都得添加
template<class E>
ArrayList<E>::ArrayList() {}

//每次实现方法都得添加
template<class E>
ArrayList<E>::ArrayList(int len) {
    if (len <= 0) {
        return;
    }
    this->len = len;

    this->arr = (E *) malloc(sizeof(E) * len);

}

//每次实现方法都得添加
template<class E>
ArrayList<E>::~ArrayList() {
    if (this->arr) {
        free(this->arr);
        this->arr = NULL;
    }
}

template<class E>
int ArrayList<E>::size() {
    return this->index;
}

template<class E>
void ArrayList<E>::add(E e) {
    ensureCapacityInternal(index + 1);  // Increments modCount!!
    this->arr[index++] = e;
}

template<class E>
E ArrayList<E>::get(int index) {
    return this->arr[index++];
}


template<class E>
void ArrayList<E>::ensureCapacityInternal(int minCapacity) {
    if (this->arr == NULL) {
        minCapacity = 10;
    }

    if (minCapacity - len > 0) {
        //创建新的数组
        grow(minCapacity);
    }
}

template<class E>
void ArrayList<E>::grow(int min_capacity) {
    // overflow-conscious code
    int old_capacity = len;
    int new_capacity = old_capacity + (old_capacity >> 1);
    if (new_capacity - min_capacity < 0)
        new_capacity = min_capacity;
//    if (newCapacity - MAX_ARRAY_SIZE > 0)
//        newCapacity = hugeCapacity(minCapacity);
    // minCapacity is usually close to size, so this is a win:
    E *new_arr = (E *) malloc(sizeof(E) * new_capacity);

    if (this->arr) {
        //原来数组数据拷贝
        memcpy(this->arr, new_arr, sizeof(E) * index); // sizeof(E)*index 字节
    }


    this->arr = new_arr;
    this->len = new_capacity;
}

#endif //JNIPROJECT_ARRAYIST_H
