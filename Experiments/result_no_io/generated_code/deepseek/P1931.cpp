#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_CURRENCIES 30
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int index;
} Currency;

typedef struct {
    int from;
    int to;
    double rate;
} Exchange;

int findCurrencyIndex(Currency currencies[], int n, const char *name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(currencies[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int bellmanFord(double rates[][MAX_CURRENCIES], int n) {
    double dist[MAX_CURRENCIES];
    for (int i = 0; i < n; i++) {
        dist[i] = 0.0;
    }
    dist[0] = 1.0;

    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (dist[u] * rates[u][v] > dist[v]) {
                    dist[v] = dist[u] * rates[u][v];
                }
            }
        }
    }

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (dist[u] * rates[u][v] > dist[v]) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    int n, m, caseNum = 0;
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        Currency currencies[MAX_CURRENCIES];
        for (int i = 0; i < n; i++) {
            scanf("%s", currencies[i].name);
            currencies[i].index = i;
        }

        scanf("%d", &m);
        Exchange exchanges[m];
        double rates[MAX_CURRENCIES][MAX_CURRENCIES];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                rates[i][j] = 0.0;
            }
        }

        for (int i = 0; i < m; i++) {
            char from[MAX_NAME_LENGTH], to[MAX_NAME_LENGTH];
            double rate;
            scanf("%s %lf %s", from, &rate, to);
            int fromIndex = findCurrencyIndex(currencies, n, from);
            int toIndex = findCurrencyIndex(currencies, n, to);
            rates[fromIndex][toIndex] = rate;
        }

        int result = bellmanFord(rates, n);
        caseNum++;
        if (result) {
            printf("Case %d: Yes\n", caseNum);
        } else {
            printf("Case %d: No\n", caseNum);
        }

        if (getchar() != '\n') {
            while (getchar() != '\n');
        }
    }

    return 0;
}