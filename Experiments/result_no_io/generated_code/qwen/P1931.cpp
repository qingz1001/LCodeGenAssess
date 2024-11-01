#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CURRENCIES 30
#define MAX_NAME_LENGTH 20

typedef struct {
    char name[MAX_NAME_LENGTH];
    double rates[MAX_CURRENCIES];
} Currency;

int findCurrencyIndex(Currency currencies[], int count, const char* name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(currencies[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void initializeRates(Currency currencies[], int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            currencies[i].rates[j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

void updateRates(Currency currencies[], int count, const char* srcName, double rate, const char* destName) {
    int srcIndex = findCurrencyIndex(currencies, count, srcName);
    int destIndex = findCurrencyIndex(currencies, count, destName);
    if (srcIndex != -1 && destIndex != -1) {
        currencies[srcIndex].rates[destIndex] = rate;
    }
}

int bellmanFord(Currency currencies[], int count, int start) {
    double dist[count];
    for (int i = 0; i < count; i++) {
        dist[i] = (i == start) ? 0.0 : INFINITY;
    }

    for (int k = 0; k < count - 1; k++) {
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                if (dist[i] + currencies[i].rates[j] < dist[j]) {
                    dist[j] = dist[i] + currencies[i].rates[j];
                }
            }
        }
    }

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (dist[i] + currencies[i].rates[j] < dist[j]) {
                return 1; // Negative cycle detected
            }
        }
    }

    return 0; // No negative cycle
}

int main() {
    int n, m;
    char src[MAX_NAME_LENGTH], dest[MAX_NAME_LENGTH];
    double rate;
    int caseCount = 0;

    while (scanf("%d", &n) == 1 && n > 0) {
        caseCount++;
        Currency currencies[MAX_CURRENCIES];
        initializeRates(currencies, n);

        for (int i = 0; i < n; i++) {
            scanf("%s", currencies[i].name);
        }

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%s %lf %s", src, &rate, dest);
            updateRates(currencies, n, src, rate, dest);
        }

        int result = bellmanFord(currencies, n, findCurrencyIndex(currencies, n, "USD"));
        printf("Case %d: ", caseCount);
        if (result) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }

        getchar(); // Consume newline character
    }

    return 0;
}