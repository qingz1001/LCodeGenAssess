#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CURRENCIES 30
#define MAX_NAME_LENGTH 20
#define EPSILON 1e-9

char currencies[MAX_CURRENCIES][MAX_NAME_LENGTH];
double rates[MAX_CURRENCIES][MAX_CURRENCIES];
int n;

int find_currency(char *name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(currencies[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

bool floyd_warshall() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (rates[i][k] * rates[k][j] > rates[i][j]) {
                    rates[i][j] = rates[i][k] * rates[k][j];
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (rates[i][i] > 1.0 + EPSILON) {
            return true;
        }
    }
    return false;
}

int main() {
    int case_num = 1;
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        for (int i = 0; i < n; i++) {
            scanf("%s", currencies[i]);
            for (int j = 0; j < n; j++) {
                rates[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }

        int m;
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            char source[MAX_NAME_LENGTH], dest[MAX_NAME_LENGTH];
            double rate;
            scanf("%s %lf %s", source, &rate, dest);
            int src_idx = find_currency(source);
            int dest_idx = find_currency(dest);
            rates[src_idx][dest_idx] = rate;
        }

        printf("Case %d: %s\n", case_num++, floyd_warshall() ? "Yes" : "No");

        if (case_num > 1) printf("\n");
    }
    return 0;
}