#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);

    int *counts = (int *)malloc(sizeof(int) * N * N);
    int count = 0;

    while (scanf("%d", &counts[count]) == 1) {
        count++;
    }

    int i, j, index = 0, value = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (value == 0) {
                if (counts[index] == 0) {
                    printf("0");
                } else {
                    printf("1");
                }
                value = 1;
                index++;
            } else {
                if (counts[index] == 0) {
                    printf("1");
                } else {
                    printf("0");
                }
                value = 0;
                index++;
            }
        }
        printf("\n");
    }

    free(counts);
    return 0;
}