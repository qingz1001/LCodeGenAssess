#include <stdio.h>
#include <string.h>

typedef long long ll;

// Function to check if a given L can cover all '1's within k operations
int can_cover(char *s, int n, int k, int L) {
    int operations = 0;
    int last_cover = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i-1] == '1' && i > last_cover) {
            operations++;
            last_cover = i + L - 1;
            if(operations > k) return 0;
        }
    }
    return 1;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, k;
        scanf("%d %d", &n, &k);
        char s[2000005];
        scanf("%s", s);
        int left = 1, right = n, res = n;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(can_cover(s, n, k, mid)){
                res = mid;
                right = mid -1;
            }
            else{
                left = mid +1;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}