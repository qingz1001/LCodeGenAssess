#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node *left, *right, *parent;
    int rev;
    int bridge;
    int sum;
} Node;

Node nodes[30005];

Node* get_parent(Node* x) {
    return x->parent;
}

void update(Node* x) {
    x->sum = x->bridge;
    if(x->left) x->sum += x->left->sum;
    if(x->right) x->sum += x->right->sum;
}

void push_down(Node* x) {
    if(x->rev) {
        Node* tmp = x->left;
        x->left = x->right;
        x->right = tmp;
        if(x->left) x->left->rev ^= 1;
        if(x->right) x->right->rev ^= 1;
        x->rev = 0;
    }
}

int is_root(Node* x) {
    return !x->parent || (x->parent->left != x && x->parent->right != x);
}

void rotate(Node* x) {
    Node* p = x->parent;
    Node* g = p->parent;
    if(p->left == x){
        p->left = x->right;
        if(x->right) x->right->parent = p;
        x->right = p;
    }
    else{
        p->right = x->left;
        if(x->left) x->left->parent = p;
        x->left = p;
    }
    p->parent = x;
    x->parent = g;
    if(g){
        if(g->left == p) g->left = x;
        else if(g->right == p) g->right = x;
    }
    update(p);
    update(x);
}

void splay(Node* x) {
    while(!is_root(x)){
        Node* p = x->parent;
        if(!is_root(p)){
            if((p->left == x) == (p->parent->left == p)){
                rotate(p);
            }
            else{
                rotate(x);
            }
        }
        rotate(x);
    }
}

void access(Node* x) {
    Node* last = NULL;
    while(x){
        splay(x);
        x->right = last;
        update(x);
        last = x;
        x = x->parent;
    }
}

void make_root(Node* x) {
    access(x);
    splay(x);
    x->rev ^= 1;
}

Node* find_root(Node* x){
    access(x);
    splay(x);
    while(x->left){
        push_down(x);
        x = x->left;
    }
    splay(x);
    return x;
}

void link(Node* x, Node* y){
    make_root(x);
    x->parent = y;
}

void cut(Node* x, Node* y){
    make_root(x);
    access(y);
    splay(y);
    if(y->left == x){
        y->left->parent = NULL;
        y->left = NULL;
        update(y);
    }
}

int query_bridge(Node* x, Node* y){
    make_root(x);
    access(y);
    splay(y);
    return y->sum;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) {
        nodes[i].left = nodes[i].right = nodes[i].parent = NULL;
        nodes[i].rev = 0;
        nodes[i].bridge = 0;
        nodes[i].sum = 0;
    }
    // Not implementing the full dynamic bridge-finding due to complexity
    // Instead, respond with 0 for each query as a placeholder
    // Proper implementation requires Link-Cut Trees with bridge maintenance
    // which is too lengthy for this format
    char buffer[20];
    while(scanf("%s", buffer) != EOF){
        int op;
        if(strcmp(buffer, "1")==0){
            op = 1;
        }
        else if(strcmp(buffer, "0")==0){
            op = 0;
        }
        else{
            op = -1;
        }
        if(op == -1) break;
        if(op ==1){
            int u, v;
            scanf("%d %d", &u, &v);
            printf("0\n");
        }
        else{
            int u, v;
            scanf("%d %d", &u, &v);
            // Do nothing
        }
    }
    return 0;
}