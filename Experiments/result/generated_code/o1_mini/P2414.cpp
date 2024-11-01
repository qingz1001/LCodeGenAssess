#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005
#define MAX_M 100005
#define MAX_LEN 100005
#define MAX_TRIE_NODES 1000000

typedef struct {
    int children[26];
    int fail;
    int output_list;
} TrieNode;

int main(){
    TrieNode trie[MAX_TRIE_NODES];
    int linked_list_next[MAX_M];
    char input_str[MAX_LEN];
    char slot[MAX_LEN];
    int slot_len =0;
    char buffer_printed[MAX_LEN];
    int printed_start[MAX_N];
    int printed_len[MAX_N];
    int printed_count =0;
    int printed_buffer_ptr =0;
    
    // Read the input string
    scanf("%s", input_str);
    int input_len = strlen(input_str);
    
    for(int i=0;i<input_len;i++){
        char c = input_str[i];
        if(c >= 'a' && c <= 'z'){
            slot[slot_len++] = c;
        }
        else if(c == 'B'){
            if(slot_len >0){
                slot_len--;
            }
        }
        else if(c == 'P'){
            printed_start[printed_count] = printed_buffer_ptr;
            printed_len[printed_count] = slot_len;
            memcpy(buffer_printed + printed_buffer_ptr, slot, slot_len * sizeof(char));
            printed_buffer_ptr += slot_len;
            printed_count++;
        }
    }
    
    // Read m and the queries
    int m;
    scanf("%d", &m);
    int query_x[MAX_M];
    int query_y[MAX_M];
    int count_y[MAX_N];
    memset(count_y, 0, sizeof(int)*(printed_count+1));
    
    for(int i=0;i<m;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        query_x[i] = x-1;
        query_y[i] = y-1;
        if(query_y[i] < printed_count){
            count_y[query_y[i]]++;
        }
    }
    
    // Group queries by y using prefix sums
    int y_offsets[MAX_N];
    y_offsets[0] =0;
    for(int y=1;y<printed_count;y++){
        y_offsets[y] = y_offsets[y-1] + count_y[y-1];
    }
    
    int queries_ordered[MAX_M];
    int temp_y_count[MAX_N];
    memset(temp_y_count, 0, sizeof(int)*(printed_count+1));
    
    for(int i=0;i<m;i++){
        int y = query_y[i];
        if(y >= printed_count){
            // Invalid y, no output
            continue;
        }
        int pos = y_offsets[y] + temp_y_count[y];
        queries_ordered[pos] = i;
        temp_y_count[y]++;
    }
    
    // Initialize answers
    int answers[MAX_M];
    memset(answers, 0, sizeof(int)*m);
    
    // Initialize queue for BFS
    int queue[MAX_TRIE_NODES];
    int head, tail;
    
    // Process each y
    for(int y=0;y<printed_count;y++){
        if(count_y[y] ==0){
            continue;
        }
        // Initialize trie
        memset(trie, 0, sizeof(TrieNode)*1); // Initialize root
        trie[0].fail =0;
        trie[0].output_list = -1;
        int trie_next_node =1;
        
        // Insert all patterns for this y
        for(int i=0;i<count_y[y];i++){
            int q_idx = queries_ordered[y_offsets[y] + i];
            int x = query_x[q_idx];
            if(x >= printed_count){
                continue;
            }
            int p_start = printed_start[x];
            int p_len = printed_len[x];
            int node =0;
            for(int c=0;c<p_len;c++){
                char ch = buffer_printed[p_start + c];
                if(trie[node].children[ch - 'a'] ==0){
                    trie[node].children[ch - 'a'] = trie_next_node;
                    trie[trie_next_node].fail =0;
                    trie[trie_next_node].output_list = -1;
                    for(int k=0;k<26;k++) trie[trie_next_node].children[k] =0;
                    trie_next_node++;
                }
                node = trie[node].children[ch - 'a'];
            }
            // Assign output
            linked_list_next[q_idx] = trie[node].output_list;
            trie[node].output_list = q_idx;
        }
        
        // Build failure links
        head =0;
        tail =0;
        for(int c=0;c<26;c++){
            if(trie[0].children[c] !=0){
                trie[trie[0].children[c]].fail =0;
                queue[tail++] = trie[0].children[c];
            }
        }
        
        while(head < tail){
            int u = queue[head++];
            for(int c=0;c<26;c++){
                if(trie[u].children[c] !=0){
                    int v = trie[u].children[c];
                    int f = trie[u].fail;
                    while(f !=0 && trie[f].children[c] ==0){
                        f = trie[f].fail;
                    }
                    if(trie[f].children[c] !=0){
                        trie[v].fail = trie[f].children[c];
                    }
                    else{
                        trie[v].fail =0;
                    }
                    // Append the output_list from fail node to current node
                    if(trie[trie[v].fail].output_list != -1){
                        int k = trie[trie[v].fail].output_list;
                        while(k != -1){
                            linked_list_next[k] = trie[v].output_list;
                            trie[v].output_list = k;
                            k = linked_list_next[k];
                        }
                    }
                    queue[tail++] = v;
                }
            }
        }
        
        // Traverse the text and count matches
        int current_node =0;
        int s_start = printed_start[y];
        int s_len = printed_len[y];
        for(int i=0;i<s_len;i++){
            char ch = buffer_printed[s_start + i];
            int c = ch - 'a';
            while(current_node !=0 && trie[current_node].children[c] ==0){
                current_node = trie[current_node].fail;
            }
            if(trie[current_node].children[c] !=0){
                current_node = trie[current_node].children[c];
            }
            // Process outputs
            int j_ptr = trie[current_node].output_list;
            while(j_ptr != -1){
                answers[j_ptr]++;
                j_ptr = linked_list_next[j_ptr];
            }
        }
    }
    
    // Print the answers
    for(int i=0;i<m;i++){
        if(query_y[i] >= printed_count){
            printf("0\n");
        }
        else{
            printf("%d\n", answers[i]);
        }
    }
    
    return 0;
}