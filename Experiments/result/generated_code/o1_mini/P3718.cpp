#include <stdio.h>
#include <string.h>
#include <math.h>

typedef long long ll;

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    char s[100005];
    scanf("%s", s);
    // Binary search for minimal m
    int left =1, right =n, res =n;
    while(left <= right){
        int mid = left + (right - left)/2;
        int toggles =0;
        int i=0;
        while(i < n){
            char current = s[i];
            int start = i;
            while(i < n && s[i] == current){
                i++;
            }
            int len = i - start;
            if(len > mid){
                toggles += (len -1)/mid;
            }
        }
        if(toggles <=k){
            res = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%d\n", res);
}