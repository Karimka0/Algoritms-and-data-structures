#include <iostream>
#include <vector>

int mod;
const int kNine = 9;
const int kTen = 10;

class BigInteger {
  static const size_t kBase = 1000000000;
  bool sign_ = true;
  size_t discharges_ = 0;
  std::vector<long long> number_;

  void Shift(int digit) {
    if (*this == 0) {
      return;
    }
    std::vector<long long> new_number;
    for (int i = 0; i < digit; ++i) {
      new_number.push_back(0);
    }
    for (long long ii : number_) {
      new_number.push_back(ii);
    }
    number_ = new_number;
    discharges_ = number_.size();
  }

 public:
  BigInteger() = default;

  explicit BigInteger(size_t num) : sign_(true), discharges_(1) {
    number_.push_back(num % kBase);
    if (num >= kBase) {
      number_.push_back(num / kBase);
      ++discharges_;
    }
  }

  explicit BigInteger(int num) : sign_(num >= 0), discharges_(1) {
    if (!sign_) {
      num = -num;
    }
    if (static_cast<size_t>(num) >= kBase) {
      number_.push_back(static_cast<size_t>(num) % kBase);
      num /= kBase;
      discharges_++;
    }
    number_.push_back(num);
  }

  BigInteger(long long num) : sign_(num >= 0), discharges_(1) {
    if (!sign_) {
      num = -num;
    }
    number_.push_back(num);
  }

  BigInteger(bool sign_now, size_t size, std::vector<long long> digits_now)
      : sign_(sign_now), discharges_(size) {
    for (size_t i = 0; i < digits_now.size(); ++i) {
      number_.push_back(digits_now[i]);
    }
  }

  BigInteger& operator+=(const BigInteger& other) {
    BigInteger result;

    if (*this >= other) {
      result.discharges_ = other.discharges_;
      for (size_t i = 0; i < result.discharges_; ++i) {
        long long sum = number_[i] + other.number_[i];
        if (i == 0) {
          result.number_.push_back(sum % kBase);
          result.number_.push_back(sum / kBase);
        } else {
          result.number_[i] += sum % kBase;
          result.number_.push_back(sum / kBase);
        }
      }
      ++result.discharges_;

      if (discharges_ != other.discharges_) {
        result.number_[result.discharges_ - 1] +=
            number_[result.discharges_ - 1];
      }

      for (size_t i = result.discharges_; i < discharges_; ++i) {
        result.number_.push_back(number_[i]);
        ++result.discharges_;
      }

      if (result.number_.back() == 0) {
        result.number_.pop_back();
        --result.discharges_;
      }
    } else {
      result = other;
      result += *this;
    }
    *this = result;
    return *this;
  }

  BigInteger& operator-=(const BigInteger& other) {
    BigInteger result;
    if (*this >= other) {
      result.discharges_ = other.discharges_;
      long long shift = 0;

      for (size_t i = 0; i < other.discharges_; ++i) {
        long long diff = number_[i] - other.number_[i];
        result.number_.push_back(diff + shift);
        shift = 0;
        if (result.number_[i] < 0) {
          result.number_[i] += kBase;
          shift = -1;
        }
      }

      for (size_t i = other.discharges_; i < discharges_; ++i) {
        result.number_.push_back(number_[i] + shift);
        ++result.discharges_;
        shift = 0;
        if (result.number_[i] < 0) {
          result.number_[i] += kBase;
          shift = -1;
        }
      }

      while (result.number_.size() > 1 && result.number_.back() == 0) {
        --result.discharges_;
        result.number_.pop_back();
      }

    } else {
      result = other;
      result -= *this;
      result = -result;
    }
    *this = result;
    return *this;
  }

  BigInteger& operator*=(const BigInteger& other) {
    BigInteger result;
    result.discharges_ = discharges_ + other.discharges_;
    result.number_.resize(result.discharges_, 0);

    for (size_t i = 0; i < discharges_; ++i) {
      long long shift = 0;
      for (size_t j = 0; j < other.discharges_ || (shift != 0); ++j) {
        long long mult =
            result.number_[i + j] +
            number_[i] * (j < other.discharges_ ? other.number_[j] : 0) + shift;
        result.number_[i + j] = mult % kBase;
        shift = mult / kBase;
      }
    }

    while (result.number_.size() > 1 && result.number_.back() == 0) {
      result.number_.pop_back();
    }

    result.discharges_ = result.number_.size();
    result.sign_ = sign_ == other.sign_;
    *this = result;
    return *this;
  }

