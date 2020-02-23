#ifndef __POLINOM_H__
#define __POLINOM_H__

#include <algorithm>
#include <chrono>
#include <random>
#include <functional>
#include <iostream>
#include <iomanip>
using namespace std;

extern long long mulcnt, pluscnt;

class Polinom {
public:
    int n;
    int *a;

    Polinom() {
        n = 0;
    }

    Polinom(int n) {
        this->n = n;
        this->a = new int[n + 1];

        long long seed = chrono::high_resolution_clock::now().time_since_epoch().count();
        mt19937 eng;
        eng.seed(seed);
        uniform_int_distribution<int> range(-10, 10);
        for (int i = 0; i <= this->n; i++) {
            this->a[i] = range(eng);
        }
    }

    Polinom(int n, int seed) {
        this->n = n;
        this->a = new int[n + 1];
        if (seed != 0) {
            mt19937 eng;
            eng.seed(seed);
            uniform_int_distribution<int> range(-10, 10);
            for (int i = 0; i <= this->n; i++) {
                this->a[i] = range(eng);
            }   
        } else {
            for (int i = 0; i <= this->n; i++) {
                this->a[i] = 0;
            }
        }
    }

    Polinom(const Polinom& other) {
        this->a = new int[other.n + 1];
        this->n = other.n;
        for (int i = 0; i <= this->n; i++) {
            this->a[i] = other.a[i];
        }
    }

    ~Polinom() {
        delete[] this->a;
    }

    Polinom& operator=(const Polinom& other) {
        delete[] this->a;
        this->a = new int[other.n + 1];
        this->n = other.n;
        for (int i = 0; i <= this->n; i++) {
            this->a[i] = other.a[i];
        }
        return (*this);
    }

    int& operator[](int i) {
        return this->a[i];
    }

    const int& operator[](int i) const {
        return this->a[i];
    }

    friend Polinom operator+(const Polinom& p1, const Polinom& p2);
    friend Polinom operator-(const Polinom& p1, const Polinom& p2);
    friend ostream& operator<<(ostream& os, Polinom other);
    // friend Polinom mul_bf(Polinom& p1, Polinom& p2);
    // friend Polinom mul_dnf(const Polinom& p1, const Polinom& p2);
};


Polinom operator+(const Polinom& p1, const Polinom& p2) {
    Polinom ret(max(p1.n, p2.n), 0);
    for (int i = 0; i <= min(p1.n, p2.n); i++) {
        ret[i] = p1[i] + p2[i];
    }
    for (int i = min(p1.n, p2.n) + 1; i <= ret.n; i++) {
        if (i <= p1.n) {
            ret[i] = p1[i];
        } else {
            ret[i] = p2[i];
        }
    }
    return ret;
}

Polinom operator-(const Polinom& p1, const Polinom& p2) {
    Polinom ret(max(p1.n, p2.n), 0);
    for (int i = 0; i <= min(p1.n, p2.n); i++) {
        ret[i] = p1[i] - p2[i];
    }
    for (int i = min(p1.n, p2.n) + 1; i <= ret.n; i++) {
        if (i <= p1.n) {
            ret[i] = p1[i];
        } else {
            ret[i] = -p2[i];
        }
    }
    return ret;
}


ostream& operator<<(ostream& os, Polinom other) {
    bool first = true;
    for (int i = other.n; i >= 0; i--) {
        int val = other[i];
        if (val != 0) {
            if (first == true) {
                first = false;
                os << val;
            }  else {
                if (val > 0) {
                    os << " + ";
                } else {
                    os << " - ";
                }
                val = abs(val);
                if (val != 1) {
                    os << val;
                } else {
                    if (i == 0) {
                        os << val;
                    }
                }
            }

            if (i > 0) {
                os << 'x';
                if (i > 1) {
                    os << '^' << i;
                }
            }
        }
    }
    if (first) {
        os << 0;
    }
    return os;
}

// Polinom mul_bf(Polinom& p1, Polinom& p2) {
//     Polinom ret(p1.n + p2.n, 0);
//     for (int i = 0; i <= p1.n; i++) {
//         for (int j = 0; j <= p2.n; j++) {
//             ret[i + j] += p1[i] * p2[j];
//             pluscnt++;
//             mulcnt++;
//         }
//     }
//     return ret;
// }

// Polinom mul_dnc(const Polinom& p1, const Polinom& p2) {
//     if (p1.n <= 1) {
//         Polinom ret(p1.n + p2.n, 0);
//         for (int i = 0; i <= p1.n; i++) {
//             for (int j = 0; j <= p2.n; j++) {
//                 ret[i + j] += p1[i] * p2[j];
//                 pluscnt++;
//                 mulcnt++;
//             }
//         }
//         return ret;
//     }

//     int hn = p1.n / 2;
//     Polinom a0(hn - 1, 0), a1(p1.n - hn, 0);
//     Polinom b0(hn - 1, 0), b1(p1.n - hn, 0);
//     for (int i = 0; i <= hn - 1; i++) {
//         a0[i] = p1[i];
//         b0[i] = p2[i];
//     }
//     for (int i = hn; i <= p1.n; i++) {
//         a1[i - hn] = p1[i];
//         b1[i - hn] = p2[i];
//     }

//     Polinom u(mul_dnc(a0, b0));
//     Polinom z(mul_dnc(a1, b1));
//     Polinom y(mul_dnc(a0 + a1, b0 + b1));
//     Polinom ret(y.n + 2 * hn, 0);
//     for (int i = 0; i <= y.n; i++) {
//         if (i <= u.n) {
//             ret[i] += u[i];
//             ret[i + hn] -= u[i];
//             pluscnt += 2;
//         }
//         ret[i + hn] += y[i] - z[i];
//         ret[i + (2 * hn)] += z[i];
//         pluscnt += 3;
//     }
//     return ret;
// }
#endif