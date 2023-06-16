#pragma once

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class stack {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  stack() : len_(0), cap_(0), data_(nullptr){};
  stack(const stack<T> &s);
  stack(stack<T> &&s);
  ~stack();

  reference top() { return *(data_ + len_); }
  value_type peek() { return top(); }

  bool empty() { return len_ == 0; }
  size_type size() { return len_; };
  size_type capacity() { return cap_; };

  void push(const_reference value);
  void pop() { --len_; }

 private:
  const size_type maxCap_ = 1000000;
  size_type len_ = 0;
  size_type cap_ = 0;
  value_type *data_ = nullptr;

  auto doubleMemBlock_() -> void;
};

}  //  namespace s21
#include "s21_stack.inl"
