#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<locale.h>
#include<string.h>

#define MAX 100

// структура з даними
struct Data {
    char product[MAX];
    char company[MAX];
    int term;
    int retail_price;
    int count;
    char deliverer[MAX];
    int purchase_price;
};

// структура вузла
struct Node {
    struct Data data;
    struct Node* next;
};

// структура однозвʼязного списку
struct List {
    int size;
    struct Node* head;
};

// прототипи функцій
void init_list(struct List* list);
struct Node* create_node(struct Data data);
void push_back(struct List* list, struct Data data);
void add_node(struct List* list, int num, struct Data data);
void erase_all(struct List* list);
void erase_node(struct List* list, int num);
void change_node(struct List* list, int num, struct Data data);
void sort_list(struct List* list, int mode);
void print_table(struct List* list, bool* p);
void print_list(struct List* list);
void print_node(struct List* list, int num);
void find_name(struct List* list, char name[MAX]);
void find_price(struct List* list, int mi, int ma);
void find_term(struct List* list, int sup_term);
int find_deliverer(struct List* list, char deliv[MAX]);
bool confirm(char* prompt);
int get_int(char* prompt, int min, int max);
struct Data input_data();
void save_list(struct List* list);
void load_list(struct List* list);

// основна програма
int main() {
    setlocale(LC_ALL, "urk");
    puts("Програму виконав студент Ткачук С.С. групи АІ-244");
    struct List list;
    init_list(&list);
    load_list(&list);
    int num,q;
    bool ans=false;
    struct Data data;
    while (!ans) {
        printf("==============================================================\n");
        printf("|                        МЕНЮ ПРОГРАМИ                       |\n");
        printf("==============================================================\n");
        printf("| 0. Вихід                                                   |\n");
        printf("| 1. Додати елемент в кінець списку                          |\n");
        printf("| 2. Додати елемент на місце заданої позиції                 |\n");
        printf("| 3. Видалити елемент                                        |\n");
        printf("| 4. Видалити всі елементи                                   |\n");
        printf("| 5. Коригування даних                                       |\n");
        printf("| 6. Вивести елемент                                         |\n");
        printf("| 7. Вивести список                                          |\n");
        printf("| 8. Сортувати список за кількістю (за зростанням)           |\n");
        printf("| 9. Сортувати список за кількістю (за спаданням)            |\n");
        printf("| 10. Знайти елементи по назві товару                        |\n");
        printf("| 11. Знайти товари за роздрібною ціною у заданому діапазоні |\n");
        printf("| 12. Знайти товари з терміном придатності нижче заданого    |\n");
        printf("| 13. Знайти кількість товарів заданого постачальника        |\n");
        printf("| 14. Зберегти зміни                                         |\n");
        printf("| 15. Завантажити список                                     |\n");
        printf("==============================================================\n");
        q=get_int("Введіть запит: ",0,15);
        switch (q) {
            case 0:
                ans=confirm("Ви впевені, що хочете завершити роботу програми? (y/n): ");
                if (ans && confirm("Зберегти зміни списку? (y/n): ")) save_list(&list);
                break;
            case 1:
                data=input_data();
                push_back(&list,data);
                printf("Елемент додано в кінець списку\n");
                break;
            case 2:
                printf("Доступні позиції від 1 до %d\n",list.size+1);
                num=get_int("Введіть позицію: ", 1, list.size+1);
                data=input_data();
                add_node(&list,num,data);
                printf("Елемент додано на місце позиції %d\n",num);
                break;
            case 3:
                if (list.size==0) {
                    printf("Список порожній. Нічого видаляти\n");
                    break;
                }
                print_list(&list);
                printf("Доступні вузли від 1 до %d\n",list.size);
                num=get_int("Введіть номер вузла: ", 1, list.size);
                if (confirm("Ви справді хочете видалити цей елемент? (y/n): ")) {
                    erase_node(&list,num);
                    printf("Елемент видалено\n");
                }
                else printf("Видалення скасовано\n");
                break;
            case 4:
                if (list.size==0) {
                    printf("Список порожній. Нічого видаляти\n");
                    break;
                }
                if (confirm("Ви справді хочете видалити всі елементи списку? (y/n): ")) {
                    erase_all(&list);
                    printf("Елементи видалено\n");
                }
                else printf("Видалення скасовано\n");
                break;
            case 5:
                if (list.size==0) {
                    printf("Список порожній. Нічого змінювати\n");
                    break;
                }
                print_list(&list);
                printf("Доступні вузли від 1 до %d\n",list.size);
                num=get_int("Введіть номер вузла: ", 1, list.size);
                printf("\nСтарі дані:\n");
                print_node(&list,num);
                printf("\nНові дані:\n");
                data=input_data();
                change_node(&list,num,data);
                break;
            case 6:
                if (list.size==0) {
                    printf("Список порожній. Нічого виводити\n");
                    break;
                }
                printf("Доступні вузли від 1 до %d\n",list.size);
                num=get_int("Введіть номер вузла: ", 1, list.size);
                print_node(&list,num);
                break;
            case 7:
                if (list.size==0) {
                    printf("Список порожній. Нічого виводити\n");
                    break;
                }
                printf("Всього елементів: %d\n",list.size);
                print_list(&list);
                break;
            case 8:
                if (list.size==0) {
                    printf("Список порожній. Нічого сортувати\n");
                    break;
                }
                printf("Відсортований список за зростанням:\n");
                sort_list(&list,1);
                break;
            case 9:
                if (list.size==0) {
                    printf("Список порожній. Нічого сортувати\n");
                    break;
                }
                printf("Відсортований список за спаданням:\n");
                sort_list(&list,2);
                break;
            case 10:
                if (list.size==0) {
                    printf("Список порожній. Нічого знаходити\n");
                    break;
                }
                char name[MAX];
                printf("Найменування товару: ");
                fgets(name, MAX, stdin); name[strcspn(name,"\n")]=0;
                find_name(&list,name);
                break;
            case 11:
                if (list.size==0) {
                    printf("Список порожній. Нічого знаходити\n");
                    break;
                }
                int mi=get_int("Мінімальне значення: ",1,1000000000);
                int ma=get_int("Максимальне значення: ",mi,1000000000);
                find_price(&list,mi,ma);
                break;
            case 12:
                if (list.size==0) {
                    printf("Список порожній. Нічого знаходити\n");
                    break;
                }
                int sup_term=get_int("Верхня границя терміну придатності: ",2025,9999);
                find_term(&list,sup_term);
                break;
            case 13:
                if (list.size==0) {
                    printf("Список порожній. Нічого знаходити\n");
                    break;
                }
                char deliv[MAX];
                printf("Назва постачальника: ");
                fgets(deliv, MAX, stdin); deliv[strcspn(deliv,"\n")]=0;
                int res=find_deliverer(&list,deliv);
                printf("Кількість: %d\n",res);
                break;
            case 14:
                save_list(&list);
                break;
            case 15:
                load_list(&list);
                break;
        };
        if (!ans) {
            printf("\nНатисніть <Enter>, щоб продовжити: ");
            getchar();
        }
    }
    printf("Програма завершила свою роботу\n");
}

