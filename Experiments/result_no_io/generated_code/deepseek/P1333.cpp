#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLORS 250000
#define MAX_COLOR_LENGTH 11

typedef struct {
    char color[MAX_COLOR_LENGTH];
    int degree;
} ColorNode;

typedef struct {
    ColorNode nodes[MAX_COLORS];
    int count;
} ColorMap;

int findColorIndex(ColorMap *map, const char *color) {
    for (int i = 0; i < map->count; i++) {
        if (strcmp(map->nodes[i].color, color) == 0) {
            return i;
        }
    }
    strcpy(map->nodes[map->count].color, color);
    map->nodes[map->count].degree = 0;
    return map->count++;
}

int main() {
    ColorMap colorMap = {0};
    char color1[MAX_COLOR_LENGTH], color2[MAX_COLOR_LENGTH];
    int degreeSum = 0;

    while (scanf("%s %s", color1, color2) != EOF) {
        int index1 = findColorIndex(&colorMap, color1);
        int index2 = findColorIndex(&colorMap, color2);
        colorMap.nodes[index1].degree++;
        colorMap.nodes[index2].degree++;
        degreeSum += 2;
    }

    if (degreeSum % 2 != 0) {
        printf("Impossible\n");
        return 0;
    }

    int oddDegreeCount = 0;
    for (int i = 0; i < colorMap.count; i++) {
        if (colorMap.nodes[i].degree % 2 != 0) {
            oddDegreeCount++;
        }
    }

    if (oddDegreeCount == 0 || oddDegreeCount == 2) {
        printf("Possible\n");
    } else {
        printf("Impossible\n");
    }

    return 0;
}