#include <stdio.h>
#include <stdbool.h>

int countAdditionEquations(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (i != j && i != k && j != k) {
                    if (arr[i] == arr[j] + arr[k] || arr[i] == arr[k] + arr[j]) {
                        count++;
                    }
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
        int arr[30];
        for (int i = 0; i < m; i++) {
            scanf("%d", &arr[i]);
        }
        printf("%d\n", countAdditionEquations(arr, m));
    }
    return 0;
}