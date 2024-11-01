#include <stdio.h>
#include <string.h>

int main(){
    int s;
    scanf("%d", &s);
    
    // Determine length of s
    int tmp_s = s;
    int len_s = 0;
    while(tmp_s > 0){
        len_s++;
        tmp_s /= 10;
    }
    
    // Initialize min_steps array
    int min_steps[100000];
    for(int i=0;i<100000;i++) min_steps[i]=-1;
    min_steps[s] = 0;
    
    // Initialize BFS queue
    int queue[100000];
    int front = 0, rear = 0;
    queue[rear++] = s;
    
    while(front < rear){
        int current = queue[front++];
        int step = min_steps[current];
        
        // Extract digits of current number
        int digits[10];
        int len = 0;
        int tmp = current;
        while(tmp > 0){
            digits[len++] = tmp % 10;
            tmp /= 10;
        }
        // Reverse to get digits from left to right
        for(int i=0; i<len/2; i++){
            int temp = digits[i];
            digits[i] = digits[len-1-i];
            digits[len-1-i] = temp;
        }
        
        // Operation 1: Swap any two digits
        for(int i=0; i<len; i++){
            for(int j=i+1; j<len; j++){
                // Swap digits[i] and digits[j]
                int swapped = current;
                int power_i = 1, power_j = 1;
                for(int p=0; p<len-p-1>p; p++) power_i *= 10;
                for(int p=0; p<len-j-1; p++) power_j *= 10;
                int di = digits[i];
                int dj = digits[j];
                swapped += (dj - di) * power_i;
                swapped += (di - dj) * power_j;
                
                // Alternatively, reconstruct the number
                int new_num = 0;
                for(int k=0; k<len; k++){
                    if(k == i) new_num = new_num * 10 + digits[j];
                    else if(k == j) new_num = new_num * 10 + digits[i];
                    else new_num = new_num * 10 + digits[k];
                }
                
                if(new_num < 100000 && min_steps[new_num]==-1){
                    min_steps[new_num] = step + 1;
                    queue[rear++] = new_num;
                }
            }
        }
        
        // Operation 2: Delete any digit
        if(len > 1){
            for(int i=0; i<len; i++){
                int new_num = 0;
                for(int k=0; k<len; k++) if(k != i) new_num = new_num * 10 + digits[k];
                if(new_num < 100000 && min_steps[new_num]==-1){
                    min_steps[new_num] = step + 1;
                    queue[rear++] = new_num;
                }
            }
        }
        
        // Operation 3: Insert x between adjacent digits with s_i < x < s_{i+1}
        if(len < len_s){
            for(int i=0; i<len-1; i++){
                int si = digits[i];
                int si1 = digits[i+1];
                for(int x = si + 1; x < si1; x++){
                    int new_num = 0;
                    for(int k=0; k<=i; k++) new_num = new_num * 10 + digits[k];
                    new_num = new_num * 10 + x;
                    for(int k=i+1; k<len; k++) new_num = new_num * 10 + digits[k];
                    if(new_num < 100000 && min_steps[new_num]==-1){
                        min_steps[new_num] = step + 1;
                        queue[rear++] = new_num;
                    }
                }
            }
        }
    }
    
    int m;
    scanf("%d", &m);
    while(m--){
        int t;
        scanf("%d", &t);
        if(t < 100000 && min_steps[t] != -1){
            printf("%d\n", min_steps[t]);
        }
        else{
            printf("-1\n");
        }
    }
    return 0;
}