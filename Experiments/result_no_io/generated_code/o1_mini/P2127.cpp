#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int cmpfunc(const void *a, const void *b) {
    long long aa = *(long long*)a;
    long long bb = *(long long*)b;
    if (aa < bb) return -1;
    else if (aa > bb) return 1;
    else return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    long long *arr = (long long*) malloc(N * sizeof(long long));
    for(int i=0;i<N;i++) scanf("%lld", &arr[i]);
    long long *sorted = (long long*) malloc(N * sizeof(long long));
    for(int i=0;i<N;i++) sorted[i] = arr[i];
    qsort(sorted, N, sizeof(long long), cmpfunc);
    long long global_min = sorted[0];
    char *visited = (char*) calloc(N, sizeof(char));
    long long total_cost = 0;
    for(int i=0;i<N;i++){
        if(!visited[i]){
            int j = i;
            long long cycle_sum = 0;
            long long cycle_min = 1000000001;
            int cycle_size =0;
            while(!visited[j]){
                visited[j] = 1;
                long long val = arr[j];
                cycle_sum += val;
                if(val < cycle_min) cycle_min = val;
                cycle_size++;
                long long *found = (long long*) bsearch(&val, sorted, N, sizeof(long long), cmpfunc);
                if(found == NULL){
                    // This should not happen as all elements are unique
                    break;
                }
                int sorted_idx = found - sorted;
                j = sorted_idx;
            }
            if(cycle_size >1){
                long long option1 = cycle_sum + (cycle_size - 2)*cycle_min;
                long long option2 = cycle_sum + cycle_min + (cycle_size +1)*global_min;
                if(option1 < option2) total_cost += option1;
                else total_cost += option2;
            }
        }
    }
    printf("%lld\n", total_cost);
    free(arr);
    free(sorted);
    free(visited);
    return 0;
}