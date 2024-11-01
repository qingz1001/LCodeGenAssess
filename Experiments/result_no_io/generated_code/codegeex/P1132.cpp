#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100000
#define MAXM 50000

int s, m;
int visited[MAXN + 1];
int dist[MAXN + 1];

void bfs() {
    int queue[MAXN + 1];
    int front = 0, rear = 0;
    queue[rear++] = s;
    visited[s] = 1;
    dist[s] = 0;

    while (front < rear) {
        int current = queue[front++];
        int num[6];
        int len = 0;

        while (current > 0) {
            num[len++] = current % 10;
            current /= 10;
        }

        // Rule 1: Swap any two digits
        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                int new_num = 0;
                for (int k = 0; k < len; k++) {
                    if (k == i) new_num = new_num * 10 + num[j];
                    else if (k == j) new_num = new_num * 10 + num[i];
                    else new_num = new_num * 10 + num[k];
                }
                if (!visited[new_num]) {
                    visited[new_num] = 1;
                    dist[new_num] = dist[current] + 1;
                    queue[rear++] = new_num;
                }
            }
        }

        // Rule 2: Delete any digit
        for (int i = 0; i < len; i++) {
            int new_num = 0;
            for (int k = 0; k < len; k++) {
                if (k != i) new_num = new_num * 10 + num[k];
            }
            if (!visited[new_num]) {
                visited[new_num] = 1;
                dist[new_num] = dist[current] + 1;
                queue[rear++] = new_num;
            }
        }

        // Rule 3: Insert a digit between any two digits
        for (int i = 0; i < len; i++) {
            for (int digit = num[i] + 1; digit < num[i + 1]; digit++) {
                int new_num = 0;
                for (int k = 0; k < len; k++) {
                    new_num = new_num * 10 + num[k];
                    if (k == i) new_num = new_num * 10 + digit;
                }
                if (!visited[new_num] && new_num <= s) {
                    visited[new_num] = 1;
                    dist[new_num] = dist[current] + 1;
                    queue[rear++] = new_num;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &s, &m);
    memset(visited, 0, sizeof(visited));
    memset(dist, 0, sizeof(dist));
    bfs();

    for (int i = 0; i < m; i++) {
        int t;
        scanf("%d", &t);
        if (visited[t]) {
            printf("%d\n", dist[t]);
        } else {
            printf("-1\n");
        }
    }

    return 0;
}