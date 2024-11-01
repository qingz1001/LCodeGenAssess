#include <stdio.h>

int main() {
    int M;
    scanf("%d", &M);

    for (int start = 1; start <= M / 2; start++) {
        int sum = 0;
        for (int end = start; end < M; end++) {
            sum += end;
            if (sum == M) {
                printf("%d %d\n", start, end);
                break;
            } else if (sum > M) {
                break;
            }
        }
    }

    return 0;
}