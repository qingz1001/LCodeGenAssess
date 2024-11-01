#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10001
#define MAX_DEP 100

int main(){
    int n;
    scanf("%d", &n);
    int len[MAX_N];
    int finish_time[MAX_N];
    int dependencies[MAX_N][MAX_DEP];
    int dep_count[MAX_N];
    for(int i=1;i<=n;i++){
        int task_num;
        scanf("%d", &task_num);
        scanf("%d", &len[i]);
        dep_count[i]=0;
        while(1){
            int dep;
            scanf("%d", &dep);
            if(dep ==0) break;
            dependencies[i][dep_count[i]++] = dep;
        }
        if(dep_count[i]==0){
            finish_time[i] = len[i];
        }
        else{
            int max_time =0;
            for(int j=0;j<dep_count[i];j++){
                if(finish_time[dependencies[i][j]] > max_time){
                    max_time = finish_time[dependencies[i][j]];
                }
            }
            finish_time[i] = max_time + len[i];
        }
    }
    int total_time =0;
    for(int i=1;i<=n;i++) {
        if(finish_time[i] > total_time){
            total_time = finish_time[i];
        }
    }
    printf("%d\n", total_time);
    return 0;
}