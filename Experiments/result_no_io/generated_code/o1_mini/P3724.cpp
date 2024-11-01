#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_F 100000000
#define MAX_DAY 100
#define MAX_MC 100
#define MAX_M 20

typedef struct Node {
    int L;
    long long F;
} Node;

typedef struct {
    Node* nodes;
    int size;
    int capacity;
} NodeSet;

void initSet(NodeSet* set) {
    set->capacity = 1000;
    set->size = 0;
    set->nodes = (Node*)malloc(set->capacity * sizeof(Node));
}

void addNode(NodeSet* set, int L, long long F) {
    // Check if already exists
    for(int i=0;i<set->size;i++) {
        if(set->nodes[i].L == L && set->nodes[i].F == F)
            return;
    }
    // Add new node
    if(set->size == set->capacity) {
        set->capacity *=2;
        set->nodes = (Node*)realloc(set->nodes, set->capacity * sizeof(Node));
    }
    set->nodes[set->size].L = L;
    set->nodes[set->size].F = F;
    set->size++;
}

int main(){
    int n, m;
    long long mc;
    scanf("%d %d %lld", &n, &m, &mc);
    int a[MAX_DAY];
    int w[MAX_DAY];
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    for(int i=0;i<n;i++) scanf("%d", &w[i]);
    long long C[MAX_M];
    for(int i=0;i<m;i++) scanf("%lld", &C[i]);

    // Precompute possible F values
    NodeSet current, next_set;
    initSet(&current);
    addNode(&current, 0, 1);
    for(int day=0; day<n; day++){
        initSet(&next_set);
        for(int i=0;i<current.size;i++){
            int L = current.nodes[i].L;
            long long F = current.nodes[i].F;
            // Action3: L +=1, F unchanged
            addNode(&next_set, L+1, F);
            // Action4: if L >=1, F *=L
            if(L >=1){
                if(F * L <= MAX_F){
                    addNode(&next_set, L, F * L);
                }
            }
        }
        // Move to next day
        free(current.nodes);
        current = next_set;
    }

    // Collect all F values
    long long F_values[2000];
    int F_size=0;
    for(int i=0;i<current.size;i++) {
        F_values[F_size++] = current.nodes[i].F;
    }
    free(current.nodes);

    // Remove duplicates and sort
    // Simple bubble sort for small F_size
    for(int i=0;i<F_size-1;i++) {
        for(int j=i+1;j<F_size;j++) {
            if(F_values[i] > F_values[j]){
                long long tmp = F_values[i];
                F_values[i] = F_values[j];
                F_values[j] = tmp;
            }
        }
    }
    // Remove duplicates
    int unique_F_size=0;
    long long unique_F[2000];
    for(int i=0;i<F_size;i++) {
        if(i==0 || F_values[i]!=F_values[i-1]){
            unique_F[unique_F_size++] = F_values[i];
        }
    }

    // Prepare sum of two Fs
    long long sum_F[200000];
    int sum_size=0;
    for(int i=0;i<unique_F_size;i++){
        for(int j=i;j<unique_F_size;j++){
            if(unique_F[i] + unique_F[j] > MAX_F) continue;
            sum_F[sum_size++] = unique_F[i] + unique_F[j];
        }
    }
    // Sort sum_F
    for(int i=0;i<sum_size-1;i++) {
        for(int j=i+1;j<sum_size;j++) {
            if(sum_F[i] > sum_F[j]){
                long long tmp = sum_F[i];
                sum_F[i] = sum_F[j];
                sum_F[j] = tmp;
            }
        }
    }
    // Remove duplicates
    long long unique_sum_F[200000];
    int unique_sum_size=0;
    for(int i=0;i<sum_size;i++) {
        if(i==0 || sum_F[i]!=sum_F[i-1]){
            unique_sum_F[unique_sum_size++] = sum_F[i];
        }
    }

    // For each boss, check possible
    for(int k=0;k<m;k++){
        long long target = C[k];
        int possible =0;
        // k=0
        if(target == n){
            possible =1;
        }
        // k=1
        if(!possible){
            long long req = target - (n-1);
            if(req >=1){
                // Binary search in unique_F
                int left=0, right=unique_F_size-1, found=0;
                while(left <= right){
                    int mid = left + (right - left)/2;
                    if(unique_F[mid] == req){
                        found=1;
                        break;
                    }
                    else if(unique_F[mid] < req) left = mid +1;
                    else right = mid -1;
                }
                if(found) possible =1;
            }
        }
        // k=2
        if(!possible){
            long long req = target - (n-2);
            if(req >=2){
                // Binary search in unique_sum_F
                int left=0, right=unique_sum_size-1, found=0;
                while(left <= right){
                    int mid = left + (right - left)/2;
                    if(unique_sum_F[mid] == req){
                        found=1;
                        break;
                    }
                    else if(unique_sum_F[mid] < req) left = mid +1;
                    else right = mid -1;
                }
                if(found) possible =1;
            }
        }
        printf("%d\n", possible ? 1 : 0);
    }
    return 0;
}