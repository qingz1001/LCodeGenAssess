#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_D 1000
#define MAX_WORD_LEN 10
#define MAX_L 26
#define MAX_B 26

typedef struct {
    char word[MAX_WORD_LEN +1];
    int len;
    int letters[MAX_WORD_LEN];
} Word;

int cmp_uint64(const void *a, const void *b){
    uint64_t ua = *(uint64_t*)a;
    uint64_t ub = *(uint64_t*)b;
    if(ua < ub) return -1;
    if(ua > ub) return 1;
    return 0;
}

int main(){
    int B, L;
    scanf("%d %d", &B, &L);
    int D;
    scanf("%d", &D);
    Word words[MAX_D];
    for(int i=0;i<D;i++){
        char buffer[MAX_WORD_LEN +1];
        scanf("%s", buffer);
        strcpy(words[i].word, buffer);
        words[i].len = strlen(buffer);
        for(int j=0;j<words[i].len;j++){
            words[i].letters[j] = buffer[j] - 'A';
        }
    }
    
    // Generate all possible split points
    // There are C(L-1, B-1) assignments
    // Use recursion to generate split points
    // To optimize, use iterative generation with indices
    
    // Initialize split points
    int split[B-1];
    for(int i=0;i<B-1;i++) split[i] = i+1;
    
    // Initialize variables to track best assignment
    int best_unique = -1;
    int best_split[B-1];
    
    // Function to generate next combination
    // Returns 0 when no more combinations
    while(1){
        // Current split points are in split[0..B-2]
        // Assign buttons based on split
        int button_of_letter[MAX_L];
        int current_button =1;
        int split_idx =0;
        for(int i=0;i<L;i++){
            if(split_idx < B-1 && i == split[split_idx]){
                current_button++;
                split_idx++;
            }
            button_of_letter[i] = current_button;
        }
        // Now, button_of_letter has mapping from letter 0..L-1 to button 1..B
        
        // For each word, compute its button sequence as uint64_t
        uint64_t sequences[MAX_D];
        for(int i=0;i<D;i++){
            uint64_t key =0;
            for(int j=0;j<words[i].len;j++){
                key = (key <<5) | (button_of_letter[words[i].letters[j]]);
            }
            sequences[i] = key;
        }
        // Sort sequences
        uint64_t sorted[MAX_D];
        memcpy(sorted, sequences, sizeof(uint64_t)*D);
        qsort(sorted, D, sizeof(uint64_t), cmp_uint64);
        // Count unique sequences
        int unique =0;
        int cnt=1;
        for(int i=1;i<D;i++){
            if(sorted[i] == sorted[i-1]){
                cnt++;
            }
            else{
                if(cnt ==1) unique++;
                cnt =1;
            }
        }
        if(cnt ==1) unique++;
        // Update best assignment
        if(unique > best_unique){
            best_unique = unique;
            memcpy(best_split, split, sizeof(int)*(B-1));
        }
        else if(unique == best_unique){
            // Tie-break: most letters on button1, then button2, etc.
            // Compare current split with best_split
            int better = 0;
            for(int i=0;i<B-1;i++){
                if(split[i] > best_split[i]){
                    better =1;
                    break;
                }
                else if(split[i] < best_split[i]){
                    break;
                }
            }
            if(better){
                memcpy(best_split, split, sizeof(int)*(B-1));
            }
        }
        // Generate next combination
        int i;
        for(i=B-2;i>=0;i--){
            if(split[i] < L-1 - (B-2 -i)){
                split[i]++;
                for(int j=i+1;j<B-1;j++) split[j] = split[j-1]+1;
                break;
            }
        }
        if(i <0) break;
    }
    
    // Now, best_split has the best assignment
    // Compute the button mapping
    int button_of_letter[MAX_L];
    int current_button =1;
    int split_idx =0;
    for(int i=0;i<L;i++){
        if(split_idx < B-1 && i == best_split[split_idx]){
            current_button++;
            split_idx++;
        }
        button_of_letter[i] = current_button;
    }
    
    // Now, compute unique count again (optional, since already have best_unique)
    // Output
    printf("%d\n", best_unique);
    // Now, output the button assignments
    // Collect letters for each button
    char buttons_letters[MAX_B][MAX_L+1];
    for(int b=0;b<B;b++) buttons_letters[b][0] = '\0';
    for(int i=0;i<L;i++){
        int b = button_of_letter[i]-1;
        int len = strlen(buttons_letters[b]);
        buttons_letters[b][len] = 'A' + i;
        buttons_letters[b][len+1] = '\0';
    }
    for(int b=0;b<B;b++) printf("%s\n", buttons_letters[b]);
    return 0;
}