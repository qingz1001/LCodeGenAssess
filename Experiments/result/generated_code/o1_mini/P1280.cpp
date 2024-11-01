#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int p;
    int t;
} Task;

int compare(const void *a, const void *b){
    Task *ta = (Task*)a;
    Task *tb = (Task*)b;
    if(ta->p != tb->p){
        return ta->p - tb->p;
    }
    return tb->t - ta->t; // Secondary sort not necessary, but can sort by t descending
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    Task *tasks = (Task*)malloc(sizeof(Task)*k);
    for(int i=0;i<k;i++){
        scanf("%d %d", &tasks[i].p, &tasks[i].t);
    }
    qsort(tasks, k, sizeof(Task), compare);
    int available_time =1;
    long long total_work =0;
    int index=0;
    for(int t=1;t<=n;t++){
        int cnt=0;
        int max_dur =0;
        while(index <k && tasks[index].p ==t){
            cnt++;
            if(tasks[index].t > max_dur){
                max_dur = tasks[index].t;
            }
            index++;
        }
        if(cnt >1){
            if(t >= available_time){
                total_work += max_dur;
                available_time = t + max_dur;
            }
        }
        else if(cnt ==1){
            int dur = tasks[index-1].t;
            if(t >= available_time){
                total_work += dur;
                available_time = t + dur;
            }
        }
    }
    printf("%d\n", n - (int)total_work);
    free(tasks);
    return 0;
}