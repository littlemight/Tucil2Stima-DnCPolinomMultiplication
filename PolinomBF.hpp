#ifndef __POLINOMBF_H__
#define __POLINOMBF_H__

#include "Polinom.hpp"

class PolinomBF: public Polinom {
public:
    PolinomBF(): Polinom() {
    }

    PolinomBF(int n): Polinom(n) {
    }

    PolinomBF(int n, int seed): Polinom(n, seed) {
    }

    PolinomBF(const PolinomBF& other): Polinom(other) {
    }

    ~PolinomBF() {
    }

    friend PolinomBF operator*(const PolinomBF& p1, const PolinomBF& p2);
};


PolinomBF operator*(const PolinomBF& p1, const PolinomBF& p2) {
    PolinomBF ret(p1.n + p2.n, 0);
    for (int i = 0; i <= p1.n; i++) {
        for (int j = 0; j <= p2.n; j++) {
            ret[i + j] += p1[i] * p2[j];
            pluscnt++;
            mulcnt++;
        }
    }
    return ret;
}
#endif