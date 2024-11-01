#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, m;
        long long M;
        scanf("%d %d %lld", &n, &m, &M);
        int fixed_a[300];
        int count =0;
        for(int i=0;i<m;i++){
            int p, q;
            scanf("%d %d", &p, &q);
            fixed_a[count++] = q;
        }
        qsort(fixed_a, count, sizeof(int), cmp);
        int invalid =0;
        for(int i=0;i<count;i++){
            if(fixed_a[i] > (i+1)){
                invalid =1;
                break;
            }
        }
        if(invalid){
            printf("NO\n");
            continue;
        }
        long long res =1;
        for(int k = count+1; k<=n; k++){
            res = (res * k) % M;
        }
        printf("YES %lld\n", res);
    }
    return 0;
}