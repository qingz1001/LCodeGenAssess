#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAXM 500005
#define MOD 1000000007

typedef long long ll;

// BIT structure for standard BIT
typedef struct {
    int size;
    ll tree[MAXN];
} BIT;

// Initialize BIT
void BIT_init(BIT *b, int size){
    b->size = size;
    memset(b->tree, 0, sizeof(ll)*(size+1));
}

// Add to BIT
void BIT_add(BIT *b, int idx, ll val){
    while(idx <= b->size){
        b->tree[idx] = (b->tree[idx] + val) % MOD;
        idx += idx & -idx;
    }
}

// Query prefix sum BIT
ll BIT_query(BIT *b, int idx){
    ll res = 0;
    while(idx > 0){
        res = (res + b->tree[idx]) % MOD;
        idx -= idx & -idx;
    }
    return res;
}

// BIT structure for range addition and point query
typedef struct {
    int size;
    ll tree[MAXN];
} BIT_range;

// Initialize BIT_range
void BIT_range_init(BIT_range *b, int size){
    b->size = size;
    memset(b->tree, 0, sizeof(ll)*(size+1));
}

// Range add in BIT_range
void BIT_range_add(BIT_range *b, int l, int r, ll val){
    int idx = l;
    while(idx <= b->size){
        b->tree[idx] = (b->tree[idx] + val) % MOD;
        idx += idx & -idx;
    }
    idx = r +1;
    while(idx <= b->size){
        b->tree[idx] = (b->tree[idx] - val + MOD) % MOD;
        idx += idx & -idx;
    }
}

// Point query in BIT_range
ll BIT_range_query(BIT_range *b, int idx){
    ll res = 0;
    while(idx >0){
        res = (res + b->tree[idx]) % MOD;
        idx -= idx & -idx;
    }
    return res;
}

// Struct for sorted A and B
typedef struct {
    int val;
    int id;
} Pair;

// Comparison functions
int cmpA(const void *a, const void *b){
    Pair *aa = (Pair*)a;
    Pair *bb = (Pair*)b;
    if(aa->val != bb->val)
        return aa->val - bb->val;
    return aa->id - bb->id;
}

