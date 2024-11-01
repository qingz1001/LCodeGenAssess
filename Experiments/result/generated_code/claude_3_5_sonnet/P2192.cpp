#include <stdio.h>
#include <string.h>

#define MAX_N 1000

void sort_descending(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, cards[MAX_N];
    int count_5 = 0, count_0 = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &cards[i]);
        if (cards[i] == 5) count_5++;
        else count_0++;
    }

    if (count_0 == 0 || (count_5 * 5) % 9 != 0) {
        printf("-1\n");
        return 0;
    }

    sort_descending(cards, n);

    if (cards[0] == 0) {
        printf("0\n");
        return 0;
    }

    int needed_5 = ((count_5 * 5) / 9) * 9 / 5;
    for (int i = 0; i < needed_5; i++) {
        printf("5");
    }
    printf("0\n");

    return 0;
}