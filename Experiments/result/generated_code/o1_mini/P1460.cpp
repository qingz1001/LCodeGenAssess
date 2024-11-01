#include <stdio.h>
#include <stdlib.h>

int main(){
    int v;
    scanf("%d", &v);
    int min_req[v];
    for(int i=0;i<v;i++) scanf("%d", &min_req[i]);
    int g;
    scanf("%d", &g);
    int feed[g][v];
    for(int i=0;i<g;i++) {
        for(int j=0;j<v;j++) {
            scanf("%d", &feed[i][j]);
        }
    }
    int min_num = g+1;
    int best_subset = 0;
    for(int s=1;s<(1<<g);s++){
        int count=0;
        for(int i=0;i<g;i++) if(s & (1<<i)) count++;
        if(count > min_num) continue;
        int sum[v];
        for(int i=0;i<v;i++) sum[i]=0;
        for(int i=0;i<g;i++) {
            if(s & (1<<i)) {
                for(int j=0;j<v;j++) sum[j]+=feed[i][j];
            }
        }
        int valid=1;
        for(int i=0;i<v;i++) if(sum[i]<min_req[i]) {valid=0; break;}
        if(valid){
            if(count < min_num){
                min_num = count;
                best_subset = s;
            }
            else if(count == min_num){
                int a = best_subset;
                int b = s;
                int flag = 0;
                for(int i=0;i<g;i++){
                    int a_bit = (a & (1<<i)) ? 1 : 0;
                    int b_bit = (b & (1<<i)) ? 1 : 0;
                    if(a_bit != b_bit){
                        if(!a_bit){
                            best_subset = s;
                        }
                        break;
                    }
                }
            }
        }
    }
    printf("%d", min_num);
    for(int i=0;i<g;i++) if(best_subset & (1<<i)) printf(" %d", i+1);
    printf("\n");
    return 0;
}