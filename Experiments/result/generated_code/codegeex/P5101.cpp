#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

int N, M;
int C[MAXN];
int freq[MAXN];
int min_cost[MAXN];

void calculate_min_costs() {
    for (int i = 1; i <= M; i++) {
        min_cost[i] = 0;
    }

    for (int i = 1; i <= N; i++) {
        freq[C[i]]++;
    }

    for (int i = 1; i <= M; i++) {
        min_cost[i] += freq[i] - 1;
    }

    for (int i = 1; i <= N / 2; i++) {
        int left_color = C[i];
        int right_color = C[N - i + 1];
        if (left_color != right_color) {
            min_cost[left_color] += 1;
            min_cost[right_color] += 1;
        }
    }

    for (int i = 1; i <= M; i++) {
        printf("%d\n", min_cost[i]);
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &C[i]);
    }

    calculate_min_costs();

    return 0;
}