#include <stdio.h>
#include <math.h>

#define G 10.0
#define EPSILON 0.0001

int main() {
    int H, S1, V, L, K, n;
    scanf("%d %d %d %d %d %d", &H, &S1, &V, &L, &K, &n);

    int count = 0;
    for (int i = 0; i < n; i++) {
        double t = sqrt(2.0 * (H - K) / G);
        double s = i;
        double s_car_front = S1 + V * t;
        double s_car_back = s_car_front - L;

        if (s >= s_car_back - EPSILON && s <= s_car_front + EPSILON) {
            count++;
        } else {
            double t_ground = sqrt(2.0 * H / G);
            s_car_front = S1 + V * t_ground;
            s_car_back = s_car_front - L;
            if (s >= s_car_back - EPSILON && s <= s_car_front + EPSILON && t_ground > t) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}