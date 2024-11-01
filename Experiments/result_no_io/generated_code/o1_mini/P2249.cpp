#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    long long *a = (long long*)malloc(n * sizeof(long long));
    for(int i=0;i<n;i++) scanf("%lld", &a[i]);
    for(int i=0;i<m;i++){
        long long q;
        scanf("%lld", &q);
        int left=0, right=n-1, res=-1;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(a[mid] == q){
                res = mid +1;
                right = mid -1;
            }
            else if(a[mid] < q) left = mid +1;
            else right = mid -1;
        }
        printf("%d%c", res, i==m-1? '\n':' ');
    }
    free(a);
    return 0;
}