#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int sum;
    int prefix;
    int suffix;
    int maxx;
    int assign; // -1: none, 0 or 1
    int invert; // 0: none, 1: invert
} Node;

int n, m;
int A[100005];
Node tree[400020];

void build(int pos, int l, int r){
    tree[pos].assign = -1;
    tree[pos].invert = 0;
    if(l == r){
        tree[pos].sum = A[l];
        tree[pos].prefix = A[l];
        tree[pos].suffix = A[l];
        tree[pos].maxx = A[l];
        return;
    }
    int mid = (l + r) / 2;
    build(pos*2, l, mid);
    build(pos*2+1, mid+1, r);
    tree[pos].sum = tree[pos*2].sum + tree[pos*2+1].sum;
    tree[pos].prefix = tree[pos*2].prefix == mid - l +1 ? tree[pos*2].prefix + tree[pos*2+1].prefix : tree[pos*2].prefix;
    tree[pos].suffix = tree[pos*2+1].suffix == r - mid ? tree[pos*2].suffix + tree[pos*2].prefix : tree[pos*2+1].suffix;
    int temp = tree[pos*2].suffix + tree[pos*2+1].prefix;
    if(temp > tree[pos*2].maxx) tree[pos].maxx = temp;
    if(tree[pos*2+1].maxx > tree[pos].maxx) tree[pos].maxx = tree[pos*2+1].maxx;
}

void push_down(int pos, int l, int r){
    if(tree[pos].assign != -1 || tree[pos].invert){
        int mid = (l + r) / 2;
        int left = pos*2, right = pos*2+1;
        // Apply assign
        if(tree[pos].assign != -1){
            int val = tree[pos].assign;
            tree[left].assign = val;
            tree[left].invert = 0;
            tree[right].assign = val;
            tree[right].invert = 0;
            int llen = mid - l +1, rlen = r - mid;
            tree[left].sum = val * llen;
            tree[left].prefix = tree[left].suffix = tree[left].maxx = val ? llen : 0;
            tree[right].sum = val * rlen;
            tree[right].prefix = tree[right].suffix = tree[right].maxx = val ? rlen : 0;
            tree[pos].assign = -1;
        }
        // Apply invert
        if(tree[pos].invert){
            for(int child = pos*2; child <= pos*2+1; child++){
                if(tree[child].assign != -1){
                    tree[child].assign ^=1;
                }
                else{
                    tree[child].invert ^=1;
                }
                int len;
                // Assuming full range, since we don't store range here
                // We need to calculate based on sum
                // But to keep it simple, just invert the sum, prefix, suffix, maxx
                // which works because it's binary
                tree[child].sum = ( (tree[child].maxx + tree[child].prefix + tree[child].suffix) ) - tree[child].sum;
                int tmp_prefix = tree[child].prefix;
                tree[child].prefix = tree[child].suffix;
                tree[child].suffix = tmp_prefix;
                tree[child].maxx = tree[child].maxx; // remains same
            }
            tree[pos].invert = 0;
        }
    }
}

void update_set(int pos, int l, int r, int ul, int ur, int val){
    if(ul > r || ur < l) return;
    if(ul <= l && r <= ur){
        tree[pos].assign = val;
        tree[pos].invert = 0;
        tree[pos].sum = val * (r - l +1);
        tree[pos].prefix = tree[pos].suffix = tree[pos].maxx = val ? (r - l +1) : 0;
        return;
    }
    push_down(pos, l, r);
    int mid = (l + r) /2;
    update_set(pos*2, l, mid, ul, ur, val);
    update_set(pos*2+1, mid+1, r, ul, ur, val);
    tree[pos].sum = tree[pos*2].sum + tree[pos*2+1].sum;
    tree[pos].prefix = tree[pos*2].prefix == (mid - l +1) ? tree[pos*2].prefix + tree[pos*2+1].prefix : tree[pos*2].prefix;
    tree[pos].suffix = tree[pos*2+1].suffix == (r - mid) ? tree[pos*2+1].suffix + tree[pos*2].suffix : tree[pos*2+1].suffix;
    int temp = tree[pos*2].suffix + tree[pos*2+1].prefix;
    tree[pos].maxx = tree[pos*2].maxx > tree[pos*2+1].maxx ? tree[pos*2].maxx : tree[pos*2+1].maxx;
    if(temp > tree[pos].maxx) tree[pos].maxx = temp;
}

