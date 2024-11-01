#include <stdio.h>
#include <stdbool.h>

#define MAX_R 50
#define MAX_C 50
#define MAX_N 100

int r, c, n;
int cow[MAX_N][2];
bool field[MAX_R][MAX_C];

bool is_safe(int exclude) {
    for (int i = 0; i < n; i++) {
        if (i == exclude) continue;
        int x = cow[i][0], y = cow[i][1];
        while (x > 0 || y < c) {
            if (x > 0 && !field[x-1][y]) {
                x--;
            } else if (y < c-1 && !field[x][y+1]) {
                y++;
            } else {
                return false;
            }
        }
    }
    return true;
}

int main() {
    scanf("%d %d", &r, &c);
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cow[i][0], &cow[i][1]);
        cow[i][0]--; cow[i][1]--;
        field[cow[i][0]][cow[i][1]] = true;
    }
    
    if (is_safe(-1)) {
        printf("0\n");
        return 0;
    }
    
    bool found = false;
    for (int i = 0; i < n; i++) {
        field[cow[i][0]][cow[i][1]] = false;
        if (is_safe(i)) {
            printf("%d\n", i+1);
            found = true;
        }
        field[cow[i][0]][cow[i][1]] = true;
    }
    
    if (!found) {
        printf("-1\n");
    }
    
    return 0;
}