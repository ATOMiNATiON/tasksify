#ifndef SLL
#define SLL

#include <inttypes.h>
#include <stdio.h>

struct list;
typedef struct list List;

List *list_create(const char *filename);

void free_list(List **list);
void list_tasks(List *list);
void add_task(const char *taskname, List **list, const char *filename);

#endif
