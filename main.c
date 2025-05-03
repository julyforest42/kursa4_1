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

// додавання вузла за даними в кінець списку
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
    if (num<1 || num>list->size) {
        printf("Сталася помилка! Введіть коректні дані\n");
        return;
    }
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
    if (num<1 || num>list->size) {
        printf("Сталася помилка! Введіть коректні дані\n");
        return;
    }
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
    struct Node *a[list->size], *curr=list->head;
    for (int i=0; i<list->size; i++) {
        a[i]=curr;
        curr=curr->next;
    }
    struct Node* i_ptr=a[0], *j_ptr, *op;
    struct Data tmp;
    while (i_ptr->next!=NULL) {
        j_ptr=i_ptr->next;
        op=i_ptr;
        while (j_ptr!=NULL) {
            if ((mode==1 && op->data.count>j_ptr->data.count) ||
                (mode==2 && i_ptr->data.count<j_ptr->data.count)) op=j_ptr;
            j_ptr=j_ptr->next;
        }
        tmp=i_ptr->data;
        i_ptr->data=op->data;
        op->data=tmp;
        i_ptr=i_ptr->next;
    }
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
    if (num<1 || num>list->size) {
        printf("Сталася помилка! Введіть коректні дані\n");
        return;
    }
    bool p[list->size];
    for (int i=0; i<list->size; i++) p[i]=false;
    p[num-1]=true;
    print_table(list, p);
}

// знайти елементи за назвою товару
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

// знайти елементи за роздрібною ціною на проміжку
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

// знайти елементи за терміном придатності нижче заданого
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

// знайти суму кількості товарів заданого постачальника
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

// введення даних
struct Data input_data() {
    struct Data data;
    printf("Найменування товару: ");
    fgets(data.product, MAX, stdin); data.product[strcspn(data.product,"\n")]=0;
    printf("Фірма виробник: ");
    fgets(data.company, MAX, stdin); data.company[strcspn(data.company,"\n")]=0;
    printf("Термін придатності: ");
    scanf("%d",&data.term); getchar();
    printf("Ціна роздрібна: ");
    scanf("%d",&data.retail_price); getchar();
    printf("Кількість: ");
    scanf("%d",&data.count); getchar();
    printf("Постачальник: ");
    fgets(data.deliverer, MAX, stdin); data.deliverer[strcspn(data.deliverer,"\n")]=0;
    printf("Закупівельна ціна: ");
    scanf("%d",&data.purchase_price); getchar();
    return data;
};

// зберегти список до файлу
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

// завантажити список з файлу
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

// основна програма
int main() {
    setlocale(LC_ALL, "urk");
    puts("Програму виконав студент Ткачук С.С. групи АІ-244");
    struct List list;
    init_list(&list);
    load_list(&list);
    int num,q;
    char ans='n',save;
    struct Data data;
    while (ans!='y') {
        printf("=============================================================\n");
        printf("| Введіть запит:                                            |\n");
        printf("| 0. Зберегти зміни                                         |\n");
        printf("| 1. Додати елемент в кінець списку                         |\n");
        printf("| 2. Додати елемент на місце заданої позиції                |\n");
        printf("| 3. Видалити елемент                                       |\n");
        printf("| 4. Коригування даних                                      |\n");
        printf("| 5. Вивести елемент                                        |\n");
        printf("| 6. Вивести список                                         |\n");
        printf("| 7. Сортувати список за кількістю (за зростанням)          |\n");
        printf("| 8. Сортувати список за кількістю (за спаданням)           |\n");
        printf("| 9. Знайти елементи по назві товару                        |\n");
        printf("| 10. Знайти товари за родрібною ціною у заданому діапазоні |\n");
        printf("| 11. Знайти товари з терміном придатності нижче заданого   |\n");
        printf("| 12. Знайти кількість товарів заданого постачальника       |\n");
        printf("| 13. Видалити всі елементи                                 |\n");
        printf("| 14. Завантажити список з файлу save.dat                   |\n");
        printf("| 15. Вихід                                                 |\n");
        printf("=============================================================\n:");
        scanf("%d",&q); getchar();
        switch (q) {
            case 0:
                save_list(&list);
                break;
            case 1:
                data=input_data();
                push_back(&list,data);
                break;
            case 2:
                printf("Виберіть номер вузла (1-%d): ",list.size+1);
                scanf("%d",&num); getchar();
                if (num<1 || num>list.size+1) {
                    printf("Сталася помилка! Введіть коректні дані\n");
                    break;
                }
                data=input_data();
                add_node(&list,num,data);
                break;
            case 3:
                print_list(&list);
                printf("Виберіть номер вузла: ");
                scanf("%d",&num); getchar();
                erase_node(&list,num);
                break;
            case 4:
                print_list(&list);
                printf("\nВиберіть номер вузла: ");
                scanf("%d",&num); getchar();
                printf("\nСтарі дані:\n");
                print_node(&list,num);
                printf("\nНові дані:\n");
                data=input_data();
                change_node(&list,num,data);
                break;
            case 5:
                printf("Виберіть номер вузла (всього %d): ",list.size);
                scanf("%d",&num); getchar();
                print_node(&list,num);
                break;
            case 6:
                printf("Всього елементів: %d\n",list.size);
                print_list(&list);
                break;
            case 7:
                sort_list(&list,1);
                printf("Список відсортовано за зростанням.\n");
                break;
            case 8:
                sort_list(&list,2);
                printf("Список відсортовано за спаданням.\n");
                break;
            case 9:
                char name[MAX];
                printf("Найменування товару: ");
                fgets(name, MAX, stdin); name[strcspn(name,"\n")]=0;
                find_name(&list,name);
                break;
            case 10:
                int mi,ma;
                printf("Мінімальне значення: ");
                scanf("%d",&mi); getchar();
                printf("Максимальне значення: ");
                scanf("%d",&ma); getchar();
                find_price(&list,mi,ma);
                break;
            case 11:
                int sup_term;
                printf("Верхня границя терміну придатності: ");
                scanf("%d",&sup_term); getchar();
                find_term(&list,sup_term);
                break;
            case 12:
                char deliv[MAX];
                printf("Назва постачальника: ");
                fgets(deliv, MAX, stdin); deliv[strcspn(deliv,"\n")]=0;
                int res=find_deliverer(&list,deliv);
                printf("Кількість: %d\n",res);
                break;
            case 13:
                erase_all(&list);
                printf("Всі елементи було видалено\n");
                break;
            case 14:
                load_list(&list);
                break;
            case 15:
                printf("Ви впевені, що хочете завершити роботу програми? (y/n): ");
                scanf("%c",&ans); getchar();
                if (ans=='y') {
                    printf("Зберегти зміни списку? (y/n): ");
                    scanf("%c",&save); getchar();
                    if (save=='y') save_list(&list);
                }
                break;
            default:
                printf("Невірний запит! Спробуйте ще раз\n");
                break;
        };
        if (ans!='y') {
            printf("\nНатисніть <Enter>, щоб продовжити: ");
            getchar();
        }
    }
    printf("Програма завершила свою роботу\n");
}
