#include <stdio.h>

int main() {
    int M, P, A, O, S, U;
    scanf("%d %d %d %d %d %d", &M, &P, &A, &O, &S, &U);

    long long S_mod = 0;
    for (int i = 0; i <= M; i++) {
        long long happiness = 1;
        for (int j = 0; j < A; j++) {
            happiness = (happiness * (O * i * i + S * i + U)) % P;
        }
        S_mod = (S_mod + happiness) % P;
    }

    printf("%lld\n", S_mod);
    return 0;
}