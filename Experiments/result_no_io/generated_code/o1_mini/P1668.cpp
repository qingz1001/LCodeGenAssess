#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int S;
    int E;
} Interval;

// Comparator: first by S ascending, then by E descending
int cmp(const void *a, const void *b){
    Interval *ia = (Interval *)a;
    Interval *ib = (Interval *)b;
    if(ia->S != ib->S)
        return ia->S - ib->S;
    return ib->E - ia->E;
}

int main(){
    int N;
    long long T;
    if(scanf("%d %lld", &N, &T)!=2){
        return 1;
    }
    Interval *arr = (Interval *)malloc(sizeof(Interval)*N);
    for(int i=0;i<N;i++){
        scanf("%d %d", &arr[i].S, &arr[i].E);
    }
    qsort(arr, N, sizeof(Interval), cmp);
    long long current_end = 0;
    int count = 0;
    int i = 0;
    while(current_end < T){
        long long temp = current_end;
        while(i < N && arr[i].S <= current_end +1){
            if(arr[i].E > temp){
                temp = arr[i].E;
            }
            i++;
        }
        if(temp == current_end){
            printf("-1\n");
            free(arr);
            return 0;
        }
        current_end = temp;
        count++;
    }
    printf("%d\n", count);
    free(arr);
    return 0;
}