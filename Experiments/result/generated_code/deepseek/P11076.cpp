#include <stdio.h>
#include <string.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, x, y;
        scanf("%d %d %d", &n, &x, &y);
        char s[n + 1];
        scanf("%s", s);

        int countF = 0, countS = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'F') countF++;
            else countS++;
        }

        int remainingF = x - countF;
        int remainingS = y - countS;

        if (remainingF <= 0) {
            printf("0\n");
        } else {
            printf("%d\n", remainingF);
        }
    }
    return 0;
}