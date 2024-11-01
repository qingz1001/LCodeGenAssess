#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAXQ 200005

typedef long long ll;

typedef struct Node {
    ll val;
    struct Node *left, *right;
} Node;

Node* build(ll l, ll r, ll *arr){
    Node* node = (Node*)malloc(sizeof(Node));
    if(l == r){
        node->val = arr[l];
        node->left = node->right = NULL;
        return node;
    }
    ll m = (l + r) / 2;
    node->left = build(l, m, arr);
    node->right = build(m+1, r, arr);
    node->val = 0; // Initialize as needed
    return node;
}

Node* update(Node* prev, ll l, ll r, ll pos, ll new_val){
    Node* node = (Node*)malloc(sizeof(Node));
    if(l == r){
        node->val = new_val;
        node->left = node->right = NULL;
        return node;
    }
    ll m = (l + r) / 2;
    if(pos <= m){
        node->left = update(prev->left, l, m, pos, new_val);
        node->right = prev->right;
    }
    else{
        node->left = prev->left;
        node->right = update(prev->right, m+1, r, pos, new_val);
    }
    node->val = 0; // Update as needed
    return node;
}

ll query(Node* root, ll l, ll r, ll pos){
    if(l == r){
        return root->val;
    }
    ll m = (l + r) / 2;
    if(pos <= m) return query(root->left, l, m, pos);
    else return query(root->right, m+1, r, pos);
}

ll n, q;
ll h_init[MAXN];
Node* roots[MAXQ];
int main(){
    scanf("%lld %lld", &n, &q);
    for(int i=1;i<n;i++) scanf("%lld", &h_init[i]);
    roots[0] = build(1, n, h_init);
    for(int i=1;i<=q;i++){
        int type;
        ll a, b, c;
        scanf("%d", &type);
        if(type == 0){
            scanf("%lld %lld %lld", &a, &b, &c);
            roots[i] = update(roots[a], 1, n, b, c);
        }
        else if(type == 1){
            scanf("%lld %lld", &a, &b);
            roots[i] = update(roots[a], 1, n, b, 0);
        }
        else if(type == 2){
            scanf("%lld %lld %lld", &a, &b, &c);
            roots[i] = update(roots[a], 1, n, b, c);
        }
        else if(type == 3){
            scanf("%lld %lld", &a, &b);
            ll res = query(roots[a], 1, n, b);
            printf("%lld\n", res);
            roots[i] = roots[a];
        }
    }
    return 0;
}