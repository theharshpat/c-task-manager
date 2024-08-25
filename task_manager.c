#include "task_manager.h"
#include <stdio.h>
#include <string.h>

void init_task_manager(TaskManager *manager) {
    manager->task_count = 0;
}

int add_task(TaskManager *manager, const char *description) {
    if (manager->task_count >= MAX_TASKS) {
        return -1; // Task list is full
    }

    Task *new_task = &manager->tasks[manager->task_count];
    new_task->id = manager->task_count + 1;
    strncpy(new_task->description, description, MAX_DESCRIPTION_LENGTH - 1);
    new_task->description[MAX_DESCRIPTION_LENGTH - 1] = '\0';
    new_task->completed = false;

    manager->task_count++;
    return new_task->id;
}

bool complete_task(TaskManager *manager, int task_id) {
    for (int i = 0; i < manager->task_count; i++) {
        if (manager->tasks[i].id == task_id) {
            manager->tasks[i].completed = true;
            return true;
        }
    }
    return false;
}

void list_tasks(const TaskManager *manager) {
    printf("Tasks:\n");
    for (int i = 0; i < manager->task_count; i++) {
        const Task *task = &manager->tasks[i];
        printf("%d. [%c] %s\n", task->id, task->completed ? 'X' : ' ', task->description);
    }
}

bool save_tasks(const TaskManager *manager, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        return false;
    }

    fwrite(&manager->task_count, sizeof(int), 1, file);
    fwrite(manager->tasks, sizeof(Task), manager->task_count, file);

    fclose(file);
    return true;
}

bool load_tasks(TaskManager *manager, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return false;
    }

    fread(&manager->task_count, sizeof(int), 1, file);
    fread(manager->tasks, sizeof(Task), manager->task_count, file);

    fclose(file);
    return true;
}

int main() {
    TaskManager manager;
    init_task_manager(&manager);

    add_task(&manager, "Buy groceries");
    add_task(&manager, "Finish project report");
    add_task(&manager, "Call mom");

    complete_task(&manager, 2);

    list_tasks(&manager);

    save_tasks(&manager, "tasks.dat");

    TaskManager loaded_manager;
    init_task_manager(&loaded_manager);
    load_tasks(&loaded_manager, "tasks.dat");

    printf("\nLoaded tasks:\n");
    list_tasks(&loaded_manager);

    return 0;
}
