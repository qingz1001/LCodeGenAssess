#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CURRENCIES 30
#define MAX_NAME_LENGTH 20
#define INF 1e9

typedef struct {
    char name[MAX_NAME_LENGTH];
    int id;
} Currency;

typedef struct {
    int src_id, dest_id;
    double rate;
} ExchangeRate;

int main() {
    int n, m;
    Currency currencies[MAX_CURRENCIES];
    ExchangeRate rates[1000];
    int rate_count = 0;
    int case_num = 0;

    while (1) {
        scanf("%d", &n);
        if (n == 0)
            break;

        case_num++;
        for (int i = 0; i < n; i++) {
            scanf("%s", currencies[i].name);
            currencies[i].id = i;
        }

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            char src_name[MAX_NAME_LENGTH], dest_name[MAX_NAME_LENGTH];
            double rate;
            scanf("%s %lf %s", src_name, &rate, dest_name);

            int src_id = -1, dest_id = -1;
            for (int j = 0; j < n; j++) {
                if (strcmp(src_name, currencies[j].name) == 0)
                    src_id = j;
                if (strcmp(dest_name, currencies[j].name) == 0)
                    dest_id = j;
            }

            if (src_id != -1 && dest_id != -1) {
                rates[rate_count++] = (ExchangeRate){src_id, dest_id, rate};
            }
        }

        // Bellman-Ford algorithm to detect negative cycle
        double dist[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j)
                    dist[i][j] = 0;
                else
                    dist[i][j] = INF;
            }
        }

        for (int i = 0; i < rate_count; i++) {
            dist[rates[i].src_id][rates[i].dest_id] = rates[i].rate;
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] < INF && dist[k][j] < INF && dist[i][j] > dist[i][k] * dist[k][j]) {
                        dist[i][j] = dist[i][k] * dist[k][j];
                    }
                }
            }
        }

        int has_cycle = 0;
        for (int i = 0; i < n; i++) {
            if (dist[i][i] > 1.0) {
                has_cycle = 1;
                break;
            }
        }

        printf("Case %d: %s\n", case_num, has_cycle ? "Yes" : "No");
    }

    return 0;
}