#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int count = 0, current = 0;
    for (int i = 0; i < N * N; ++i) {
        int num;
        scanf("%d", &num);
        if (num == current) {
            count++;
        } else {
            printf("%d", current);
            count = 1;
            current = num;
        }
    }
    printf("%d\n", current);
    return 0;
}