#include <stdio.h>
#include <string.h>

void removeDigits(char *n, int k) {
    int len = strlen(n);
    while (k > 0) {
        int i = 0;
        while (i < len - 1 && n[i] <= n[i + 1]) {
            i++;
        }
        for (int j = i; j < len - 1; j++) {
            n[j] = n[j + 1];
        }
        len--;
        k--;
    }
    n[len] = '\0';
}

int main() {
    char n[251];
    int k;
    scanf("%s", n);
    scanf("%d", &k);

    removeDigits(n, k);

    // Remove leading zeros
    int i = 0;
    while (n[i] == '0' && n[i + 1] != '\0') {
        i++;
    }
    printf("%s\n", n + i);

    return 0;
}