  BigInteger& operator/=(const BigInteger& other) {
    if (*this == 0) {
      return *this;
    }

    BigInteger numerator = *this;
    BigInteger denominator = other;
    BigInteger result = 0;
    BigInteger diff = 0;
    BigInteger temp2 = 0;
    if (!numerator.sign_) {
      numerator = -numerator;
    }
    if (!denominator.sign_) {
      denominator = -denominator;
    }
    if (numerator < denominator) {
      *this = 0;
      return *this;
    }

    for (size_t i = numerator.discharges_; i > 0; --i) {
      diff.Shift(1);
      result.Shift(1);
      diff += number_[i - 1];
      if (diff < denominator) {
        continue;
      }
      int left = 0;
      int right = kBase + 1;
      while (right > left) {
        int middle = (left + right) >> 1;
        temp2 = denominator;
        temp2 *= middle;
        if (diff > temp2) {
          ++middle;
          left = middle;
        } else {
          right = middle;
        }
      }
      BigInteger temp = denominator;
      temp *= left;
      if (diff < temp) {
        --left;
        temp -= denominator;
      }
      result += left;
      diff -= temp;
    }
    while (result.number_.size() > 1 && result.number_.back() == 0) {
      result.number_.pop_back();
    }
    result.discharges_ = result.number_.size();
    result.sign_ = this->sign_ == other.sign_;
    *this = result;
    return *this;
  }

  BigInteger& operator%=(const BigInteger& other) {
    BigInteger temp = *this;
    temp /= other;
    temp *= other;
    *this -= temp;
    return *this;
  }

  BigInteger operator-() const {
    BigInteger result = *this;
    if (*this != 0) {
      result.sign_ = !result.sign_;
    }
    return result;
  }

  BigInteger& operator++() {
    *this += 1;
    return *this;
  }

  BigInteger operator++(int) {
    BigInteger temp = *this;
    ++(*this);
    return temp;
  }

  BigInteger& operator--() {
    *this -= 1;
    return *this;
  }

  BigInteger operator--(int) {
    BigInteger temp = *this;
    --(*this);
    return temp;
  }

  bool operator==(const BigInteger& other) const {
    return sign_ == other.sign_ && number_ == other.number_;
  }

  bool operator!=(const BigInteger& other) const { return !(*this == other); }

  bool operator<(const BigInteger& other) const {
    if (sign_ != other.sign_) {
      return !sign_ && other.sign_;
    }

    if (discharges_ != other.discharges_) {
      return (discharges_ < other.discharges_) == sign_;
    }

    for (size_t i = discharges_; i > 0; --i) {
      if (number_[i - 1] != other.number_[i - 1]) {
        return (number_[i - 1] < other.number_[i - 1]) == sign_;
      }
    }
    return false;
  }

  bool operator<=(const BigInteger& other) const { return !(other < *this); }

  bool operator>(const BigInteger& other) const { return other < *this; }

  bool operator>=(const BigInteger& other) const { return !(*this < other); }

  explicit operator bool() const { return *this != 0; }

 private:
  static int Len(long long num) {
    if (num == 0) {
      return 1;
    }
    int ans = 0;
    while (num > 0) {
      ++ans;
      num /= kTen;
    }
    return ans;
  }
};

BigInteger operator+(const BigInteger& left, const BigInteger& right) {
  BigInteger result = left;
  result += right;
  return result;
}

BigInteger operator-(const BigInteger& left, const BigInteger& right) {
  BigInteger result = left;
  result -= right;
  return result;
}

BigInteger operator*(const BigInteger& left, const BigInteger& right) {
  BigInteger result = left;
  result *= right;
  return result;
}

BigInteger operator/(const BigInteger& left, const BigInteger& right) {
  BigInteger result = left;
  result /= right;
  return result;
}

