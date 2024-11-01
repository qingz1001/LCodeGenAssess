#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

// Comparator for qsort
int cmp(const void *a, const void *b){
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if(x < y) return -1;
    else if(x > y) return 1;
    else return 0;
}

// Binary search to find first element > key
ll upper_bound(ll *arr, ll n, ll key){
    ll l = 0, r = n;
    while(l < r){
        ll m = l + (r - l)/2;
        if(arr[m] <= key) l = m +1;
        else r = m;
    }
    return l;
}

int main(){
    int n, Q;
    scanf("%d %d", &n, &Q);
    ll *x = (ll*)malloc(n * sizeof(ll));
    char s[50];
    for(int i=0;i<n;i++){
        scanf("%s", s);
        int len = strlen(s);
        // Parse a_i
        int pos = 0;
        int a_neg = 0;
        if(s[pos] == '-'){
            a_neg = 1;
            pos++;
        }
        ll a = 0;
        while(s[pos] != 'x'){
            a = a*10 + (s[pos]-'0');
            pos++;
        }
        if(a_neg) a = -a;
        pos++; // skip 'x'
        // Parse b_i
        int b_neg = 0;
        if(s[pos] == '-'){
            b_neg = 1;
            pos++;
        }
        else if(s[pos] == '+'){
            pos++;
        }
        ll b =0;
        while(s[pos] != '='){
            b = b*10 + (s[pos]-'0');
            pos++;
        }
        if(b_neg) b = -b;
        pos++; // skip '='
        // Parse c_i
        ll c=0;
        while(pos < len){
            c = c*10 + (s[pos]-'0');
            pos++;
        }
        // Compute x_i
        ll xi = (c - b)/a;
        x[i] = xi;
    }
    // Sort and unique
    qsort(x, n, sizeof(ll), cmp);
    int unique_n = 0;
    for(int i=0;i<n;i++){
        if(i==0 || x[i] != x[i-1]){
            x[unique_n++] = x[i];
        }
    }
    // Process queries
    for(int i=0;i<Q;i++){
        ll L, R;
        scanf("%lld %lld", &L, &R);
        ll cnt = upper_bound(x, unique_n, R) - upper_bound(x, unique_n, L-1);
        printf("%lld\n", cnt);
    }
    free(x);
    return 0;
}