#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 1e9

typedef struct {
    int x, y;
} Point;

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int main() {
    int n;
    scanf("%d", &n);
    Point cities[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cities[i].x, &cities[i].y);
    }

    double total_length = 0.0;

    while (n > 1) {
        int min_index = -1;
        double min_distance = INF;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double dist = distance(cities[i], cities[j]);
                if (dist < min_distance) {
                    min_distance = dist;
                    min_index = i;
                }
            }
        }

        // Check for cycles
        int cycle_count = 0;
        for (int j = 0; j < n; j++) {
            if (j != min_index && distance(cities[min_index], cities[j]) == min_distance) {
                cycle_count++;
            }
        }

        if (cycle_count >= 2) {
            total_length += min_distance;
            n--;
        } else {
            // Remove the city with the minimum distance to any other city
            Point new_city = {0, 0};
            double max_dist = -INF;
            for (int j = 0; j < n; j++) {
                if (j != min_index) {
                    double dist = distance(cities[min_index], cities[j]);
                    if (dist > max_dist) {
                        max_dist = dist;
                        new_city = cities[j];
                    }
                }
            }

            // Update the cities array by removing the old city and adding the new one
            for (int j = min_index; j < n - 1; j++) {
                cities[j] = cities[j + 1];
            }
            cities[n - 1] = new_city;
            n--;
        }
    }

    printf("%.2f\n", total_length);

    return 0;
}