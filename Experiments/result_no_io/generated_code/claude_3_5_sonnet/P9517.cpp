#include <stdio.h>

#define MAX_N 100005

int main() {
    int n, bottles[MAX_N] = {0};
    int start = -1, end = -1, count = 0;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &bottles[i]);
        if (bottles[i] == 1) {
            if (start == -1) {
                start = i;
            }
            end = i;
        }
    }
    
    if (start == -1) {
        printf("0\n");
    } else {
        count = end - start + 1;
        printf("%d\n", count);
    }
    
    return 0;
}