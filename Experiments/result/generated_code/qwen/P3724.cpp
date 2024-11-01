#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 20
#define MAX_MC 100

int main() {
    int n, m, mc;
    scanf("%d %d %d", &n, &m, &mc);

    int a[MAX_N];
    int w[MAX_N];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &w[i]);
    }

    int C[MAX_M];
    for (int i = 0; i < m; ++i) {
        scanf("%d", &C[i]);
    }

    for (int i = 0; i < m; ++i) {
        int current_mc = mc;
        int current_C = C[i];
        int F = 1;
        int L = 0;
        int can_win = 0;

        for (int j = 0; j < n; ++j) {
            current_C -= a[j];
            if (current_C < 0) {
                break;
            }

            int new_current_mc = current_mc + w[j];
            if (new_current_mc > current_mc) {
                current_mc = new_current_mc;
            }

            if (current_C == 0) {
                can_win = 1;
                break;
            }

            // Option 1: Talk back to the boss
            if (F > 0) {
                --F;
                --current_C;
                if (current_C < 0) {
                    current_C = 0;
                }
                if (current_C == 0) {
                    can_win = 1;
                    break;
                }
            }

            // Option 2: Do water problems
            new_current_mc += w[j];
            if (new_current_mc > current_mc) {
                current_mc = new_current_mc;
            }

            // Option 3: Level up
            ++L;

            // Option 4: Increase讽刺能力
            F *= L;

            // Option 5: Defeat the boss
            if (F > 0) {
                current_C -= F;
                F = 0;
                L = 0;
                if (current_C <= 0) {
                    current_C = 0;
                    can_win = 1;
                    break;
                }
            }
        }

        printf("%d\n", can_win);
    }

    return 0;
}