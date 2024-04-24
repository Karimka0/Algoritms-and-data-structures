#include <iostream>
#include <vector>

const long long kMod = 1000000007;

struct Matrix {
    std::vector<std::vector<long long>> matr;
    long long sz1;
    long long sz2;

    Matrix(long long sz1, long long sz2, long long value)
            : matr(sz1, std::vector<long long>(sz2, value)), sz1(sz1), sz2(sz2) {}

    Matrix(std::vector<std::vector<long long>> vec) : matr(vec), sz1(vec[0].size()), sz2(vec.size()) {}

    Matrix(long long nn, long long mm): matr(nn, std::vector<long long>(mm, 0)), sz1(nn), sz2(mm){}

    static Matrix IdMatr(long long size) {
        Matrix ee(size, size, 0);
        for (long long i = 0; i < size; ++i) {
            ee.matr[i][i] = 1;
        }
        return ee;
    }

    Matrix operator*(const Matrix& other) {
        Matrix result(sz1, other.sz2, 0);
        for (long long i = 0; i < sz1; ++i) {
            for (long long j = 0; j < other.sz2; ++j) {
                for (long long k = 0; k < sz2; ++k) {
                    result[i][j] += matr[i][k] * other[k][j];
                    result[i][j] %= kMod;
                }
            }
        }
        return result;
    }

    Matrix Sew(long long height) {
        Matrix result(height, sz2);
        if (height < sz1) {
            for (long long i = 0; i < height; ++i) {
                result[i] = matr[i + sz1 - height];
            }
        } else {
            for (long long i = 0; i < height - sz1; ++i) {
                result[i] = {0};
            }
            for (long long i = height - sz1; i < height; ++i) {
                result[i] = matr[i - height + sz1];
            }
        }
        return result;
    }

    std::vector<long long>& operator[](long long index) { return matr[index]; }
    const std::vector<long long>& operator[](long long index) const { return matr[index]; }
};

Matrix Binpower(Matrix matrix, long long deg) {
    if (deg == 0) {
        return Matrix::IdMatr(matrix.sz1);
    }
    if (deg % 2 == 1) {
        return Binpower(matrix, deg - 1) * matrix;
    }
    Matrix bb = Binpower(matrix, deg / 2);
    return bb * bb;
}

int main() {
    long long cnt;
    long long end;
    std::cin >> cnt >> end;
    Matrix result(1, 1, 1);
    long long aa;
    long long bb;
    long long cc;
    for(long long i = 0; i < cnt; ++i) {
        std::cin >> aa >> bb >> cc;
        if (i == cnt - 1) {
            bb = std::min(end, bb);
        }
        result = result.Sew(cc + 1);
        Matrix now(cc + 1, cc + 1, 0);
        for (long long j = 0; j < cc + 1; ++j) {
            for (long long k = 0; k < cc + 1; ++k) {
                if (std::abs(k - j) <= 1) {
                    now[j][k] = 1;
                }
            }
        }
        now = Binpower(now, bb - aa);
        result = now * result;
    }
    std::cout << result[result.sz1 - 1][0];
}