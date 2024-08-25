#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <stdbool.h>

#define MAX_TASKS 100
#define MAX_DESCRIPTION_LENGTH 256

typedef struct {
    int id;
    char description[MAX_DESCRIPTION_LENGTH];
    bool completed;
} Task;

typedef struct {
    Task tasks[MAX_TASKS];
    int task_count;
} TaskManager;

void init_task_manager(TaskManager *manager);
int add_task(TaskManager *manager, const char *description);
bool complete_task(TaskManager *manager, int task_id);
void list_tasks(const TaskManager *manager);
bool save_tasks(const TaskManager *manager, const char *filename);
bool load_tasks(TaskManager *manager, const char *filename);

#endif // TASK_MANAGER_H
