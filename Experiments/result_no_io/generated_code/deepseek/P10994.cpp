#include <stdio.h>
#include <string.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    char s[100001];
    scanf("%s", s);

    int n = strlen(s);
    int countS = 0, countT = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'S') {
            countS++;
        } else if (s[i] == 'T') {
            countT++;
        }
    }

    if (countS >= a && countT >= b) {
        printf("0\n");
    } else if (countS + countT < a + b) {
        printf("-1\n");
    } else {
        int neededS = a - countS;
        int neededT = b - countT;
        int changes = 0;

        if (neededS > 0) {
            changes += neededS;
        }
        if (neededT > 0) {
            changes += neededT;
        }

        printf("%d\n", changes);
    }

    return 0;
}