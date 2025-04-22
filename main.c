#include<stdio.h>
#include<stdlib.h>
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

// видалення вузла за номером
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
    if (list->size==0) {
        printf("Тут нічого видаляти.\n");
        return;
    }
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
        printf("Сталася помилка! Спройте ще раз.\n");
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

void change_node(struct List* list, int num, struct Data data) {
    if (num<1 || num>list->size) {
        printf("Сталася помилка! Спройте ще раз.\n");
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
    struct Node* i_ptr=list->head, *j_ptr, *op;
    struct Data tmp;
    while (i_ptr->next!=NULL) {
        j_ptr=i_ptr->next;
        op=i_ptr;
        while (j_ptr!=NULL) {
            if (mode==1 && op->data.count>j_ptr->data.count) op=j_ptr;
            else if (mode==2 && i_ptr->data.count<j_ptr->data.count) op=j_ptr;
            j_ptr=j_ptr->next;
        }
        tmp=i_ptr->data;
        i_ptr->data=op->data;
        op->data=tmp;
        i_ptr=i_ptr->next;
    }
}

// введення даних
struct Data input_data() {
    struct Data data;
    printf("Найменування товару: ");
    scanf("%s",data.product); getchar();
    printf("Фірма виробник: ");
    scanf("%s",data.company); getchar();
    printf("Термін придатності: ");
    scanf("%d",&data.term); getchar();
    printf("Ціна роздрібна: ");
    scanf("%d",&data.retail_price); getchar();
    printf("Кількість: ");
    scanf("%d",&data.count); getchar();
    printf("Постачальник: ");
    scanf("%s",data.deliverer); getchar();
    printf("Закупівельна ціна: ");
    scanf("%d",&data.purchase_price); getchar();
    return data;
};

// виведення списку
void print_list(struct List* list) {
    struct Node* curr=list->head;
    int c=1;
    while (curr!=NULL) {
        struct Data data=curr->data;
        printf("#%d\n",c);
        printf("Найменування товару: %s\n",data.product);
        printf("Фірма виробник: %s\n",data.company);
        printf("Термін придатності: %d\n",data.term);
        printf("Ціна роздрібна: %d\n",data.retail_price);
        printf("Кількість: %d\n",data.count);
        printf("Постачальник: %s\n",data.deliverer);
        printf("Закупівельна ціна: %d\n",data.purchase_price);
        curr=curr->next; c++;
    }
}

// виведення вузла за номером
void print_node(struct List* list, int num) {
    if (num<1 || num>list->size) {
        printf("Сталася помилка! Спройте ще раз.\n");
        return;
    }
    struct Node* curr=list->head;
    int c=1;
    while (c<num) {
        c++;
        curr=curr->next;
    }
    struct Data data=curr->data;
    printf("#%d\n",c);
    printf("Найменування товару: %s\n",data.product);
    printf("Фірма виробник: %s\n",data.company);
    printf("Термін придатності: %d\n",data.term);
    printf("Ціна роздрібна: %d\n",data.retail_price);
    printf("Кількість: %d\n",data.count);
    printf("Постачальник: %s\n",data.deliverer);
    printf("Закупівельна ціна: %d\n",data.purchase_price);
}

// знайти елементи за назвою товару
void find_name(struct List* list, char name[MAX]) {
    struct Node* curr=list->head;
    int c=1;
    while (curr!=NULL) {
        struct Data data=curr->data;
        if (!strcmp(data.product,name)) {
            printf("#%d\n",c);
            printf("Найменування товару: %s\n",data.product);
            printf("Фірма виробник: %s\n",data.company);
            printf("Термін придатності: %d\n",data.term);
            printf("Ціна роздрібна: %d\n",data.retail_price);
            printf("Кількість: %d\n",data.count);
            printf("Постачальник: %s\n",data.deliverer);
            printf("Закупівельна ціна: %d\n",data.purchase_price);
        }
        curr=curr->next; c++;
    }
}

// знайти елементи за роздрібною ціною на проміжку
void find_price(struct List* list, int mi, int ma) {
    struct Node* curr=list->head;
    int c=1;
    while (curr!=NULL) {
        struct Data data=curr->data;
        if (data.retail_price>=mi && data.retail_price<=ma) {
            printf("#%d\n",c);
            printf("Найменування товару: %s\n",data.product);
            printf("Фірма виробник: %s\n",data.company);
            printf("Термін придатності: %d\n",data.term);
            printf("Ціна роздрібна: %d\n",data.retail_price);
            printf("Кількість: %d\n",data.count);
            printf("Постачальник: %s\n",data.deliverer);
            printf("Закупівельна ціна: %d\n",data.purchase_price);
        }
        curr=curr->next; c++;
    }
}

// знайти елементи за терміном придатності нижче заданого
void find_term(struct List* list, int sup_term) {
    struct Node* curr=list->head;
    int c=1;
    while (curr!=NULL) {
        struct Data data=curr->data;
        if (data.term<sup_term) {
            printf("#%d\n",c);
            printf("Найменування товару: %s\n",data.product);
            printf("Фірма виробник: %s\n",data.company);
            printf("Термін придатності: %d\n",data.term);
            printf("Ціна роздрібна: %d\n",data.retail_price);
            printf("Кількість: %d\n",data.count);
            printf("Постачальник: %s\n",data.deliverer);
            printf("Закупівельна ціна: %d\n",data.purchase_price);
        }
        curr=curr->next; c++;
    }
}

// знайти елементи за постачальником
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

// зберегти список до файлу
void write_list(struct List* list, FILE *f) {
    struct Node* curr=list->head;
    struct Data data;
    while (curr!=NULL) {
        data=curr->data;
        fprintf(f,"%s ",data.product);
        fprintf(f,"%s ",data.company);
        fprintf(f,"%d ",data.term);
        fprintf(f,"%d ",data.retail_price);
        fprintf(f,"%d ",data.count);
        fprintf(f,"%s ",data.deliverer);
        fprintf(f,"%d",data.purchase_price);
        if (curr->next!=NULL) fputc('\n',f);
        curr=curr->next;
    }
}

// завантажити список з файлу
void load_list(struct List* list, FILE *f) {
    struct Data data;
    while (!feof(f)) {
        fscanf(f,"%s",data.product);
        fscanf(f,"%s",data.company);
        fscanf(f,"%d",&data.term);
        fscanf(f,"%d",&data.retail_price);
        fscanf(f,"%d",&data.count);
        fscanf(f,"%s",data.deliverer);
        fscanf(f,"%d",&data.purchase_price);
        push_back(list,data);
    }
}

// основна програма
int main() {
    setlocale(LC_ALL, "urk");
    puts("Програму виконав студент Ткачук С.С. групи АІ-244");
    struct List list;
    init_list(&list);
    FILE *f;
    if ((f=fopen("save.txt","r"))!=NULL) {
        load_list(&list,f);
        fclose(f);
    }
    int num,q;
    char ans='n',save;
    struct Data data;
    while (ans!='y') {
        printf("==========================================\n");
        printf("Введіть запрос:\n");
        printf("0. Зберегти зміни\n");
        printf("1. Додати елемент в кінець списку\n");
        printf("2. Додати елемент на місце заданої позиції\n");
        printf("3. Видалити елемент\n");
        printf("4. Коригування даних\n");
        printf("5. Вивести елемент\n");
        printf("6. Вивести список\n");
        printf("7. Сортувати список за кількістю (за зростанням)\n");
        printf("8. Сортувати список за кількістю (за спаданням)\n");
        printf("9. Знайти елементи по назві товару\n");
        printf("10. Знайти товари за родрібною ціною у заданому діапазоні\n");
        printf("11. Знайти товари з терміном придатності нижче заданого\n");
        printf("12. Знайти кількість товарів заданого постачальника\n");
        printf("13. Видалити всі елементи\n");
        printf("14. Вихід\n");
        printf("==========================================\n:");
        scanf("%d",&q); getchar();
        switch (q) {
            case 0:
                f=fopen("save.txt","w");
                write_list(&list,f);
                fclose(f);
                printf("Зміни збережено.\n");
                break;
            case 1:
                data=input_data();
                push_back(&list,data);
                break;
            case 2:
                printf("Виберіть номер вузла (1-%d): ",list.size+1);
                scanf("%d",&num); getchar();
                if (num<1 || num>list.size+1) {
                    printf("Сталася помилка! Спройте ще раз.\n");
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
                printf("==========================================\n");
                printf("Старі дані:\n");
                print_node(&list,num);
                printf("==========================================\n");
                printf("Нові дані:\n");
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
                scanf("%s",name); getchar();
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
                scanf("%s",deliv); getchar();
                int res=find_deliverer(&list,deliv);
                printf("Кількість: %d\n",res);
                break;
            case 13:
                erase_all(&list);
                printf("Всі елементи було видалено.\n");
                break;
            case 14:
                printf("Ви впевені, що хочете завершити роботу програми? (y/n): ");
                scanf("%c",&ans); getchar();
                if (ans=='y') {
                    printf("Зберегти зміни списку? (y/n): ");
                    scanf("%c",&save); getchar();
                    if (save=='y') {
                        f=fopen("save.txt","w");
                        write_list(&list,f);
                        fclose(f);
                    }
                }
                break;
            default:
                printf("Невірний запит! Спробуйте ще раз.\n");
                break;
        };
        if (ans!='y') {
            printf("\nНатисніть <Enter>, щоб продовжити: ");
            getchar();
        }
    }
    printf("Програма завершила свою роботу.\n");
}