#include <stdio.h>
#include <stdlib.h>

int n, b, d;
int solution[64];
int found = 0;

int hamming_distance(int a, int b_val){
    int x = a ^ b_val;
    int count = 0;
    while(x){
        count += x & 1;
        x >>=1;
    }
    return count;
}

int selected[64];
int sel_count =0;

void backtrack(int current){
    if(found) return;
    if(sel_count == n){
        for(int i=0;i<n;i++) solution[i]=selected[i];
        found =1;
        return;
    }
    for(int i=current;i<(1<<b);i++){
        int ok =1;
        for(int j=0;j<sel_count;j++) {
            if(hamming_distance(i, selected[j]) < d){
                ok =0;
                break;
            }
        }
        if(ok){
            selected[sel_count++] = i;
            backtrack(i+1);
            sel_count--;
            if(found) return;
        }
    }
}

int cmp(const void *a, const void *b_val){
    return (*(int*)a - *(int*)b_val);
}

int main(){
    scanf("%d %d %d", &n, &b, &d);
    backtrack(0);
    qsort(solution, n, sizeof(int), cmp);
    for(int i=0;i<n;i++){
        printf("%d", solution[i]);
        if(i != n-1) printf(" ");
        if((i+1)%10 ==0) printf("\n");
    }
    if(n%10 !=0) printf("\n");
    return 0;
}