#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    double x, a;
    int level = 0, experience = 0;
    int max_experience = 0;

    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &x, &a);
        if (x > 10) x = 10;
        if (x < -10) x = -10;
        if (experience + (int)x <= 0) break;
        experience += (int)x;
        max_experience += (int)a;
    }

    while (max_experience >= 2 * level + 1) {
        level++;
        max_experience -= 2 * level + 1;
    }

    printf("%d %d\n", level, max_experience);

    return 0;
}