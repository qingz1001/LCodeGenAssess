#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 1000

void sramoc(int k, int m) {
    int digits[MAX_DIGITS] = {0};
    int len = 1;
    int remainder = 0;

    while (1) {
        for (int i = 0; i < k; i++) {
            int new_remainder = (remainder * k + i) % m;
            if (new_remainder == 0) {
                digits[len - 1] = i;
                for (int j = 0; j < len; j++) {
                    printf("%d", digits[j]);
                }
                printf("\n");
                return;
            }
        }

        for (int i = 0; i < k; i++) {
            int new_remainder = (remainder * k + i) % m;
            if (new_remainder != remainder) {
                digits[len - 1] = i;
                remainder = new_remainder;
                break;
            }
        }

        len++;
    }
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);
    sramoc(k, m);
    return 0;
}