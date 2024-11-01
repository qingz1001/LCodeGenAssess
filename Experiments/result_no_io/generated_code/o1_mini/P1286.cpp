#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUMS 36
#define MAX_NUMS 9

int compare_int(const void *a, const void *b){
    int ai = *(int*)a;
    int bi = *(int*)b;
    if(ai < bi) return -1;
    if(ai > bi) return 1;
    return 0;
}

int backtrack(int n, int a[], int k, int sorted_sums[], int sum_count, int used[]){
    if(k == n){
        return 1;
    }
    for(int i=0; i < sum_count; i++){
        if(!used[i]){
            // To ensure sorted order
            if(k >1 && sorted_sums[i] < a[k-1]){
                continue;
            }
            // Assign a[k]
            a[k] = sorted_sums[i];
            int indices_to_use[MAX_NUMS];
            int valid = 1;
            for(int j=0; j < k; j++){
                int s = a[k] + a[j];
                int found = 0;
                for(int m=0; m < sum_count; m++){
                    if(!used[m] && sorted_sums[m] == s){
                        indices_to_use[j] = m;
                        found = 1;
                        break;
                    }
                }
                if(!found){
                    valid = 0;
                    break;
                }
            }
            if(valid){
                // Mark the used sums
                for(int j=0; j < k; j++){
                    used[indices_to_use[j]] = 1;
                }
                // Recurse
                if(backtrack(n, a, k+1, sorted_sums, sum_count, used)){
                    return 1;
                }
                // Unmark the used sums
                for(int j=0; j < k; j++){
                    used[indices_to_use[j]] = 0;
                }
            }
        }
    }
    return 0;
}

int main(){
    int n;
    while(scanf("%d", &n) != EOF){
        if(n <2 || n >=10){
            // Invalid n, skip
            int skip = n*(n-1)/2;
            for(int i=0;i<skip;i++){
                int tmp;
                scanf("%d", &tmp);
            }
            printf("Impossible\n");
            continue;
        }
        int total_sums = n*(n-1)/2;
        int sums[MAX_SUMS];
        for(int i=0;i<total_sums;i++){
            scanf("%d", &sums[i]);
        }
        qsort(sums, total_sums, sizeof(int), compare_int);
        // Initialize a
        int a[MAX_NUMS];
        a[0] = 0;
        a[1] = sums[0];
        // Initialize used array
        int used[MAX_SUMS];
        memset(used, 0, sizeof(used));
        used[0] =1;
        // Remove a[1]
        // Now prepare sorted_sums
        int sorted_sums[MAX_SUMS];
        memcpy(sorted_sums, sums, sizeof(int)*total_sums);
        // Initialize a list with a[0] and a[1]
        // Now, assign a from index 2
        // Collect the remaining sums after removing a[1]
        // To handle multiple instances, use the used array
        // Now call backtrack
        if(backtrack(n, a, 2, sorted_sums, total_sums, used)){
            // Print the solution
            // Sort a just in case
            qsort(a, n, sizeof(int), compare_int);
            for(int i=0;i<n;i++){
                if(i>0) printf(" ");
                printf("%d", a[i]);
            }
            printf("\n");
        }
        else{
            printf("Impossible\n");
        }
    }
    return 0;
}