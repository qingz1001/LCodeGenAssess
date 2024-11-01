#include <stdio.h>
#include <math.h>

typedef struct {
    double r, x, y;
} Circle;

int main() {
    int n;
    scanf("%d", &n);
    Circle circles[n];

    for (int i = 0; i < n; i++) {
        scanf("%lf%lf%lf", &circles[i].r, &circles[i].x, &circles[i].y);
    }

    double totalPerimeter = 0.0;

    for (int i = 0; i < n; i++) {
        int covered = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double distance = sqrt(pow(circles[i].x - circles[j].x, 2) + pow(circles[i].y - circles[j].y, 2));
                if (distance <= circles[j].r) {
                    covered = 1;
                    break;
                }
            }
        }
        if (!covered) {
            totalPerimeter += 2 * M_PI * circles[i].r;
        }
    }

    printf("%.3lf\n", totalPerimeter);
    return 0;
}