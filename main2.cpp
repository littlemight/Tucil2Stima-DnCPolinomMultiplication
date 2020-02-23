#include "PolinomBF.hpp"
#include "PolinomDnC.hpp"
#include <iostream>
using namespace std;

long long pluscnt, mulcnt;

void reset() {
    pluscnt = mulcnt = 0;
}

int main() {
    int n;
    cout << "Masukkan N: ";
    cin >> n;
    
    PolinomBF a(n, 135), b(n, 182);
    clock_t start1 = clock();
    PolinomBF ab(a * b);
    clock_t stop1 = clock();
    double delta1 = (stop1 - start1) * 1./CLOCKS_PER_SEC;
    delta1 *= 1000;
    cout << "RUNTIME (BF): " << delta1 << " ms\n";
    cout << "PLUS COUNT: " << pluscnt << '\n';
    cout << "MUL COUNT: " << mulcnt << '\n';

    reset();
    
    PolinomDnC c(n, 135), d(n, 182);
    clock_t start2 = clock();
    PolinomDnC cd(c * d);
    clock_t stop2 = clock();
    double delta2 = (stop2 - start2) * 1./CLOCKS_PER_SEC;
    delta2 *= 1000;

    cout << '\n';

    cout << "RUNTIME (DnC): " << delta2 << " ms\n";
    cout << "PLUS COUNT: " << pluscnt << '\n';
    cout << "MUL COUNT: " << mulcnt << '\n';

    double ratio = delta1 / delta2;
    cout << '\n';
    cout << "RATIO TIMEBF/TIMEDNC: " << ratio << '\n';

    cout << ab << '\n' << cd << '\n';
    return 0;    
}