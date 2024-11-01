#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20000

int main() {
    bool is_prime[MAX + 1];
    for(int i = 0; i <= MAX; i++) is_prime[i] = true;
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i*i <= MAX; i++) {
        if(is_prime[i]) {
            for(int j = i*i; j <= MAX; j += i) is_prime[j] = false;
        }
    }

    int n;
    scanf("%d", &n);

    for(int p1 = 2; p1 <= n-4; p1++) {
        if(is_prime[p1]) {
            for(int p2 = p1; p2 <= n-p1-2; p2++) {
                if(is_prime[p2]) {
                    int p3 = n - p1 - p2;
                    if(p3 >= p2 && is_prime[p3]) {
                        printf("%d %d %d", p1, p2, p3);
                        return 0;
                    }
                }
            }
        }
    }

    return 0;
}