//
// Created by Marcin on 02.04.2019.
//

#ifndef SERVER_SYNCHRONIZEDVECTOR_H
#define SERVER_SYNCHRONIZEDVECTOR_H


#include "../../monitor.h"
#include <vector>
#include <algorithm>

template <typename T>
class SynchronizedVector: Monitor {
private:
    std::vector<T> values;
public:
    SynchronizedVector();
    void put(T);
    T get(int);
    void erase(T);
    unsigned long getSize();
    std::vector<T>& getAll();
};

template<typename T>
SynchronizedVector<T>::SynchronizedVector() {
}

template<typename T>
void SynchronizedVector<T>::put(T value) {
    enter();
    values.push_back(value);
    leave();
}

template<typename T>
T SynchronizedVector<T>::get(int position) {
    int value;
    enter();
    value = values.at(position);
    leave();
    return value;
}

template<typename T>
void SynchronizedVector<T>::erase(T value) {
    enter();
    auto position = std::find(values.begin(), values.end(), value);
    values.erase(position);
    leave();
}

template<typename T>
unsigned long SynchronizedVector<T>::getSize() {
    enter();
    auto size = values.size();
    leave();
    return size;
}

template<typename T>
std::vector<T>& SynchronizedVector<T>::getAll() {
    enter();
    auto &valuesToReturn = values;
    leave();
    return valuesToReturn;
}


#endif //SERVER_SYNCHRONIZEDVECTOR_H
