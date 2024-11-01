#include <stdio.h>

#define MAXN 50001
#define MAXM 10001

int years[MAXN];
int rains[MAXN];

void update(int index, int value) {
    for (; index < MAXN; index += index & -index) {
        rains[index] = value;
    }
}

int query(int index) {
    int result = 0;
    for (; index > 0; index -= index & -index) {
        if (rains[index] != -1 && rains[index] > result) {
            result = rains[index];
        }
    }
    return result;
}

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &years[i], &rains[i]);
        update(i, rains[i]);
    }

    scanf("%d", &m);
    while (m--) {
        int Y, X;
        scanf("%d %d", &Y, &X);
        int max_rain_Y = query(Y);
        int rain_X = query(X);

        if (rain_X <= max_rain_Y) {
            printf("true\n");
        } else {
            bool possible = false;
            for (int i = Y + 1; i < X; ++i) {
                if (query(i) < rain_X) {
                    possible = true;
                    break;
                }
            }
            if (possible) {
                printf("maybe\n");
            } else {
                printf("false\n");
            }
        }
    }

    return 0;
}