#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "task_manager.h"

void add_task(Task tasks[], int *task_count) {
    Task new_task;
    new_task.id = *task_count + 1;
    printf("Enter task title: ");
    getchar();
    fgets(new_task.title, sizeof(new_task.title), stdin);
    new_task.title[strcspn(new_task.title, "\n")] = '\0';
    printf("Enter task description: ");
    fgets(new_task.description, sizeof(new_task.description), stdin);
    new_task.description[strcspn(new_task.description, "\n")] = '\0';
    new_task.is_completed = 0;

    tasks[*task_count] = new_task;
    (*task_count)++;
    printf("Task added successfully!\n");
}


void remove_task(Task tasks[], int *task_count, int task_id) {
    int found = 0;
    for (int i = 0; i < *task_count; i++) {
        if (tasks[i].id == task_id) {
            found = 1;
            for (int j = i; j < *task_count - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            (*task_count)--;
            printf("Task removed successfully!\n");      
            break;
        }
    }
    if (!found) {
        printf("Task with ID %d not found.\n", task_id);
    }
}

void edit_task(Task tasks[], int task_count, int task_id) {
    int found = 0;
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == task_id) {
            found = 1;
            printf("Enter new title: ");
            getchar();
            fgets(tasks[i].title, sizeof(tasks[i].title), stdin);
            tasks[i].title[strcspn(tasks[i].title, "\n")] = '\0';
            printf("Enter new description: ");
            fgets(tasks[i].description, sizeof(tasks[i].description), stdin);
            tasks[i].description[strcspn(tasks[i].description, "\n")] = '\0';
            printf("Task edited successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Task with ID %d not found.\n", task_id);
    }
}

void complete_task(Task tasks[], int task_count, int task_id) {
    int found = 0;
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == task_id) {
            found = 1;
            tasks[i].is_completed = 1;
            printf("Task marked as completed!\n");
            break;
        }
    }
    if (!found) {
        printf("Task with ID %d not found.\n", task_id);
    }
}

void list_tasks(Task tasks[], int task_count) {
    if (task_count == 0) {
        printf("No tasks to display.\n");
        return;
    }
    for (int i = 0; i < task_count; i++) {
        printf("Task ID: %d\n", tasks[i].id);
        printf("Title: %s\n", tasks[i].title);
        printf("Description: %s\n", tasks[i].description);
        printf("Status: %s\n", tasks[i].is_completed ? "Completed" : "Pending");
        printf("\n");
    }
}

void search_task(Task tasks[], int task_count, const char *title) {
    int found = 0;
    for (int i = 0; i < task_count; i++) {
        if (strstr(tasks[i].title, title)) {
            printf("Task ID: %d\n", tasks[i].id);
            printf("Title: %s\n", tasks[i].title);
            printf("Description: %s\n", tasks[i].description);
            printf("Status: %s\n", tasks[i].is_completed ? "Completed" : "Pending");
            printf("\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No task found with title containing '%s'.\n", title);
    }
}

void save_tasks(Task tasks[], int task_count) {
    FILE *file = fopen("tasks.dat", "wb");
    if (file == NULL) {
        printf("Error saving tasks.\n");
        return;
    }
    fwrite(&task_count, sizeof(int), 1, file);
    fwrite(tasks, sizeof(Task), task_count, file);
    fclose(file);
    printf("Tasks saved successfully!\n");
}

void load_tasks(Task tasks[], int *task_count) {
    FILE *file = fopen("tasks.dat", "rb");
    if (file == NULL) {
        printf("No saved tasks found.\n");
        return;
    }
    fread(task_count, sizeof(int), 1, file);
    fread(tasks, sizeof(Task), *task_count, file);
    fclose(file);
    printf("Tasks loaded successfully!\n");
}

int main() {
    Task tasks[100];
    int task_count = 0;
    load_tasks(tasks, &task_count);

    int choice;
    while (1) {
        printf("Task Management System\n");
        printf("1. Add Task\n");
        printf("2. Remove Task\n");
        printf("3. Edit Task\n");
        printf("4. Complete Task\n");
        printf("5. List Tasks\n");
        printf("6. Search Task\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_task(tasks, &task_count);
                save_tasks(tasks, task_count);
                break;
            case 2: {
                int task_id;
                printf("Enter task ID to remove: ");
                scanf("%d", &task_id);
                remove_task(tasks, &task_count, task_id);
                save_tasks(tasks, task_count);
                break;
            }
            case 3: {
                int task_id;
                printf("Enter task ID to edit: ");
                scanf("%d", &task_id);
                edit_task(tasks, task_count, task_id);
                save_tasks(tasks, task_count);
                break;
            }
            case 4: {
                int task_id;
                printf("Enter task ID to complete: ");
                scanf("%d", &task_id);
                complete_task(tasks, task_count, task_id);
                save_tasks(tasks, task_count);
                break;
            }
            case 5:
                list_tasks(tasks, task_count);
                break;
            case 6: {
                char title[100];
                printf("Enter title to search: ");
                getchar();
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                search_task(tasks, task_count, title);
                break;
            }
            case 7:
                save_tasks(tasks, task_count);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
