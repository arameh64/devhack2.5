#include<stdio.h>
#include<stdlib.h>

struct Stack
{
char *data;
int size;
int capacity;
};

void stack_init(struct Stack *s)
{
s->capacity=2;
s->size=0;
s->data=malloc(sizeof(char)*s->capacity);
}

void push(struct Stack *s, char c)
{
if(s->size==s->capacity)
{
s->capacity*=2;
s->data=realloc(s->data,s->capacity);
}
s->data[s->size++]=c;
}

char pop(struct Stack *s)
{
return s->data[--s->size];
}

int is_empty(const struct Stack *s)
{
return s->size==0;
}

void stack_free(struct Stack *s)
{
free(s->data);
s->data=NULL;
s->size=0;
s->capacity=0;
}