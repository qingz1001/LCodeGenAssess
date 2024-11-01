#include <stdio.h>
#include <string.h>

void draw(char graph[1024][1024], int x, int y, int size) {
    if (size == 1) {
        graph[x][y] = 'X';
        return;
    }
    
    int new_size = size / 2;
    draw(graph, x, y + new_size, new_size);
    draw(graph, x + new_size, y, new_size);
    draw(graph, x + new_size, y + size - 1, new_size);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int size = 1;
    for (int i = 0; i < n; i++) {
        size *= 2;
    }
    
    char graph[1024][1024];
    memset(graph, ' ', sizeof(graph));
    
    draw(graph, 0, 0, size);
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size * 2 - 1; j++) {
            printf("%c", graph[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}