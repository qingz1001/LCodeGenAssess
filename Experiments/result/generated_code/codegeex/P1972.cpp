#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000

int read_int() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}

int main() {
    int n = read_int();
    int a[MAX_N + 1];
    for (int i = 1; i <= n; i++) {
        a[i] = read_int();
    }

    int m = read_int();
    int queries[MAX_M][2];
    for (int i = 0; i < m; i++) {
        queries[i][0] = read_int();
        queries[i][1] = read_int();
    }

    // Initialize the last occurrence array
    int last_occurrence[MAX_N + 1];
    for (int i = 0; i <= MAX_N; i++) {
        last_occurrence[i] = 0;
    }

    // Process each query using Mo's algorithm
    for (int i = 0; i < m; i++) {
        int l = queries[i][0];
        int r = queries[i][1];

        // Calculate the answer for the current query
        int distinct_count = 0;
        for (int j = l; j <= r; j++) {
            if (last_occurrence[a[j]] < l) {
                distinct_count++;
            }
            last_occurrence[a[j]] = j;
        }

        // Output the result for the current query
        printf("%d\n", distinct_count);
    }

    return 0;
}