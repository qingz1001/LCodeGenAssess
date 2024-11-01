#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 1500

typedef unsigned long long ull;

char prefix[MAXN + 1];
char result[MAXN + 1];

ull binary_value(char *s, int len) {
    ull value = 0;
    for (int i = 0; i < len; i++) {
        value = (value << 1) + (s[i] - '0');
    }
    return value;
}

int compare(const void *a, const void *b) {
    ull val_a = binary_value((char *)a, strlen((char *)a));
    ull val_b = binary_value((char *)b, strlen((char *)b));
    return (val_a > val_b) - (val_a < val_b);
}

void generate_combinations(char *prefix, int n, char *buffer, int index, char **results, int *count) {
    if (index == n) {
        strcpy(results[(*count)++], buffer);
        return;
    }
    buffer[index] = '0';
    generate_combinations(prefix, n, buffer, index + 1, results, count);
    buffer[index] = '1';
    generate_combinations(prefix, n, buffer, index + 1, results, count);
}

void solve(int n) {
    int total_combinations = 1 << n;
    char **combinations = (char **)malloc(total_combinations * sizeof(char *));
    for (int i = 0; i < total_combinations; i++) {
        combinations[i] = (char *)malloc((n + 1) * sizeof(char));
    }

    char buffer[MAXN + 1];
    int count = 0;
    generate_combinations("", n, buffer, 0, combinations, &count);

    qsort(combinations, count, sizeof(char *), compare);

    for (int i = 0; i < count; i++) {
        printf("%s\n", combinations[i]);
        free(combinations[i]);
    }
    free(combinations);
}

int main() {
    int n;
    scanf("%s", prefix);
    n = strlen(prefix);
    solve(n);
    return 0;
}