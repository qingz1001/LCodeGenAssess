#include <stdio.h>
#include <string.h>

void getPreOrder(char* in, char* post, int len, char* pre) {
    if (len == 0) return;
    pre[0] = post[len - 1];
    int i;
    for (i = 0; i < len; ++i) {
        if (in[i] == post[len - 1]) break;
    }
    getPreOrder(in, post, i, pre + 1);
    getPreOrder(in + i + 1, post + i, len - i - 1, pre + i + 1);
}

int main() {
    char in[9], post[9], pre[9];
    scanf("%s %s", in, post);
    getPreOrder(in, post, strlen(in), pre);
    printf("%s\n", pre);
    return 0;
}