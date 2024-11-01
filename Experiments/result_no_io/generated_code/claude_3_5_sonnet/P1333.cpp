#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STICKS 250000
#define MAX_COLOR_LEN 11

typedef struct {
    char color1[MAX_COLOR_LEN];
    char color2[MAX_COLOR_LEN];
} Stick;

Stick sticks[MAX_STICKS];
int stick_count = 0;
bool visited[MAX_STICKS];

bool dfs(int current, int count) {
    if (count == stick_count) {
        return true;
    }
    
    visited[current] = true;
    
    for (int i = 0; i < stick_count; i++) {
        if (!visited[i]) {
            if (strcmp(sticks[current].color2, sticks[i].color1) == 0) {
                if (dfs(i, count + 1)) {
                    return true;
                }
            }
            if (strcmp(sticks[current].color2, sticks[i].color2) == 0) {
                char temp[MAX_COLOR_LEN];
                strcpy(temp, sticks[i].color1);
                strcpy(sticks[i].color1, sticks[i].color2);
                strcpy(sticks[i].color2, temp);
                if (dfs(i, count + 1)) {
                    return true;
                }
            }
        }
    }
    
    visited[current] = false;
    return false;
}

bool can_arrange() {
    for (int i = 0; i < stick_count; i++) {
        memset(visited, 0, sizeof(visited));
        if (dfs(i, 1)) {
            return true;
        }
    }
    return false;
}

int main() {
    char color1[MAX_COLOR_LEN], color2[MAX_COLOR_LEN];
    while (scanf("%s %s", color1, color2) == 2) {
        strcpy(sticks[stick_count].color1, color1);
        strcpy(sticks[stick_count].color2, color2);
        stick_count++;
    }
    
    if (can_arrange()) {
        printf("Possible\n");
    } else {
        printf("Impossible\n");
    }
    
    return 0;
}