#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1501

typedef long long ll;
typedef __int128 i128;

ll n;
char prefix[MAXN];
char suffix[MAXN];

void calculate_variance(i128 *values, int size, double *mean, double *variance) {
    *mean = 0;
    for (int i = 0; i < size; i++) {
        *mean += values[i];
    }
    *mean /= size;

    *variance = 0;
    for (int i = 0; i < size; i++) {
        i128 diff = values[i] - *mean;
        *variance += diff * diff;
    }
    *variance /= size;
}

int compare(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int main() {
    scanf("%s", prefix);
    n = strlen(prefix);

    double min_variance = 1e18;
    char best_suffix[MAXN][MAXN];

    for (int i = 0; i < (1 << n); i++) {
        sprintf(suffix, "%d", i);
        if (strlen(suffix) != n) continue;

        i128 values[n + 1];
        for (int j = 0; j <= n; j++) {
            values[j] = 0;
            for (int k = 0; k < n; k++) {
                values[j] = (values[j] << 1) | (prefix[k + j % n] == '1');
            }
        }

        double mean, variance;
        calculate_variance(values, n + 1, &mean, &variance);

        if (variance < min_variance || (variance == min_variance && strcmp(suffix, best_suffix[0]) < 0)) {
            min_variance = variance;
            strcpy(best_suffix[0], suffix);
        } else if (variance == min_variance) {
            strcat(best_suffix[0], "\n");
            strcat(best_suffix[0], suffix);
        }
    }

    qsort(best_suffix[0], strlen(best_suffix[0]), sizeof(char), compare);
    printf("%s\n", best_suffix[0]);

    return 0;
}