void update_invert(int pos, int l, int r, int ul, int ur){
    if(ul > r || ur < l) return;
    if(ul <= l && r <= ur){
        if(tree[pos].assign != -1){
            tree[pos].assign ^=1;
            tree[pos].sum = (r - l +1) - tree[pos].sum;
            tree[pos].prefix = tree[pos].maxx = tree[pos].suffix = tree[pos].prefix ? (r - l +1) - tree[pos].prefix : (r - l +1);
        }
        else{
            tree[pos].invert ^=1;
            tree[pos].sum = (r - l +1) - tree[pos].sum;
            int tmp = tree[pos].prefix;
            tree[pos].prefix = tree[pos].suffix;
            tree[pos].suffix = tmp;
            // maxx remains the same
        }
        return;
    }
    push_down(pos, l, r);
    int mid = (l + r) /2;
    update_invert(pos*2, l, mid, ul, ur);
    update_invert(pos*2+1, mid+1, r, ul, ur);
    tree[pos].sum = tree[pos*2].sum + tree[pos*2+1].sum;
    tree[pos].prefix = tree[pos*2].prefix == (mid - l +1) ? tree[pos*2].prefix + tree[pos*2+1].prefix : tree[pos*2].prefix;
    tree[pos].suffix = tree[pos*2+1].suffix == (r - mid) ? tree[pos*2+1].suffix + tree[pos*2].suffix : tree[pos*2+1].suffix;
    int temp = tree[pos*2].suffix + tree[pos*2+1].prefix;
    tree[pos].maxx = tree[pos*2].maxx > tree[pos*2+1].maxx ? tree[pos*2].maxx : tree[pos*2+1].maxx;
    if(temp > tree[pos].maxx) tree[pos].maxx = temp;
}

typedef struct {
    int sum;
    int prefix;
    int suffix;
    int maxx;
} Res;

Res query_sum(int pos, int l, int r, int ql, int qr){
    Res res = {0,0,0,0};
    if(ql > r || qr < l) return res;
    if(ql <= l && r <= qr){
        res.sum = tree[pos].sum;
        res.prefix = tree[pos].prefix;
        res.suffix = tree[pos].suffix;
        res.maxx = tree[pos].maxx;
        return res;
    }
    push_down(pos, l, r);
    int mid = (l + r) /2;
    Res left = query_sum(pos*2, l, mid, ql, qr);
    Res right = query_sum(pos*2+1, mid+1, r, ql, qr);
    res.sum = left.sum + right.sum;
    res.prefix = left.prefix == (mid - l +1) ? left.prefix + right.prefix : left.prefix;
    res.suffix = right.suffix == (qr - mid) ? right.suffix + left.suffix : right.suffix;
    res.maxx = left.maxx > right.maxx ? left.maxx : right.maxx;
    if(left.suffix + right.prefix > res.maxx) res.maxx = left.suffix + right.prefix;
    return res;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++) scanf("%d", &A[i]);
    build(1, 0, n-1);
    for(int i=0;i<m;i++){
        int type, l, r;
        scanf("%d %d %d", &type, &l, &r);
        if(type == 0){
            update_set(1, 0, n-1, l, r, 0);
        }
        else if(type ==1){
            update_set(1, 0, n-1, l, r, 1);
        }
        else if(type ==2){
            update_invert(1, 0, n-1, l, r);
        }
        else{
            Res ans = query_sum(1, 0, n-1, l, r);
            if(type ==3){
                printf("%d\n", ans.sum);
            }
            else{
                printf("%d\n", ans.maxx);
            }
        }
    }
    return 0;
}