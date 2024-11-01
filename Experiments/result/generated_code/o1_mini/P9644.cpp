#include <stdio.h>
#include <string.h>

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, k;
        scanf("%d %d", &n, &k);
        char s[n+1];
        scanf("%s", s);
        // Collect positions of '1's
        int ones[n];
        int cnt = 0;
        for(int i=0;i<n;i++) if(s[i]=='1') ones[cnt++] = i;
        // Binary search for minimal L
        int left = 1, right = n, answer = n;
        while(left <= right){
            int mid = left + (right - left)/2;
            int ops = 0;
            int last = -1;
            for(int i=0;i<cnt;){
                if(last == -1 || ones[i] > last){
                    ops++;
                    last = ones[i] + mid -1;
                }
                i++;
            }
            if(ops <= k){
                answer = mid;
                right = mid -1;
            }
            else{
                left = mid +1;
            }
        }
        printf("%d\n", answer);
    }
}