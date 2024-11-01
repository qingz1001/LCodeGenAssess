#include <stdio.h>
#include <string.h>

int main() {
    char s[1001], p[1001];
    int flag = 0, flag2 = 0, flag3 = 0;
    int i, j, k = 1, n = 0;
    int t = 0, t2 = 0;

    while (gets(s)) {
        if (s[0] == '\0') break;
        n++;
        t = 0;
        for (i = 0; i < strlen(s); i++) {
            if (s[i] == '@') {
                flag = 1;
                t = 1;
                t2 = i;
                break;
            }
        }
        if (flag == 0) {
            flag2 = 1;
            flag3 = 1;
            printf("Unsuccessful @%s attempt\n%d\n%s\n", s, n, s);
            break;
        }
        if (flag3 == 1) {
            for (i = 0; i < strlen(s); i++) {
                if (s[i] == ' ') {
                    for (j = i + 1; j < strlen(s); j++) {
                        if (s[j] == ':') {
                            flag3 = 0;
                            for (k = i + 1; k < j; k++) {
                                p[k - i - 1] = s[k];
                            }
                            p[k - i - 1] = '\0';
                            break;
                        }
                    }
                    break;
                }
            }
        }
        if (strcmp(p, s) == 0) {
            printf("Successful @%s attempt\n", s);
            break;
        }
        for (i = 0; i < strlen(s); i++) {
            if (s[i] == ' ') {
                for (j = i + 1; j < strlen(s); j++) {
                    if (s[j] == ':') {
                        for (k = i + 1; k < j; k++) {
                            p[k - i - 1] = s[k];
                        }
                        p[k - i - 1] = '\0';
                        break;
                    }
                }
                break;
            }
        }
        if (strcmp(p, s) != 0 && t == 1 && flag2 == 0) {
            flag2 = 1;
            printf("Unsuccessful @%s attempt\n%d\n%s\n", s, n, s);
        }
    }
    if (flag2 == 0 && flag3 == 0) {
        printf("Unsuccessful @%s attempt\n%d\n%s\n", p, n, p);
    }
    if (flag2 == 0 && flag3 == 1) {
        printf("Unsuccessful @%s attempt\n%d\n%s\n", p, n, p);
    }
    if (flag2 == 0 && flag3 == 0 && t == 0) {
        printf("Unsuccessful @%s attempt\n%d\n%s\n", s, n, s);
    }
    if (flag2 == 0 && flag3 == 1 && t == 0) {
        printf("Unsuccessful @%s attempt\n%d\n%s\n", s, n, s);
    }
    if (flag2 == 0 && flag3 == 0 && t == 1) {
        printf("Unsuccessful @%s attempt\n%d\n%s\n", s, n, s);
    }
    if (flag2 == 0 && flag3 == 1 && t == 1) {
        printf("Unsuccessful @%s attempt\n%d\n%s\n", s, n, s);
    }
    if (flag2 == 1) {
        printf("Unsuccessful @%s attempt\n%d\n%s\n", p, n, p);
    }
    return 0;
}