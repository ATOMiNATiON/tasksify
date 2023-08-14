#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sll.h"
#define MAX_BUFF 4096
#define OPTIONS "ha:lr:"

int main(int argc, char **argv) {
    int ch = 0, a = 0, l = 0, h = 0, r = 0;
    char *task_name = NULL, *task_num = NULL;

    while ((ch = getopt(argc, argv, OPTIONS)) != -1) {
        switch (ch) {
            case 'a':
                a = 1;
                if (optind <= argc) {
                    task_name = argv[optind - 1];
                } else {
                    printf("-a requires an argument\n");
                    exit(1);
                }
                break;
            case 'l':
                l = 1;
                break;
            case 'r':
                r = 1;
                task_num = optarg; 
                break;
            case 'h': h = 1; break;      
        }
    }

    List *task = list_create(".taskrc");

    if (a && !h) {
        printf("Adding a task...\n");
        printf("%s\n", task_name);
        add_task(task_name, &task, ".taskrc"); 
    }
    
    if (l && !h) {
        printf("Listing out all tasks...\n");
        list_tasks(task);        
    }

    if (r && !h) {
        printf("Removing a task...\n");
        int task_id = atoi(task_num);
        remove_task(task_id, &task);
    }
    
    if (h) { 
        printf("SYNOPSIS:\n");
        printf("   A simple program for task managing purposes\n");
        printf("USAGE:\n");
        printf("   ./task -[OPTIONS]\n");
        printf("OPTIONS:\n");
        printf("   -a textfile   Adds a new task to your list of task. If no task is specified, nothing occurs\n");
        printf("   -l            Lists all the current tasks\n");
        printf("   -r task#      Removes a task given the task number\n");
    } 

    free_list(&task);
    return 0;    
}
