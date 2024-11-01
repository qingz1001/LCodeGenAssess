#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Maximum limits
#define MAXN 100005
#define MAXQ 300005
#define MAXTREESIZE 4000000

typedef struct TreapNode {
    int key; // p_i
    int data; // island index
    int priority;
    int size;
    int left;
    int right;
} TreapNode;

TreapNode treapNodes[MAXTREESIZE];
int treapCnt = 0;

int new_node(int key, int data) {
    treapNodes[treapCnt].key = key;
    treapNodes[treapCnt].data = data;
    treapNodes[treapCnt].priority = rand();
    treapNodes[treapCnt].size = 1;
    treapNodes[treapCnt].left = -1;
    treapNodes[treapCnt].right = -1;
    return treapCnt++;
}

int get_size(int root) {
    if (root == -1) return 0;
    return treapNodes[root].size;
}

void update_size(int root) {
    if (root == -1) return;
    treapNodes[root].size = 1 + get_size(treapNodes[root].left) + get_size(treapNodes[root].right);
}

int merge(int left, int right) {
    if (left == -1) return right;
    if (right == -1) return left;
    if (treapNodes[left].priority > treapNodes[right].priority) {
        treapNodes[left].right = merge(treapNodes[left].right, right);
        update_size(left);
        return left;
    }
    else {
        treapNodes[right].left = merge(left, treapNodes[right].left);
        update_size(right);
        return right;
    }
}

void split(int root, int key, int* left, int* right) {
    if (root == -1) {
        *left = -1;
        *right = -1;
        return;
    }
    if (key < treapNodes[root].key) {
        split(treapNodes[root].left, key, left, &treapNodes[root].left);
        update_size(root);
        *right = root;
    }
    else {
        split(treapNodes[root].right, key, &treapNodes[root].right, right);
        update_size(root);
        *left = root;
    }
}

int kth(int root, int k) {
    if (root == -1) return -1;
    int left_size = get_size(treapNodes[root].left);
    if (k <= left_size) {
        return kth(treapNodes[root].left, k);
    }
    else if (k == left_size + 1) {
        return treapNodes[root].data;
    }
    else {
        return kth(treapNodes[root].right, k - left_size - 1);
    }
}

// DSU structures
int parent[MAXN];
int treapRoot[MAXN];

int find_set(int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

int main(){
    srand(time(0));
    int n, m;
    scanf("%d %d", &n, &m);
    int p[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &p[i]);
    // Initialize DSU
    for(int i=1;i<=n;i++){
        parent[i] = i;
        treapRoot[i] = new_node(p[i], i);
    }
    // Read initial bridges
    for(int i=0;i<m;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        int fu = find_set(u);
        int fv = find_set(v);
        if(fu != fv){
            // Union by size
            if(treapNodes[treapRoot[fu]].size < treapNodes[treapRoot[fv]].size){
                parent[fu] = fv;
                treapRoot[fv] = merge(treapRoot[fu], treapRoot[fv]);
            }
            else{
                parent[fv] = fu;
                treapRoot[fu] = merge(treapRoot[fu], treapRoot[fv]);
            }
        }
    }
    int q;
    scanf("%d", &q);
    char op;
    int x, y;
    for(int i=0;i<q;i++){
        scanf(" %c %d %d", &op, &x, &y);
        if(op == 'B'){
            int fu = find_set(x);
            int fv = find_set(y);
            if(fu != fv){
                if(treapNodes[treapRoot[fu]].size < treapNodes[treapRoot[fv]].size){
                    parent[fu] = fv;
                    treapRoot[fv] = merge(treapRoot[fu], treapRoot[fv]);
                }
                else{
                    parent[fv] = fu;
                    treapRoot[fu] = merge(treapRoot[fu], treapRoot[fv]);
                }
            }
        }
        else if(op == 'Q'){
            int fu = find_set(x);
            if(treapNodes[treapRoot[fu]].size < y || y <=0){
                printf("-1\n");
            }
            else{
                int res = kth(treapRoot[fu], y);
                printf("%d\n", res);
            }
        }
    }
    return 0;
}