#include <stdio.h>
#include <stdbool.h>

int countAdditiveEquations(int *arr, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && arr[i] == arr[j]) continue;
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;
                if (arr[i] == arr[j] + arr[k]) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int m;
        scanf("%d", &m);
        int arr[m];
        for (int i = 0; i < m; i++) {
            scanf("%d", &arr[i]);
        }
        printf("%d\n", countAdditiveEquations(arr, m));
    }
    return 0;
}