#include <stdio.h>
#include <math.h>

int main() {
    int M;
    scanf("%d", &M);

    for (int start = 1; start <= M / 2; start++) {
        int sum = 0;
        int end = start;

        while (sum < M) {
            sum += end;
            if (sum == M && end > start) {
                printf("%d %d\n", start, end);
                break;
            }
            end++;
        }
    }

    return 0;
}