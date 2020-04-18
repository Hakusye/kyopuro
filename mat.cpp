#include <bits/stdc++.h>

/**
 * @brief standard operations for M x N matrix.
 */
template <size_t M = 0, size_t N = 0> class Mat {
public:
  std::array<std::array<double, N>, M> data;

  /**
   * @brief constructor by initializer-list
   */
  Mat(std::initializer_list<double> _data) {
    auto it = _data.begin();
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) 
        data[i][j] = *it++;
    }
  }

  /**
   * @brief constructor by 1-d array
   */
  Mat(double _data[M * N]) {
    size_t k = 0;
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++)
        data[i][j] = _data[k++];
    }
  }

  /**
   * @brief constructor by std::array
   */
  Mat(std::array<std::array<double, N>, M> &_data) {
    data = _data;
  }

  /**
   * @brief constructor makes zero matrix
   */
  Mat() {
    for (size_t m = 0; m < M; m++) {
      for (size_t n = 0; n < N; n++) {
        data[m][n] = 0;
      }
    }
  }

  /**
   * @brief returns scalar value if mat is 1 x 1 matrix.
   */
  double scalarize() {
    throw std::runtime_error("スカラーに変換できません");
  }

  /**
   * @brief returns [index]th element if mat is vector.
   */
  double _(size_t index) {
    if (N != 1)
      throw std::runtime_error("ベクトルではありません");
    return data[index - 1][0];
  }

  /**
   * @brief returns the [i], [j] element of the matrix.
   */
  inline double at(size_t i, size_t j) {
    return data[i][j];
  }

  /**
   * @brief returns a identity matrix.
   */
  template <size_t K>
  static Mat<K, K> E() {
    Mat<K, K> e{};
    for (size_t i = 0; i < K; i++) {
      e.data[i][i] = 1;
    }
    return e;
  }

  /**
   * @brief returns inverse matrix by using sweep out method.
   */
  Mat<M, N> operator~() {
    if (M != N)
      throw std::runtime_error("逆行列を定義できません");
    if (M == 2 && N == 2) {
      const double a = at(0, 0), b = at(0, 1), c = at(1, 0), d = at(1, 1);
      return Mat<2, 2>{d, -b, -c, a} / (a * d - b * c);
    }

    auto inv_a = E<N>(), cp = Mat<M, N>(data);

    for (size_t i = 0; i < N; i++) {
      if(cp.data[i][i] == 0)
        throw std::runtime_error("逆行列が存在しません");
      double buf = 1 / cp.data[i][i];
      for (size_t j = 0; j < N; j++) {
        cp.data[i][j] *= buf;
        inv_a.data[i][j] *= buf;
      }

      for (size_t j = 0; j < N; j++) {
        if (i != j) {
          buf = cp.data[j][i];
          for (size_t k = 0; k < N; k++) {
            cp.data[j][k] -= cp.data[i][k] * buf;
            inv_a.data[j][k] -= inv_a.data[i][k] * buf;
          }
        }
      }
    }
    return inv_a;
  }

  /**
   * @brief returns the determinant of the matrix.
   */
  double det() {
    if (M != N)
      throw std::runtime_error("行列式を定義できません");

    auto cp = Mat<M, N>(data);
    // 三角行列を作成
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < N; j++) {
        if (i < j) {
          double buf = cp.data[j][i] / cp.data[i][i];
          for (size_t k = 0; k < N; k++) {
            cp.data[j][k] -= cp.data[i][k] * buf;
          }
        }
      }
    }
    // 対角成分の積
    return cp.tr();
  }

  /**
   * @brief returns the norm of the matrix.
   */
  double norm() {
    if (N != 1)
      throw std::runtime_error("ノルムを定義できません");
    double norm = 0.0;
    for (size_t i = 0; i < M; i++) {
      norm += data[i][0] * data[i][0];
    }
    return sqrt(norm);
  }

  /**
   * @brief returns the transposed matrix.
   */
  Mat<N, M> operator!() {
    Mat<N, M> transposed;
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        transposed.data[j][i] = data[i][j];
      }
    }
    return transposed;
  }

  /**
   * @brief returns the matrix elements makes negative.
   */
  Mat<M, N> operator-() {
    Mat<M, N> mat;
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        mat.data[i][j] = -data[i][j];
      }
    }
    return mat;
  }

  /**
   * @brief returns the trace of the matrix.
   */
  double tr() {
    if (M != N)
      throw std::runtime_error("トレースを定義できません");

    int prod = 1;
    for (size_t i = 0; i < N; i++) {
      prod *= data[i][i];
    }
    return prod;
  }

  /**
   * @brief returns the product with [other].
   */
  template <size_t K>
  Mat<M, K> operator*(Mat<N, K> other) {
    Mat<M, K> c{};
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < K; j++) {
        for (size_t k = 0; k < N; k++) {
          c.data[i][j] += data[i][k] * other.data[k][j];
        }
      }
    }
    return c;
  }

  /**
   * @brief returns equally with [other]
   */
  bool operator==(Mat<M, N> other) {
    return data == other.data;
  }

  /**
   * @brief returns the multiplies with [k]
   */
  Mat<M, N> operator*(double k) {
    Mat<M, N> b{};
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        b.data[i][j] = data[i][j] * k;
      }
    }
    return b;
  }

  /**
   * @brief returns the multiplies with [k], targeted 1 x 1 mat.
   */
  Mat<M, N> operator*(Mat<1, 1> k) {
    return *this * k.data[0][0];
  }

  /**
   * @brief returns the division by [k]
   */
  Mat<M, N> operator/(double k) {
    Mat<M, N> b{};
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        b.data[i][j] = data[i][j] / k;
      }
    }
    return b;
  }

  /**
   * @brief returns the multiplies with [k], targeted 1 x 1 mat.
   */
  Mat<M, N> operator/(Mat<1, 1> k) {
    return *this / k.data[0][0];
  }

  /**
   * @brief returns the summation with [other]
   */
  Mat<M, N> operator+(Mat<M, N> other) {
    Mat<M, N> c{};
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        c.data[i][j] = data[i][j] + other.data[i][j];
      }
    }
    return c;
  }

  /**
   * @brief assigns the summation with [other]
   */
  void operator+=(Mat<M, N> other) {
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        data[i][j] += other.data[i][j];
      }
    }
  }

  /**
   * @brief assigns the difference with [other]
   */
  void operator-=(Mat<M, N> other) {
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        data[i][j] -= other.data[i][j];
      }
    }
  }

  /**
   * @brief returns the difference with [other]
   */
  Mat<M, N> operator-(Mat<M, N> other) {
    Mat<M, N> c{};
    for (size_t i = 0; i < M; i++) {
      for (size_t j = 0; j < N; j++) {
        c.data[i][j] = data[i][j] - other.data[i][j];
      }
    }
    return c;
  }
}; 

