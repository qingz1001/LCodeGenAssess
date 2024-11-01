#include <stdio.h>
#include <string.h>

#define MAXN 5000001

int main() {
    int N;
    char S[MAXN];
    scanf("%d\n", &N);
    fgets(S, sizeof(S), stdin);

    // Remove newline characters from the input string
    for (int i = 0; i < N; ++i) {
        if (S[i] == '\n') {
            S[i] = '\0';
            break;
        }
    }

    // Find all rotations of the string and store them in a sorted array
    char rotations[N * 2];
    for (int i = 0; i < N; ++i) {
        strncpy(rotations + i * N, S + i, N);
        rotations[i * N + N - 1] = '\0';
    }
    qsort(rotations, N, N, strcmp);

    // Find the lexicographically smallest rotation
    char min_rotation[N + 1];
    strncpy(min_rotation, rotations, N);
    min_rotation[N] = '\0';

    // Find the position of the first character of the smallest rotation in the original string
    int pos = 0;
    while (pos < N && S[pos] != min_rotation[0]) {
        ++pos;
    }

    // Calculate the password
    int password = pos - 1;

    printf("%d\n", password);

    return 0;
}