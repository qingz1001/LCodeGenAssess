#include <stdio.h>
#include <string.h>

#define MAX_WORDS 1001
#define MAX_WORD_LENGTH 11

int main() {
    int n, m;
    scanf("%d", &n);
    char target_words[MAX_WORDS][MAX_WORD_LENGTH];
    for (int i = 0; i < n; i++) {
        scanf("%s", target_words[i]);
    }
    
    scanf("%d", &m);
    char article_words[m][MAX_WORD_LENGTH];
    for (int i = 0; i < m; i++) {
        scanf("%s", article_words[i]);
    }
    
    int target_count = 0;
    int target_index[MAX_WORDS] = {0}; // 记录目标单词在文章中的位置
    int article_index[MAX_WORDS] = {0}; // 记录文章单词是否为目标单词
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (strcmp(target_words[i], article_words[j]) == 0) {
                target_index[target_count++] = j;
                article_index[j] = 1;
                break;
            }
        }
    }
    
    int max_target_count = 0;
    int min_length = m;
    int current_count = 0;
    int start = 0;
    for (int end = 0; end < m; end++) {
        if (article_index[end]) {
            current_count++;
        }
        
        while (current_count == target_count) {
            int length = target_index[target_count - 1] - target_index[0] + 1;
            if (length < min_length) {
                min_length = length;
            }
            if (article_index[target_index[0]]) {
                current_count--;
            }
            start++;
            while (start <= end && !article_index[start]) {
                start++;
            }
            for (int i = 0; i < target_count; i++) {
                if (target_index[i] == start - 1) {
                    target_index[i] = -1;
                }
            }
        }
    }
    
    printf("%d\n", target_count);
    printf("%d\n", min_length);
    
    return 0;
}