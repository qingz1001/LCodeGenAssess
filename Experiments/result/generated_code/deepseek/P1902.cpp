#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 1000
#define MAXM 1000
#define INF 1000000000

int n, m;
int p[MAXN][MAXM];
bool visited[MAXN][MAXM];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

typedef struct {
    int x, y, max_damage;
} State;

State queue[MAXN * MAXM];
int front = 0, rear = 0;

void push(State s) {
    queue[rear++] = s;
}

State pop() {
    return queue[front++];
}

bool empty() {
    return front == rear;
}

bool valid(int x, int y, int max_damage) {
    return x >= 0 && x < n && y >= 0 && y < m && !visited[x][y] && p[x][y] <= max_damage;
}

bool bfs(int max_damage) {
    front = rear = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j] = false;
        }
    }

    for (int j = 0; j < m; j++) {
        if (p[0][j] <= max_damage) {
            push((State){0, j, p[0][j]});
            visited[0][j] = true;
        }
    }

    while (!empty()) {
        State curr = pop();
        if (curr.x == n - 1) {
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            if (valid(nx, ny, max_damage)) {
                push((State){nx, ny, p[nx][ny]});
                visited[nx][ny] = true;
            }
        }
    }

    return false;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &p[i][j]);
        }
    }

    int left = 0, right = 1000;
    while (left < right) {
        int mid = (left + right) / 2;
        if (bfs(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", left);
    return 0;
}