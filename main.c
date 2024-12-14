#include"header.h"

struct node *head = NULL;


/**
 * @brief      { Вывести связанный список в консоль. }
 */
void printList() {
   struct node *ptr = head;
   printf("--------------------------------------------------------------------\n");
   printf("number   name \n");
   //начать с начала
   while(ptr != NULL) {
      printf("  %d     %s\n",ptr->key,ptr->data);
      ptr = ptr->next;
   }
    
   printf("--------------------------------------------------------------------\n");
}



/**
 * @brief      { запись значений на первую позицию списка. }
 *
 * @param[in]  key   The key
 * @param      data  The data
 */
void insertFirst(int key, char* data) {
   //создать ссылку
   struct node *link = (struct node*) malloc(sizeof(struct node));
    
   link->key = key;
   link->data = data;
    
   //указать на старый первый элемент
   link->next = head;
    
   //указать на новый первый элемент
   head = link;
}


/**
** @brief      { возвращает размер списка }
*
* @return     { description_of_the_return_value }
*/
int length() {
   int length = 0;
   struct node *current;
    
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
    
   return length;
}


/**
* @brief      { Сортировка числового поля по возрастанию }
*/
void sort_key() {

   char* tempData;
   int i, j, k, tempkey;
   struct node *current;
   struct node *next;
    
   int size = length();
   k = size ;
    
   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
      current = head;
      next = head->next;
        
      for ( j = 1 ; j < k ; j++ ) {   

         if ( current->key > next->key ) {
            tempkey = current->key;
            current->key = next->key;
            next->key = tempkey;

            tempData = current->data;
            current->data = next->data;
            next->data = tempData;
         }
            
         current = current->next;
         next = next->next;
      }
   }   
}

/**
* @brief      { запись списка в файл }
*/
void file_write() 
{
    struct node *ptr = head;
    char name_file[MAX_SIZE_TEXT];

    printf("Введите имя файла для записи:\n");
    scanf_s("%s", name_file, sizeof(name_file)); 

    FILE *fp = fopen(name_file, "w");

    if (fp) {
        if (ptr != NULL) { 
            while (ptr->next != NULL) { 
                fprintf(fp, "%d,%s\n", ptr->key, ptr->data);
                ptr = ptr->next;
            }
            fprintf(fp, "%d,%s", ptr->key, ptr->data);
        }
        fclose(fp);
        printf("Данные успешно записаны в файл %s\n", name_file); 
    } else {
        printf("Ошибка открытия файла %s\n", name_file); 
    }
}


/**
 * @brief      { чтение файла и запись в список }
 */
void file_read()
{
    int key;
    char *code = NULL;
    size_t code_size = 0; 
    int c;
    char name_file[MAX_SIZE_TEXT];

    printf("Введите имя файла для чтения\n");
    scanf_s("%s",name_file);

    FILE *fp=fopen(name_file,"r");
    if ( fp == NULL ) {

        printf("Ошибка\n");
        return;
    };
    while((c = fgetc(fp)) != EOF)
    {
        if( c == ',' ){
            key = atoi(code);
            code = NULL;
            code_size  = 0;
        }
        else if(c == '\n'){
            insertFirst(key,code);
            code = NULL;
            code_size = 0;
        }
        else {
            code = (char*) realloc(code, code_size+2);
            code[code_size++] = (char) c;
            code[code_size] = '\0';
        }
    }
    insertFirst(key,code);
    fclose(fp);
}


/**
 * @brief      { сохранение введённого значения в список }
 */
void saving_in_the_list()
{
    char *data_load;
    data_load = (char*)malloc(sizeof(*data_load)*MAX_SIZE_TEXT);
    int key_load;
    printf("введите имя\n");
    scanf_s("%s",data_load);
    printf("введите номер\n");
    scanf_s("%d",&key_load);
    insertFirst(key_load,data_load);
}


//
// @brief      { Сортировка текстового поля связанного списка по алфавиту. }
//
// @param      header  The header
//
// @return     { description_of_the_return_value }
//
struct node* mergeSort(struct node* header) {
    if (header == NULL || header->next == NULL) {
        return header;
    }

