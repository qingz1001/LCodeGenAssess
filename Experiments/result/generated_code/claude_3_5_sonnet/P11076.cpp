#include <stdio.h>
#include <string.h>

#define MAX_N 200005

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int solve(int n, int x, int y, char *s) {
    int f_count = 0, s_count = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'F') f_count++;
        else s_count++;
    }

    int f_need = x - f_count;
    int s_left = y - s_count - 1;

    if (f_need <= 0) return 0;
    if (s_left <= 0) return f_need;

    int low = 1, high = f_need, ans = f_need;
    while (low <= high) {
        int mid = (low + high) / 2;
        int groups = (f_need + mid - 1) / mid;
        if (groups - 1 <= s_left) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, x, y;
        char s[MAX_N];
        scanf("%d %d %d", &n, &x, &y);
        scanf("%s", s);

        int result = solve(n, x, y, s);
        printf("%d\n", result);
    }

    return 0;
}