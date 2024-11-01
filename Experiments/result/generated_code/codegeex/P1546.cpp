#include <stdio.h>

#define MAX_COUNTRIES 100
#define INF 100000

int main() {
    int N;
    scanf("%d", &N);

    int distances[MAX_COUNTRIES][MAX_COUNTRIES];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &distances[i][j]);
        }
    }

    int min_cost = 0;
    int visited[MAX_COUNTRIES] = {0};
    visited[0] = 1;

    for (int i = 0; i < N - 1; i++) {
        int min_edge = INF;
        int next_country = -1;

        for (int j = 0; j < N; j++) {
            if (!visited[j]) {
                for (int k = 0; k < N; k++) {
                    if (visited[k] && distances[k][j] < min_edge) {
                        min_edge = distances[k][j];
                        next_country = j;
                    }
                }
            }
        }

        min_cost += min_edge;
        visited[next_country] = 1;
    }

    printf("%d\n", min_cost);

    return 0;
}