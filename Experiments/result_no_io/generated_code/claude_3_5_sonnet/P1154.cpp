#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000
#define MAX_S 1000000

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int N, S[MAX_N];
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }
    
    int K = S[1] - S[0];
    for (int i = 2; i < N; i++) {
        K = abs(gcd(K, S[i] - S[0]));
    }
    
    for (int i = K; i <= MAX_S; i++) {
        int hash[MAX_S] = {0};
        int valid = 1;
        
        for (int j = 0; j < N; j++) {
            int index = S[j] % i;
            if (hash[index]) {
                valid = 0;
                break;
            }
            hash[index] = 1;
        }
        
        if (valid) {
            printf("%d\n", i);
            break;
        }
    }
    
    return 0;
}