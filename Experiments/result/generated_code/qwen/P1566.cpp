#include <stdio.h>

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
        
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (i != j && arr[i] == arr[j]) {
                    count++;
                }
            }
        }
        
        printf("%d\n", count);
    }
    return 0;
}