#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int N;
    scanf("%d", &N);
    int* price = (int*)malloc(N*sizeof(int));
    for(int i=0;i<N;i++) scanf("%d", &price[i]);
    int* dp_len = (int*)malloc(N*sizeof(int));
    int* dp_cnt = (int*)malloc(N*sizeof(int));
    for(int i=0;i<N;i++){
        dp_len[i]=1;
        dp_cnt[i]=1;
    }
    for(int i=1;i<N;i++){
        for(int j=0;j<i;j++){
            if(price[j] > price[i]){
                if(dp_len[j]+1 > dp_len[i]){
                    dp_len[i] = dp_len[j]+1;
                    dp_cnt[i] = dp_cnt[j];
                }
                else if(dp_len[j]+1 == dp_len[i]){
                    dp_cnt[i] += dp_cnt[j];
                }
            }
        }
    }
    int max_len=0;
    for(int i=0;i<N;i++) if(dp_len[i] > max_len) max_len = dp_len[i];
    long long total=0;
    for(int i=0;i<N;i++) if(dp_len[i]==max_len) total += dp_cnt[i];
    printf("%d %lld", max_len, total);
    free(price);
    free(dp_len);
    free(dp_cnt);
    return 0;
}