#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000000

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    for (int i = 0; i < k; ++i) {
        int w;
        scanf("%d", &w);
        int *white = (int *)malloc(w * sizeof(int));
        
        for (int j = 0; j < w; ++j) {
            scanf("%d", &white[j]);
        }
        
        int has_winning_strategy = 0;
        
        for (int j = 0; j < w; ++j) {
            int x = white[j];
            if (n % x == 0) {
                has_winning_strategy = 1;
                break;
            }
        }
        
        if (has_winning_strategy) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
        
        free(white);
    }
    
    return 0;
}