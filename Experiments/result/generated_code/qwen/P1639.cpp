#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b, x, y;
    scanf("%d %d %d %d", &a, &b, &x, &y);

    // Calculate the minimum distance using either direct transportation or teleportation
    int direct_distance = abs(b - a);
    int teleport_distance = abs(a - x) + abs(y - b);

    // Output the minimum of the two distances
    printf("%d\n", direct_distance < teleport_distance ? direct_distance : teleport_distance);

    return 0;
}