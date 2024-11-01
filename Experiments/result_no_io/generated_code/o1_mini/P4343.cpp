#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Function to simulate and count submissions for a given n
ll count_submissions(int l, ll *logs, ll n){
    ll current = 0;
    ll submissions = 0;
    for(int i=0;i<l;i++){
        if(logs[i] >=0){
            current += logs[i];
        }
        else{
            current += logs[i];
            if(current <0) current =0;
        }
        if(current >= n){
            submissions++;
            current =0;
        }
    }
    return submissions;
}

int main(){
    int l;
    ll k;
    scanf("%d %lld", &l, &k);
    ll *logs = (ll*)malloc(sizeof(ll)*l);
    for(int i=0;i<l;i++) scanf("%lld", &logs[i]);
    
    // Find max_code_length
    ll current =0, max_code =0;
    for(int i=0;i<l;i++){
        if(logs[i] >=0){
            current += logs[i];
        }
        else{
            current += logs[i];
            if(current <0) current=0;
        }
        if(current > max_code) max_code = current;
    }
    
    if(k ==0){
        // n must be > max_code
        printf("%lld %lld\n", max_code +1, max_code +1);
        free(logs);
        return 0;
    }
    
    // Binary search for n_min
    ll left =1, right = max_code;
    ll n_min = -1;
    while(left < right){
        ll mid = left + (right - left)/2;
        ll submissions = count_submissions(l, logs, mid);
        if(submissions > k){
            left = mid +1;
        }
        else{
            right = mid;
        }
    }
    ll submissions_min = count_submissions(l, logs, left);
    if(submissions_min !=k){
        printf("-1\n");
        free(logs);
        return 0;
    }
    n_min = left;
    
    // Binary search for n_max
    left =1;
    right = max_code;
    ll n_max = -1;
    while(left < right){
        ll mid = left + (right - left +1)/2;
        ll submissions = count_submissions(l, logs, mid);
        if(submissions < k){
            right = mid -1;
        }
        else{
            left = mid;
        }
    }
    ll submissions_max = count_submissions(l, logs, left);
    if(submissions_max !=k){
        printf("-1\n");
        free(logs);
        return 0;
    }
    n_max = left;
    
    if(n_min > n_max){
        printf("-1\n");
        free(logs);
        return 0;
    }
    
    printf("%lld %lld\n", n_min, n_max);
    free(logs);
    return 0;
}