#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Comparator for qsort
int cmpfunc(const void *a, const void *b){
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if(x < y) return -1;
    else if(x > y) return 1;
    else return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    ll *a = (ll*)malloc(n * sizeof(ll));
    for(int i=0;i<n;i++) scanf("%lld", &a[i]);
    qsort(a, n, sizeof(ll), cmpfunc);
    // Count frequencies and runs
    ll max_freq=1;
    int runs=1;
    int i=0;
    while(i < n){
        ll current = a[i];
        int count=1;
        i++;
        while(i < n && a[i]==current){
            count++;
            i++;
        }
        if(count > max_freq) max_freq = count;
        // Check for run
        if(i < n){
            if(a[i] != current +1){
                runs++;
            }
        }
    }
    // Calculate g
    ll g;
    // To count number of runs
    g = 1;
    for(int i=1;i<n;i++){
        if(a[i] != a[i-1]+1){
            g++;
        }
    }
    // Find max frequency
    max_freq=1;
    i=0;
    while(i < n){
        ll current = a[i];
        int count=1;
        i++;
        while(i < n && a[i]==current){
            count++;
            i++;
        }
        if(count > max_freq) max_freq = count;
    }
    // g is max of runs and max_freq
    if(g < max_freq) g = max_freq;
    // Compute floor(n/g)
    printf("%lld", n / g);
    free(a);
    return 0;
}