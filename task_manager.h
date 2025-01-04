// task_manager.h

#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

typedef struct {
    int id;
    char title[100];
    char description[255];
    int is_completed; // 0 برای انجام نشده، 1 برای انجام شده
} Task;

void add_task(Task tasks[], int *task_count);
void remove_task(Task tasks[], int *task_count, int task_id);
void edit_task(Task tasks[], int task_count, int task_id);
void complete_task(Task tasks[], int task_count, int task_id);
void list_tasks(Task tasks[], int task_count);
void search_task(Task tasks[], int task_count, const char *title);
void save_tasks(Task tasks[], int task_count);
void load_tasks(Task tasks[], int *task_count);

#endif