#include <stdio.h>
#include <stdlib.h>

#define MAX_A 1000000
#define MAX_N 10000

int main(){
    int n;
    scanf("%d", &n);
    int *a = (int*)malloc(n * sizeof(int));
    int max_a = 0;
    for(int i=0;i<n;i++){
        scanf("%d", &a[i]);
        if(a[i] > max_a){
            max_a = a[i];
        }
    }
    // Allocate frequency array
    int *freq = (int*)calloc(max_a +1, sizeof(int));
    for(int i=0;i<n;i++){
        freq[a[i]]++;
    }
    // Allocate cnt_mult array
    int *cnt_mult = (int*)calloc(max_a +1, sizeof(int));
    for(int G=1; G<=max_a; G++){
        for(int m=G; m<=max_a; m +=G){
            cnt_mult[G] += freq[m];
        }
    }
    // Allocate answer array
    int *ans = (int*)calloc(n +1, sizeof(int));
    for(int G = max_a; G >=1; G--){
        if(cnt_mult[G] >=1){
            int limit = cnt_mult[G] < n ? cnt_mult[G] : n;
            for(int k=1; k<=limit; k++){
                if(ans[k]==0){
                    ans[k] = G;
                }
            }
        }
    }
    // Print answers
    for(int k=1; k<=n; k++){
        printf("%d\n", ans[k]);
    }
    // Free allocated memory
    free(a);
    free(freq);
    free(cnt_mult);
    free(ans);
    return 0;
}