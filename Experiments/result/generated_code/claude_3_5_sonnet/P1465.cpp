#include <stdio.h>
#include <string.h>

char roman[] = "IVXLCDM";
int values[] = {1, 5, 10, 50, 100, 500, 1000};
int count[7];

void addRoman(int n) {
    for (int i = 6; i >= 0; i--) {
        while (n >= values[i]) {
            count[i]++;
            n -= values[i];
        }
        if (i > 0 && i % 2 == 0) {
            if (n >= values[i] - values[i-2]) {
                count[i-2]++;
                count[i]++;
                n -= (values[i] - values[i-2]);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    memset(count, 0, sizeof(count));

    for (int i = 1; i <= n; i++) {
        addRoman(i);
    }

    for (int i = 0; i < 7; i++) {
        if (count[i] > 0) {
            printf("%c %d\n", roman[i], count[i]);
        }
    }

    return 0;
}