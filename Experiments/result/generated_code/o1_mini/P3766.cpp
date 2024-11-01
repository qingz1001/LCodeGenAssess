#include <stdio.h>
#include <math.h>

typedef unsigned long long ull;

// Precomputed zeta values up to k=60
double zeta_vals[61];

// Function to compute zeta(k) by summing terms until the term is less than 1e-20
void compute_zeta() {
    for(int k = 2; k <= 60; k++) {
        double sum = 0.0;
        double term;
        ull a = 1;
        while(1) {
            term = 1.0 / pow((double)a, (double)k);
            if(term <= 1e-20) break;
            sum += term;
            a++;
        }
        zeta_vals[k] = sum;
    }
}

// Function to compute a^k with overflow check
ull power_k(ull a, int k, ull n) {
    ull res = 1;
    for(int i = 0; i < k; i++) {
        if(a == 0) return 0;
        if(res > n / a) return n + 1;
        res *= a;
    }
    return res;
}

// Function to compute floor(n^(1/k)) using binary search
ull floor_root(ull n, int k) {
    ull low = 1, high = n, res = 1;
    while(low <= high) {
        ull mid = low + (high - low) / 2;
        ull p = power_k(mid, k, n);
        if(p <= n) {
            res = mid;
            low = mid + 1;
        }
        else {
            high = mid -1;
        }
    }
    return res;
}

int main(){
    int T;
    compute_zeta();
    if(scanf("%d", &T)!=1) return 0;
    while(T--){
        ull n;
        if(scanf("%llu", &n)!=1) return 0;
        double total = 0.0;
        for(int k =2; k <=60; k++){
            ull A = floor_root(n, k);
            if(A <2) break;
            double pow_term = pow((double)(A +1), (double)(k -1));
            double tail = 1.0 / ((double)(k -1) * pow_term);
            double s_kA = zeta_vals[k] -1.0 - tail;
            total += s_kA;
        }
        printf("%.14lf\n", total);
    }
    return 0;
}