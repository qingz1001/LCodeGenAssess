#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_CURRENCIES 30
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
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

int bellmanFord(int n, double rates[][MAX_CURRENCIES], int source) {
    double dist[MAX_CURRENCIES];
    for (int i = 0; i < n; i++) {
        dist[i] = 0.0;
    }
    dist[source] = 1.0;

    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (rates[u][v] > 0 && dist[u] * rates[u][v] > dist[v]) {
                    dist[v] = dist[u] * rates[u][v];
                }
            }
        }
    }

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (rates[u][v] > 0 && dist[u] * rates[u][v] > dist[v]) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    int n, m, caseNum = 0;
    Currency currencies[MAX_CURRENCIES];
    Exchange exchanges[MAX_CURRENCIES * MAX_CURRENCIES];
    double rates[MAX_CURRENCIES][MAX_CURRENCIES] = {0};

    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        for (int i = 0; i < n; i++) {
            scanf("%s", currencies[i].name);
        }

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            char from[MAX_NAME_LENGTH], to[MAX_NAME_LENGTH];
            double rate;
            scanf("%s %lf %s", from, &rate, to);
            int fromIndex = findCurrencyIndex(currencies, n, from);
            int toIndex = findCurrencyIndex(currencies, n, to);
            rates[fromIndex][toIndex] = rate;
        }

        int possible = 0;
        for (int i = 0; i < n; i++) {
            if (bellmanFord(n, rates, i)) {
                possible = 1;
                break;
            }
        }

        printf("Case %d: %s\n", ++caseNum, possible ? "Yes" : "No");

        // Clear rates for next case
        memset(rates, 0, sizeof(rates));
    }

    return 0;
}