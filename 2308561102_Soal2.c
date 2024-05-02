#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct 
{
    char data[MAX_SIZE];
    int top;
} Stack;

void inisialisasi_stack(Stack *stack_kalimat)
{
    stack_kalimat->top = -1;
}

int isEmpty(Stack *stack_kalimat)
{
    return (stack_kalimat->top == -1);
}

int isFull(Stack *stack_kalimat)
{
    return (stack_kalimat->top == MAX_SIZE - 1);
}

void push(Stack *stack_kalimat, char data_untuk_masuk)
{
    if (!isFull(stack_kalimat))
    {
        stack_kalimat->data[++(stack_kalimat->top)] = data_untuk_masuk;
    }
    else
    {
        printf("Stack dalam keadaan Full.\n");
    }
}

char pop(Stack *stack_kalimat)
{
    if (!isEmpty(stack_kalimat))
    {
        return stack_kalimat->data[(stack_kalimat->top)--];
    }
    else
    {
        printf("Stack dalam keadaan Empty.\n");
        return -1;
    }
}

int cek_palindrom(char *kalimat)
{
    Stack stack_kalimat;
    inisialisasi_stack(&stack_kalimat);

    int length = strlen(kalimat);
    char temp;
    
    for (int i = 0; i < length; i++) 
    {
        temp = tolower(kalimat[i]);
        if ((temp >= 'a' && temp <= 'z') || (temp >= '0' && temp <= '9')) 
        {
            push(&stack_kalimat, temp);
        }
    }

    for (int i = 0; i < length; i++) 
    {
        temp = tolower(kalimat[i]);
        if ((temp >= 'a' && temp <= 'z') || (temp >= '0' && temp <= '9')) 
        {

            if (temp != pop(&stack_kalimat)) 
            {
                return 0;
            }
        }
    }

    return 1;
}

int main()
{
    system("cls");
    char kalimat[MAX_SIZE];
    printf("Masukkan sebuah kalimat: ");
    fgets(kalimat, MAX_SIZE, stdin);

    if (cek_palindrom(kalimat) == 1)
    {
        printf("Kalimat tersebut adalah palindrom.\n");
    }
    else
    {
        printf("Kalimat tersebut bukan palindrom.\n");
    }
    printf("\n");
    return 0;
}