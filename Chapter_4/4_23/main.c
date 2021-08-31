#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct{
    uint16_t *arr;
    uint16_t length;
}list;

typedef struct{
    list my_list;
    uint16_t end_val;
}arg_t;

void append(list *my_list, uint16_t value){
    my_list->arr[my_list->length] = value;
    my_list->length++;
}

void findPrime1(void *param){
    printf("Thread 1, Start!\n");
    arg_t *p_arg = (arg_t *)param;

    for(int current_val = 3; current_val < p_arg->end_val/2; current_val++){
        int is_prime = 1;
        for(int i = 2; i < current_val/2; i++){
            if(current_val % i == 0){
                is_prime = 0;
                break;
            }
        }
        if(is_prime){
            append(&(p_arg->my_list), current_val);
        }
    }
    printf("Thread 1, End\n");
}

void findPrime2(void *param){
    printf("Thread 2, Start!\n");
    arg_t *p_arg = (arg_t *)param;

    for(int current_val = p_arg->end_val/2; current_val < p_arg->end_val; current_val++){
        int is_prime = 1;
        for(int i = 2; i < current_val/2; i++){
            if(current_val % i == 0){
                is_prime = 0;
                break;
            }
        }
        if(is_prime){
            append(&(p_arg->my_list), current_val);
        }
    }
    printf("Thread 2, End\n");
}
int main(int argc, char *argv[]){
    if (argc <= 1){
        fprintf(stderr, "Error invaild input\n");
        return -1;
    }
    uint16_t input = atoi(argv[1]);
    
    arg_t *p_arg1 = malloc(sizeof(arg_t));
    p_arg1->my_list.arr  = (uint16_t *)malloc(input);
    p_arg1->end_val = input;
    append(&p_arg1->my_list.arr, 2); // init

    arg_t *p_arg2 = malloc(sizeof(arg_t));
    p_arg2->my_list.arr = (uint16_t *)malloc(input);
    p_arg2->end_val = input;

    pthread_t *tid[2];

    pthread_create(tid[0], NULL, findPrime1,(void *)p_arg1);
    pthread_create(tid[1], NULL, findPrime2,(void *)p_arg2);
    pthread_join(*tid[0], NULL);
    pthread_join(*tid[1], NULL);

    for(int i = 0; i < p_arg1->my_list.length; i++)
        printf("Thread 1, index: %d; val: %d\n", i, p_arg1->my_list.arr[i]);

    for(int i = 0; i < p_arg2->my_list.length; i++)
        printf("Thread 2, index: %d; val: %d\n", i, p_arg2->my_list.arr[i]);

    free(p_arg1->my_list.arr);
    free(p_arg1);

    free(p_arg2->my_list.arr);
    free(p_arg2);
    return 0;

}
