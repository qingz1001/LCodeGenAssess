#include <stdio.h>
#include <string.h>

#define MAX_CURRENCIES 30
#define MAX_EXCHANGES 900

typedef struct {
    char from[MAX_CURRENCIES][MAX_CURRENCIES];
    double rate[MAX_CURRENCIES][MAX_CURRENCIES];
    char to[MAX_CURRENCIES][MAX_CURRENCIES];
} ExchangeRate;

int find_currency(char currencies[MAX_CURRENCIES][MAX_CURRENCIES], int num_currencies, char *currency) {
    for (int i = 0; i < num_currencies; i++) {
        if (strcmp(currencies[i], currency) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    int n, m, case_number = 1;
    char currencies[MAX_CURRENCIES][MAX_CURRENCIES];
    ExchangeRate rates[MAX_EXCHANGES];

    while (1) {
        scanf("%d", &n);
        if (n == 0) {
            break;
        }

        for (int i = 0; i < n; i++) {
            scanf("%s", currencies[i]);
        }

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%s %lf %s", rates[i].from, &rates[i].rate[i], rates[i].to);
        }

        int graph[MAX_CURRENCIES][MAX_CURRENCIES];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                graph[i][j] = -1;
            }
        }

        for (int i = 0; i < m; i++) {
            int from_index = find_currency(currencies, n, rates[i].from);
            int to_index = find_currency(currencies, n, rates[i].to);
            graph[from_index][to_index] = rates[i].rate[i];
        }

        int visited[MAX_CURRENCIES];
        for (int i = 0; i < n; i++) {
            visited[i] = 0;
        }

        int can_arbitrage = 0;
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (graph[i][k] != -1 && graph[k][j] != -1 && graph[i][j] == -1) {
                        graph[i][j] = graph[i][k] * graph[k][j];
                    }
                    if (graph[i][j] != -1 && graph[i][j] > 1.0) {
                        can_arbitrage = 1;
                    }
                }
            }
        }

        printf("Case %d: %s\n", case_number++, can_arbitrage ? "Yes" : "No");
    }

    return 0;
}