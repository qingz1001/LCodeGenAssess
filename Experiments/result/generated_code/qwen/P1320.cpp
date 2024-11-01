#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    printf("%d ", N);

    int count = 1, prev = 0;
    for (int i = 0; i < N * N; ++i) {
        char ch;
        scanf(" %c", &ch);
        if (ch == prev) {
            count++;
        } else {
            printf("%d ", count);
            prev = ch;
            count = 1;
        }
    }
    printf("%d\n", count);

    return 0;
}