#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int line = 1;
    while (N > line) {
        N -= line;
        line++;
    }

    if (line % 2 == 0) {
        printf("%d/%d\n", N, line - N + 1);
    } else {
        printf("%d/%d\n", line - N + 1, N);
    }

    return 0;
}