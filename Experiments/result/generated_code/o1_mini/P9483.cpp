#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll weight;
    ll wear;
} Stack;

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        Stack stacks[n];
        for(int i=0;i<n;i++){
            scanf("%lld", &stacks[i].weight);
            stacks[i].wear = 0;
        }
        ll total_cost = 0;
        int size = n;
        while(size >1){
            // Find the best pair to merge
            ll min_cost = 1e18;
            int merge_i = -1, merge_j = -1;
            int push_dir = 0; // 0: push i to j, 1: push j to i
            for(int i=0;i<size;i++){
                for(int j=i+1;j<size;j++){
                    // Cost to push i onto j
                    ll cost1 = stacks[i].weight + stacks[i].wear + stacks[j].wear;
                    if(cost1 < min_cost){
                        min_cost = cost1;
                        merge_i = i;
                        merge_j = j;
                        push_dir = 0;
                    }
                    // Cost to push j onto i
                    ll cost2 = stacks[j].weight + stacks[i].wear + stacks[j].wear;
                    if(cost2 < min_cost){
                        min_cost = cost2;
                        merge_i = i;
                        merge_j = j;
                        push_dir = 1;
                    }
                }
            }
            if(merge_i == -1 || merge_j == -1){
                break;
            }
            total_cost += min_cost;
            // Create new stack
            Stack new_stack;
            if(push_dir ==0){
                // Push i onto j
                new_stack.weight = stacks[merge_i].weight + stacks[merge_j].weight;
            }
            else{
                // Push j onto i
                new_stack.weight = stacks[merge_i].weight + stacks[merge_j].weight;
            }
            // Calculate new wear
            if(stacks[merge_i].wear > stacks[merge_j].wear){
                new_stack.wear = stacks[merge_i].wear * 2 +1;
            }
            else{
                new_stack.wear = stacks[merge_j].wear * 2 +1;
            }
            // Remove merge_i and merge_j
            // Replace merge_i with new_stack and remove merge_j
            stacks[merge_i] = new_stack;
            // Move the last stack to merge_j
            stacks[merge_j] = stacks[size-1];
            size--;
        }
        printf("%lld\n", total_cost);
    }
    return 0;
}