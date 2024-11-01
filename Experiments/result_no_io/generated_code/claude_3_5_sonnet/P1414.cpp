#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10000
#define MAX_INF 1000000

int n;
int abilities[MAX_N];
int gcd_table[MAX_INF + 1];
int result[MAX_N + 1];

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void precompute_gcd() {
    for (int i = 1; i <= MAX_INF; i++) {
        gcd_table[i] = i;
    }
    for (int i = 2; i <= MAX_INF; i++) {
        if (gcd_table[i] == i) {
            for (int j = i; j <= MAX_INF; j += i) {
                gcd_table[j] = gcd(gcd_table[j], i);
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &abilities[i]);
    }
    
    precompute_gcd();
    
    memset(result, 0, sizeof(result));
    
    for (int mask = 1; mask < (1 << n); mask++) {
        int group_gcd = 0;
        int count = 0;
        
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (group_gcd == 0) {
                    group_gcd = abilities[i];
                } else {
                    group_gcd = gcd(group_gcd, abilities[i]);
                }
                count++;
            }
        }
        
        if (group_gcd > result[count]) {
            result[count] = group_gcd;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        printf("%d\n", result[i]);
    }
    
    return 0;
}