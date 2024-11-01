#include <stdio.h>
#include <string.h>

int main() {
    int N;
    char S[105];
    scanf("%d %s", &N, S);

    for (int K = 1; K <= N; K++) {
        int count = 0;
        for (int i = 0; i <= N - K; i++) {
            int found = 0;
            for (int j = i + 1; j <= N - K; j++) {
                if (strncmp(S + i, S + j, K) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                count++;
            }
        }
        if (count == N - K + 1) {
            printf("%d\n", K);
            return 0;
        }
    }

    return 0;
}