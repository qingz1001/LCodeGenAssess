#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_A 1000000

int main(){
    int n;
    scanf("%d", &n);
    int *freq = (int*)calloc(MAX_A+1, sizeof(int));
    int num, max_A_val = 0;
    for(int i=0;i<n;i++){
        scanf("%d", &num);
        if(num > max_A_val) max_A_val = num;
        freq[num]++;
    }
    int *cnt = (int*)calloc(max_A_val+1, sizeof(int));
    for(int g=1; g<=max_A_val; g++){
        for(int m=g; m<=max_A_val; m+=g){
            cnt[g] += freq[m];
        }
    }
    int *ans = (int*)calloc(n+1, sizeof(int));
    int count_set = 0;
    for(int g = max_A_val; g >=1 && count_set < n; g--){
        if(cnt[g] >=1){
            int limit = cnt[g] < n ? cnt[g] : n;
            for(int k=1; k<=limit && count_set < n; k++){
                if(ans[k] ==0){
                    ans[k] = g;
                    count_set++;
                }
            }
        }
    }
    for(int k=1; k<=n; k++){
        printf("%d\n", ans[k]);
    }
    free(freq);
    free(cnt);
    free(ans);
    return 0;
}