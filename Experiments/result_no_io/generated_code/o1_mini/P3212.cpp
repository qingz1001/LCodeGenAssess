#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int t;
    int a;
    int b;
} Task;

int compare_a_asc(const void *a, const void *b) {
    Task *ta = (Task *)a;
    Task *tb = (Task *)b;
    if (ta->a != tb->a)
        return ta->a - tb->a;
    return 0;
}

int compare_b_desc(const void *a, const void *b) {
    Task *ta = (Task *)a;
    Task *tb = (Task *)b;
    if (tb->b != ta->b)
        return tb->b - ta->b;
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    Task tasks[20];
    int type3_indices[10];
    int k = 0;
    for(int i=0;i<n;i++){
        scanf("%d %d %d", &tasks[i].t, &tasks[i].a, &tasks[i].b);
        if(tasks[i].t == 3){
            type3_indices[k++] = i;
        }
    }
    int total_assignments = 1 << k;
    long long min_makespan = 0;
    // Calculate an initial upper bound
    for(int i=0;i<n;i++){
        min_makespan += tasks[i].a + tasks[i].b;
    }
    for(int mask=0; mask < total_assignments; mask++){
        // Assign orders for type3 tasks
        // Create lists for A->B and B->A
        Task listAB[20];
        int sizeAB = 0;
        Task listBA[20];
        int sizeBA = 0;
        for(int i=0;i<n;i++){
            if(tasks[i].t == 1){
                listAB[sizeAB++] = tasks[i];
            }
            else if(tasks[i].t == 2){
                listBA[sizeBA++] = tasks[i];
            }
            else { // t ==3
                int bit = (mask >> (i < type3_indices[k]? i : 0)) & 1;
                // Determine the bit for this type3 task
                int pos = -1;
                for(int m=0;m<k;m++) if(type3_indices[m] == i){ pos = m; break;}
                if(pos != -1){
                    int assigned = (mask >> pos) & 1;
                    if(assigned){
                        listAB[sizeAB++] = tasks[i];
                    }
                    else{
                        listBA[sizeBA++] = tasks[i];
                    }
                }
            }
        }
        // Sort listAB by a ascending
        qsort(listAB, sizeAB, sizeof(Task), compare_a_asc);
        // Sort listBA by b descending
        qsort(listBA, sizeBA, sizeof(Task), compare_b_desc);
        // Try two group orderings: AB first then BA, and BA first then AB
        for(int order=0; order <2; order++){
            long long machineA = 0;
            long long machineB = 0;
            if(order ==0){
                // AB first
                for(int i=0;i<sizeAB;i++){
                    machineA += listAB[i].a;
                    if(machineA > machineB){
                        machineB = machineA;
                    }
                    machineB += listAB[i].b;
                }
                for(int i=0;i<sizeBA;i++){
                    machineB += listBA[i].b;
                    if(machineB > machineA){
                        machineA = machineB;
                    }
                    machineA += listBA[i].a;
                }
            }
            else{
                // BA first
                for(int i=0;i<sizeBA;i++){
                    machineB += listBA[i].b;
                    if(machineB > machineA){
                        machineA = machineB;
                    }
                    machineA += listBA[i].a;
                }
                for(int i=0;i<sizeAB;i++){
                    machineA += listAB[i].a;
                    if(machineA > machineB){
                        machineB = machineA;
                    }
                    machineB += listAB[i].b;
                }
            }
            long long makespan = (machineA > machineB) ? machineA : machineB;
            if(makespan < min_makespan){
                min_makespan = makespan;
            }
            // Initialize min_makespan on first iteration
            if(mask ==0 && order ==0){
                min_makespan = makespan;
            }
            else{
                if(makespan < min_makespan){
                    min_makespan = makespan;
                }
            }
        }
    }
    printf("%lld\n", min_makespan);
    return 0;
}