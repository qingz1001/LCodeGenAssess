#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 2001

int paper[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void dfs(int x, int y) {
    if (x < 0 || x >= MAX_SIZE || y < 0 || y >= MAX_SIZE || visited[x][y] || paper[x][y] == 1) {
        return;
    }
    
    visited[x][y] = 1;
    
    for (int i = 0; i < 4; i++) {
        dfs(x + dx[i], y + dy[i]);
    }
}

int count_holes() {
    int count = 0;
    memset(visited, 0, sizeof(visited));
    
    for (int i = 0; i < MAX_SIZE; i++) {
        dfs(0, i);
        dfs(MAX_SIZE - 1, i);
        dfs(i, 0);
        dfs(i, MAX_SIZE - 1);
    }
    
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (!visited[i][j] && paper[i][j] == 0) {
                count++;
                dfs(i, j);
            }
        }
    }
    
    return count;
}

void cut(int x1, int y1, int x2, int y2) {
    x1 += 1000;
    y1 += 1000;
    x2 += 1000;
    y2 += 1000;
    
    if (x1 == x2) {
        for (int y = y1; y <= y2; y++) {
            paper[x1][y] = 1;
        }
    } else {
        for (int x = x1; x <= x2; x++) {
            paper[x][y1] = 1;
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);
    
    memset(paper, 0, sizeof(paper));
    
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        
        if (x1 > x2) {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }
        if (y1 > y2) {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }
        
        cut(x1, y1, x2, y2);
        printf("%d\n", count_holes());
    }
    
    return 0;
}