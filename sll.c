#include <stdio.h>
#include "sll.h"
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 4096

void remove_row(const char *filename, int row_num);

typedef struct list {
    int task_id;
    char *task_name;
    List *next;
} List;

List *list_create(const char *filename) {
    List *lst = NULL;
    List *current = NULL;
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    char buff[MAX_SIZE];
     
    while (fgets(buff, sizeof(buff), fp)) {
        char *task_name = strdup(buff);
        if (!task_name) {
            printf("Error with memory\n");
            exit(1);
        }
        List *new_node = calloc(1, sizeof(List));
        
        if (!new_node) {
            printf("Error with memory\n");
            free(task_name);
            exit(1);
        } 

        new_node->task_id = lst ? current->task_id + 1: 1;
        new_node->task_name = task_name;

        if (!lst) {
            lst = new_node;
            current = lst;
        } else {
            current->next = new_node;
            current = current->next;    
        }

    }

    fclose(fp);
    return lst;
}

void list_tasks(List *list) {
    while (list) {
        printf("#%d: %s\n", list->task_id, list->task_name);
        list = list->next;
    }
}

void free_list(List **list) {
    if (!list || !*list) {
        return;
    }
    
    List *current = *list;
    while (current) {
        List *temp = current;
        current = current->next;

        free(temp->task_name);
        free(temp);
    }
    *list = NULL;
}

void add_task(const char *task_name, List **list, const char *filename) {
    if (!task_name || !list) {
        return;
    }

    char *new_task = strdup(task_name);
    if (!new_task) {
        printf("Error making new task\n");
        exit(1);
    }

    // Create a new List node and link it
    List *new_node = calloc(1, sizeof(List));
    if (!new_node) {
        printf("Memory allocation error\n");
        free(new_task);
        exit(1);
    }

    new_node->task_name = new_task;

    if (!*list) {
        new_node->task_id = 1;
        *list = new_node;
    } else {
        List *current = *list;
        while (current->next) {
            current = current->next;
        }
        new_node->task_id = current->task_id + 1;
        current->next = new_node;
    }

    // Update the file contents
    FILE *fp = fopen(filename, "a"); // Open the file in append mode
    if (!fp) {
        printf("Error opening file\n");
        exit(1);
    }
    fprintf(fp, "%s\n", task_name);
    fclose(fp);
    printf("\n");
}

void remove_task(int task_id, List **list) {
    if (!list || !*list) {
        return;
    }

    List *current = *list;
    List *prev = NULL;

    while (current) {
        if (current->task_id == task_id) {
            remove_row(".taskrc", task_id);
            printf("%s\n", current->task_name);

            if (prev) {
                prev->next = current->next;
            } else {
                *list = current->next;
            }

            // Free memory
            free(current->task_name);
            free(current);

            // Update task IDs in the linked list after removal
            current = *list;
            int new_task_id = 1;
            while (current) {
                current->task_id = new_task_id;
                new_task_id++;
                current = current->next;
            }

            return; // Task found and removed
        }

        prev = current;
        current = current->next;
    }
}
 

void remove_row(const char *filename, int row_num) {
    FILE *original_fp = fopen(filename, "r");
    if (original_fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    FILE *temp_fp = fopen("temp.txt", "w");
    if (temp_fp == NULL) {
        printf("Error opening file\n");
        fclose(original_fp);
        exit(1);
    }

    char buff[4096];
    int current_row = 1;

    while (fgets(buff, sizeof(buff), original_fp)) {
        if (current_row != row_num) {
            fputs(buff, temp_fp);
        }
        current_row++;
    }

    fclose(original_fp);
    fclose(temp_fp);

    remove(filename);       // Remove the original file
    rename("temp.txt", filename);  // Rename the temporary file
}
