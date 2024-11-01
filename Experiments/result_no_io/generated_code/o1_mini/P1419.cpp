#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef long long ll;

int main(){
    int n, S, T;
    scanf("%d", &n);
    scanf("%d %d", &S, &T);
    double a[MAXN];
    double prefix[MAXN];
    double min_a = 1e5, max_a = -1e5;
    for(int i=1;i<=n;i++){
        scanf("%lf", &a[i]);
        if(a[i] < min_a) min_a = a[i];
        if(a[i] > max_a) max_a = a[i];
    }
    double low = min_a, high = max_a, mid, eps=1e-5;
    prefix[0]=0.0;
    for(int i=1;i<=n;i++) prefix[i] = prefix[i-1];
    // Binary search
    for(int it=0; it<100; it++){
        mid = (low + high)/2.0;
        // Transform prefix
        for(int i=1;i<=n;i++) prefix[i] = prefix[i] - mid;
        // Now check
        int dq[MAXN];
        int front=0, back=0;
        double min_prefix = 0.0;
        // Initialize
        for(int i=0;i<=n;i++) prefix[i] += 0.0; // dummy
        // Initialize min prefix up to i-T
        // Reset prefix to original
        for(int i=1;i<=n;i++) prefix[i] = prefix[i] - a[i] + mid;
        // Recalculate prefix
        prefix[0]=0.0;
        for(int i=1;i<=n;i++) prefix[i] = prefix[i-1] + (a[i] - mid);
        front=0; back=0;
        dq[back++] =0;
        int found=0;
        for(int i=S;i<=n;i++){
            // Add i-T
            if(i-T-1 >=0){
                // Remove from front
                if(front < back && dq[front] == i-T-1) front++;
            }
            // Add i-S
            while(front < back && prefix[i-S] <= prefix[dq[back-1]]) back--;
            dq[back++] = i-S;
            // Check
            if(front < back && prefix[i] - prefix[dq[front]] >=0){
                found=1;
                break;
            }
        }
        if(found){
            low = mid;
        }
        else{
            high = mid;
        }
    }
    printf("%.3lf", low);
}