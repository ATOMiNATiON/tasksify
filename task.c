#include <stdio.h>
#include <unistd.h>

#define OPTIONS "ha:l"

int main(int argc, char **argv) {
    int ch = 0, a = 0, l = 0, h = 0;
    char *tskname;
    while ((ch = getopt(argc, argv, OPTIONS)) != -1) {
        switch (ch) {
            case 'a':
                a = 1;
                tskname = optarg;
                break;
            case 'l':
                l = 1;
                break;
            case 'h': h = 1; break;      
        }
    }
    
    if (a && !h) {
        printf("Adding a task...\n");
        printf("%s\n", tskname);
    }
    
    if (l && !h) {
        printf("Listing out all tasks...\n");
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
