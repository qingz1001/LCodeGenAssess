#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int lower_bound(int *arr, int n, int q){
    int left = 0, right = n;
    while(left < right){
        int mid = left + (right - left)/2;
        if(arr[mid] < q){
            left = mid +1;
        }
        else{
            right = mid;
        }
    }
    if(left < n && arr[left] == q){
        return left +1;
    }
    return -1;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int *a = (int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    int *q = (int*)malloc(m*sizeof(int));
    for(int i=0;i<m;i++) scanf("%d", &q[i]);
    char *output = (char*)malloc((m*12)+1);
    int pos =0;
    for(int i=0;i<m;i++){
        int res = lower_bound(a, n, q[i]);
        if(res == -1){
            output[pos++] = '-';
            output[pos++] = '1';
        }
        else{
            // Convert res to string
            int tmp = res;
            char num[12];
            int len =0;
            if(tmp ==0){
                num[len++] = '0';
            }
            else{
                while(tmp >0){
                    num[len++] = (tmp%10)+'0';
                    tmp /=10;
                }
            }
            for(int j=len-1;j>=0;j--) output[pos++] = num[j];
        }
        if(i != m-1) output[pos++] = ' ';
    }
    output[pos] = '\0';
    printf("%s", output);
    free(a);
    free(q);
    free(output);
    return 0;
}