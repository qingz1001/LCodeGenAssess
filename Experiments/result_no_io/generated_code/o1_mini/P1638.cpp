#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int *a = (int*)malloc((n+1)*sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    int *count = (int*)calloc(m+2, sizeof(int));
    int unique = 0;
    int left=1, right=1;
    int min_len = n+1;
    int res_a=1, res_b=n;
    for(right=1; right<=n; right++){
        if(a[right] >=1 && a[right] <=m){
            if(count[a[right]] ==0) unique++;
            count[a[right]]++;
        }
        while(unique == m){
            if(right - left +1 < min_len || (right - left +1 == min_len && left < res_a)){
                min_len = right - left +1;
                res_a = left;
                res_b = right;
            }
            if(a[left] >=1 && a[left] <=m){
                count[a[left]]--;
                if(count[a[left]] ==0) unique--;
            }
            left++;
        }
    }
    printf("%d %d\n", res_a, res_b);
    free(a);
    free(count);
    return 0;
}