int cmpB(const void *a, const void *b){
    Pair *aa = (Pair*)a;
    Pair *bb = (Pair*)b;
    if(aa->val != bb->val)
        return aa->val - bb->val;
    return aa->id - bb->id;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    ll a[MAXN];
    for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
    // Compute A_j and B_j
    ll A[MAXN], Bj[MAXN];
    for(int i=1;i<=n;i++){
        A[i] = (a[i] >=0)? (ll)(i < (n -i +1) ? i : (n -i +1)) : 0;
        A[i] = (i < (n -i +1)) ? i : (n -i +1);
        Bj[i] = (ll)(A[i] == i ? (n -i +1) : i);
    }
    // Prepare sorted_A and sorted_B
    Pair sorted_A_arr[MAXN];
    Pair sorted_B_arr[MAXN];
    for(int i=1;i<=n;i++){
        sorted_A_arr[i-1].val = A[i];
        sorted_A_arr[i-1].id = i;
        sorted_B_arr[i-1].val = Bj[i];
        sorted_B_arr[i-1].id = i;
    }
    qsort(sorted_A_arr, n, sizeof(Pair), cmpA);
    qsort(sorted_B_arr, n, sizeof(Pair), cmpB);
    // Map j to posA and posB
    int posA[MAXN], posB[MAXN];
    for(int i=0;i<n;i++){
        posA[sorted_A_arr[i].id] = i+1;
        posB[sorted_B_arr[i].id] = i+1;
    }
    // Initialize BIT_A and BIT_A2
    BIT BIT_A, BIT_A2;
    BIT_init(&BIT_A, n);
    BIT_init(&BIT_A2, n);
    for(int i=1;i<=n;i++){
        int idx = posA[i];
        BIT_add(&BIT_A, idx, a[i]);
        ll temp = ((A[i]*(A[i]+1)/2)%MOD) * a[i] % MOD;
        BIT_add(&BIT_A2, idx, temp);
    }
    // Initialize BIT_range_A_a
    BIT_range range_A_a;
    BIT_range_init(&range_A_a, n);
    for(int i=1;i<=n;i++){
        if(A[i]+1 <= Bj[i]){
            BIT_range_add(&range_A_a, A[i]+1, Bj[i], (A[i]*a[i])%MOD);
        }
    }
    // Initialize BIT_B and BIT_B2
    BIT BIT_B, BIT_B2;
    BIT_init(&BIT_B, n);
    BIT_init(&BIT_B2, n);
    for(int i=1;i<=n;i++){
        int idx = posB[i];
        ll temp1 = (Bj[i] * a[i]) % MOD;
        ll temp2 = (Bj[i] * Bj[i]) % MOD;
        temp2 = (temp2 * a[i]) % MOD;
        BIT_add(&BIT_B, idx, temp1);
        BIT_add(&BIT_B2, idx, temp2);
    }
    // Process operations
    char op[2];
    for(int q=0; q<m; q++){
        scanf("%s", op);
        if(op[0]=='1'){
            int u, v;
            ll d;
            scanf("%d %d %lld", &u, &v, &d);
            // Update j from u to v
            // Since A and B are arbitrary, need to iterate j from u to v
            for(int j=u; j<=v; j++){
                ll old_a = a[j];
                a[j] = (a[j] + d) % MOD;
                // Update BIT_A
                BIT_add(&BIT_A, posA[j], d);
                // Update BIT_A2
                ll temp = (A[j]*(A[j]+1)/2)%MOD;
                temp = (temp * d) % MOD;
                BIT_add(&BIT_A2, posA[j], temp);
                // Update BIT_range_A_a
                if(A[j]+1 <= Bj[j]){
                    BIT_range_add(&range_A_a, A[j]+1, Bj[j], (A[j]*d)%MOD);
                }
                // Update BIT_B and BIT_B2
                BIT_add(&BIT_B, posB[j], (Bj[j] * d) % MOD);
                ll tempB2 = (Bj[j] * Bj[j]) % MOD;
                tempB2 = (tempB2 * d) % MOD;
                BIT_add(&BIT_B2, posB[j], tempB2);
            }
        }
        else{
            int l, r;
            scanf("%d %d", &l, &r);
            // term1:
            // Find pos_l and pos_r in sorted_A where A_j >=l and A_j <=r
            // Binary search for lower_bound(l)
            int left = 1, right_pos = n, pos_l = n+1;
            while(left <= right_pos){
                int mid = (left + right_pos)/2;
                if(sorted_A_arr[mid-1].val >= l){
                    pos_l = mid;
                    right_pos = mid -1;
                }
                else{
                    left = mid +1;
                }
            }
            // Binary search for upper_bound(r)
            left = 1; right_pos = n; int pos_r_sortedA = 0;
            while(left <= right_pos){
                int mid = (left + right_pos)/2;
                if(sorted_A_arr[mid-1].val <= r){
                    pos_r_sortedA = mid;
                    left = mid +1;
                }
                else{
                    right_pos = mid -1;
                }
            }
            // sum1
            ll sum1 = (BIT_A2.query(&BIT_A2, pos_r_sortedA) - BIT_A2.query(&BIT_A2, pos_l-1)) % MOD;
            // sum_A_sum
            ll sum_A_sum = (BIT_query(&BIT_A, pos_r_sortedA) - BIT_query(&BIT_A, pos_l-1)) % MOD;
            // sum2
            ll sum2 = ((-( ((l-1) * l /2 ) % MOD)) * sum_A_sum) % MOD;
            // common
            ll common = (((r * (r +1) /2) % MOD) - (((ll)(l-1) * (ll)l /2) % MOD) + MOD) % MOD;
            // sum_a_gt_r
            ll sum_a_gt_r = (BIT_query(&BIT_A, n) - BIT_query(&BIT_A, pos_r_sortedA)) % MOD;
            // sum4
            ll sum4 = (common * sum_a_gt_r) % MOD;
            // term1
            ll term1 = (sum1 + sum2 + sum4) % MOD;
            // term2
            ll sum_A_a = 0;
            if(l <=r){
                for(int k=l; k<=r; k++) {
                    sum_A_a = (sum_A_a + BIT_range_query(&range_A_a, k)) % MOD;
                }
            }
            // term3:
            // sum_B_a = (r - l +1)*BIT_B.query(l-1) + r*(BIT_B.query(r-1) - BIT_B.query(l-1)) - (BIT_B2.query(r-1) - BIT_B2.query(l-1))
            ll sumB = 0;
            // (r - l +1)*BIT_B.query(l-1)
            ll part1 = ((r - l +1) * BIT_query(&BIT_B, sorted_B_arr[0].val < l ? 1 : 0)) % MOD;
            // r*(BIT_B.query(r-1) - BIT_B.query(l-1))
            ll part2 = (r * ((BIT_query(&BIT_B, n) - BIT_query(&BIT_B, 0)) % MOD)) % MOD;
            // (BIT_B2.query(r-1) - BIT_B2.query(l-1))
            ll part3 = (BIT_query(&BIT_B2, n) - BIT_query(&BIT_B2, 0)) % MOD;
            sumB = ( (part1 + part2) % MOD - part3 + MOD ) % MOD;
            // Total
            ll total = (term1 + sum_A_a + sumB) % MOD;
            printf("%lld\n", total);
        }
    }
    return 0;
}