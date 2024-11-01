#include <stdio.h>
#include <string.h>

#define MAX_N 200

char matrix[MAX_N][MAX_N + 1];
int compressed[MAX_N * MAX_N + 1];

int main() {
    int N = 0;
    while (scanf("%s", matrix[N]) != EOF) {
        N++;
    }

    int count = 0;
    int index = 1;
    char current = '0';

    compressed[0] = N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == current) {
                count++;
            } else {
                compressed[index++] = count;
                count = 1;
                current = matrix[i][j];
            }
        }
    }

    compressed[index++] = count;

    printf("%d", compressed[0]);
    for (int i = 1; i < index; i++) {
        printf(" %d", compressed[i]);
    }
    printf("\n");

    return 0;
}