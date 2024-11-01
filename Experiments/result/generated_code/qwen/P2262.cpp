#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USER_NUMBER 100
#define MAX_SERVER_FLUX 10000000
#define MAX_USER_FLUX 1000000
#define MAX_NAME_LENGTH 100
#define MAX_COMMAND_LENGTH 100

typedef enum {
    FILE,
    FOLDER
} FileType;

typedef struct Node {
    char name[MAX_NAME_LENGTH];
    int size;
    FileType type;
    struct Node* parent;
    struct Node** children;
    int num_children;
    char state[20];
} Node;

typedef struct User {
    char name[MAX_NAME_LENGTH];
    int userType;
    int userState;
    Node* userPosition;
} User;

Node* root;
User users[MAX_USER_NUMBER];
int user_count;

void init_server() {
    root = (Node*)malloc(sizeof(Node));
    strcpy(root->name, "/");
    root->size = 0;
    root->type = FOLDER;
    root->parent = NULL;
    root->children = NULL;
    root->num_children = 0;
    strcpy(root->state, "normal");
}

Node* create_node(char* name, int size, FileType type) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->name, name);
    new_node->size = size;
    new_node->type = type;
    new_node->parent = NULL;
    new_node->children = NULL;
    new_node->num_children = 0;
    strcpy(new_node->state, "normal");
    return new_node;
}

void add_child(Node* parent, Node* child) {
    if (parent->children == NULL) {
        parent->children = (Node**)malloc(sizeof(Node*));
        parent->children[parent->num_children++] = child;
    } else {
        parent->children = (Node**)realloc(parent->children, sizeof(Node*) * (parent->num_children + 1));
        parent->children[parent->num_children++] = child;
    }
    child->parent = parent;
}

void parse_input() {
    scanf("%d %d %d", &root->size, &root->size, &root->size);
    char line[MAX_COMMAND_LENGTH];
    fgets(line, sizeof(line), stdin);
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '-') break;
        char* token = strtok(line, " ");
        int time = atoi(token);
        token = strtok(NULL, " ");
        if (strcmp(token, "connect") == 0) {
            token = strtok(NULL, " ");
            int userType = atoi(token);
            token = strtok(NULL, " ");
            for (int i = 0; i < user_count; i++) {
                if (strcmp(users[i].name, token) == 0) {
                    printf("unsuccess\n");
                    break;
                }
            }
            if (user_count < MAX_USER_NUMBER) {
                strcpy(users[user_count].name, token);
                users[user_count].userType = userType;
                users[user_count].userState = 0;
                users[user_count].userPosition = root;
                user_count++;
                printf("success\n");
            }
        } else if (strcmp(token, "quit") == 0) {
            token = strtok(NULL, " ");
            for (int i = 0; i < user_count; i++) {
                if (strcmp(users[i].name, token) == 0) {
                    printf("success\n");
                    users[i].userState = 0;
                    users[i].userPosition = NULL;
                    break;
                }
            }
        } else if (strcmp(token, "cd") == 0) {
            token = strtok(NULL, " ");
            Node* current = users[token].userPosition;
            if (current != NULL && strcmp(token, "..") == 0) {
                if (current->parent != NULL) {
                    users[token].userPosition = current->parent;
                    printf("success\n");
                } else {
                    printf("unsuccess\n");
                }
            } else {
                for (int i = 0; i < current->num_children; i++) {
                    if (strcmp(current->children[i]->name, token) == 0) {
                        users[token].userPosition = current->children[i];
                        printf("success\n");
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    init_server();
    parse_input();
    return 0;
}