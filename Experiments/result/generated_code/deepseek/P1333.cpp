#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLORS 500000
#define MAX_LEN 11

typedef struct {
    char color[MAX_LEN];
    int degree;
} Color;

typedef struct {
    char start[MAX_LEN];
    char end[MAX_LEN];
} Stick;

Color colors[MAX_COLORS];
Stick sticks[MAX_COLORS];
int color_count = 0;

int find_color_index(char *color) {
    for (int i = 0; i < color_count; i++) {
        if (strcmp(colors[i].color, color) == 0) {
            return i;
        }
    }
    strcpy(colors[color_count].color, color);
    colors[color_count].degree = 0;
    return color_count++;
}

int main() {
    char start[MAX_LEN], end[MAX_LEN];
    int stick_count = 0;

    while (scanf("%s %s", start, end) != EOF) {
        int start_index = find_color_index(start);
        int end_index = find_color_index(end);
        colors[start_index].degree++;
        colors[end_index].degree++;
        strcpy(sticks[stick_count].start, start);
        strcpy(sticks[stick_count].end, end);
        stick_count++;
    }

    int odd_degree_count = 0;
    for (int i = 0; i < color_count; i++) {
        if (colors[i].degree % 2 != 0) {
            odd_degree_count++;
        }
    }

    if (odd_degree_count == 0 || odd_degree_count == 2) {
        printf("Possible\n");
    } else {
        printf("Impossible\n");
    }

    return 0;
}