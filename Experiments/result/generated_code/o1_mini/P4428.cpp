#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long ll;

typedef struct Node {
    int key;
    int priority;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new treap node
Node* newNode(int key){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->priority = rand();
    node->left = node->right = NULL;
    return node;
}

// Split treap into left (keys < key) and right (keys >= key)
void split(Node* root, int key, Node** left, Node** right){
    if(!root){
        *left = *right = NULL;
    }
    else if(key <= root->key){
        split(root->left, key, left, &(root->left));
        *right = root;
    }
    else{
        split(root->right, key, &(root->right), right);
        *left = root;
    }
}

// Merge two treaps
Node* merge(Node* left, Node* right){
    if(!left || !right)
        return left ? left : right;
    if(left->priority > right->priority){
        left->right = merge(left->right, right);
        return left;
    }
    else{
        right->left = merge(left, right->left);
        return right;
    }
}

// Insert a key into treap
Node* insert(Node* root, Node* node){
    if(!root)
        return node;
    if(node->priority > root->priority){
        split(root, node->key, &(node->left), &(node->right));
        return node;
    }
    if(node->key < root->key)
        root->left = insert(root->left, node);
    else
        root->right = insert(root->right, node);
    return root;
}

// Delete a key from treap
Node* deleteNode(Node* root, int key){
    if(!root)
        return NULL;
    if(root->key == key){
        Node* temp = merge(root->left, root->right);
        free(root);
        return temp;
    }
    if(key < root->key)
        root->left = deleteNode(root->left, key);
    else
        root->right = deleteNode(root->right, key);
    return root;
}

// In-order traversal to collect keys in [l, r]
int keys[100005];
int cnt;
void inorder(Node* root, int l, int r){
    if(!root) return;
    if(root->key > l)
        inorder(root->left, l, r);
    if(root->key >= l && root->key <= r)
        keys[cnt++] = root->key;
    if(root->key < r)
        inorder(root->right, l, r);
}

int main(){
    srand(time(NULL));
    int n;
    scanf("%d", &n);
    int *a = (int*)malloc((n+2)*sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    Node* root = NULL;
    for(int i=1;i<=n;i++) if(a[i]==1) root = insert(root, newNode(i));
    int m;
    scanf("%d", &m);
    while(m--){
        int type;
        scanf("%d", &type);
        if(type ==1){
            int i;
            scanf("%d", &i);
            if(a[i]==1){
                root = deleteNode(root, i);
                a[i]=0;
            }
            else{
                root = insert(root, newNode(i));
                a[i]=1;
            }
        }
        else{
            int l, r;
            scanf("%d %d", &l, &r);
            cnt=0;
            inorder(root, l, r);
            ll total = ((ll)(r-l+1)) * (r-l+2) /2;
            ll sum =0;
            for(int i=0;i<cnt;i++){
                int pos = keys[i];
                int prev = (i>0)? keys[i-1] : l-1;
                int next = (i<cnt-1)? keys[i+1] : r+1;
                ll left = pos - prev -1;
                ll right = next - pos -1;
                sum += (left +1) * (right +1);
            }
            printf("%lld\n", total - sum);
        }
    }
    free(a);
    return 0;
}