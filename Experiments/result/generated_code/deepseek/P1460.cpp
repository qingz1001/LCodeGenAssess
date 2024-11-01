#include <stdio.h>
#include <stdbool.h>

#define MAX_V 25
#define MAX_G 15

int v, g;
int required[MAX_V];
int feeds[MAX_G][MAX_V];
int best_count = MAX_G + 1;
int best_feeds[MAX_G];

bool is_sufficient(int *current_feeds) {
    int total[MAX_V] = {0};
    for (int i = 0; i < g; i++) {
        if (current_feeds[i]) {
            for (int j = 0; j < v; j++) {
                total[j] += feeds[i][j];
            }
        }
    }
    for (int i = 0; i < v; i++) {
        if (total[i] < required[i]) {
            return false;
        }
    }
    return true;
}

void dfs(int feed_index, int *current_feeds, int feed_count) {
    if (feed_index == g) {
        if (is_sufficient(current_feeds)) {
            if (feed_count < best_count) {
                best_count = feed_count;
                for (int i = 0; i < g; i++) {
                    best_feeds[i] = current_feeds[i];
                }
            }
        }
        return;
    }

    current_feeds[feed_index] = 1;
    dfs(feed_index + 1, current_feeds, feed_count + 1);
    current_feeds[feed_index] = 0;
    dfs(feed_index + 1, current_feeds, feed_count);
}

int main() {
    scanf("%d", &v);
    for (int i = 0; i < v; i++) {
        scanf("%d", &required[i]);
    }
    scanf("%d", &g);
    for (int i = 0; i < g; i++) {
        for (int j = 0; j < v; j++) {
            scanf("%d", &feeds[i][j]);
        }
    }

    int current_feeds[MAX_G] = {0};
    dfs(0, current_feeds, 0);

    printf("%d", best_count);
    for (int i = 0; i < g; i++) {
        if (best_feeds[i]) {
            printf(" %d", i + 1);
        }
    }
    printf("\n");

    return 0;
}