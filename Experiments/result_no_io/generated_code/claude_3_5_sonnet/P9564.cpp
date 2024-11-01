#include <stdio.h>

int main() {
    int A, B;
    scanf("%d %d", &A, &B);

    int possible = 0;
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            for (int k = 1; k <= 6; k++) {
                int red = 0, black = 0;
                if (i == 1 || i == 4) red += i;
                else black += i;
                if (j == 1 || j == 4) red += j;
                else black += j;
                if (k == 1 || k == 4) red += k;
                else black += k;

                if (red == A && black == B) {
                    possible = 1;
                    break;
                }
            }
            if (possible) break;
        }
        if (possible) break;
    }

    if (possible) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}