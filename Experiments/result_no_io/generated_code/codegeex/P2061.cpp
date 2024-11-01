#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
    int height;
} Building;

int compare(const void *a, const void *b) {
    Building *buildingA = (Building *)a;
    Building *buildingB = (Building *)b;
    return buildingA->start - buildingB->start;
}

int main() {
    int N;
    scanf("%d", &N);

    Building buildings[N];
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d", &buildings[i].start, &buildings[i].end, &buildings[i].height);
    }

    // Sort buildings by their start position
    qsort(buildings, N, sizeof(Building), compare);

    long long totalArea = 0;
    int currentEnd = 0;
    int maxHeight = 0;

    for (int i = 0; i < N; i++) {
        if (buildings[i].start > currentEnd) {
            // No overlap, add the area of the previous segment
            totalArea += maxHeight * (currentEnd - buildings[i].start);
            currentEnd = buildings[i].end;
            maxHeight = buildings[i].height;
        } else if (buildings[i].end > currentEnd) {
            // Overlap, update the end and max height
            if (buildings[i].height > maxHeight) {
                totalArea += (buildings[i].height - maxHeight) * (buildings[i].end - currentEnd);
                maxHeight = buildings[i].height;
            }
            currentEnd = buildings[i].end;
        }
    }

    // Add the area of the last segment
    totalArea += maxHeight * (currentEnd - buildings[0].start);

    printf("%lld\n", totalArea);
    return 0;
}