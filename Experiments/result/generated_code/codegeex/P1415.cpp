#include <stdio.h>
#include <string.h>

int main() {
    char str[501];
    scanf("%s", str);
    int len = strlen(str);

    if (len == 1) {
        printf("%s", str);
        return 0;
    }

    int i, j;
    for (i = 1; i < len; i++) {
        int flag = 0;
        for (j = 0; j < i; j++) {
            if (str[j] > str[j + 1]) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            continue;
        }

        int k;
        for (k = i + 1; k <= len; k++) {
            flag = 0;
            for (j = 0; j < k - i; j++) {
                if (str[j + i] > str[j + k]) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }

        if (k == len + 1) {
            printf("%s", str);
            return 0;
        }

        printf("%s,", str);
        printf("%s", str + k);
        return 0;
    }

    printf("%s", str);
    return 0;
}