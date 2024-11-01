#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct Node {
    int id;
    int C;
    int L;
    struct Node** children;
    int child_count;
    int child_capacity;
} Node;

ll max_val = 0;
long long M;
Node* nodes_ptr[100005];

void add_child(Node* parent, Node* child) {
    if (parent->child_count == parent->child_capacity) {
        parent->child_capacity = parent->child_capacity == 0 ? 4 : parent->child_capacity * 2;
        parent->children = realloc(parent->children, parent->child_capacity * sizeof(Node*));
    }
    parent->children[parent->child_count++] = child;
}

ll dfs(Node* root, ll* size, ll* sum) {
    *size = 1;
    *sum = root->C;
    for(int i=0;i<root->child_count;i++) {
        ll child_size, child_sum;
        dfs(root->children[i], &child_size, &child_sum);
        *size += child_size;
        *sum += child_sum;
    }
    if(*sum <= M){
        ll satisfaction = (*size) * (ll)(root->L);
        if(satisfaction > max_val){
            max_val = satisfaction;
        }
    }
    return *sum;
}

int main(){
    int N;
    scanf("%d %lld", &N, &M);
    for(int i=1;i<=N;i++){
        nodes_ptr[i] = (Node*)malloc(sizeof(Node));
        nodes_ptr[i]->id = i;
        nodes_ptr[i]->children = NULL;
        nodes_ptr[i]->child_count = 0;
        nodes_ptr[i]->child_capacity = 0;
        int B, C, L;
        scanf("%d %d %d", &B, &C, &L);
        nodes_ptr[i]->C = C;
        nodes_ptr[i]->L = L;
        if(B != 0){
            add_child(nodes_ptr[B], nodes_ptr[i]);
        }
    }
    // Find root
    Node* root = NULL;
    for(int i=1;i<=N;i++){
        int B;
        // Assuming B was read earlier, but not stored. Instead, find B=0
        // Alternatively, track during input
        // For simplicity, assume node with id=1 is root if B_i=0
        // But better track it
        // Modify input reading to track root
    }
    // Find root
    for(int i=1;i<=N;i++){
        // To find root, check B_i=0
        // But B_i was not stored, need to read again or store during input
        // Modify the input reading to store B_i
        // Restart
        // Re-implement input with tracking root
        break;
    }
    // Re-implement with tracking root
    // Reset
    freopen(NULL, "r", stdin);
    scanf("%d %lld", &N, &M);
    Node* root_new = NULL;
    for(int i=1;i<=N;i++){
        nodes_ptr[i] = (Node*)malloc(sizeof(Node));
        nodes_ptr[i]->id = i;
        nodes_ptr[i]->children = NULL;
        nodes_ptr[i]->child_count = 0;
        nodes_ptr[i]->child_capacity = 0;
        int B, C, L;
        scanf("%d %d %d", &B, &C, &L);
        nodes_ptr[i]->C = C;
        nodes_ptr[i]->L = L;
        if(B == 0){
            root_new = nodes_ptr[i];
        }
        else{
            add_child(nodes_ptr[B], nodes_ptr[i]);
        }
    }
    if(root_new != NULL){
        ll size, total;
        dfs(root_new, &size, &total);
    }
    printf("%lld\n", max_val);
    // Free memory
    for(int i=1;i<=N;i++){
        free(nodes_ptr[i]->children);
        free(nodes_ptr[i]);
    }
    return 0;
}