//
// Created by Marcin on 17.04.2019.
//

#ifndef SERVER_MUTUALEXCLUSIVEHASHMAP_H
#define SERVER_MUTUALEXCLUSIVEHASHMAP_H

#include <pthread.h>
#include <unordered_map>

template <typename T>
class MutualExclusiveHashMap {
    pthread_mutex_t mutex;
    std::unordered_map<int, T> map;
public:
    MutualExclusiveHashMap();
    void put(int, T);
    T get(int);
};

template <typename T>
MutualExclusiveHashMap<T>::MutualExclusiveHashMap() {
    pthread_mutex_init(&mutex, nullptr);
}

template<typename T>
void MutualExclusiveHashMap<T>::put(int key, T value) {
    pthread_mutex_lock(&mutex);
    map[key] = value;
    pthread_mutex_unlock(&mutex);
}

template<typename T>
T MutualExclusiveHashMap<T>::get(int key) {
    T value;
    pthread_mutex_lock(&mutex);
    value = map[key];
    pthread_mutex_unlock(&mutex);
    return value;
}


#endif //SERVER_MUTUALEXCLUSIVEHASHMAP_H
