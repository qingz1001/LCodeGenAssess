#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10001
#define MAX_PREREQ 100

int main(){
    int n;
    if(scanf("%d", &n)!=1){
        return 1;
    }
    int finish_time[MAX_N] = {0};
    int len;
    int prereq;
    for(int i=1;i<=n;i++){
        int task_id;
        if(scanf("%d", &task_id)!=1){
            return 1;
        }
        if(task_id != i){
            return 1;
        }
        if(scanf("%d", &len)!=1){
            return 1;
        }
        int max_dep = 0;
        while(scanf("%d", &prereq)==1 && prereq != 0){
            if(prereq <1 || prereq >=i){
                // invalid prerequisite
                return 1;
            }
            if(finish_time[prereq] > max_dep){
                max_dep = finish_time[prereq];
            }
        }
        finish_time[i] = max_dep + len;
    }
    int result = 0;
    for(int i=1;i<=n;i++){
        if(finish_time[i] > result){
            result = finish_time[i];
        }
    }
    printf("%d\n", result);
    return 0;
}