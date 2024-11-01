#include <stdio.h>
#include <string.h>

int main() {
    int N;
    char S[101];
    scanf("%d", &N);
    scanf("%s", S);

    int K = 1;
    while (K <= N) {
        int found = 0;
        for (int i = 0; i <= N - K; i++) {
            for (int j = i + K; j <= N - K; j++) {
                if (strncmp(S + i, S + j, K) == 0) {
                    found = 1;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) break;
        K++;
    }

    printf("%d\n", K);
    return 0;
}