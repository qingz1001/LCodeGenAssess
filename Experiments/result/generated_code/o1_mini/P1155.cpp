#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAX_OPS 4005

int main(){
    int n;
    scanf("%d", &n);
    int P[MAXN];
    for(int i=0;i<n;i++) scanf("%d", &P[i]);
    // Assignments: 1 for S1, 2 for S2
    int assign[MAXN];
    int top_S1 = n+1, top_S2 = n+1;
    for(int i=0;i<n;i++){
        if(P[i] < top_S1){
            assign[i] = 1;
            top_S1 = P[i];
        }
        else if(P[i] < top_S2){
            assign[i] = 2;
            top_S2 = P[i];
        }
        else{
            printf("0");
            return 0;
        }
    }
    // Simulate the operations
    char ops[MAX_OPS];
    int ops_cnt = 0;
    int S1[MAXN], top1 = -1;
    int S2[MAXN], top2 = -1;
    int expected = 1;
    int i = 0;
    while(i < n || top1 >=0 || top2 >=0){
        // Pop as much as possible
        int popped = 0;
        while(1){
            if(top1 >=0 && S1[top1] == expected && top2 >=0 && S2[top2] == expected){
                // Prefer 'b'
                ops[ops_cnt++] = 'b';
                top1--;
                expected++;
                popped = 1;
            }
            else if(top1 >=0 && S1[top1] == expected){
                ops[ops_cnt++] = 'b';
                top1--;
                expected++;
                popped = 1;
            }
            else if(top2 >=0 && S2[top2] == expected){
                ops[ops_cnt++] = 'd';
                top2--;
                expected++;
                popped = 1;
            }
            else{
                break;
            }
        }
        if(i < n){
            if(assign[i] == 1){
                ops[ops_cnt++] = 'a';
                S1[++top1] = P[i];
            }
            else{
                ops[ops_cnt++] = 'c';
                S2[++top2] = P[i];
            }
            i++;
        }
        else{
            // No more input, try to pop remaining
            if(!popped){
                break;
            }
        }
    }
    // Final check
    if(expected == n+1){
        for(int j=0;j<ops_cnt;j++){
            if(j >0) printf(" ");
            printf("%c", ops[j]);
        }
    }
    else{
        printf("0");
    }
    return 0;
}