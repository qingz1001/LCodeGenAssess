#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 200005

int main() {
    int M, D;
    scanf("%d %d", &M, &D);

    int *arr = (int *)malloc(sizeof(int) * MAX_SIZE);
    int len = 0;
    int last_query = 0;

    char operation[2];
    int n;

    for (int i = 0; i < M; i++) {
        scanf("%s %d", operation, &n);

        if (operation[0] == 'A') {
            n = (n + last_query) % D;
            arr[len++] = n;
        } else if (operation[0] == 'Q') {
            int max = arr[len - n];
            for (int j = len - n + 1; j < len; j++) {
                if (arr[j] > max) {
                    max = arr[j];
                }
            }
            last_query = max;
            printf("%d\n", max);
        }
    }

    free(arr);
    return 0;
}