#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 500000
#define MAX_P 2000000000

long long m[MAX_N];
int n, k;

int check(long long p) {
    int shots = 0;
    long long damage[MAX_N] = {0};
    
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            damage[i] = damage[i-1];
        }
        
        if (damage[i] < m[i]) {
            long long needed = m[i] - damage[i];
            int curr_shots = (needed + p - 1) / p;
            shots += curr_shots;
            
            if (shots > k) {
                return 0;
            }
            
            damage[i] += curr_shots * p;
            
            for (int j = i + 1; j < n && j - i <= p; j++) {
                damage[j] += curr_shots * (p - (j - i) * (j - i));
            }
        }
    }
    
    return 1;
}

long long binary_search() {
    long long left = 1, right = MAX_P, mid;
    
    while (left < right) {
        mid = left + (right - left) / 2;
        
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

int main() {
    scanf("%d %d", &n, &k);
    
    for (int i = 0; i < n; i++) {
        scanf("%lld", &m[i]);
    }
    
    printf("%lld\n", binary_search());
    
    return 0;
}