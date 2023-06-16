#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_

#include <initializer_list>
#include <limits>

namespace s21 {

template <typename T>
class queue {
  using value_type = T;
  using size_type = std::size_t;
  using reference = T &;
  using const_reference = const T &;

 public:
  queue() : len_(0), cap_(0), data_(nullptr) {}
  queue(std::initializer_list<T> args);
  queue(const queue &other);
  queue(queue &&other) noexcept;

  queue &operator=(queue &&other) noexcept;

  ~queue();

  const_reference front() { return *begin_; }
  const_reference back() { return *(begin_ + len_ - 1); }
  value_type peek() { return front(); }

  bool empty() { return len_ == 0; }
  size_type size() const { return len_; }

  void push(value_type value);
  void pop();
  void swap(queue &other);

  template <class... Args>
  void emplace_back(Args &&...args);
  void print();

 private:
  const size_type maxCap_ = 1000000;
  size_type len_ = 0;
  size_type cap_ = 0;
  value_type *data_ = nullptr;
  value_type *begin_ = data_;

  void copy_(const queue &other);
  void doubleMemBlock_();
};

}  //  namespace s21
#include "s21_queue.inl"
#endif  //  SRC_S21_QUEUE_H_
