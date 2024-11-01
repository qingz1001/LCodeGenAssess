#include <stdio.h>
#include <string.h>

#define MAX_SIZE 101

char matrix[MAX_SIZE][MAX_SIZE];
int n;

bool is_word(int x, int y, char direction) {
    char* word = "yizhong";
    int dx = 0, dy = 0;
    switch (direction) {
        case 'u': dx = -1; dy = 0; break;
        case 'd': dx = 1; dy = 0; break;
        case 'l': dx = 0; dy = -1; break;
        case 'r': dx = 0; dy = 1; break;
        case 'ul': dx = -1; dy = -1; break;
        case 'ur': dx = -1; dy = 1; break;
        case 'dl': dx = 1; dy = -1; break;
        case 'dr': dx = 1; dy = 1; break;
    }
    for (int i = 0; i < 7; i++) {
        int nx = x + dx * i;
        int ny = y + dy * i;
        if (nx < 0 || nx >= n || ny < 0 || ny >= n || matrix[nx][ny] != word[i]) {
            return false;
        }
    }
    return true;
}

void highlight_word(int x, int y, char direction) {
    int dx = 0, dy = 0;
    switch (direction) {
        case 'u': dx = -1; dy = 0; break;
        case 'd': dx = 1; dy = 0; break;
        case 'l': dx = 0; dy = -1; break;
        case 'r': dx = 0; dy = 1; break;
        case 'ul': dx = -1; dy = -1; break;
        case 'ur': dx = -1; dy = 1; break;
        case 'dl': dx = 1; dy = -1; break;
        case 'dr': dx = 1; dy = 1; break;
    }
    for (int i = 0; i < 7; i++) {
        int nx = x + dx * i;
        int ny = y + dy * i;
        matrix[nx][ny] = '*';
    }
}

void process_matrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 'y') {
                for (char dir = 'u'; dir <= 'dr'; dir++) {
                    if (is_word(i, j, dir)) {
                        highlight_word(i, j, dir);
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", matrix[i]);
    }
    process_matrix();
    for (int i = 0; i < n; i++) {
        printf("%s\n", matrix[i]);
    }
    return 0;
}