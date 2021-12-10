/*1) ���������� �������
2) �������� �������
3) ����� �������� �� ��������� ����������
4) ����� ����������� � ���������� �������*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
/*��������� �������� ������*/

typedef struct stuff {
    char* st;
    char* quant;
};
struct Note {
    char* name;
    struct stuff* schedule;
    char* instruction;
};


/*������ ��� ���������� ������ ������������ �����*/
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
        case 5: {
            char* it;
            printf("Enter filepath: ");
            it = get_string();
            save_file(it);
            break;
        }
        case 6: {
            char* it;
            printf("Enter filepath: ");
            it = get_string();
            load_from_file(it);
            break;
        }
        case 0:
            exit(1);
        }
    }
}

void save_file(char* filePath) {
    FILE* f;
    if (f = fopen( filePath, "w")) {
        sort();
        int a = _msize(note_list) / sizeof(struct Note);
        for (int i = 0; i < a - 1; i++) {
            fprintf(f, ":\n");
            fprintf(f,"%s%s%s", "[", note_list[i].name, "]\n");
            int b = _msize(note_list[i].schedule) / sizeof(struct stuff);
            fprintf(f, "[");
            for (int j = 0; j < b - 1; j++) {
                fprintf(f, "%s*%s ", note_list[i].schedule[j].st, note_list[i].schedule[j].quant);
            }
            fprintf(f, "]\n");
            fprintf(f, "%s%s%s", "[", note_list[i].instruction, "]\n");
        }
        printf("Done!");
        fclose(f);
    }
    else printf("error opening file\n");
}
void load_from_file(char* filePath) {
    FILE* f;
    char buf[128];
    if (f = fopen(filePath, "r")) {
        fgets(buf, 127, f);
        while (!feof(f)) {
            
            if (buf[0] == ':') {
                fgets(buf, 127, f);
                struct Note one;
                int iter = 0;
                int mas = _msize(note_list);
                int len = sizeof(struct Note);
                one.schedule = create_list();
                for (int i = 0; i < 128; i++) {
                    int k = 1, len1 = 0, capacity =1;
                    char* s = (char*)malloc(sizeof(char));
                    if (buf[i] == '[') {
                        i++;
                        while (buf[i] != ']' && buf[i] != '\n') {
                            s[(len1)++] = buf[i++]; // ������� � ������ ����� ������

                            // ���� �������� ������ ������ ������� ����������, �� �������� ��� ������
                            capacity++; // ����������� ������� ������ � ��� ����
                            s = (char*)realloc(s, capacity * sizeof(char));
                        }
                        s[len1] = '\0';
                        one.name = s;
                    }
                    break;
                }
                fgets(buf, 127, f);
                for (int i = 0; i < 128; i++) {
                    
                    if (buf[i] == '[') {
                        i++;
                        while (buf[i] != ']'&&buf[i] != '\n') {
                            char *th1 = (char*)malloc(sizeof(char));
                            char* th2 = (char*)malloc(sizeof(char));
                            int len1 = 0, capacity = 1;
                            while (buf[i] != '*') {
                                
                                th1[(len1)++] = buf[i++]; // ������� � ������ ����� ������

                            // ���� �������� ������ ������ ������� ����������, �� �������� ��� ������
                                capacity++; // ����������� ������� ������ � ��� ����
                                th1 = (char*)realloc(th1, capacity * sizeof(char));
                            }
                            th1[len1] = '\0';
                            i++;
                            len1 = 0, capacity = 1;
                            while (buf[i] != ' ' && buf[i] != ']') {
                                
                                th2[(len1)++] = buf[i++]; // ������� � ������ ����� ������

                            // ���� �������� ������ ������ ������� ����������, �� �������� ��� ������
                                capacity++; // ����������� ������� ������ � ��� ����
                                th2 = (char*)realloc(th2, capacity * sizeof(char));
                            }
                            th2[len1] = '\0';
                            int mas = _msize(one.schedule);
                            int len = sizeof(struct stuff);
                            one.schedule = (struct stuff*)realloc(one.schedule, (mas / len + 1) * sizeof(struct stuff));
                            struct stuff it;
                            it.st = th1;
                            it.quant = th2;
                            *(one.schedule + (mas / len) - 1) = it;
                            i++;
                        }
                    }
                    break;

                }
                fgets(buf, 127, f);
                for (int i = 0; i < 128; i++) {
                    int k = 0, len1 = 0, capacity =1;
                    char* s = (char*)malloc(sizeof(char));
                    if (buf[i] == '[') {
                        i++;
                        while (buf[i] != ']' && buf[i] != '\n') {
                            s[(len1)++] = buf[i++]; // ������� � ������ ����� ������

                            // ���� �������� ������ ������ ������� ����������, �� �������� ��� ������
                            capacity++; // ����������� ������� ������ � ��� ����
                            s = (char*)realloc(s, capacity * sizeof(char)); // ������ ����� ������ � ����������� ��������  
                        }
                        s[len1] = '\0';
                        one.instruction = s;
                    }
                    break;
                }
                note_list = (struct Note*)realloc(note_list, (mas / len + 1) * sizeof(struct Note));
                *(note_list + (mas / len) - 1) = one;
            }
        }
        printf("Done!\n");
        fclose(f);
    }
    else printf("error opening file\n");
}


char* get_string() {
    int len = 0; // ���������� ������ �����
    int capacity = 1; // ������� ���������� ������������ ������ (1, ��� ��� ����� ����� '\0')
    char* s = (char*)malloc(sizeof(char)); // ������������ ������ ������

    char c = getchar(); // ������ ��� ������ ������

    // ������ �������, ���� �� ������� ������ �������� ������ (\n)
    while (c != '\n') {
        s[(len)++] = c; // ������� � ������ ����� ������

        // ���� �������� ������ ������ ������� ����������, �� �������� ��� ������
        if (len >= capacity) {
            capacity *= 2; // ����������� ������� ������ � ��� ����
            s = (char*)realloc(s, capacity * sizeof(char)); // ������ ����� ������ � ����������� ��������  
        }

        c = getchar(); // ��������� ��������� ������          
    }

    s[len] = '\0'; // ��������� ������ �������� ����� ������

    return s; // ���������� ��������� �� ��������� ������
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