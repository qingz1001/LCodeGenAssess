#include <stdio.h>
#include <string.h>

#define MAX_N 105

int main() {
    int N;
    char colors[MAX_N];
    
    scanf("%d", &N);
    scanf("%s", colors);
    
    for (int K = 1; K <= N; K++) {
        int count = 0;
        for (int i = 0; i + K - 1 < N; i++) {
            int found = 0;
            for (int j = 0; j + K - 1 < N; j++) {
                if (i != j && strncmp(colors + i, colors + j, K) == 0) {
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