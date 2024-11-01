#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
    char dir;
} Mirror;

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int N, Bx, By;
    scanf("%d %d %d", &N, &Bx, &By);

    Mirror mirrors[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %c", &mirrors[i].x, &mirrors[i].y, &mirrors[i].dir);
    }

    int count = 0;
    for (int x = -1000000000; x <= 1000000000; x++) {
        for (int y = -1000000000; y <= 1000000000; y++) {
            if (x == 0 && y == 0) continue;
            int dx = Bx - x, dy = By - y;
            int g = gcd(dx, dy);
            dx /= g, dy /= g;

            int found = 0;
            for (int i = 0; i < N; i++) {
                int mx = mirrors[i].x, my = mirrors[i].y;
                int mdx = mx - x, mdy = my - y;
                int mg = gcd(mdx, mdy);
                mdx /= mg, mdy /= mg;

                if ((mdx * dy - mdy * dx) * (dx * mdy - dy * mdx) > 0) {
                    found = 1;
                    break;
                }
            }

            if (!found) count++;
        }
    }

    printf("%d\n", count);
    return 0;
}