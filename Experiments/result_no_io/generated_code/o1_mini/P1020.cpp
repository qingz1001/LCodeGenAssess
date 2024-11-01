#include <stdio.h>
#include <stdlib.h>

// Comparator for qsort in non-decreasing order
int cmp(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    if(x < y) return -1;
    else if(x > y) return 1;
    else return 0;
}

int main(){
    int *a = malloc(sizeof(int)*100005);
    int n = 0;
    while(scanf("%d", &a[n]) != EOF){
        n++;
    }
    
    // Part 1: Longest Non-Increasing Subsequence
    int *tails = malloc(sizeof(int)*n);
    int len = 0;
    for(int i=0;i<n;i++){
        int l=0, r=len;
        while(l < r){
            int m = l + (r - l)/2;
            if(tails[m] < a[i]){
                r = m;
            }
            else{
                l = m +1;
            }
        }
        tails[l] = a[i];
        if(l == len) len++;
    }
    printf("%d\n", len);
    
    // Part 2: Minimum number of sequences
    // We keep the stack tops sorted in ascending order
    int *stacks = malloc(sizeof(int)*n);
    int stack_len = 0;
    for(int i=0;i<n;i++){
        int h = a[i];
        int l=0, r=stack_len;
        while(l < r){
            int m = l + (r - l)/2;
            if(stacks[m] >= h){
                r = m;
            }
            else{
                l = m +1;
            }
        }
        if(l < stack_len){
            stacks[l] = h;
        }
        else{
            stacks[stack_len++] = h;
        }
    }
    printf("%d\n", stack_len);
    
    free(a);
    free(tails);
    free(stacks);
    return 0;
}