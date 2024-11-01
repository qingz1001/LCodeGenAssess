#include <stdio.h>
#include <string.h>

int main() {
    char s[10000001];
    scanf("%s", s);
    int n = strlen(s);
    int p = 0;

    for (int i = 0; i < n; i++) {
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (s[j] == s[i]) {
                count++;
            } else {
                break;
            }
        }
        if (count > p) {
            p = count;
        }
    }

    printf("%d\n", p);
    return 0;
}