/**
 * @brief inspect matrix values
 */
template <size_t M, size_t N>
std::ostream &operator<<(std::ostream &out, Mat<M, N> const &mat) {
  out << std::endl;
  for (auto l : mat.data) {
    for (auto c : l) {
      out << std::setw(3) << c << " ";
    }
    out << std::endl;
  }
  std::cout << std::endl;
  return out;
}

/**
 * @brief to scalar value
 */
template <>
double Mat<1, 1>::scalarize() {
  return data[0][0];
}

/**
 * @brief test helper
 */
template <class T>
bool test(T given, T expect) {
  if (!(given == expect)) {
    std::cout << "[given]\n"
    << given << std::endl
    << "[expect]\n"
    << expect;
    return false;
  }
  return true;
}

/**
 * @brief test code
 */
void unit_test() {
  auto A = Mat<2, 2>{
    1, 2, 
    3, 4
  },
  auto B = Mat<2, 2>{
    5, 6, 
    7, 8
  };
  test(A + B, Mat<2, 2>{6, 8, 10, 12});
  test(A - B, Mat<2, 2>{-4, -4, -4, -4});
  test(A * B, Mat<2, 2>{19, 22, 43, 50});
  test(-A, Mat<2, 2> {-1, -2, -3, -4});
  test(!A, Mat<2, 2>{1, 3, 2, 4});
  test(A * 2, Mat<2, 2>{2, 4, 6, 8});
  test(A / 2, Mat<2, 2>{0.5, 1, 1.5, 2});
  auto V = Mat<2, 1> { 3, 4 };
  test(V.norm(), 5.0);
}