// ініціалізація списку
void init_list(struct List* list) {
    list->size=0;
    list->head=NULL;
}

// створення вузла
struct Node* create_node(struct Data data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data=data;
    new_node->next=NULL;
    return new_node;
}

// додавання вузла в кінець списку
void push_back(struct List* list, struct Data data) {
    if (list->head==NULL) {
        list->head=create_node(data);
        list->size=1;
        return;
    }
    struct Node* curr=list->head;
    while (curr->next!=NULL) curr=curr->next;
    curr->next=create_node(data);
    list->size++;
}

// додавання вузла за номером
void add_node(struct List* list, int num, struct Data data) {
    struct Node* curr=list->head;
    struct Node* tmp;
    if (num==1) {
        tmp=create_node(data);
        tmp->next=list->head;
        list->head=tmp;
    }
    else {
        int c=1;
        while (c+1<num){
            curr=curr->next;
            c++;
        }
        tmp=create_node(data);
        tmp->next=curr->next;
        curr->next=tmp;
    }
    list->size++;
}

// видалення всіх вузлів
void erase_all(struct List* list) {
    if (list->size==0) return;
    struct Node* tmp;
    while (list->head->next!=NULL) {
        tmp=list->head->next->next;
        free(list->head->next);
        list->head->next=tmp;
    }
    free(list->head);
    list->head=NULL;
    list->size=0;
}

