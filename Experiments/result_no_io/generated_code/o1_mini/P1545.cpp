#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000000

typedef struct {
    int *data;
    int head;
    int tail;
    int size;
} deque;

// Initialize deque
void init_deque(deque *dq, int max_size){
    dq->data = (int*)malloc(sizeof(int) * (max_size + 1));
    dq->head = 0;
    dq->tail = 0;
    dq->size = max_size;
}

// Push back
void push_back(deque *dq, int value){
    while(dq->tail > dq->head && dq->data[dq->tail-1] >= value){
        dq->tail--;
    }
    dq->data[dq->tail++] = value;
}

// Pop front if out of window
void pop_front_if_less(deque *dq, int value){
    if(dq->head < dq->tail && dq->data[dq->head] < value){
        dq->head++;
    }
}

// Get front
int get_front(deque *dq){
    if(dq->head < dq->tail){
        return dq->data[dq->head];
    }
    return INF;
}

// Free deque
void free_deque(deque *dq){
    free(dq->data);
}

int main(){
    int N, L;
    scanf("%d %d", &N, &L);
    int A, B;
    scanf("%d %d", &A, &B);
    int s, e;
    int impossible = 0;
    for(int i=0;i<N;i++){
        scanf("%d %d", &s, &e);
        if(e - s > 2 * B){
            impossible = 1;
        }
    }
    if(impossible){
        printf("-1\n");
        return 0;
    }

    // Initialize DP
    int *DP = (int*)malloc(sizeof(int)*(L+1));
    for(int i=0;i<=L;i++) DP[i] = INF;
    DP[0] = 0;

    // Initialize deques for parity 0 and 1
    deque dq0, dq1;
    init_deque(&dq0, L+1);
    init_deque(&dq1, L+1);
    // Push initial j=0
    if(0 %2 ==0){
        push_back(&dq0, 0);
    }
    else{
        push_back(&dq1, 0);
    }

    for(int i=1;i<=L;i++){
        int p = i %2;
        // Determine window [s, e]
        int s_w = i - 2*B;
        if(s_w <0) s_w =0;
        int e_w = i - 2*A;
        if(e_w < s_w){
            // No possible j
            // DP[i] remains INF
        }
        else{
            // Remove j < s_w from deque[p]
            if(p ==0){
                while(dq0.head < dq0.tail && dq0.data[dq0.head] < s_w){
                    dq0.head++;
                }
                // Now, the front of dq0 is the minimum j >= s_w and <= e_w
                if(dq0.head < dq0.tail && dq0.data[dq0.head] <= e_w){
                    DP[i] = DP[dq0.data[dq0.head]] +1;
                }
            }
            else{
                while(dq1.head < dq1.tail && dq1.data[dq1.head] < s_w){
                    dq1.head++;
                }
                // Now, the front of dq1 is the minimum j >= s_w and <= e_w
                if(dq1.head < dq1.tail && dq1.data[dq1.head] <= e_w){
                    DP[i] = DP[dq1.data[dq1.head]] +1;
                }
            }
        }

        // Now, add j = i to the appropriate deque
        // Only if i + 2*A <= L to be useful, but to keep it simple, always add
        if(i + 2*A <= L){
            if(i %2 ==0){
                while(dq0.head < dq0.tail && DP[i] <= DP[dq0.data[dq0.tail-1]]){
                    dq0.tail--;
                }
                dq0.data[dq0.tail++] = i;
            }
            else{
                while(dq1.head < dq1.tail && DP[i] <= DP[dq1.data[dq1.tail-1]]){
                    dq1.tail--;
                }
                dq1.data[dq1.tail++] = i;
            }
        }
    }

    if(DP[L] >= INF){
        printf("-1\n");
    }
    else{
        printf("%d\n", DP[L]);
    }

    // Free memory
    free(DP);
    free_deque(&dq0);
    free_deque(&dq1);
    return 0;
}