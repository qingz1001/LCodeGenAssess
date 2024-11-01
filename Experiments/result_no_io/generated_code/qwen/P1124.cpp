#include <stdio.h>
#include <string.h>

#define MAXN 10005

int main() {
    int n, p;
    char S[MAXN], S_prime[MAXN];

    scanf("%d", &n);
    scanf("%s", S_prime);
    scanf("%d", &p);

    for (int i = 0; i < n; i++) {
        S[i] = S_prime[(i + p) % n];
    }

    printf("%s\n", S);

    return 0;
}