#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int sum;
    int max1;
    int pre;
    int suf;
    int size;
    int set; // -1: none, 0 or 1
    int flip;
} Node;

int n, m;
int A[100005];
Node tree[400020];

void build(int idx, int l, int r){
    tree[idx].set = -1;
    tree[idx].flip = 0;
    tree[idx].size = r - l + 1;
    if(l == r){
        tree[idx].sum = A[l];
        tree[idx].max1 = A[l];
        tree[idx].pre = A[l];
        tree[idx].suf = A[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2*idx, l, mid);
    build(2*idx+1, mid+1, r);
    Node left = tree[2*idx];
    Node right = tree[2*idx+1];
    tree[idx].sum = left.sum + right.sum;
    tree[idx].pre = left.pre == left.size ? left.pre + right.pre : left.pre;
    tree[idx].suf = right.suf == right.size ? right.suf + left.suf : right.suf;
    tree[idx].max1 = left.suf + right.pre > left.max1 ? (left.suf + right.pre > right.max1 ? left.suf + right.pre : right.max1) : (left.max1 > right.max1 ? left.max1 : right.max1);
}

void push_down(int idx, int l, int r){
    if(tree[idx].set != -1 || tree[idx].flip){
        int mid = (l + r) / 2;
        int left = 2*idx, right = 2*idx+1;
        for(int child = left; child <= right; child++){
            if(tree[idx].set != -1){
                tree[child].set = tree[idx].set;
                tree[child].flip = 0;
                tree[child].sum = tree[idx].set * tree[child].size;
                tree[child].pre = tree[idx].set ? tree[child].size : 0;
                tree[child].suf = tree[idx].set ? tree[child].size : 0;
                tree[child].max1 = tree[idx].set ? tree[child].size : 0;
            }
            if(tree[idx].flip){
                if(tree[child].set != -1){
                    tree[child].set ^=1;
                }
                else{
                    tree[child].flip ^=1;
                }
                tree[child].sum = tree[child].size - tree[child].sum;
                int temp_pre = tree[child].pre;
                tree[child].pre = tree[child].suf;
                tree[child].suf = temp_pre;
                tree[child].max1 = tree[child].max1; // It remains the same
                tree[child].max1 = tree[child].max1; // Actually, max1 remains same since flipping 1s to 0s and vice versa
                // To correctly update max1 after flip
                if(tree[child].set == -1){
                    tree[child].pre = tree[child].pre;
                    tree[child].suf = tree[child].suf;
                    tree[child].max1 = tree[child].max1;
                } else {
                    tree[child].pre = tree[child].set ? tree[child].size : 0;
                    tree[child].suf = tree[child].set ? tree[child].size : 0;
                    tree[child].max1 = tree[child].set ? tree[child].size : 0;
                }
            }
        }
        tree[idx].set = -1;
        tree[idx].flip = 0;
    }
}

void update(int idx, int l, int r, int ul, int ur, int type){
    if(ul > r || ur < l) return;
    if(ul <= l && r <= ur){
        if(type == 0 || type ==1){
            tree[idx].set = type;
            tree[idx].flip = 0;
            tree[idx].sum = type * tree[idx].size;
            tree[idx].pre = type ? tree[idx].size : 0;
            tree[idx].suf = type ? tree[idx].size : 0;
            tree[idx].max1 = type ? tree[idx].size : 0;
        }
        else if(type == 2){
            if(tree[idx].set != -1){
                tree[idx].set ^=1;
                tree[idx].sum = tree[idx].size - tree[idx].sum;
                tree[idx].pre = tree[idx].set ? tree[idx].size : 0;
                tree[idx].suf = tree[idx].set ? tree[idx].size : 0;
                tree[idx].max1 = tree[idx].set ? tree[idx].size : 0;
            }
            else{
                tree[idx].flip ^=1;
                tree[idx].sum = tree[idx].size - tree[idx].sum;
                int temp = tree[idx].pre;
                tree[idx].pre = tree[idx].suf;
                tree[idx].suf = temp;
                tree[idx].max1 = tree[idx].max1; // Same as above
            }
        }
        return;
    }
    push_down(idx, l, r);
    int mid = (l + r) / 2;
    update(2*idx, l, mid, ul, ur, type);
    update(2*idx+1, mid+1, r, ul, ur, type);
    Node left = tree[2*idx];
    Node right = tree[2*idx+1];
    tree[idx].sum = left.sum + right.sum;
    tree[idx].pre = left.pre == left.size ? left.pre + right.pre : left.pre;
    tree[idx].suf = right.suf == right.size ? right.suf + left.suf : right.suf;
    int temp_max = left.suf + right.pre;
    if(temp_max > left.max1){
        tree[idx].max1 = temp_max > right.max1 ? temp_max : right.max1;
    }
    else{
        tree[idx].max1 = left.max1 > right.max1 ? left.max1 : right.max1;
    }
}

typedef struct {
    int sum;
    int max1;
    int pre;
    int suf;
    int size;
} Res;

Res query_sum(int idx, int l, int r, int ql, int qr){
    Res res;
    if(ql > r || qr < l){
        res.sum = 0;
        res.max1 = 0;
        res.pre = 0;
        res.suf = 0;
        res.size = 0;
        return res;
    }
    if(ql <= l && r <= qr){
        res.sum = tree[idx].sum;
        res.max1 = tree[idx].max1;
        res.pre = tree[idx].pre;
        res.suf = tree[idx].suf;
        res.size = tree[idx].size;
        return res;
    }
    push_down(idx, l, r);
    int mid = (l + r) / 2;
    Res left = query_sum(2*idx, l, mid, ql, qr);
    Res right = query_sum(2*idx+1, mid+1, r, ql, qr);
    res.sum = left.sum + right.sum;
    res.pre = left.pre == left.size ? left.pre + right.pre : left.pre;
    res.suf = right.suf == right.size ? right.suf + left.suf : right.suf;
    res.max1 = left.max1;
    if(left.suf + right.pre > res.max1) res.max1 = left.suf + right.pre;
    if(right.max1 > res.max1) res.max1 = right.max1;
    res.size = left.size + right.size;
    return res;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++) scanf("%d", &A[i]);
    build(1, 0, n-1);
    for(int i=0;i<m;i++){
        int type, l, r;
        scanf("%d %d %d", &type, &l, &r);
        if(type == 0 || type ==1 || type ==2){
            update(1, 0, n-1, l, r, type);
        }
        else{
            Res res = query_sum(1, 0, n-1, l, r);
            if(type ==3){
                printf("%d\n", res.sum);
            }
            else{
                printf("%d\n", res.max1);
            }
        }
    }
    return 0;
}