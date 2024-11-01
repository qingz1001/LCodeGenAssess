#include <stdio.h>
#include <string.h>

int main() {
    int N;
    char sequence[101];
    scanf("%d", &N);
    scanf("%s", sequence);

    for (int K = 1; K <= N; K++) {
        int found = 0;
        for (int i = 0; i <= N - K; i++) {
            for (int j = i + 1; j <= N - K; j++) {
                if (strncmp(&sequence[i], &sequence[j], K) == 0) {
                    found = 1;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) {
            printf("%d\n", K);
            break;
        }
    }

    return 0;
}