#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *cards = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &cards[i]);
    }

    int count_0 = 0, count_5 = 0;
    for (int i = 0; i < n; i++) {
        if (cards[i] == 0) count_0++;
        else count_5++;
    }

    if (count_5 == 0 && count_0 > 0) {
        printf("0\n");
        free(cards);
        return 0;
    } else if (count_5 == 0 && count_0 == 0) {
        printf("-1\n");
        free(cards);
        return 0;
    }

    int *result = (int *)malloc((n - count_0 + 1) * sizeof(int));
    int index = 0;
    for (int i = 0; i < count_5; i++) {
        result[index++] = 5;
    }
    for (int i = 0; i < count_0; i++) {
        result[index++] = 0;
    }

    // Check if the number is divisible by 90
    int sum = 0;
    for (int i = 0; i < n - count_0; i++) {
        sum += result[i];
    }
    if (sum % 9 != 0) {
        printf("-1\n");
        free(cards);
        free(result);
        return 0;
    }

    for (int i = 0; i < n - count_0; i++) {
        printf("%d", result[i]);
    }
    printf("\n");

    free(cards);
    free(result);
    return 0;
}