#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    int *count = (int *)calloc(n, sizeof(int));
    int *temp = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d%d", &arr[i * 2], &arr[i * 2 + 1]);
        count[arr[i * 2] - 1]++;
        count[arr[i * 2 + 1] - 1]++;
    }

    int max = 0;
    for (int i = 0; i < n; i++) {
        if (count[i] != 2) {
            printf("-1\n");
            return 0;
        }
        if (count[i] > max) {
            max = count[i];
        }
    }

    int *index = (int *)malloc(max * sizeof(int));
    int *num = (int *)calloc(max, sizeof(int));
    int j = 0;

    for (int i = 0; i < n; i++) {
        if (count[i] == 2) {
            index[j] = i;
            j++;
        }
    }

    int m = 0;
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (count[i] == 1) {
            temp[k] = i;
            k++;
        }
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < max; j++) {
            if (temp[i] == index[j]) {
                num[j]++;
            }
        }
    }

    int min = n;
    for (int i = 0; i < max; i++) {
        if (num[i] < min) {
            min = num[i];
        }
    }

    printf("%d\n", min);
    free(arr);
    free(count);
    free(temp);
    free(index);
    free(num);

    return 0;
}