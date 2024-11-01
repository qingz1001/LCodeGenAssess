#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int p;
    int t;
} Task;

int compare(const void *a, const void *b) {
    Task *ta = (Task *)a;
    Task *tb = (Task *)b;
    if (ta->p != tb->p)
        return ta->p - tb->p;
    return ta->t - tb->t;
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    Task *tasks = (Task *)malloc(k * sizeof(Task));
    for(int i=0;i<k;i++) {
        scanf("%d %d", &tasks[i].p, &tasks[i].t);
    }
    qsort(tasks, k, sizeof(Task), compare);
    int next_available = 1;
    long long busy = 0;
    int i = 0;
    while(i < k){
        int current_p = tasks[i].p;
        int j = i;
        while(j < k && tasks[j].p == current_p){
            j++;
        }
        int count = j - i;
        if(current_p >= next_available){
            if(count >=1){
                // Choose the first task (smallest t)
                busy += tasks[i].t;
                next_available = current_p + tasks[i].t;
            }
        }
        i = j;
    }
    long long free_time = n - busy;
    printf("%lld\n", free_time);
    free(tasks);
    return 0;
}