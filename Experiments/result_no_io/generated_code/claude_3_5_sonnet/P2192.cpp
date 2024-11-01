#include <stdio.h>
#include <string.h>

#define MAX_N 1000

void sortDescending(char *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                char temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    char cards[MAX_N + 1];
    int count_5 = 0, count_0 = 0;

    scanf("%d", &n);
    scanf("%s", cards);

    for (int i = 0; i < n; i++) {
        if (cards[i] == '5') count_5++;
        else if (cards[i] == '0') count_0++;
    }

    if (count_0 == 0) {
        if (count_5 >= 9) {
            for (int i = 0; i < count_5 - count_5 % 9; i++) {
                printf("5");
            }
            printf("\n");
        } else {
            printf("-1\n");
        }
    } else if (count_5 == 0) {
        printf("0\n");
    } else {
        sortDescending(cards, n);
        int start = 0;
        while (start < n && cards[start] == '0') start++;
        
        if (start == n) {
            printf("0\n");
        } else {
            int remainder = 0;
            for (int i = start; i < n; i++) {
                remainder = (remainder * 10 + (cards[i] - '0')) % 90;
            }
            
            if (remainder == 0) {
                for (int i = start; i < n; i++) {
                    printf("%c", cards[i]);
                }
                printf("\n");
            } else {
                printf("-1\n");
            }
        }
    }

    return 0;
}