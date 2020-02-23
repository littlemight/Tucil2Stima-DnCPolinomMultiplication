#include <bits/stdc++.h>
#include "Polinom.hpp"
using namespace std;

long long pluscnt, mulcnt;

void reset() {
    pluscnt = mulcnt = 0;
}

int main() {
    cout << fixed << setprecision(9);
    int n;
    cout << "Masukkan derajat: ";
    cin >> n;
    Polinom a(n, 135), b(n, 182);

    clock_t start1 = clock();
    Polinom tm1(mul_bf(a, b));
    clock_t stop1 = clock();
    double delta1 = (stop1 - start1) * 1./CLOCKS_PER_SEC;
    delta1  *= 1000;
    cout << "RUNTIME (BF): " << delta1 << " ms\n";
    cout << "PLUS COUNT: " << pluscnt << '\n';
    cout << "MUL COUNT: " << mulcnt << '\n';

    reset();
    clock_t start2 = clock();
    Polinom tm2(mul_dnc(a, b));
    clock_t stop2 = clock();
    double delta2 = (stop2 - start2) * 1./CLOCKS_PER_SEC;
    delta2 *= 1000;

    cout << '\n';

    cout << "RUNTIME (DnC): " << delta2 << " ms\n";
    cout << "PLUS COUNT: " << pluscnt << '\n';
    cout << "MUL COUNT: " << mulcnt << '\n';

    // cout << tm1 << '\n' << tm2 << '\n';
    return 0;
}