// видалення вузла за номером
void erase_node(struct List* list, int num) {
    struct Node* curr=list->head;
    struct Node* tmp;
    if (num==1) {
        tmp=list->head->next;
        free(list->head);
        list->head=tmp;
    }
    else {
        int c=1;
        while (c+1<num){
            curr=curr->next;
            c++;
        }
        tmp=curr->next->next;
        free(curr->next);
        curr->next=tmp;
    }
    list->size--;
}

// зміна даних вузла
void change_node(struct List* list, int num, struct Data data) {
    struct Node* curr=list->head;
    int c=1;
    while (c<num) {
        c++;
        curr=curr->next;
    }
    curr->data=data;
}

// сортування списку за кількістю: режим 1 - за зростанням; режим 2 - за спаданням
void sort_list(struct List* list, int mode) {
    int n=list->size, op;
    struct Node** arr=malloc(sizeof(struct Node*)*n);
    struct Node* curr=list->head, *tmp;
    for (int i=0; i<n; i++) { arr[i]=curr; curr=curr->next; }
    for (int i=0; i<n-1; i++) {
        op=i;
        for (int j=i+1; j<n; j++) {
            if ((mode==1 && arr[op]->data.count>arr[j]->data.count) ||
                (mode==2 && arr[op]->data.count<arr[j]->data.count)) op=j;
        }
        tmp=arr[i]; arr[i]=arr[op]; arr[op]=tmp;
    }
    struct List tmp_list;
    init_list(&tmp_list);
    for (int i=0; i<n; i++) push_back(&tmp_list, arr[i]->data);
    print_list(&tmp_list);
    free(arr);
}

// виведення списку у вигляді таблиці заданих елементів
void print_table(struct List* list, bool* p) {
    bool ok=false;
    for (int i=0; i<list->size; i++) {
        if (p[i]) {
            ok=true;
            break;
        }
    }
    if (!ok) {
        printf("У списку немає елементів для виведення\n");
        return;
    }
    printf("=====================================================================================================================================\n");
    printf("| Номер | Найменування товару | Фірма виробник | Термін придатності | Ціна роздрібна | Кількість | Постачальник | Закупівельна ціна |\n");
    printf("=====================================================================================================================================\n");
    struct Node* curr=list->head;
    int i=0;
    while (curr!=NULL) {
        struct Data data=curr->data;
        curr=curr->next;
        if (!p[i++]) continue;
        printf("| %5d ",i);
        printf("| %19s ",data.product);
        printf("| %14s ",data.company);
        printf("| %18d ",data.term);
        printf("| %14d ",data.retail_price);
        printf("| %9d ",data.count);
        printf("| %12s ",data.deliverer);
        printf("| %17d |\n",data.purchase_price);
    }
    printf("=====================================================================================================================================\n");
}

// виведення списку
void print_list(struct List* list) {
    bool p[list->size];
    for (int i=0; i<list->size; i++) p[i]=true;
    print_table(list, p);
}

// виведення вузла за номером
void print_node(struct List* list, int num) {
    bool p[list->size];
    for (int i=0; i<list->size; i++) p[i]=false;
    p[num-1]=true;
    print_table(list, p);
}

// знаходження елементів за назвою товару
void find_name(struct List* list, char name[MAX]) {
    struct Node* curr=list->head;
    bool p[list->size];
    int i=0;
    while (curr!=NULL) {
        struct Data data=curr->data;
        if (!strcmp(data.product,name)) p[i]=true;
        else p[i]=false;
        curr=curr->next; i++;
    }
    print_table(list, p);
}

