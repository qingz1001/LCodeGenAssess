#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef long long ll;

int cmp_int(const void* a, const void* b){
    int ia = *(int*)a;
    int ib = *(int*)b;
    return ia - ib;
}

int main(){
    int N, K;
    if(scanf("%d %d", &N, &K)!=2)return 0;
    int* mandatory_days = (int*)malloc(K * sizeof(int));
    for(int i=0;i<K;i++) scanf("%d", &mandatory_days[i]);
    int* C = (int*)malloc((N+1) * sizeof(int));
    for(int i=1;i<=N;i++) scanf("%d", &C[i]);
    // Sort the mandatory_days
    qsort(mandatory_days, K, sizeof(int), cmp_int);
    // Extract the c_i for mandatory_days
    int* mandatory_c = (int*)malloc(K * sizeof(int));
    for(int i=0;i<K;i++) mandatory_c[i] = C[mandatory_days[i]];
    // Check if mandatory_c is strictly increasing
    int possible = 1;
    for(int i=1;i<K;i++) if(mandatory_c[i] <= mandatory_c[i-1]) { possible =0; break;}
    if(!possible){ printf("impossible"); return 0;}
    // Function to compute LIS length
    // Implemented inline
    int total = K;
    // Before first mandatory day
    if(K >0){
        if(mandatory_days[0] >1){
            // Collect eligible C[i] < mandatory_c[0]
            int size = mandatory_days[0]-1;
            int* segment = (int*)malloc(size * sizeof(int));
            int cnt=0;
            for(int i=1;i < mandatory_days[0];i++) if(C[i] < mandatory_c[0]) segment[cnt++] = C[i];
            // Compute LIS on segment
            if(cnt >0){
                int* lis = (int*)malloc(cnt * sizeof(int));
                int lis_len =0;
                for(int i=0;i<cnt;i++){
                    // Binary search
                    int left=0, right=lis_len;
                    while(left < right){
                        int mid = left + (right - left)/2;
                        if(lis[mid] < segment[i]) left = mid +1;
                        else right = mid;
                    }
                    lis[left] = segment[i];
                    if(left == lis_len) lis_len++;
                }
                total += lis_len;
                free(lis);
            }
            free(segment);
        }
        // Between mandatory days
        for(int j=1;j<K;j++){
            int start = mandatory_days[j-1]+1;
            int end = mandatory_days[j]-1;
            if(start > end) continue;
            // Collect C[i] > mandatory_c[j-1] and < mandatory_c[j]
            int size = end - start +1;
            int* segment = (int*)malloc(size * sizeof(int));
            int cnt=0;
            for(int i=start;i<=end;i++) if(C[i] > mandatory_c[j-1] && C[i] < mandatory_c[j]) segment[cnt++] = C[i];
            // Compute LIS on segment
            if(cnt >0){
                int* lis = (int*)malloc(cnt * sizeof(int));
                int lis_len =0;
                for(int i=0;i<cnt;i++){
                    // Binary search
                    int left=0, right=lis_len;
                    while(left < right){
                        int mid = left + (right - left)/2;
                        if(lis[mid] < segment[i]) left = mid +1;
                        else right = mid;
                    }
                    lis[left] = segment[i];
                    if(left == lis_len) lis_len++;
                }
                total += lis_len;
                free(lis);
            }
            free(segment);
        }
        // After last mandatory day
        if(mandatory_days[K-1] < N){
            // Collect C[i] > mandatory_c[K-1]
            int size = N - mandatory_days[K-1];
            int* segment = (int*)malloc(size * sizeof(int));
            int cnt=0;
            for(int i=mandatory_days[K-1]+1;i<=N;i++) if(C[i] > mandatory_c[K-1]) segment[cnt++] = C[i];
            // Compute LIS on segment
            if(cnt >0){
                int* lis = (int*)malloc(cnt * sizeof(int));
                int lis_len =0;
                for(int i=0;i<cnt;i++){
                    // Binary search
                    int left=0, right=lis_len;
                    while(left < right){
                        int mid = left + (right - left)/2;
                        if(lis[mid] < segment[i]) left = mid +1;
                        else right = mid;
                    }
                    lis[left] = segment[i];
                    if(left == lis_len) lis_len++;
                }
                total += lis_len;
                free(lis);
            }
            free(segment);
        }
    }
    else{
        // K ==0, find standard LIS
        int* lis = (int*)malloc(N * sizeof(int));
        int lis_len =0;
        for(int i=1;i<=N;i++){
            int left=0, right=lis_len;
            while(left < right){
                int mid = left + (right - left)/2;
                if(lis[mid] < C[i]) left = mid +1;
                else right = mid;
            }
            lis[left] = C[i];
            if(left == lis_len) lis_len++;
        }
        total += lis_len;
        free(lis);
    }
    // Now verify that mandatory days are included and strictly increasing
    // Since we already checked c_i for mandatory days are strictly increasing and segments are bounded, it's valid
    printf("%d", total);
    // Free memory
    free(mandatory_days);
    free(C);
    free(mandatory_c);
    return 0;
}