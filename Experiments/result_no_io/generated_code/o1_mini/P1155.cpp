#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPS 4000

typedef struct {
    int top;
    int data[1001];
} Stack;

int main(){
    int n;
    scanf("%d", &n);
    int P[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &P[i]);
    
    Stack S1, S2;
    S1.top = S2.top = 0;
    int current = 1;
    int pos = 1;
    char operations[MAX_OPS];
    int op_len = 0;
    
    while(current <= n){
        // Try to pop from S1 or S2 if possible
        while(S1.top >0 && S1.data[S1.top] == current){
            operations[op_len++] = 'b';
            S1.top--;
            current++;
        }
        while(S2.top >0 && S2.data[S2.top] == current){
            operations[op_len++] = 'd';
            S2.top--;
            current++;
        }
        if(pos > n) break;
        // Push to S1 (a) first for lex order
        // Save current state
        Stack tempS1 = S1, tempS2 = S2;
        int tempPos = pos;
        char tempOps[MAX_OPS];
        int tempOpLen = op_len;
        
        // Try operation a
        S1.data[++S1.top] = P[pos];
        operations[op_len++] = 'a';
        pos++;
        // After push, check if we can pop
        while(S1.top >0 && S1.data[S1.top] == current){
            operations[op_len++] = 'b';
            S1.top--;
            current++;
        }
        // Continue
    }
    // After all input processed, try to pop remaining
    while(S1.top >0 || S2.top >0){
        if(S1.top >0 && S1.data[S1.top] == current){
            printf("b ");
            S1.top--;
            current++;
            continue;
        }
        if(S2.top >0 && S2.data[S2.top] == current){
            printf("d ");
            S2.top--;
            current++;
            continue;
        }
        // Cannot pop the desired number
        printf("0");
        return 0;
    }
    // Now, print the operations
    if(current == n+1){
        for(int i=0;i<op_len;i++) printf("%c%c", operations[i], i<op_len-1?' ':'\n');
    }
    else{
        printf("0");
    }
    return 0;
}