BigInteger operator%(const BigInteger& left, const BigInteger& right) {
  BigInteger result = left;
  result %= right;
  return result;
}

BigInteger operator""_bi(unsigned long long value) {
  return BigInteger(static_cast<size_t>(value));
}

std::istream& operator>>(std::istream& is, BigInteger& big_int) {
  std::string input;
  is >> input;

  bool sign = true;
  size_t start = 0;
  if (!input.empty() && input[0] == '-') {
    sign = false;
    start = 1;
  }

  std::vector<long long> now_number;
  size_t full = (input.size() - start) / kNine;
  size_t rem = (input.size() - start) % kNine;

  std::string now_digit;
  for (size_t i = full; i != 0; --i) {
    for (int j = 0; j < kNine; ++j) {
      if (start + rem + (i - 1) * kNine + j >= 0 &&
          start + rem + (i - 1) * kNine + j < input.size()) {
        now_digit += input[start + rem + (i - 1) * kNine + j];
      }
    }
    now_number.push_back(stoll(now_digit));
    now_digit = "";
  }

  if (rem != 0) {
    for (size_t i = start; i < rem + start; ++i) {
      if (i < input.size()) {
        now_digit += input[i];
      }
    }
    now_number.push_back(stoll(now_digit));
  }

  big_int = BigInteger(sign, now_number.size(), now_number);
  return is;
}

struct Matrix {
  std::vector<std::vector<int>> matr;
  int size;

  Matrix(int new_size, int value)
      : matr(new_size, std::vector<int>(new_size, value)), size(new_size) {}

  static Matrix IdMatr(int size) {
    Matrix ee(size, 0);
    for (int i = 0; i < size; ++i) {
      ee.matr[i][i] = 1;
    }
    return ee;
  }

  Matrix(std::vector<std::vector<int>> vec) : matr(vec), size(vec[0].size()) {}

  Matrix& operator*=(const Matrix& matrix) {
    Matrix result(size, 0);
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        for (int k = 0; k < size; ++k) {
          result[i][j] += matr[i][k] * matrix[k][j];
          result[i][j] %= mod;
        }
      }
    }
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        operator[](i)[j] = result[i][j];
      }
    }
    return *this;
  }

  Matrix operator*(const Matrix& multiplier) {
    Matrix result(*this);
    result *= multiplier;
    return result;
  }

  std::vector<int>& operator[](int index) { return matr[index]; }
  const std::vector<int>& operator[](int index) const { return matr[index]; }
};

bool Can(int p1, int p2, int mm) {
  for (int i = 0; i < mm - 1; ++i) {
    int b1 = (p1 >> i) & 1;
    int b2 = (p1 >> (i + 1)) & 1;
    int b3 = (p2 >> i) & 1;
    int b4 = (p2 >> (i + 1)) & 1;
    if (b1 == 1 && b2 == 1 && b3 == 1 && b4 == 1) {
      return false;
    }
    if (b1 == 0 && b2 == 0 && b3 == 0 && b4 == 0) {
      return false;
    }
  }
  return true;
}

Matrix Binpower(Matrix matrix, BigInteger deg) {
  if (deg == 0) {
    return Matrix::IdMatr(matrix.size);
  }
  if (deg % 2 == 1) {
    return Binpower(matrix, deg - 1) * matrix;
  }
  Matrix bb = Binpower(matrix, deg / 2);
  return bb * bb;
}

int main() {
  BigInteger nn;
  int mm;
  std::cin >> nn >> mm >> mod;
  std::vector<std::vector<int>> dp((1 << mm), std::vector<int>((1 << mm), 0));
  for (int i = 0; i < (1 << mm); ++i) {
    for (int j = 0; j < (1 << mm); ++j) {
      if (Can(i, j, mm)) {
        dp[i][j] = 1;
      } else {
        dp[i][j] = 0;
      }
    }
  }
  Matrix matrix = Matrix(dp);
  matrix = Binpower(matrix, nn - 1);
  long long ans = 0;
  for (int i = 0; i < matrix.size; ++i) {
    for (int j = 0; j < matrix.size; ++j) {
      ans += matrix[i][j];
      ans %= mod;
    }
  }
  std::cout << ans << '\n';
}