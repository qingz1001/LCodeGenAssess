#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200

typedef __int128 int128;

double variance(int128 *arr, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    double mean = sum / n;
    double var = 0.0;
    for (int i = 0; i < n; i++) {
        var += (arr[i] - mean) * (arr[i] - mean);
    }
    return var / n;
}

void generate_min_toxicity_suffix(const char *prefix, int n) {
    int128 values[1 << n];
    int count = 0;

    for (int i = 0; i < (1 << n); i++) {
        int128 value = 0;
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) != 0) {
                value |= (1LL << (n - j - 1));
            } else {
                value |= (0LL << (n - j - 1));
            }
        }
        for (int j = 0; j <= n; j++) {
            int128 subvalue = 0;
            for (int k = 0; k < j; k++) {
                subvalue <<= 1;
                if (k < n && prefix[k] == '1') {
                    subvalue |= 1;
                }
            }
            subvalue <<= (n - j);
            subvalue |= value;
            values[count++] = subvalue;
        }
    }

    qsort(values, count, sizeof(int128), [](const void *a, const void *b) {
        return (*(int128 *)a - *(int128 *)b);
    });

    int min_variance = INT_MAX;
    for (int i = 0; i < count; i++) {
        int128 *subvalues = malloc((n + 1) * sizeof(int128));
        int subcount = 0;
        for (int j = 0; j <= n; j++) {
            subvalues[subcount++] = values[i] >> (n - j);
        }
        double var = variance(subvalues, n + 1);
        free(subvalues);
        if (var < min_variance) {
            min_variance = var;
        }
    }

    for (int i = 0; i < count; i++) {
        int128 *subvalues = malloc((n + 1) * sizeof(int128));
        int subcount = 0;
        for (int j = 0; j <= n; j++) {
            subvalues[subcount++] = values[i] >> (n - j);
        }
        double var = variance(subvalues, n + 1);
        free(subvalues);
        if (var == min_variance) {
            printf("%s\n", prefix);
        }
    }
}

int main() {
    int n;
    char prefix[MAXN];

    scanf("%d %s", &n, prefix);

    generate_min_toxicity_suffix(prefix, n);

    return 0;
}