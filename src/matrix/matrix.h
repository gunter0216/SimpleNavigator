#ifndef SRC_MATRIX_MATRIX_H_
#define SRC_MATRIX_MATRIX_H_

#include <climits>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <string>

namespace s21 {
template <typename T>
class Matrix {
 public:
  Matrix();

  Matrix(int rows, int cols);

  Matrix(const Matrix &other);

  Matrix(Matrix &&other) noexcept;

  Matrix(const std::initializer_list<std::initializer_list<T>> &list);

  explicit Matrix(const std::string &path);

  ~Matrix();

  int getRows() const { return _rows; }

  int getCols() const { return _cols; }

  int size() const { return getRows(); };

  T **getMatrix();

  void clear();

  void swap(Matrix &other);

  void print() const;

  void removeRowColumn(const int row, const int col);

  Matrix<T> &operator=(const Matrix &other);

  Matrix<T> &operator=(Matrix &&other) noexcept;

  bool operator==(const Matrix &other);

  bool operator!=(const Matrix &other);

  T &operator()(int i, int j) const;

  T *operator[](int i) const;

 private:
  int _rows, _cols;
  T **_matrix;
};
}  // namespace s21

template <typename T>
s21::Matrix<T>::Matrix(const std::string &path) : Matrix() {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::invalid_argument("can't open file");
  }
  file >> _rows;
  _cols = _rows;
  if (_rows > 0 && _cols > 0) {
    _matrix = new T *[_rows];
    for (int i = 0; i < _rows; ++i) {
      _matrix[i] = new T[_cols];
      for (int j = 0; j < _cols; ++j) {
        file >> _matrix[i][j];
      }
    }
  } else {
    _cols = _rows = 0;
    _matrix = nullptr;
  }
  file.close();
}

template <typename T>
s21::Matrix<T>::Matrix() {
  _cols = 0;
  _rows = 0;
  _matrix = nullptr;
}

template <typename T>
s21::Matrix<T>::Matrix(int rows, int cols) {
  _cols = cols;
  _rows = rows;
  _matrix = new T *[_rows];
  for (int i = 0; i < _rows; i++) _matrix[i] = new T[_cols]{};
}

template <typename T>
s21::Matrix<T>::Matrix(const Matrix &other) {
  if (this != &other) {
    _rows = other._rows;
    _cols = other._cols;
    _matrix = new T *[_rows];
    for (int i = 0; i < _rows; i++) {
      _matrix[i] = new T[_cols];
      for (int j = 0; j < _cols; j++) {
        _matrix[i][j] = other._matrix[i][j];
      }
    }
  }
}

template <typename T>
s21::Matrix<T>::Matrix(Matrix &&other) noexcept {
  if (this != &other) {
    _cols = other._cols;
    _rows = other._rows;
    _matrix = other._matrix;
    other._cols = other._rows = 0;
    other._matrix = nullptr;
  }
}

template <typename T>
s21::Matrix<T>::Matrix(
    const std::initializer_list<std::initializer_list<T>> &list)
    : Matrix(list.size(), list.begin()->size()) {
  int i = 0, j = 0;
  for (auto item1 : list) {
    for (auto item2 : item1) {
      _matrix[i][j] = item2;
      ++j;
    }
    ++i;
    j = 0;
  }
}

template <typename T>
s21::Matrix<T>::~Matrix() {
  clear();
}

template <typename T>
T **s21::Matrix<T>::getMatrix() {
  return _matrix;
}

template <typename T>
void s21::Matrix<T>::clear() {
  if (_matrix != nullptr) {
    for (int i = 0; i < _rows; ++i) delete[] _matrix[i];
    delete[] _matrix;
  }
  _matrix = nullptr;
  _rows = _cols = 0;
}

template <typename T>
void s21::Matrix<T>::swap(Matrix &other) {
  std::swap(_matrix, other._matrix);
  std::swap(_cols, other._cols);
  std::swap(_rows, other._rows);
}

template <typename T>
s21::Matrix<T> &s21::Matrix<T>::operator=(const Matrix &other) {
  if (this != &other) {
    clear();
    _cols = other._cols;
    _rows = other._rows;
    _matrix = new T *[_rows];
    for (int i = 0; i < _rows; i++) {
      _matrix[i] = new T[_cols];
      for (int j = 0; j < _cols; j++) {
        _matrix[i][j] = other._matrix[i][j];
      }
    }
  }
  return *this;
}

template <typename T>
s21::Matrix<T> &s21::Matrix<T>::operator=(Matrix &&other) noexcept {
  if (this != &other) {
    clear();
    _cols = other._cols;
    _rows = other._rows;
    _matrix = other._matrix;
    other._matrix = nullptr;
    other._cols = other._rows = 0;
  }
  return *this;
}

template <typename T>
bool s21::Matrix<T>::operator==(const Matrix &other) {
  bool result = true;
  if (other._cols != _cols || other._rows != _rows) {
    result = false;
  } else {
    for (int i = 0; i < _rows && result; ++i) {
      for (int j = 0; j < _cols && result; ++j) {
        if (other._matrix[i][j] != _matrix[i][j]) {
          result = false;
        }
      }
    }
  }
  return result;
}

template <typename T>
bool s21::Matrix<T>::operator!=(const Matrix &other) {
  return !(*this == other);
}

template <typename T>
T &s21::Matrix<T>::operator()(int i, int j) const {
  if (i >= _rows || j >= _cols || i < 0 || j < 0) {
    std::string exc = "Index was out of range, i = ";
    exc += std::to_string(i) + " j = " + std::to_string(j) + " when size is " +
           std::to_string(_rows) + "x" + std::to_string(_cols);
    throw std::out_of_range(exc);
  }
  return _matrix[i][j];
}

template <typename T>
T *s21::Matrix<T>::operator[](int i) const {
  return _matrix[i];
}

template <typename T>
void s21::Matrix<T>::print() const {
  if (_matrix != nullptr) {
    std::cout << _rows << " " << _cols << std::endl;
    for (int i = 0; i < _rows; ++i) {
      for (int j = 0; j < _cols; ++j) {
        std::cout << _matrix[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
}

template <typename T>
void s21::Matrix<T>::removeRowColumn(const int row, const int col) {
  if (row > _rows || col > _cols)
    throw std::out_of_range("Index was out of range");

  Matrix matrix(_rows - 1, _cols - 1);
  size_t i2 = 0;
  for (size_t i = 0; i < _rows; ++i) {
    if (i != row) {
      size_t j2 = 0;
      for (size_t j = 0; j < _cols; ++j) {
        if (j != col) {
          matrix[i2][j2] = (*this)[i][j];
          ++j2;
        }
      }
      ++i2;
    }
  }
  *this = matrix;
}

#endif  // SRC_MATRIX_MATRIX_H_
