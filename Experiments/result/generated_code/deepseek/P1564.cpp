#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int rooms = 0;
    int i = 0;
    while (i < n) {
        int count1 = 0, count2 = 0;
        int j = i;
        while (j < n) {
            if (arr[j] == 1) count1++;
            else count2++;
            if (abs(count1 - count2) > m) {
                break;
            }
            j++;
        }
        rooms++;
        i = j;
    }

    printf("%d\n", rooms);
    free(arr);
    return 0;
}