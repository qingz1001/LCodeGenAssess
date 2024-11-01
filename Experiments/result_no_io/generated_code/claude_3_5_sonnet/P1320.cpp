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

    printf("%d ", N);

    int count = 0;
    char current = '0';
    int index = 0;

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

    for (int i = 0; i < index; i++) {
        printf("%d ", compressed[i]);
    }

    return 0;
}