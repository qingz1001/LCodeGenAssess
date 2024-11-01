#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 100000
#define MAX_QUEUE 70000

int main(){
    int s;
    scanf("%d", &s);
    // Get length L
    int temp = s;
    int L =0;
    if(temp ==0){
        L=1;
    }
    else{
        while(temp >0){
            L++;
            temp /=10;
        }
    }
    
    // Initialize distance array
    int *distance = (int*)malloc(sizeof(int)*MAX_NUM);
    for(int i=0;i<MAX_NUM;i++) distance[i]=-1;
    
    // Initialize queue
    int *queue = (int*)malloc(sizeof(int)*MAX_QUEUE);
    int head=0, tail=0;
    distance[s]=0;
    queue[tail++]=s;
    
    // BFS
    while(head < tail){
        int current = queue[head++];
        int current_dist = distance[current];
        
        // Extract digits
        int digits[10];
        int len=0;
        int n = current;
        if(n ==0){
            digits[len++]=0;
        }
        else{
            int stack[10];
            int top=0;
            while(n >0){
                stack[top++] = n%10;
                n /=10;
            }
            for(int i=top-1;i>=0;i--) digits[len++] = stack[i];
        }
        
        // Operation 1: Swap any two digits
        for(int i=0;i<len;i++){
            for(int j=i+1;j<len;j++){
                // Swap
                int tmp = digits[i];
                digits[i] = digits[j];
                digits[j] = tmp;
                
                // Build new number
                int new_num=0;
                for(int k=0;k<len;k++) new_num = new_num*10 + digits[k];
                
                // Restore swap
                tmp = digits[i];
                digits[i] = digits[j];
                digits[j] = tmp;
                
                if(distance[new_num]==-1){
                    distance[new_num] = current_dist +1;
                    queue[tail++] = new_num;
                }
            }
        }
        
        // Operation 2: Delete any one digit
        if(len >1){
            for(int i=0;i<len;i++){
                int new_num=0;
                for(int k=0;k<len;k++) if(k !=i) new_num = new_num*10 + digits[k];
                if(distance[new_num]==-1){
                    distance[new_num] = current_dist +1;
                    queue[tail++] = new_num;
                }
            }
        }
        
        // Operation 3: Insert a digit x between si and si+1 where si <x <si+1
        if(len >=1 && len < L){
            for(int i=0;i<len-1;i++){
                if(digits[i] < digits[i+1]){
                    for(int x = digits[i]+1; x < digits[i+1]; x++){
                        // Insert x between i and i+1
                        int new_digits[10];
                        int new_len =0;
                        for(int k=0;k<=len;k++){
                            if(k ==i+1){
                                new_digits[new_len++] = x;
                            }
                            if(k < len) new_digits[new_len++] = digits[k];
                        }
                        // Build new number
                        int new_num=0;
                        for(int k=0;k<new_len;k++) new_num = new_num*10 + new_digits[k];
                        if(new_len <= L && distance[new_num]==-1){
                            distance[new_num] = current_dist +1;
                            queue[tail++] = new_num;
                        }
                    }
                }
            }
        }
    }
    
    // Read queries
    int m;
    scanf("%d", &m);
    while(m--){
        int t;
        scanf("%d", &t);
        printf("%d\n", distance[t]);
    }
    
    free(distance);
    free(queue);
    return 0;
}