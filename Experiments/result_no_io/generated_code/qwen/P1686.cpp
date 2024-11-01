#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 250000

int main() {
    int n;
    char moves[MAX_N + 1];
    
    scanf("%d %s", &n, moves);
    
    int x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        switch (moves[i]) {
            case 'N': y++; break;
            case 'S': y--; break;
            case 'E': x++; break;
            case 'W': x--; break;
        }
    }
    
    int min_len = abs(x) + abs(y);
    int start = 0, end = n;
    char direction = ' ';
    
    if (x > 0 && y == 0) {
        direction = 'E';
    } else if (x < 0 && y == 0) {
        direction = 'W';
    } else if (y > 0 && x == 0) {
        direction = 'N';
    } else if (y < 0 && x == 0) {
        direction = 'S';
    }
    
    printf("%d %d %d %c\n", min_len, start, end, direction);
    
    return 0;
}