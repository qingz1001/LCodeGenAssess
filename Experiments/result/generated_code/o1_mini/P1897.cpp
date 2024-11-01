#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    int aa = *(int*)a;
    int bb = *(int*)b;
    if(aa < bb) return -1;
    if(aa > bb) return 1;
    return 0;
}

int main(){
    int n;
    if(scanf("%d", &n)!=1){
        return 0;
    }
    if(n ==0){
        printf("0");
        return 0;
    }
    int *a = (int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        scanf("%d", &a[i]);
    }
    qsort(a, n, sizeof(int), cmp);
    long long time =0;
    int current_floor =0;
    int i=0;
    while(i <n){
        int floor = a[i];
        int count=1;
        while(i+1 <n && a[i+1]==floor){
            count++;
            i++;
        }
        // Move to floor
        time += (long long)(floor - current_floor)*6;
        // Open doors and people exit
        time +=5 + count;
        current_floor = floor;
        i++;
    }
    // Move back to 0
    if(current_floor >0){
        time += (long long)current_floor *4;
    }
    printf("%lld", time);
    free(a);
    return 0;
}