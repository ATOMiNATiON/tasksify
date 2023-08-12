#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_BUFF 4096
#define OPTIONS "ha:l"

int main(int argc, char **argv) {
    int ch = 0, a = 0, l = 0, h = 0;
    char *taskname;
    FILE *fp;
    char buff[MAX_BUFF];

    while ((ch = getopt(argc, argv, OPTIONS)) != -1) {
        switch (ch) {
            case 'a':
                a = 1;
                taskname = optarg;
                break;
            case 'l':
                l = 1;
                break;
            case 'h': h = 1; break;      
        }
    }
    
    if (a && !h) {
        printf("Adding a task...\n");
        // only do appending to a file, not writing!
        // can only append 1 item into file right now
        fp = fopen("task.txt", "a");
        fputs(taskname, fp);
        fclose(fp); 
    }
    
    if (l && !h) {
        printf("Listing out all tasks...\n");
        fp = fopen("task.txt", "r");
        int tsknum = 1;
        while (fgets(buff, sizeof(buff), fp)) {
            printf("%d: %s", tsknum, buff);
            tsknum++; 
        }
        printf("\n"); 
        fclose(fp);
    }
    
    if (h) { 
        printf("SYNOPSIS:\n");
        printf("   A simple program for task managing purposes\n");
        printf("USAGE:\n");
        printf("   ./task -[OPTIONS]\n");
        printf("OPTIONS:\n");
        printf("   -a textfile   Adds a new task to your list of task. If no task is specified, nothing occurs\n");
        printf("   -l            lists all the current tasks\n");
    } 

    return 0;    
}
