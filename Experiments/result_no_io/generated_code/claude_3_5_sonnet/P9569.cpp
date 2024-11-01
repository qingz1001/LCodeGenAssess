#include <stdio.h>

#define MAX_N 100005

int n, T;
int v[MAX_N], t[MAX_N];

int main() {
    scanf("%d %d", &n, &T);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &v[i], &t[i]);
    }
    
    int max_height = -1;
    int ans = 0;
    
    for (int i = 1; i <= n; i++) {
        if (t[i] <= T) {
            int height = v[i] * (T - t[i]);
            if (height > max_height) {
                max_height = height;
                ans = i;
            }
        }
    }
    
    printf("%d\n", ans);
    
    return 0;
}