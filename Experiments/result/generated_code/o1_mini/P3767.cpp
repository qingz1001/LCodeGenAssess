#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100005

typedef struct {
    int type; // 0: parent/diff change, 1: conflict
    int node;
    int old_parent;
    int old_diff;
} Change;

typedef struct Node {
    int l, r;
    struct Node* left;
    struct Node* right;
    int *constraints;
    int cnt;
} Node;

int N, M;
typedef struct {
    int k;
    int t;
    int u;
    int v;
    int x;
} Operation;

Operation ops[MAX];
int start_time[MAX];
int end_time_[MAX];
int constraints_u[MAX];
int constraints_v[MAX];
int constraints_delta[MAX];
int constraint_cnt = 0;

// Stack for rollback
Change stack_changes[MAX * 20];
int stack_top = 0;
int num_conflicts = 0;

// Union-Find structures
int parent_[MAX];
int diff_[MAX];
int rank_[MAX];

// Segment Tree
Node* root;

// Initialize Union-Find
void init_union_find() {
    for(int i=1;i<=N;i++){
        parent_[i] = i;
        diff_[i] = 0;
        rank_[i] = 1;
    }
}

// Find with path compression
int find_set(int u) {
    if(parent_[u] == u) return u;
    int orig_parent = parent_[u];
    int root = find_set(orig_parent);
    // Push changes for rollback
    stack_changes[stack_top].type = 0;
    stack_changes[stack_top].node = u;
    stack_changes[stack_top].old_parent = parent_[u];
    stack_changes[stack_top].old_diff = diff_[u];
    stack_top++;
    diff_[u] = (diff_[u] + diff_[orig_parent]) %5;
    parent_[u] = root;
    return root;
}

// Union with delta
void unite(int u, int v, int delta) {
    int ru = find_set(u);
    int rv = find_set(v);
    if(ru != rv){
        if(rank_[ru] < rank_[rv]){
            ru ^= rv; rv ^= ru; ru ^= rv;
            delta = (5 - delta) %5;
        }
        // Push changes for rollback
        stack_changes[stack_top].type = 0;
        stack_changes[stack_top].node = rv;
        stack_changes[stack_top].old_parent = parent_[rv];
        stack_changes[stack_top].old_diff = diff_[rv];
        stack_top++;
        parent_[rv] = ru;
        diff_[rv] = (diff_[u] + delta - diff_[v] + 5) %5;
        if(rank_[ru] == rank_[rv]){
            stack_changes[stack_top].type = 0;
            stack_changes[stack_top].node = ru;
            stack_changes[stack_top].old_parent = parent_[ru];
            stack_changes[stack_top].old_diff = diff_[ru];
            stack_top++;
            rank_[ru]++;
        }
    }
    else{
        int required = (diff_[v] - diff_[u] - delta +5)%5;
        if(required !=0){
            stack_changes[stack_top].type = 1;
            stack_changes[stack_top].node = -1;
            stack_changes[stack_top].old_parent = -1;
            stack_changes[stack_top].old_diff = -1;
            stack_top++;
            num_conflicts++;
        }
    }
}

// Rollback to a certain stack top
void rollback(int target) {
    while(stack_top > target){
        stack_top--;
        if(stack_changes[stack_top].type == 0){
            int node = stack_changes[stack_top].node;
            parent_[node] = stack_changes[stack_top].old_parent;
            diff_[node] = stack_changes[stack_top].old_diff;
        }
        else{
            num_conflicts--;
        }
    }
}

// Build segment tree
Node* build(int l, int r){
    Node* node = (Node*)malloc(sizeof(Node));
    node->l = l;
    node->r = r;
    node->left = node->right = NULL;
    node->constraints = (int*)malloc(sizeof(int)*10);
    node->cnt = 0;
    if(l != r){
        int mid = (l + r)/2;
        node->left = build(l, mid);
        node->right = build(mid+1, r);
    }
    return node;
}

// Add constraint to segment tree
void add_constraint(Node* node, int l, int r, int constraint_id){
    if(node->r < l || node->l > r) return;
    if(l <= node->l && node->r <= r){
        node->constraints[node->cnt++] = constraint_id;
        return;
    }
    add_constraint(node->left, l, r, constraint_id);
    add_constraint(node->right, l, r, constraint_id);
}

// Traverse and solve
void dfs_traverse(Node* node, char* res){
    int prev = stack_top;
    // Apply all constraints in this segment
    for(int i=0;i<node->cnt;i++){
        int cid = node->constraints[i];
        unite(constraints_u[cid], constraints_v[cid], constraints_delta[cid]);
    }
    if(node->l == node->r){
        if(num_conflicts ==0){
            res[node->l] = '1';
        }
        else{
            res[node->l] = '0';
        }
    }
    else{
        dfs_traverse(node->left, res);
        dfs_traverse(node->right, res);
    }
    // Rollback
    rollback(prev);
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=1;i<=M;i++){
        scanf("%d %d", &ops[i].k, &ops[i].t);
        if(ops[i].t ==1 || ops[i].t ==2){
            scanf("%d %d", &ops[i].u, &ops[i].v);
        }
        else{
            scanf("%d", &ops[i].x);
        }
    }
    // Initialize
    for(int i=1;i<=M;i++){
        start_time[i] = i;
        end_time_[i] = M+1;
    }
    // Map for deletions
    for(int i=1;i<=M;i++){
        if(ops[i].t ==3){
            int x = ops[i].x;
            end_time_[x] = i;
        }
    }
    // Collect constraints
    for(int i=1;i<=M;i++){
        if(ops[i].t ==1 || ops[i].t ==2){
            constraints_u[constraint_cnt] = ops[i].u;
            constraints_v[constraint_cnt] = ops[i].v;
            if(ops[i].t ==1){
                constraints_delta[constraint_cnt] = 1;
            }
            else{
                constraints_delta[constraint_cnt] = 4;
            }
            // Add to segment tree later
            // Store start and end times
            // start_time[i] = i
            // end_time[i] already set
            // We'll use constraint_cnt as id
            // Link operation i to constraint id
            // So when adding constraints, we need to map them
            // Here, we assume each add operation has a unique constraint id
            start_time[i] = i;
            end_time_[i] = end_time_[i];
            constraint_cnt++;
        }
    }
    // Build segment tree
    root = build(1, M);
    // Assign constraints to segment tree
    for(int i=1;i<=M;i++){
        if(ops[i].t ==1 || ops[i].t ==2){
            int cid = i-1;
            add_constraint(root, start_time[i], end_time_[i]-1, i-1);
        }
    }
    // Initialize Union-Find
    init_union_find();
    // Prepare result array
    char* res = (char*)malloc(sizeof(char)*(M+2));
    memset(res, '0', M+1);
    // Traverse and solve
    dfs_traverse(root, res);
    // Output results
    for(int i=1;i<=M;i++){
        if(res[i] == '1') printf("excited\n");
        else printf("naive\n");
    }
    return 0;
}