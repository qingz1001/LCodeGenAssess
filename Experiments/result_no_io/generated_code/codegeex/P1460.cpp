#include <stdio.h>

#define MAX_VITAMINS 25
#define MAX_FEEDS 15

int needs[MAX_VITAMINS];
int feeds[MAX_FEEDS][MAX_VITAMINS];
int feed_count;

void dfs(int index, int vitamin_count, int *selected_feeds) {
    if (index == feed_count) {
        if (vitamin_count == 0) {
            for (int i = 0; i < feed_count; i++) {
                if (selected_feeds[i]) {
                    printf("%d ", i + 1);
                }
            }
            printf("\n");
            exit(0);
        }
        return;
    }

    for (int i = 0; i < MAX_VITAMINS; i++) {
        selected_feeds[index] = 0;
        dfs(index + 1, vitamin_count, selected_feeds);

        for (int j = 0; j < MAX_VITAMINS; j++) {
            vitamin_count -= feeds[index][j] * selected_feeds[index];
        }

        selected_feeds[index] = 1;
        dfs(index + 1, vitamin_count, selected_feeds);
    }
}

int main() {
    int v, g;
    scanf("%d", &v);
    for (int i = 0; i < v; i++) {
        scanf("%d", &needs[i]);
    }
    scanf("%d", &g);
    feed_count = g;
    for (int i = 0; i < g; i++) {
        for (int j = 0; j < v; j++) {
            scanf("%d", &feeds[i][j]);
        }
    }

    int selected_feeds[MAX_FEEDS] = {0};
    dfs(0, v, selected_feeds);

    return 0;
}