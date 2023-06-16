#include "s21_queue.h"
#include <iostream>
namespace s21 {

template<typename T>
queue<T>::queue(std::initializer_list<T> args) {
    if (args.size() > 0) {
        cap_ = len_ = args.size();
        begin_ = data_ = new T[cap_];
        auto itr = data_;
        for (auto &i : args) {
            itr[0] = i;
            itr++;
        }
    }
}

template<typename T>
queue<T>::queue(const queue &other) {
    copy_(other);
}

template<typename T>
queue<T>::queue(queue &&other) noexcept {
    if (this != &other) {
        data_ = other.data_;
        begin_ = other.begin_;
        other.begin_ = other.data_ = nullptr;
        len_ = other.len_;
        cap_ = other.cap_;
        other.cap_ = other.len_ = 0;
    }
}

template<typename T>
queue<T>::~queue() {
    if (data_) {
        delete[] data_;
        data_ = nullptr;
        cap_ = len_ = 0;
    }
}

template<typename T>
void queue<T>::copy_(const queue &other) {
    if (&other != this) {
        if (cap_)
            delete data_;
        len_ = cap_ = other.len_;
        begin_ = new T[cap_];
        data_ = begin_;
        for (int i = 0; i < len_; ++i)
            begin_[i] = other.begin_[i];
    }
}

template<typename T>
queue<T> &queue<T>::operator=(queue &&other) noexcept {
    if (this != &other) {
        if (data_ != nullptr)
            delete[] data_;
        data_ = other.data_;
        len_ = other.len_;
        cap_ = other.cap_;
        begin_ = other.begin_;
        other.data_ = nullptr;
        other.len_ = other.cap_ = 0;
    }
    return *this;
}

template<typename T>
void queue<T>::doubleMemBlock_() {
    if (cap_ >= maxCap_)
        throw std::bad_array_new_length();
    if (cap_ == 0) cap_ = 1;
    size_type newCap = (cap_ >= maxCap_ >> 1) ? maxCap_ : cap_ * 2;
    value_type *tmpArray = new value_type[newCap];
    if (tmpArray == nullptr)
        throw std::bad_alloc();
    cap_ = newCap;
    for (int i = 0; i < (int)len_; ++i)
        tmpArray[i] = begin_[i];
    delete[]data_;
    begin_ = data_ = tmpArray;
}

template<typename T>
void queue<T>::push(value_type value) {
    if (len_ >= cap_ - (begin_ - data_))
        doubleMemBlock_();
    begin_[len_++] = value;
}

template<typename T>
void queue<T>::pop() {
    if (len_ > 0) {
        --len_;
        begin_++;
    } else {
        begin_ = data_;
        len_ = 0;
    }
}

template<typename T>
void queue<T>::swap(queue &other) {
    if (this != &other) {
        std::swap(data_, other.data_);
        std::swap(begin_, other.begin_);
        std::swap(cap_, other.cap_);
        std::swap(len_, other.len_);
    }
}

template<typename T>
template<class... Args>
void queue<T>::emplace_back(Args &&... args) {
    const size_type sizeArgs = sizeof ...(Args);
    value_type arr[sizeArgs] = {args...};
    for (int i = 0; i < sizeArgs; ++i)
        push(arr[i]);
}

template<typename T>
void queue<T>::print() {
  for (auto i = &front(); i <= &back(); ++i)
    std::cout << *i << ' ';
  std::cout << '\n';
}

}  //  namespace s21
