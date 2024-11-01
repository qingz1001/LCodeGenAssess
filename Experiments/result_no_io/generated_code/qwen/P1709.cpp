#include <stdio.h>
#include <string.h>

#define MAX_N 5000000
#define BUFFER_SIZE 80

int main() {
    int N;
    scanf("%d", &N);
    char S[MAX_N + 1];
    char buffer[BUFFER_SIZE];
    int index = 0;

    while (fgets(buffer, BUFFER_SIZE, stdin)) {
        for (int i = 0; i < strlen(buffer); ++i) {
            if (buffer[i] != '\n') {
                S[index++] = buffer[i];
            }
        }
    }

    S[index] = '\0';

    char result[MAX_N + 1];
    int min_index = -1;

    for (int i = 0; i < N; ++i) {
        snprintf(result, sizeof(result), "%.*s%s", N - i, S + i, S);
        for (int j = 0; j < N; ++j) {
            if (result[j] < result[min_index] || min_index == -1) {
                min_index = j;
            }
        }
    }

    printf("%d\n", min_index);

    return 0;
}