/*1) добавление записей
2) Удаление записей
3) Поиск рецептов по неполному совпадению
4) Вывод содержимого в алфавитном порядке*/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
/*Структуры хранения данных*/

typedef struct stuff {
    char* st;
    char* quant;
};
struct Note {
    char* name;
    struct stuff* schedule;
    char* instruction;
};


/*Функци для считывания строки произвольной длины*/
char* get_string();
struct stuff* create_list();
struct stuff* add_stuff_list(struct stuff* schedule);
void menu();
void add();
void del();
void sear();
void show();
void save_file(char* filePath);
void load_from_file(char* filePath);
void sort();

struct Note* note_list;


int main() {
    note_list = (struct Note*)calloc(1, sizeof(struct Note));
    menu();
    return 0;
}

void menu() {
    while (1)
    {
        int choose = 0;
        printf("%s", "Enter option: \n");
        printf("%s", "1) Add recipe \n");
        printf("%s", "2) Delete recipe \n");
        printf("%s", "3) Search recipe \n");
        printf("%s", "4) Show recipe \n");
        printf("%s", "0) Exit\n");
        scanf_s("%d", &choose);
        getchar();
        switch (choose) {
        case 1:
            add();
            break;
        case 2:
            del();
            break;
        case 3:
            sear();
            break;
        case 4:
            show();
            break;
        case 0:
            exit(1);
        }
    }
}


char* get_string() {
    int len = 0; // изначально строка пуста
    int capacity = 1; // ёмкость контейнера динамической строки (1, так как точно будет '\0')
    char* s = (char*)malloc(sizeof(char)); // динамическая пустая строка

    char c = getchar(); // символ для чтения данных

    // читаем символы, пока не получим символ переноса строки (\n)
    while (c != '\n') {
        s[(len)++] = c; // заносим в строку новый символ

        // если реальный размер больше размера контейнера, то увеличим его размер
        if (len >= capacity) {
            capacity *= 2; // увеличиваем ёмкость строки в два раза
            s = (char*)realloc(s, capacity * sizeof(char)); // создаём новую строку с увеличенной ёмкостью  
        }

        c = getchar(); // считываем следующий символ          
    }

    s[len] = '\0'; // завершаем строку символом конца строки

    return s; // возвращаем указатель на считанную строку
}


struct stuff* create_list() {
    struct stuff* it = (struct stuff*)calloc(1, sizeof(struct stuff));
    return it;
}


struct stuff* add_stuff_list(struct stuff* schedule) {
    int mas = _msize(schedule);
    int len = sizeof(struct stuff);
    schedule = (struct stuff*)realloc(schedule, (mas/len+1) * sizeof(struct stuff));
    struct stuff it;
    printf("%s", "enter name of ingredient: \n");
    it.st = get_string();
    printf("%s", "enter quantity: ");
    it.quant = get_string();
    *(schedule + (mas / len)-1) = it;
    return schedule;
}

void add() {
    struct Note one;
    int iter = 0;
    int mas = _msize(note_list);
    int len = sizeof(struct Note);
    one.schedule = create_list();
    printf("%s", "name: ");
    one.name = get_string();
    printf("%s", "number of ingredients: ");
    scanf_s("%d", &iter);
    getchar();
    for (int i = 0; i < iter; i++) {
        printf("%d %s", i+1, "ingredient: \n");
        one.schedule = add_stuff_list(one.schedule);
    }
    printf("%s", "instruction: \n");
    one.instruction = get_string();
    note_list = (struct Note*)realloc(note_list, (mas/len + 1) * sizeof(struct Note));
    *(note_list + (mas/len) - 1) = one;
    system("cls");
}

void del() {
    show();
    printf("%s", "Which recipe would be deleted\n");
    show();
    int choose;
    scanf_s("%d", &choose);
    getchar();
    int a = _msize(note_list) / sizeof(struct Note);
    for (int i = choose; i < a - 1; i++) {
        note_list[i] = note_list[i + 1];
    }
    note_list = (struct Note*)realloc(note_list, (a - 1) * sizeof(struct Note));
    system("cls");
}

void show() {
    system("cls");
    sort();
    int a = _msize(note_list) / sizeof(struct Note);
    for (int i = 0; i < a-1; i++) {
        printf("%d) %s %s%s", i+1, "Recipe name:", note_list[i].name, "\n");
        int b = _msize(note_list[i].schedule) / sizeof(struct stuff);
        printf("%s", "Ingeidients: \n");
        for (int j = 0; j < b-1; j++) {
            printf("    %s - %s%s", note_list[i].schedule[j].st, note_list[i].schedule[j].quant, "\n");
        }
        printf("%s: \n    %s\n\n", "Instruction", note_list[i].instruction);
    }
}



void sort() {
    int a = _msize(note_list) / sizeof(struct Note)-1;
    for (int i = 1; i < a; i++) {
        char* f, * s;
        int flag = 0;
        f = note_list[i - 1].name;
        s = note_list[i].name;
        int lenght = strlen(f) > strlen(s) ? strlen(s) : strlen(f);
        for (int j = 0; j < lenght; j++) {
            if (note_list[i - 1].name[j] > note_list[i].name[j] && flag == 0) {
                struct Note ex;
                ex = note_list[i - 1];
                note_list[i - 1] = note_list[i];
                note_list[i] = ex;
                i = 0;
                break;
            }
            else if (note_list[i - 1].name[j] < note_list[i].name[j]) {
                flag = 1;
            }
        }
    }
}


void sear() {
    system("cls");
    printf("%s", "print search element : ");
    char* key = get_string();
    int flag = 0;
    int a = _msize(note_list) / sizeof(struct Note);
    for (int i = 0; i < a-1; i++) {
        int b = _msize(note_list[i].schedule) / sizeof(struct stuff);
        if (strstr(note_list[i].name, key) != NULL|| strstr(note_list[i].instruction, key) != NULL)
        {
            flag++;
            printf("%d) %s %s%s", i + 1, "Recipe name:", note_list[i].name, "\n");
            
            printf("%s", "Ingeidients: \n");
            for (int j = 0; j < b - 1; j++) {
                printf("    %s - %s%s", note_list[i].schedule[j].st, note_list[i].schedule[j].quant, "\n");
            }
            printf("%s: \n    %s\n\n", "Instruction", note_list[i].instruction);
            continue;
        }
        for (int j = 0; j < b - 1; j++) {
            if (strstr(note_list[i].schedule[j].st, key) != NULL) {
                printf("%d) %s %s%s", i + 1, "Recipe name:", note_list[i].name, "\n");
                flag++;
                printf("%s", "Ingeidients: \n");
                for (int j = 0; j < b - 1; j++) {
                    printf("    %s - %s%s", note_list[i].schedule[j].st, note_list[i].schedule[j].quant, "\n");
                }
                printf("%s: \n    %s\n\n", "Instruction", note_list[i].instruction);
                j = b-1;
            }
        }
    }
    if (flag == 0) {
        printf("%s", "\nThere isn't data with such request, try other\n");
    }
}