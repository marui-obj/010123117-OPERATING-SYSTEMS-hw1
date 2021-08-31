#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int min_value = 0, max_value = 0;
float avg_value = 0;


typedef struct{
    int *arr;
    uint8_t length;
}list;

void argvToArray(char *arr_in[], list *out, int argc){
    int size = argc - 1;
    out->length = size;
    out->arr = (int*) malloc(sizeof(int)*size);
    printf("Size of array: %d\n",out->length);
    for(int i = 0; i < size; i++){
        out->arr[i] = atoi(arr_in[i+1]);
    }
}

void findAverage(list *my_list){
    float sum = 0;
    int c_num = my_list->length;
    for(int i = 0; i < c_num; i++)
        sum = sum + my_list->arr[i];

    avg_value = sum / c_num;
}

void findMinimum(list *my_list){
    uint8_t min_index = 0;
    int c_num = my_list->length;
    for (int i = 0; i < c_num; i++){
        int current_val = my_list->arr[i];
        int min_val = my_list->arr[min_index];

        if (current_val < min_val)
            min_index = i;
    }
    min_value = my_list->arr[min_index];
}

void findMaximum(list * my_list){
    uint8_t max_index = 0;
    int c_num = my_list->length;
    for (int i = 0; i < c_num; i++){
        int current_val = my_list->arr[i];
        int max_val = my_list->arr[max_index];

        if (current_val > max_val)
            max_index = i;
    }
    max_value = my_list->arr[max_index];
}


int main(int argc, char *argv[])
{
    list my_list;
    argvToArray(argv, &my_list, argc);

    pthread_t *tid[3];
    
    void (*func_ptr[3])() = {findAverage, findMinimum, findMaximum};

    for (int i = 0; i < 3; i++){
        pthread_create(tid[i], NULL, func_ptr[i],&my_list);
    }

    for (int i = 0; i < 3; i++){
        pthread_join(*tid[i], NULL);
    }

    printf("The average value is %f\n", avg_value);
    printf("The min value is %d\n", min_value);
    printf("The max value is %d\n,", max_value);
    free(my_list.arr);
    return 0;
}
