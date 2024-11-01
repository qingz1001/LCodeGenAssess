#include <stdio.h>
#include <math.h>

#define MAX_N 3000

int main() {
    int n, row, line;
    scanf("%d %d %d", &n, &row, &line);

    double bosses[MAX_N][2];
    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf", &bosses[i][0], &bosses[i][1]);
    }

    double min_distance = -1;

    for (double x = 1; x <= row; x += 0.01) {
        for (double y = 1; y <= line; y += 0.01) {
            double max_dist_to_boss = 0;
            for (int i = 0; i < n; ++i) {
                double dist = sqrt(pow(x - bosses[i][0], 2) + pow(y - bosses[i][1], 2));
                if (dist > max_dist_to_boss) {
                    max_dist_to_boss = dist;
                }
            }
            if (max_dist_to_boss > min_distance) {
                min_distance = max_dist_to_boss;
            }
        }
    }

    printf("%.2f\n", min_distance);
    return 0;
}