#include <stdio.h>

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int a[15];
    for (int i = 0; i < k; i++) {
        scanf("%d", &a[i]);
    }
    
    int time = 0;
    int i = 0;
    while (i < n) {
        i += m;
        time++;
        if (i >= n) break;
        for (int j = 0; j < k; j++) {
            if (a[j] == i) {
                m++;
                break;
            }
        }
    }
    
    printf("%d\n", time);
    return 0;
}