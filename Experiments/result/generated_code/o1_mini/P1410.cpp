#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b){
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    int N;
    while(scanf("%d", &N)!=EOF){
        long long arr[N];
        for(int i=0;i<N;i++) scanf("%lld", &arr[i]);
        qsort(arr, N, sizeof(long long), cmp);
        int flag=1;
        int t=0, c=0;
        int i=0;
        while(i<N){
            int cnt=1;
            while(i+cnt<N && arr[i+cnt]==arr[i]) cnt++;
            if(cnt >2){
                flag=0;
                break;
            }
            if(cnt ==2) t++;
            else c++;
            i += cnt;
        }
        if(!flag){
            printf("No!\n");
            continue;
        }
        int half = N/2;
        if((half - t) <=c && (half - t)>=0){
            printf("Yes!\n");
        }
        else{
            printf("No!\n");
        }
    }
    return 0;
}