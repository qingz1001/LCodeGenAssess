#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int *a = (int*)malloc((n+1)*sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    int *seen = (int*)calloc(n+1, sizeof(int));
    int *pos = (int*)malloc(k*sizeof(int));
    int count =0;
    for(int i=1;i<=n && count <k;i++){
        if(!seen[a[i]]){
            seen[a[i]]=1;
            pos[count++] = i;
        }
    }
    if(count <k){
        printf("-1\n");
    }
    else{
        long long res =0;
        for(int i=0;i<k;i++) res += (long long)(pos[i] - (i+1));
        printf("%lld\n", res);
    }
    free(a);
    free(seen);
    free(pos);
    return 0;
}