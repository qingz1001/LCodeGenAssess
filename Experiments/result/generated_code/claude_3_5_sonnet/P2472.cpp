#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_R 20
#define MAX_C 20
#define INF 0x3f3f3f3f

int r, c, d;
int h[MAX_R][MAX_C];
bool lizard[MAX_R][MAX_C];
int match[MAX_R][MAX_C];
bool vis[MAX_R][MAX_C];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

bool is_valid(int x, int y) {
    return x >= 0 && x < r && y >= 0 && y < c;
}

bool dfs(int x, int y) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (h[i][j] > 0 && !vis[i][j]) {
                int dist = (x - i) * (x - i) + (y - j) * (y - j);
                if (dist <= d * d) {
                    vis[i][j] = true;
                    if (match[i][j] == -1 || dfs(match[i][j] / c, match[i][j] % c)) {
                        match[i][j] = x * c + y;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int hungarian() {
    int result = 0;
    memset(match, -1, sizeof(match));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (lizard[i][j]) {
                memset(vis, false, sizeof(vis));
                if (dfs(i, j)) result++;
            }
        }
    }
    return result;
}

int main() {
    scanf("%d %d %d", &r, &c, &d);
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &h[i][j]);
        }
    }
    
    int lizard_count = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            char ch;
            scanf(" %c", &ch);
            lizard[i][j] = (ch == 'L');
            if (lizard[i][j]) lizard_count++;
        }
    }
    
    int max_escaped = hungarian();
    printf("%d\n", lizard_count - max_escaped);
    
    return 0;
}