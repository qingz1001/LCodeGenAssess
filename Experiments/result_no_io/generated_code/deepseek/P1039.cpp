#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_M 20
#define MAX_P 100
#define MAX_NAME_LEN 20
#define MAX_LINE_LEN 250

typedef struct {
    char name[MAX_NAME_LEN];
    char statement[MAX_LINE_LEN];
} Statement;

char names[MAX_M][MAX_NAME_LEN];
Statement statements[MAX_P];
int M, N, P;

bool is_guilty[MAX_M];
bool is_liar[MAX_M];

bool is_day_valid(char *day) {
    const char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int i = 0; i < 7; i++) {
        if (strcmp(day, days[i]) == 0) {
            return true;
        }
    }
    return false;
}

int find_name_index(char *name) {
    for (int i = 0; i < M; i++) {
        if (strcmp(name, names[i]) == 0) {
            return i;
        }
    }
    return -1;
}

bool validate_statement(int index, int guilty_index, char *day) {
    char *stmt = statements[index].statement;
    char *name = statements[index].name;
    int name_index = find_name_index(name);

    if (strstr(stmt, "I am guilty.") != NULL) {
        return is_liar[name_index] ? name_index != guilty_index : name_index == guilty_index;
    } else if (strstr(stmt, "I am not guilty.") != NULL) {
        return is_liar[name_index] ? name_index == guilty_index : name_index != guilty_index;
    } else if (strstr(stmt, "is guilty.") != NULL) {
        char target_name[MAX_NAME_LEN];
        sscanf(stmt, "%s is guilty.", target_name);
        int target_index = find_name_index(target_name);
        return is_liar[name_index] ? target_index != guilty_index : target_index == guilty_index;
    } else if (strstr(stmt, "is not guilty.") != NULL) {
        char target_name[MAX_NAME_LEN];
        sscanf(stmt, "%s is not guilty.", target_name);
        int target_index = find_name_index(target_name);
        return is_liar[name_index] ? target_index == guilty_index : target_index != guilty_index;
    } else if (strstr(stmt, "Today is") != NULL) {
        char stmt_day[MAX_NAME_LEN];
        sscanf(stmt, "Today is %s.", stmt_day);
        return is_liar[name_index] ? !is_day_valid(stmt_day) : strcmp(stmt_day, day) == 0;
    }
    return true;
}

int main() {
    scanf("%d %d %d", &M, &N, &P);
    for (int i = 0; i < M; i++) {
        scanf("%s", names[i]);
    }
    for (int i = 0; i < P; i++) {
        scanf("%s: %[^\n]", statements[i].name, statements[i].statement);
    }

    int possible_guilty_count = 0;
    int possible_guilty_index = -1;

    for (int guilty_index = 0; guilty_index < M; guilty_index++) {
        for (int day_index = 0; day_index < 7; day_index++) {
            const char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
            char *day = (char *)days[day_index];

            memset(is_liar, false, sizeof(is_liar));
            int liar_count = 0;

            for (int i = 0; i < M; i++) {
                if (i != guilty_index) {
                    is_liar[i] = true;
                    liar_count++;
                }
            }

            if (liar_count != N) continue;

            bool valid = true;
            for (int i = 0; i < P; i++) {
                if (!validate_statement(i, guilty_index, day)) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                if (possible_guilty_index == -1) {
                    possible_guilty_index = guilty_index;
                } else {
                    possible_guilty_index = -2;
                }
                possible_guilty_count++;
            }
        }
    }

    if (possible_guilty_count == 0) {
        printf("Impossible\n");
    } else if (possible_guilty_count > 1) {
        printf("Cannot Determine\n");
    } else {
        printf("%s\n", names[possible_guilty_index]);
    }

    return 0;
}