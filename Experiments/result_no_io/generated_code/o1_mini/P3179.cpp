#include <stdio.h>
#include <stdlib.h>

// Comparator for qsort
int cmp(const void *a, const void *b){
    int aa = *(int*)a;
    int bb = *(int*)b;
    if(aa < bb) return -1;
    if(aa > bb) return 1;
    return 0;
}

int main(){
    int n, k;
    if(scanf("%d", &n)!=1) return 0;
    if(scanf("%d", &k)!=1) return 0;
    while(k--){
        int w;
        if(scanf("%d", &w)!=1) return 0;
        if(w ==0){
            printf("No\n");
            // Continue to next query
            // Read the next line which should have 0 elements, but since w=0, no elements to read
            continue;
        }
        int S[100];
        for(int i=0;i<w;i++) scanf("%d", &S[i]);
        qsort(S, w, sizeof(int), cmp);
        int m = S[w-1];
        int answer = 0; // 0: No, 1: Yes
        for(int i=0;i<w;i++){
            int x = S[i];
            if(m %x !=0) continue;
            int k_val = m /x;
            if(k_val != w) continue;
            int flag = 1;
            for(int j=1;j<=k_val;j++){
                if(S[j-1] != x *j){
                    flag =0;
                    break;
                }
            }
            if(flag){
                answer =1;
                break;
            }
        }
        if(answer) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}