// знаходження елементів за роздрібною ціною на проміжку
void find_price(struct List* list, int mi, int ma) {
    struct Node* curr=list->head;
    bool p[list->size];
    int i=0;
    while (curr!=NULL) {
        struct Data data=curr->data;
        if (data.retail_price>=mi && data.retail_price<=ma) p[i]=true;
        else p[i]=false;
        curr=curr->next; i++;
    }
    print_table(list, p);
}

// знаходження елементів за терміном придатності нижче заданого
void find_term(struct List* list, int sup_term) {
    struct Node* curr=list->head;
    bool p[list->size];
    int i=0;
    while (curr!=NULL) {
        struct Data data=curr->data;
        if (data.term<sup_term) p[i]=true;
        else p[i]=false;
        curr=curr->next; i++;
    }
    print_table(list, p);
}

// знаходження суми кількості товарів заданого постачальника
int find_deliverer(struct List* list, char deliv[MAX]) {
    struct Node* curr=list->head;
    int c=1, sum=0;
    while (curr!=NULL) {
        struct Data data=curr->data;
        if (!strcmp(data.deliverer,deliv)) {
            sum+=data.count;
        }
        curr=curr->next; c++;
    }
    return sum;
}

// підтвердження (y/n)
bool confirm(char* prompt) {
    char str[MAX];
    while (true) {
        printf("%s",prompt);
        fgets(str,sizeof(str),stdin); str[strcspn(str,"\n")]=0;
        int n=strlen(str);
        if (n==1 && (str[0]=='y' || str[0]=='Y')) return true;
        if (n==1 && (str[0]=='n' || str[0]=='N')) return false;
        printf("Відповідь не розпізнано. Спробуйте ще раз\n");
    }
    return false;
}

// введення та перевірка числа
int get_int(char* prompt, int min, int max) {
    int val;
    char str[MAX];
    while (true) {
        printf("%s", prompt);
        fgets(str, sizeof(str), stdin); str[strcspn(str,"\n")]=0;
        if (sscanf(str, "%d", &val)!=1) {
            printf("Невірний формат. Введіть число\n");
            continue;
        }
        if (val<min || val>max) {
            printf("Число повинно бути в діапазоні [%d..%d]\n", min, max);
            continue;
        }
        return val;
    }
}

// введення даних
struct Data input_data() {
    struct Data data;
    printf("Найменування товару: ");
    fgets(data.product, MAX, stdin); data.product[strcspn(data.product,"\n")]=0;
    printf("Фірма виробник: ");
    fgets(data.company, MAX, stdin); data.company[strcspn(data.company,"\n")]=0;
    data.term=get_int("Термін придатності: ", 2025, 9999);
    data.retail_price=get_int("Ціна роздрібна: ", 1, 1000000000);
    data.count=get_int("Кількість: ", 1, 1000000000);
    printf("Постачальник: ");
    fgets(data.deliverer, MAX, stdin); data.deliverer[strcspn(data.deliverer,"\n")]=0;
    data.purchase_price=get_int("Закупівельна роздрібна: ", 1, 1000000000);
    return data;
};

// збереження списку до файлу
void save_list(struct List* list) {
    FILE *f;
    if ((f=fopen("save.dat","wb"))==NULL) {
        printf("Створення файлу save.dat для збереження даних\n");
    }
    struct Node* curr=list->head;
    while (curr!=NULL) {
        fwrite(&curr->data,sizeof(struct Data),1,f);
        curr=curr->next;
    }
    printf("Зміни збережено\n");
    fclose(f);
}

// завантаження списку з файлу
void load_list(struct List* list) {
    FILE *f;
    if ((f=fopen("save.dat","rb"))==NULL) {
        printf("Не вдалося відкрити файл save.dat для завантаження списку\n");
        return;
    }
    erase_all(list);
    struct Data data;
    while (fread(&data, sizeof(struct Data), 1, f)) {
        push_back(list,data);
    }
    printf("Список оновлено\n");
    fclose(f);
}
