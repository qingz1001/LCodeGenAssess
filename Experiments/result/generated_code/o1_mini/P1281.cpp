#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    int m, k;
    scanf("%d %d", &m, &k);
    int pages[m];
    for(int i=0;i<m;i++) scanf("%d", &pages[i]);
    
    // Find the minimal possible maximum using binary search
    int left = pages[0];
    int right = 0;
    for(int i=0;i<m;i++) {
        if(pages[i] > left) left = pages[i];
        right += pages[i];
    }
    
    while(left < right){
        int mid = left + (right - left)/2;
        int cnt =1;
        int current =0;
        for(int i=0;i<m;i++){
            if(current + pages[i] > mid){
                cnt++;
                current = pages[i];
            }
            else{
                current += pages[i];
            }
        }
        if(cnt <= k) right = mid;
        else left = mid +1;
    }
    
    // Now left is the minimal maximum
    // Reconstruct the allocation
    int segments[k][2];
    int seg = k-1;
    int sum =0;
    int end = m-1;
    for(int i=m-1;i>=0;i--){
        if(sum + pages[i] > left || i+1 < seg+1){
            segments[seg][0] = i+2;
            segments[seg][1] = end+1;
            seg--;
            sum = pages[i];
            end = i;
        }
        else{
            sum += pages[i];
        }
    }
    segments[seg][0] = 1;
    segments[seg][1] = end+1;
    seg--;
    for(; seg >=0; seg--){
        segments[seg][0] = segments[seg+1][0];
        segments[seg][1] = segments[seg+1][0]-1;
    }
    
    // Now fill the remaining segments
    int current_start =1;
    for(int i=0;i<k;i++){
        if(segments[i][0]==0 && segments[i][1]==0){
            segments[i][0] = current_start;
            segments[i][1] = current_start;
            current_start++;
        }
    }
    
    for(int i=0;i<k;i++) printf("%d %d\n", segments[i][0], segments[i][1]);
}