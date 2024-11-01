#include <stdio.h>
#include <limits.h>

int minLandings(int n, int s, int *distances, int *ranges) {
    int totalDistance = 0;
    for (int i = 0; i < n; i++) {
        totalDistance += distances[i];
    }

    int maxRange = INT_MIN;
    for (int i = 0; i < s; i++) {
        maxRange = (maxRange > ranges[i]) ? maxRange : ranges[i];
    }

    if (totalDistance % maxRange != 0) {
        return -1;
    }

    int minLanding = n / (totalDistance / maxRange);
    return minLanding + 1;
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);

    int distances[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &distances[i]);
    }

    int ranges[s];
    for (int i = 0; i < s; i++) {
        scanf("%d", &ranges[i]);
    }

    for (int i = 0; i < s; i++) {
        int result = minLandings(n, s, distances, ranges);
        if (result == -1) {
            printf("NIE\n");
        } else {
            printf("%d\n", result);
        }
    }

    return 0;
}