#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    int arr[3] = {a, b, c};
    qsort(arr, 3, sizeof(int), (int (*)(const void *, const void *))strcmp);
    int d = arr[1] - arr[0];
    if (arr[2] - arr[1] == d) {
        printf("%d\n", arr[0] - d);
    } else {
        printf("%d\n", arr[1] + d);
    }
    return 0;
}