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

        int fwin = 0, swin = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'F') fwin++;
            else swin++;
        }

        if (fwin >= x) {
            printf("0\n");
            continue;
        }

        int max_consecutive_f = 0, current_consecutive_f = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'F') {
                current_consecutive_f++;
            } else {
                if (current_consecutive_f > max_consecutive_f) {
                    max_consecutive_f = current_consecutive_f;
                }
                current_consecutive_f = 0;
            }
        }
        if (current_consecutive_f > max_consecutive_f) {
            max_consecutive_f = current_consecutive_f;
        }

        int min_required_f = x - fwin;
        int min_required_s = y - swin;

        if (min_required_f <= min_required_s) {
            printf("%d\n", min_required_f);
        } else {
            printf("%d\n", max_consecutive_f);
        }
    }
    return 0;
}