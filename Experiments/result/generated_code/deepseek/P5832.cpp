#include <stdio.h>
#include <string.h>

int main() {
    int N;
    char sequence[101];
    scanf("%d", &N);
    scanf("%s", sequence);

    for (int K = 1; K <= N; K++) {
        int unique = 1;
        for (int i = 0; i <= N - K; i++) {
            for (int j = i + 1; j <= N - K; j++) {
                if (strncmp(&sequence[i], &sequence[j], K) == 0) {
                    unique = 0;
                    break;
                }
            }
            if (!unique) break;
        }
        if (unique) {
            printf("%d\n", K);
            break;
        }
    }

    return 0;
}