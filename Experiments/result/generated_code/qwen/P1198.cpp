#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

int main() {
    int M, D;
    scanf("%d %d", &M, &D);
    
    int t = 0;
    int *arr = (int *)malloc(MAXN * sizeof(int));
    int size = 0;
    
    for (int i = 0; i < M; i++) {
        char op[2];
        scanf("%s", op);
        
        if (op[0] == 'Q') {
            int L;
            scanf("%d", &L);
            printf("%d\n", arr[size - L]);
            t = arr[size - L];
        } else if (op[0] == 'A') {
            int n;
            scanf("%d", &n);
            arr[size++] = (n + t) % D;
        }
    }
    
    free(arr);
    return 0;
}