    struct node *slow = header;
    struct node *fast = header->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    struct node *secondHalf = slow->next;
    slow->next = NULL;

    struct node *first = mergeSort(header);
    struct node *second = mergeSort(secondHalf);

    struct node *sortedHead = NULL;
    if (strcmp(first->data, second->data) <= 0) {
        sortedHead = first;
        first = first->next;
    } else {
        sortedHead = second;
        second = second->next;
    }

    struct node *current = sortedHead;
    while (first != NULL && second != NULL) {
        if (strcmp(first->data, second->data) <= 0) {
            current->next = first;
            first = first->next;
        } else {
            current->next = second;
            second = second->next;
        }
        current = current->next;
    }

    current->next = (first != NULL) ? first : second;
    return sortedHead;
}


/**
 * @brief      { вывод значений больше введённого числа. }
 */
void print_nodes_with_key_greater_than() {
    struct node *current = head;
    int threshold;
    printf("Введите число минимума для вывода\n");
    scanf_s("%d", &threshold);

    printf("Узлы со значением ключа больше %d:\n", threshold);
    printf("--------------------------------------------------------------------\n");
    while (current != NULL) {
        if (current->key > threshold) {
            printf("  %d     %s\n", current->key, current->data);
        }
        current = current->next;
    }
    printf("--------------------------------------------------------------------\n");
}


/**
 * @brief      { Удаление произвольного объекта (нумерация сверху вниз). }
 *
 * @param      head  The head
 */
void deletePosition(struct node **head) 
{
    struct node *current = *head;
    struct node *previous = NULL;
    int count = 0;

    int position;
    printf("Введите ключ узла для удаления: ");
    scanf("%d", &position);

    if (*head == NULL || position <= 0) {
         printf("Узел не найден (пустой список или позиция вне границ списка)\n ");
    }

    while (current != NULL && count < position -1) { 
        previous = current;
        current = current->next;
        count++;
    }

    if (current == NULL) {
        printf("Узел не найден (позиция вне границ списка)\n ");
    }

    if (previous == NULL) { 
        *head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current->data);
    free(current);
}


/**
 * @brief     { Вывод узлов начинающися на введённую букву. }
 */
void print_nodes_with_matching_first_letter() 
{ 
    struct node *current = head;

    if (head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    char letter;
    printf("Введите первую букву:\n ");
    scanf(" %c", &letter);

    letter = tolower(letter);

    printf("Узлы, начинающиеся с буквы '%c':\n", letter);
    printf("--------------------------------------------------------------------\n");
    while (current != NULL) {
        if (current->data != NULL && tolower(current->data[0]) == letter) {
            printf("  %d     %s\n", current->key, current->data);
        }
        current = current->next;
    }
    printf("--------------------------------------------------------------------\n");
}

/**
 * @brief      { Главная функция. }
 *
 */
int main() {
    int choice;
    do {
        printf("0 - Выход из программы\n");
        printf("1 - Удаление произвольного объекта (нумерация сверху вниз)\n");
        printf("2 - Вывод всех объектов на экран в виде таблицы\n");
        printf("3 - Загрузка набора объектов из файл\n");
        printf("4 - Сохранение набора объектов в файл\n");
        printf("5 - Добавление новых объектов\n");
        printf("6 - сортировка по возрастанию числового поля\n");
        printf("7 - сортировка по алфавиту текстового поля\n");
        printf("8 - вывод значений больше введённого числа\n");
        printf("9 - вывод узлов начинающися на введённую букву\n");

        scanf_s("%d", &choice);

        switch (choice) {
            case 1: deletePosition(&head); break;
            case 2: printList(); break;
            case 3: file_read(); break;
            case 4: file_write(); break;
            case 5: saving_in_the_list(); break;
            case 6: sort_key(); break;
            case 7: head = mergeSort(head); break;
            case 8: print_nodes_with_key_greater_than(); break;
            case 9: print_nodes_with_matching_first_letter(); break;
            case 0: printf("Выход из программы.\n"); break;
            default: printf("Неверный выбор.\n");  
        } 
    } while (choice != 0);
   return 0;
}