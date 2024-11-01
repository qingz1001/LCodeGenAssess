#include <stdio.h>
#include <string.h>

int main() {
    char s[100005];
    scanf("%s", s);
    int len = strlen(s);
    int cnt1 = 0, cnt2 = 0, cnt3 = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] == '\\') {
            if (s[i + 1] == 'r' && s[i + 2] == '\n') {
                cnt1++;
            } else if (s[i + 1] == 'n') {
                cnt2++;
            } else if (s[i + 1] == 'r') {
                cnt3++;
            }
        }
    }

    if (cnt1 > 0) {
        printf("windows\n");
    } else if (cnt2 > 0) {
        printf("linux\n");
    } else if (cnt3 > 0) {
        printf("mac\n");
    }

    return 0;
}