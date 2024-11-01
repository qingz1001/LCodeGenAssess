#include <stdio.h>
#include <stdlib.h>

void sort_interval(int *arr, int l, int r, int op) {
    // op = 0: ascending, op = 1: descending
    for (int i = l; i <= r; i++) {
        for (int j = i + 1; j <= r; j++) {
            if ((op == 0 && arr[i] > arr[j]) || (op == 1 && arr[i] < arr[j])) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    for (int i = 0; i < m; i++) {
        int op, l, r;
        scanf("%d %d %d", &op, &l, &r);
        sort_interval(arr, l - 1, r - 1, op);
    }
    
    int q;
    scanf("%d", &q);
    printf("%d\n", arr[q - 1]);
    
    free(arr);
    return 0;
}