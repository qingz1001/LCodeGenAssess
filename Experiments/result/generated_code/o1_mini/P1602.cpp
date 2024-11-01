#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 1000
#define MAX_QUEUE (MAX_M + 1)

typedef struct {
    int parent;
    int digit;
} State;

int main(){
    int k, m;
    scanf("%d %d", &k, &m);
    
    State states[MAX_M];
    for(int i=0;i<m;i++){
        states[i].parent = -1;
        states[i].digit = -1;
    }
    
    int queue[MAX_QUEUE];
    int front = 0, rear = 0;
    
    // Initialize queue with digits 1 to k-1
    for(int d=1; d<k; d++){
        int rem = d % m;
        if(states[rem].parent == -1){
            states[rem].parent = -2; // Start marker
            states[rem].digit = d;
            queue[rear++] = rem;
            if(rem == 0){
                printf("%d\n", d);
                return 0;
            }
        }
    }
    
    // BFS
    while(front < rear){
        int current = queue[front++];
        for(int d=0; d<k; d++){
            int new_rem = (current * k + d) % m;
            if(states[new_rem].parent == -1){
                states[new_rem].parent = current;
                states[new_rem].digit = d;
                queue[rear++] = new_rem;
                if(new_rem == 0){
                    // Reconstruct number
                    char number[MAX_M + 1];
                    int pos = 0;
                    int rem = new_rem;
                    while(states[rem].parent != -2){
                        number[pos++] = '0' + states[rem].digit;
                        rem = states[rem].parent;
                    }
                    number[pos++] = '0' + states[rem].digit;
                    // Reverse the number
                    for(int i=pos-1; i>=0; i--){
                        putchar(number[i]);
                    }
                    putchar('\n');
                    return 0;
                }
            }
        }
    }
    
    return 0;
}