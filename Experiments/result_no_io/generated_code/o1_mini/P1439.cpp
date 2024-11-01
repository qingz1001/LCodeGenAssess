#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    
    int *pos1 = (int*)malloc((n+1) * sizeof(int));
    for(int i=0; i<n; i++){
        int x;
        scanf("%d", &x);
        pos1[x] = i;
    }
    
    int *A = (int*)malloc(n * sizeof(int));
    for(int i=0; i<n; i++){
        int x;
        scanf("%d", &x);
        A[i] = pos1[x];
    }
    
    int *tail = (int*)malloc(n * sizeof(int));
    int len = 0;
    for(int i=0; i<n; i++){
        int x = A[i];
        int left = 0, right = len;
        while(left < right){
            int mid = left + (right - left) / 2;
            if(tail[mid] < x)
                left = mid + 1;
            else
                right = mid;
        }
        tail[left] = x;
        if(left == len) len++;
    }
    
    printf("%d\n", len);
    
    free(pos1);
    free(A);
    free(tail);
    return 0;
}