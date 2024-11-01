#include <stdio.h>
#include <string.h>

#define MAX_LEN 251

void removeLeadingZeros(char *num) {
    int i = 0;
    while (num[i] == '0' && num[i + 1] != '\0') {
        i++;
    }
    if (i > 0) {
        memmove(num, num + i, strlen(num) - i + 1);
    }
}

int main() {
    char n[MAX_LEN];
    int k, len, i, j;

    scanf("%s", n);
    scanf("%d", &k);

    len = strlen(n);
    
    for (i = 0; i < k; i++) {
        for (j = 0; j < len - 1; j++) {
            if (n[j] > n[j + 1]) {
                memmove(&n[j], &n[j + 1], len - j);
                len--;
                break;
            }
        }
        if (j == len - 1) {
            n[--len] = '\0';
        }
    }

    removeLeadingZeros(n);

    if (n[0] == '\0') {
        printf("0\n");
    } else {
        printf("%s\n", n);
    }

    return 0;
}