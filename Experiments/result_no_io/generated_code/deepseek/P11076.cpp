#include <stdio.h>
#include <string.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, x, y;
        scanf("%d %d %d", &n, &x, &y);
        char s[200005];
        scanf("%s", s);

        int f_wins = 0, s_wins = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'F') f_wins++;
            else s_wins++;
        }

        int remaining_f_wins = x - f_wins;
        int remaining_s_wins = y - s_wins;

        if (remaining_f_wins <= 0) {
            printf("0\n");
            continue;
        }

        int max_consecutive_f = 0;
        int current_consecutive_f = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] == 'F') {
                current_consecutive_f++;
                max_consecutive_f = max(max_consecutive_f, current_consecutive_f);
            } else {
                current_consecutive_f = 0;
            }
        }

        int min_consecutive_f = remaining_f_wins;
        if (max_consecutive_f >= remaining_f_wins) {
            min_consecutive_f = max_consecutive_f;
        }

        printf("%d\n", min_consecutive_f);
    }
    return 0;
}