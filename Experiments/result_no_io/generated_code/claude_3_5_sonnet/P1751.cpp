#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 5001
#define MAX_K 1001

int n, k, h;
int graph[MAX_N][MAX_N];
int distance[MAX_N][MAX_N];
int worm_pos[MAX_K];
int food_pos;
int eaten[MAX_K];
int final_pos[MAX_K];

void dfs(int start, int current, int dist, int parent) {
    distance[start][current] = dist;
    for (int i = 1; i <= n; i++) {
        if (graph[current][i] && i != parent) {
            dfs(start, i, dist + 1, current);
        }
    }
}

void calculate_distances() {
    for (int i = 1; i <= n; i++) {
        dfs(i, i, 0, -1);
    }
}

int move_worms() {
    int min_dist = MAX_N;
    int winner = -1;

    for (int i = 0; i < k; i++) {
        int dist = distance[worm_pos[i]][food_pos];
        if (dist < min_dist) {
            min_dist = dist;
            winner = i;
        }
    }

    for (int i = 0; i < k; i++) {
        if (i == winner) {
            worm_pos[i] = food_pos;
            eaten[i]++;
        } else {
            int current_dist = distance[worm_pos[i]][food_pos];
            for (int j = 1; j <= n; j++) {
                if (graph[worm_pos[i]][j] && distance[j][food_pos] < current_dist) {
                    int blocked = 0;
                    for (int w = 0; w < i; w++) {
                        if (worm_pos[w] == j) {
                            blocked = 1;
                            break;
                        }
                    }
                    if (!blocked) {
                        worm_pos[i] = j;
                        break;
                    }
                }
            }
        }
    }

    return winner;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = graph[b][a] = 1;
    }

    calculate_distances();

    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &worm_pos[i]);
        final_pos[i] = worm_pos[i];
    }

    scanf("%d", &h);
    for (int i = 0; i < h; i++) {
        scanf("%d", &food_pos);
        move_worms();
    }

    for (int i = 0; i < k; i++) {
        final_pos[i] = worm_pos[i];
    }

    for (int i = 0; i < k; i++) {
        printf("%d %d\n", final_pos[i], eaten[i]);
    }

    return 0;
}