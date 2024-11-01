#include <stdio.h>
#include <math.h>

#define MAX_N 3000
#define MAX_SIZE 50

int n, row, line;
int bosses[MAX_N][2];

double calculate_distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double find_furthest_distance() {
    double max_distance = 0.0;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= line; j++) {
            double min_distance = INFINITY;
            for (int k = 0; k < n; k++) {
                min_distance = fmin(min_distance, calculate_distance(i, j, bosses[k][0], bosses[k][1]));
            }
            max_distance = fmax(max_distance, min_distance);
        }
    }
    return max_distance;
}

int main() {
    scanf("%d %d %d", &n, &row, &line);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &bosses[i][0], &bosses[i][1]);
    }
    
    double result = find_furthest_distance();
    printf("%.2f\n", result);
    
    return 0;
}