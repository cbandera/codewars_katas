// https://www.codewars.com/kata/591521e2d64db03a010000fe
#include <array>

class Matrix {
public:
  Matrix() = default;
  Matrix(float t00, float t01, float t10, float t11) {
    this->m_[0][0] = t00;
    this->m_[0][1] = t01;
    this->m_[1][0] = t10;
    this->m_[1][1] = t11;
  };
  float &operator()(size_t i, size_t j) { return this->m_[i][j]; }
  bool operator==(const Matrix &other) const {
    return this->m_[0][0] == other.m_[0][0] &&
           this->m_[0][1] == other.m_[0][1] &&
           this->m_[1][0] == other.m_[1][0] && this->m_[1][1] == other.m_[1][1];
  }
  Matrix operator*(const Matrix &other) const {
    Matrix result{};
    result.m_[0][0] =
        other.m_[0][0] * this->m_[0][0] + other.m_[0][1] * this->m_[1][0];
    result.m_[0][1] =
        other.m_[0][0] * this->m_[0][1] + other.m_[0][1] * this->m_[1][1];
    result.m_[1][0] =
        other.m_[1][0] * this->m_[0][0] + other.m_[1][1] * this->m_[1][0];
    result.m_[1][1] =
        other.m_[1][0] * this->m_[0][1] + other.m_[1][1] * this->m_[1][1];
    return result;
  }
  Matrix operator*(const float value) const {
    Matrix result{};
    result.m_[0][0] = this->m_[0][0] * value;
    result.m_[0][1] = this->m_[0][1] * value;
    result.m_[1][0] = this->m_[1][0] * value;
    result.m_[1][1] = this->m_[1][1] * value;
    return result;
  }
  float det() const {
    return this->m_[0][0] * this->m_[1][1] - this->m_[0][1] * this->m_[1][0];
  }

private:
  std::array<std::array<float, 2>, 2> m_{};
};

class Dih4 {
public:
  Dih4() = default;
  Dih4(const Matrix &t) : t_{t} {};
  Dih4(float t00, float t01, float t10, float t11) : t_{t00, t01, t10, t11} {};
  bool is_rotation() const { return t_.det() > 0; }
  bool is_reflection() const { return t_.det() < 0; }
  Dih4 then(const Dih4 &other) const { return Dih4(other.t_ * this->t_); }
  Dih4 inv() const {
    if (*this == Dih4::ROTATE_90_ANTICLOCKWISE ||
        *this == Dih4::ROTATE_90_CLOCKWISE) {
      return this->t_ * -1;
    } else {
      return *this;
    }
  }
  bool operator==(const Dih4 &other) const { return this->t_ == other.t_; }
  bool operator!=(const Dih4 &other) const { return !(this->t_ == other.t_); }

  static const Dih4 IDENTITY;
  static const Dih4 ROTATE_90_ANTICLOCKWISE;
  static const Dih4 ROTATE_180;
  static const Dih4 ROTATE_90_CLOCKWISE;
  static const Dih4 REFLECT_VERTICAL;
  static const Dih4 REFLECT_FORWARD_DIAGONAL;
  static const Dih4 REFLECT_HORIZONTAL;
  static const Dih4 REFLECT_REVERSE_DIAGONAL;

private:
  Matrix t_{};
};

const Dih4 Dih4::IDENTITY(1, 0, 0, 1);
const Dih4 Dih4::ROTATE_90_ANTICLOCKWISE(0, -1, 1, 0);
const Dih4 Dih4::ROTATE_180(-1, 0, 0, -1);
const Dih4 Dih4::ROTATE_90_CLOCKWISE(0, 1, -1, 0);
const Dih4 Dih4::REFLECT_VERTICAL(1, 0, 0, -1);
const Dih4 Dih4::REFLECT_FORWARD_DIAGONAL(0, 1, 1, 0);
const Dih4 Dih4::REFLECT_HORIZONTAL(-1, 0, 0, 1);
const Dih4 Dih4::REFLECT_REVERSE_DIAGONAL(0, -1, -1, 0);