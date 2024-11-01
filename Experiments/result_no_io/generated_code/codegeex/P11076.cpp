#include <stdio.h>
#include <string.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, x, y;
        scanf("%d %d %d", &n, &x, &y);
        char s[200005];
        scanf("%s", s);

        int f_count = 0, s_count = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'F') {
                f_count++;
            } else {
                s_count++;
            }
        }

        int max_consecutive_f = 0, current_consecutive_f = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'F') {
                current_consecutive_f++;
            } else {
                max_consecutive_f = fmax(max_consecutive_f, current_consecutive_f);
                current_consecutive_f = 0;
            }
        }
        max_consecutive_f = fmax(max_consecutive_f, current_consecutive_f);

        int min_consecutive_f = max_consecutive_f;
        for (int i = 0; i < max_consecutive_f; i++) {
            if (f_count + i > x || s_count + (n - f_count - i) >= y) {
                min_consecutive_f = i;
                break;
            }
        }

        printf("%d\n", min_consecutive_f);
    }
    return 0;
}