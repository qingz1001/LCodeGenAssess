#include <stdio.h>
#include <string.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, x, y;
        scanf("%d %d %d", &n, &x, &y);
        char s[n + 1];
        scanf("%s", s);

        int max_consecutive = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == 'F') {
                max_consecutive++;
            } else {
                break;
            }
        }

        int min_max_consecutive = n - max_consecutive;
        printf("%d\n", min_max_consecutive);
    }
    return 0;
}