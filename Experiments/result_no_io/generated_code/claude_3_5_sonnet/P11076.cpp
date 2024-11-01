#include <stdio.h>
#include <string.h>

#define MAX_N 200005

char s[MAX_N];

int solve(int n, int x, int y) {
    int f_wins = 0, s_wins = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'F') f_wins++;
        else s_wins++;
    }

    int remaining_f = x - f_wins;
    int remaining_s = y - s_wins;

    if (remaining_f <= 0) return 0;

    int left = 1, right = remaining_f;
    while (left < right) {
        int mid = left + (right - left) / 2;
        int f_turns = (remaining_f + mid - 1) / mid;
        int s_turns = f_turns - 1;

        if (s_turns >= remaining_s) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, x, y;
        scanf("%d %d %d", &n, &x, &y);
        scanf("%s", s);

        int result = solve(n, x, y);
        printf("%d\n", result);
    }

    return 0;
}