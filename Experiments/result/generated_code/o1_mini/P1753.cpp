#include <stdio.h>
#include <stdlib.h>

#define MAXN 2000001
#define LOGK 21

int w_arr[MAXN];
int log_table[MAXN];
int st[LOGK][2000001];
int main(){
    int n;
    scanf("%d", &n);
    for(int i=0;i<=n;i++) scanf("%d", &w_arr[i]);

    // Build log table
    log_table[1] = 0;
    for(int i=2;i<=n;i++) log_table[i] = log_table[i/2] +1;

    // Initialize st[0][i] = i+1 (1-based indexing)
    for(int i=0;i<n;i++) st[0][i] = i+1;

    // Build Sparse Table
    for(int k=1; k < LOGK; k++){
        for(int i=0; i + (1<<k) <= n; i++){
            int x = st[k-1][i];
            int y = st[k-1][i + (1 << (k-1))];
            if(w_arr[x] < w_arr[y]){
                st[k][i] = x;
            }
            else{
                st[k][i] = y;
            }
        }
    }

    // Allocate stack
    // Maximum stack size is roughly 2n
    int *stack_l = (int *)malloc(sizeof(int) * (2*n));
    int *stack_r = (int *)malloc(sizeof(int) * (2*n));
    if(!stack_l || !stack_r){
        return 1;
    }
    int top =0;
    stack_l[top] =0;
    stack_r[top] =n;
    top++;

    long long total_cost =0;

    // Define a function to find the index with minimum w in [l, r]
    // Using the Sparse Table
    // l and r are 1-based indices
    // Returns the index with the smallest w in [l, r]
    #define FIND_MIN(l, r) ({ \
        int length = (r) - (l) +1; \
        int j = log_table[length]; \
        int x = st[j][(l)-1]; \
        int y = st[j][(r) - (1<<j)]; \
        (w_arr[x] < w_arr[y] ? x : y); \
    })

    while(top >0){
        top--;
        int l = stack_l[top];
        int r = stack_r[top];
        if(l +1 >= r) continue;
        int k = FIND_MIN(l+1, r-1);
        total_cost += (long long)w_arr[l] * w_arr[k] * w_arr[r];
        // Push [l, k] and [k, r] to stack
        stack_l[top] = l;
        stack_r[top] = k;
        top++;
        stack_l[top] = k;
        stack_r[top] = r;
        top++;
    }

    printf("%lld\n", total_cost);

    free(stack_l);
    free(stack_r);
    return 0;
}