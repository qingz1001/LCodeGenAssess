#include <stdio.h>
#include <stdlib.h>

#define MAXN 205

int n, m;
char front[MAXN][MAXN], back[MAXN][MAXN];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", front[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%s", back[i]);
    }

    int result = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (front[i][j] == '/' && back[i][j] == '\\') {
                result++;
            } else if (front[i][j] == '\\' && back[i][j] == '/') {
                result++;
            } else if (front[i][j] == 'X' || back[i][j] == 'X') {
                result += 2;
            }
        }
    }

    printf("%d\n", result);

    return 0;
}