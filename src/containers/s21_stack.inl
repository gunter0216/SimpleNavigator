#include "s21_stack.h"
namespace s21 {

template<class T>
stack<T>::~stack() {
    if (data_) {
        delete[] data_;
        data_ = nullptr;
        cap_ = len_ = 0;
    }
}

template<typename T>
void stack<T>::doubleMemBlock_() {
    if (len_ < cap_) return;
    if (cap_ >= maxCap_) throw std::bad_array_new_length();
    if (cap_ == 0) cap_ = 1;
    size_type newCap = (cap_ >= maxCap_ >> 1) ? maxCap_ : cap_ * 2;
    T *tmpArray = new T[newCap];
    if (tmpArray == nullptr) throw std::bad_alloc();
    cap_ = newCap;
    for (int i = 0; i < len_; ++i) tmpArray[i] = data_[i];
    delete[] data_;
    data_ = tmpArray;
}

template<typename T>
void stack<T>::push(const_reference value) {
    if (len_ == cap_) doubleMemBlock_();
    data_[len_++] = value;
}

template<typename T>
stack<T>::stack(const stack<T> &s) {
    if(&s != this){
        cap_ = s->cap_;
        len_ = s->len_;
        data_ = new T[len_];
        for (int i = 0; i < len_; ++i) {
            data_[i] = s->data_[i];
        }
    }
}
template<typename T>
stack<T>::stack(stack<T> &&s) {

}

}  //  namespace s21
