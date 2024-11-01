#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b) {
    int aa = *(int*)a;
    int bb = *(int*)b;
    return aa - bb;
}

int is_possible(int n, int k, int* a, int x) {
    int operations = 0;
    int i = 0;
    while (i < n) {
        if (a[i] >= x) {
            i++;
            continue;
        }
        int j = i;
        while (j < n && a[j] < x) {
            j++;
        }
        int len = j - i;
        if (len == 0) {
            i++;
            continue;
        }
        int mid = (len + 1) / 2 - 1;
        // After setting to median, the median should be >=x
        // To ensure this, at least half of the segment should be >=x
        // So we can assume one operation covers this segment
        operations++;
        if (operations > k)
            return 0;
        i = j;
    }
    return 1;
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int* a = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    
    int low = 0, high = 1000000000, ans = 0;
    while(low <= high){
        int mid = low + (high - low) / 2;
        if(is_possible(n, k, a, mid)){
            ans = mid;
            low = mid + 1;
        }
        else{
            high = mid -1;
        }
    }
    printf("%d\n", ans);
    free(a);
    return 0;
}