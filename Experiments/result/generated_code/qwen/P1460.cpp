#include <stdio.h>
#include <stdlib.h>

#define MAX_VITAMINS 26
#define MAX_FEEDS 16

int vitaminc[MAX_VITAMINS];
int feed[MAX_FEEDS][MAX_VITAMINS];
int min_feeds[MAX_FEEDS];
int selected_feeds[MAX_FEEDS];
int num_selected_feeds;

void dfs(int index, int remaining_vitamins[], int current_feeds[]) {
    if (index == 0) {
        int total = 0;
        for (int i = 0; i < num_selected_feeds; i++) {
            total += current_feeds[selected_feeds[i]];
        }
        if (total > 0) {
            int valid = 1;
            for (int i = 0; i < MAX_VITAMINS; i++) {
                if (remaining_vitamins[i] > 0) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                if (num_selected_feeds < num_selected_feeds || 
                    (num_selected_feeds == num_selected_feeds && selected_feeds[0] < current_feeds[0])) {
                    memcpy(selected_feeds, current_feeds, sizeof(current_feeds));
                    num_selected_feeds = num_selected_feeds;
                }
            }
        }
        return;
    }

    dfs(index - 1, remaining_vitamins, current_feeds);

    for (int i = 0; i < MAX_VITAMINS; i++) {
        remaining_vitamins[i] -= feed[index - 1][i];
    }
    current_feeds[index - 1] = 1;
    dfs(index - 1, remaining_vitamins, current_feeds);
}

int main() {
    int v, g;
    scanf("%d", &v);
    for (int i = 0; i < v; i++) {
        scanf("%d", &vitaminc[i]);
    }
    scanf("%d", &g);
    for (int i = 0; i < g; i++) {
        for (int j = 0; j < v; j++) {
            scanf("%d", &feed[i][j]);
        }
    }

    int remaining_vitamins[MAX_VITAMINS];
    for (int i = 0; i < MAX_VITAMINS; i++) {
        remaining_vitamins[i] = vitaminc[i];
    }

    int current_feeds[MAX_FEEDS] = {0};
    num_selected_feeds = 0;

    dfs(g, remaining_vitamins, current_feeds);

    printf("%d ", num_selected_feeds);
    for (int i = 0; i < num_selected_feeds; i++) {
        printf("%d ", selected_feeds[i] + 1);
    }
    printf("\n");

    return 0;
}