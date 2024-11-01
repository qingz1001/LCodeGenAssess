#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    char cards[1001];
    scanf("%s", cards);

    // Count the number of '5's and '0's
    int count_5 = 0, count_0 = 0;
    for (int i = 0; i < n; i++) {
        if (cards[i] == '5') count_5++;
        else if (cards[i] == '0') count_0++;
    }

    // If there are no '5's, we can only have one '0' as the result
    if (count_5 == 0) {
        if (count_0 > 0) printf("0\n");
        else printf("-1\n");
        return 0;
    }

    // Otherwise, we need at least two '5's to form a number divisible by 90
    if (count_5 >= 2) {
        // Sort the string in descending order
        qsort(cards, n, sizeof(char), (int (*)(const void *, const void *))strcmp);
        // Move all '0's to the end
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (cards[i] != '0') {
                cards[j++] = cards[i];
            }
        }
        while (j < n) {
            cards[j++] = '0';
        }
        printf("%s\n", cards);
    } else {
        printf("-1\n");
    }

    return 0;
}