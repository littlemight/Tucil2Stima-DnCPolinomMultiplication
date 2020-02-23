#ifndef __POLINOMDNC_H__
#define __POLINOMDNC_H__

#include "Polinom.hpp"

class PolinomDnC: public Polinom {
public:
    PolinomDnC(): Polinom() {
    }

    PolinomDnC(int n): Polinom(n) {
    }

    PolinomDnC(int n, int seed): Polinom(n, seed) {
    }

    PolinomDnC(const PolinomDnC& other): Polinom(other) {
    }

    ~PolinomDnC() {
    }

    friend PolinomDnC operator+(const PolinomDnC& p1, const PolinomDnC& p2);
    friend PolinomDnC operator*(const PolinomDnC& p1, const PolinomDnC& p2);
};

PolinomDnC operator+(const PolinomDnC& p1, const PolinomDnC& p2) {
    PolinomDnC ret(max(p1.n, p2.n), 0);
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

PolinomDnC operator*(const PolinomDnC& p1, const PolinomDnC& p2) {
    if (p1.n <= 1) {
        PolinomDnC ret(p1.n + p2.n, 0);
        for (int i = 0; i <= p1.n; i++) {
            for (int j = 0; j <= p2.n; j++) {
                ret[i + j] += p1[i] * p2[j];
                pluscnt++;
                mulcnt++;
            }
        }
        return ret;
    }

    int hn = p1.n / 2;
    PolinomDnC a0(hn - 1, 0), a1(p1.n - hn, 0);
    PolinomDnC b0(hn - 1, 0), b1(p1.n - hn, 0);
    for (int i = 0; i <= hn - 1; i++) {
        a0[i] = p1[i];
        b0[i] = p2[i];
    }
    for (int i = hn; i <= p1.n; i++) {
        a1[i - hn] = p1[i];
        b1[i - hn] = p2[i];
    }

    PolinomDnC u(a0 * b0);
    PolinomDnC z(a1 * b1);
    PolinomDnC y((a0 + a1) * (b0 + b1));
    PolinomDnC ret(y.n + 2 * hn, 0);
    for (int i = 0; i <= y.n; i++) {
        if (i <= u.n) {
            ret[i] += u[i];
            ret[i + hn] -= u[i];
            pluscnt += 2;
        }
        ret[i + hn] += y[i] - z[i];
        ret[i + (2 * hn)] += z[i];
        pluscnt += 3;
    }
    return ret;
}
#endif