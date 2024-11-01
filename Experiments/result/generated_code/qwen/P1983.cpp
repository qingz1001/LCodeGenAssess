#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int levels[MAXN];
    for (int i = 1; i <= n; i++) {
        levels[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int s;
        scanf("%d", &s);
        int stops[s];
        for (int j = 0; j < s; j++) {
            scanf("%d", &stops[j]);
        }

        int max_level = 1;
        for (int j = 0; j < s; j++) {
            if (levels[stops[j]] > max_level) {
                max_level = levels[stops[j]];
            }
        }

        for (int j = 0; j < s; j++) {
            levels[stops[j]] = max_level;
        }
    }

    int result = 0;
    for (int i = 1; i <= n; i++) {
        if (levels[i] == 1) {
            result++;
        }
    }

    printf("%d\n", result);

    return 0;
}