#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 10000

char keyword[MAX_LEN], text[MAX_LEN], result[MAX_LEN];
char words[1000][50];
int word_count = 0;

void split_words(char *str) {
    char *p = str;
    char word[50];
    int len = 0;
    
    while (*p) {
        if (isalpha(*p)) {
            word[len++] = *p;
        } else if (len > 0) {
            word[len] = '\0';
            strcpy(words[word_count++], word);
            len = 0;
        }
        p++;
    }
    if (len > 0) {
        word[len] = '\0';
        strcpy(words[word_count++], word);
    }
}

int is_word(char *str) {
    int count = 0;
    char *p = str;
    while (*p) {
        if (isalpha(*p)) count++;
        p++;
    }
    return count >= 2;
}

int find_word(char *word) {
    for (int i = 0; i < word_count; i++) {
        if (strcmp(words[i], word) == 0) return 1;
    }
    return 0;
}

void process_text() {
    char *p = text;
    char *r = result;
    char word[50];
    int len = 0;
    int in_bold = 0;
    
    while (*p) {
        if (isalpha(*p)) {
            word[len++] = *p;
        } else {
            if (len > 0) {
                word[len] = '\0';
                if (is_word(word) && find_word(word)) {
                    if (!in_bold) {
                        strcpy(r, "<b>");
                        r += 3;
                        in_bold = 1;
                    }
                } else {
                    if (in_bold) {
                        strcpy(r, "</b>");
                        r += 4;
                        in_bold = 0;
                    }
                }
                strcpy(r, word);
                r += len;
                len = 0;
            }
            *r++ = *p;
        }
        p++;
    }
    
    if (len > 0) {
        word[len] = '\0';
        if (is_word(word) && find_word(word)) {
            if (!in_bold) {
                strcpy(r, "<b>");
                r += 3;
            }
        } else {
            if (in_bold) {
                strcpy(r, "</b>");
                r += 4;
            }
        }
        strcpy(r, word);
        r += len;
    }
    
    if (in_bold) {
        strcpy(r, "</b>");
        r += 4;
    }
    
    *r = '\0';
}

int main() {
    fgets(keyword, MAX_LEN, stdin);
    fgets(text, MAX_LEN, stdin);
    
    keyword[strcspn(keyword, "\n")] = 0;
    text[strcspn(text, "\n")] = 0;
    
    split_words(keyword);
    process_text();
    
    printf("%s\n", result);
    
    return 0;
}