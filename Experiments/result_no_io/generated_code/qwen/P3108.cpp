#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define INF 1000000000

typedef struct {
    int x, y;
    char dir;
} Mirror;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int N, Bx, By;
    scanf("%d %d %d", &N, &Bx, &By);

    Mirror mirrors[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %c", &mirrors[i].x, &mirrors[i].y, &mirrors[i].dir);
    }

    int count = 0;
    for (int x = -INF; x <= INF; x++) {
        for (int y = -INF; y <= INF; y++) {
            if (x == 0 && y == 0) continue;
            int dx = Bx - x;
            int dy = By - y;
            int g = gcd(abs(dx), abs(dy));
            dx /= g;
            dy /= g;

            int valid = 1;
            for (int i = 0; i < N; i++) {
                int mx = mirrors[i].x;
                int my = mirrors[i].y;
                int mdx = mx - x;
                int mdy = my - y;
                int mg = gcd(abs(mdx), abs(mdy));
                mdx /= mg;
                mdy /= mg;

                if ((mdx * dx + mdy * dy) % 2 != 0) {
                    valid = 0;
                    break;
                }
            }

            if (valid) count++;
        }
    }

    printf("%d\n", count);
    return 0;
}