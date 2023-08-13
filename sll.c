#include <stdio.h>
#include "sll.h"
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 4096

typedef struct list {
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
        printf("%s\n", list->task_name);
        list = list->next;
    }
}

void free_list(List **list) {
    while (*list) {
        List *temp = *list;
        *list = (*list)->next;
        free(temp->task_name);
        free(temp);
    }
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
        *list = new_node;
    } else {
        List *current = *list;
        while (current->next) {
            current = current->next;
        }
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
}
