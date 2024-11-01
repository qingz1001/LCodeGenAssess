#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int count = 0;
    int start = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            if (start == -1) {
                start = i;
            }
        } else {
            if (start != -1) {
                count++;
                start = -1;
            }
        }
    }
    if (start != -1) {
        count++;
    }
    
    printf("%d\n", count);
    return 0;
}