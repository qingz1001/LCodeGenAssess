#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    int section_count = 0, subsection_count = 0;

    for (int i = 0; i < n; i++) {
        char command[20], title[21];
        scanf("%s %s", command, title);

        if (strcmp(command, "section") == 0) {
            section_count++;
            subsection_count = 0;
            printf("%d %s\n", section_count, title);
        } else if (strcmp(command, "subsection") == 0) {
            subsection_count++;
            printf("%d.%d %s\n", section_count, subsection_count, title);
        } else if (strcmp(command, "subsubsection") == 0) {
            printf("%d.%d.%d %s\n", section_count, subsection_count, 1, title);
        }
    }

    return 0;
}