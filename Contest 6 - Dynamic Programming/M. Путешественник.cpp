#include <iostream>
#include <vector>

long long const kMod = 1000000009;

struct Matrix {
    long long vec[4];

    Matrix(long long aa, long long bb, long long cc, long long dd) {
        vec[0] = aa;
        vec[1] = bb;
        vec[2] = cc;
        vec[3] = dd;
    }

    long long operator[](long long nn) { return vec[nn]; }
};

Matrix operator*(const Matrix& left, const Matrix& right) {
    long long aa =
            ((left.vec[0] * right.vec[0] + left.vec[1] * right.vec[2]) % kMod +
             kMod) %
            kMod;
    long long bb =
            ((left.vec[0] * right.vec[1] + left.vec[1] * right.vec[3]) % kMod +
             kMod) %
            kMod;
    long long cc =
            ((right.vec[0] * left.vec[2] + right.vec[2] * left.vec[3]) % kMod +
             kMod) %
            kMod;
    long long dd =
            ((left.vec[3] * right.vec[3] + right.vec[1] * left.vec[2]) % kMod +
             kMod) %
            kMod;
    return {aa, bb, cc, dd};
}

Matrix Binpower(Matrix matrix, long long deg) {
    if (deg == 0) {
        return {1, 0, 0, 1};
    }
    if (deg % 2 == 1) {
        return Binpower(matrix, deg - 1) * matrix;
    }
    Matrix bb = Binpower(matrix, deg / 2);
    return bb * bb;
}

long long Ways(long long xx, long long yy, long long cc) {
    long long deg = yy - xx - cc;
    if (deg < 0) {
        return 0;
    }
    Matrix fib(1, 1, 1, 0);
    Matrix fib_n = Binpower(fib, deg);
    return (fib_n[0] % kMod + kMod) % kMod;
}

struct Triple {
    long long xx;
    long long yy;
    long long ways;
};

int main() {
    int cnt;
    int qq;
    std::cin >> cnt >> qq;
    std::vector<Triple> airports(cnt);
    for (int i = 0; i < cnt; ++i) {
        Triple now{};
        std::cin >> now.xx >> now.yy >> now.ways;
        now.ways %= kMod;
        airports[i] = now;
    }
    for (int i = 0; i < qq; ++i) {
        long long cc;
        std::cin >> cc;
        long long result = 0;
        for (int j = 0; j < cnt; ++j) {
            result += ((airports[j].ways *
                        (Ways(airports[j].xx, airports[j].yy, cc) % kMod)) %
                       kMod +
                       kMod) %
                      kMod;
        }
        result %= kMod;
        if (result < 0) {
            result += kMod;
        }
        std::cout << result << "\n";
    }
}