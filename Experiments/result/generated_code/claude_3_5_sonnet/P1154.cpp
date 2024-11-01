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
    int i, j, K;
    
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }
    
    K = S[1] - S[0];
    for (i = 2; i < N; i++) {
        K = abs(gcd(K, S[i] - S[0]));
    }
    
    for (i = K; i > 0; i--) {
        int hash[MAX_S] = {0};
        int flag = 1;
        for (j = 0; j < N; j++) {
            int index = S[j] % i;
            if (hash[index]) {
                flag = 0;
                break;
            }
            hash[index] = 1;
        }
        if (flag) {
            K = i;
            break;
        }
    }
    
    printf("%d\n", K);
    
    return 0;
}