#include <stdio.h>
#include <stdlib.h>

int main(){
    int N,K;
    while(scanf("%d %d",&N,&K)!=EOF){
        int *desired_pos = (int*)calloc(N+1, sizeof(int));
        int current_sum =1;
        for(int i=0;i<K;i++){
            int S;
            scanf("%d",&S);
            for(int j=0;j<S;j++){
                int b;
                scanf("%d",&b);
                desired_pos[b] = current_sum++;
            }
        }
        int count=0;
        for(int b=1;b<=N;b++){
            if(desired_pos[b]!=0 && desired_pos[b]!=b){
                count++;
            }
        }
        if(count>0){
            printf("We need %d move operations.\n", count+1);
        }
        else{
            printf("No optimization needed.\n");
        }
        free(desired_pos);
    }
}