#include <stdio.h>
#include <stdlib.h>

int n;
int a[65];
int used[65];
int target;
int total;
int sorted_a[65];
int success;

int cmp(const void *a, const void *b){
    return (*(int*)b - *(int*)a);
}

int dfs(int start, int current_sum, int sticks_remaining){
    if(sticks_remaining == 0){
        return 1;
    }
    if(current_sum == target){
        return dfs(0, 0, sticks_remaining -1);
    }
    for(int i = start; i < n; i++){
        if(!used[i] && current_sum + a[i] <= target){
            if(i > 0 && a[i] == a[i-1] && !used[i-1]) continue;
            used[i] = 1;
            if(dfs(i+1, current_sum + a[i], sticks_remaining)){
                return 1;
            }
            used[i] = 0;
            if(current_sum == 0 || current_sum + a[i] == target){
                return 0;
            }
        }
    }
    return 0;
}

int main(){
    scanf("%d", &n);
    total = 0;
    for(int i=0;i<n;i++){
        scanf("%d", &a[i]);
        total += a[i];
    }
    qsort(a, n, sizeof(int), cmp);
    for(target = a[0]; target <= total; target++){
        if(total % target !=0) continue;
        int sticks = total / target;
        for(int i=0;i<n;i++) used[i]=0;
        success = dfs(0, 0, sticks);
        if(success){
            printf("%d\n", target);
            return 0;
        }
    }
    return 0;
}