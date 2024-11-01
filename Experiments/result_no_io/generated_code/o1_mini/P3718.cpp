#include <stdio.h>
#include <string.h>

typedef long long ll;

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    char s[100005];
    scanf("%s", s);
    int left = 1, right = n, ans = n;
    while(left <= right){
        int mid = left + (right - left) / 2;
        ll total = 0;
        int i = 0;
        while(i < n){
            int j = i;
            while(j < n && s[j] == s[i]) j++;
            int m = j - i;
            total += (m - 1) / mid;
            if(total > k) break;
            i = j;
        }
        if(total <= k){
            ans = mid;
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}