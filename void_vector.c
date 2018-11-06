#include "void_vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Void_Vector
{
    void** data;
    size_t capacity;
    size_t total;
};

static size_t nextPow(size_t x)
{
	int num = 1;
	while (num < x)
		num *= 2;
	return num;
}

Void_Vector *vectorGenerate(size_t capty)//Ctor
{
	capty = nextPow(capty);
		
	Void_Vector *v = malloc(sizeof(Void_Vector));
	if (v != NULL) 
	{
	   v->data = malloc(capty * sizeof(void*));
	   if (v->data == NULL)
	   {
	   		free(v);
			return NULL;
	   } 

	   v->capacity = capty;
	   v->total = 0;
	}
	else
	{
		return NULL;
	}
	return v;
}

void vectorDestroy(Void_Vector **v)//Dtor
{
	if (*v != NULL || v != NULL)
	{
		free((*v)->data);
        	free(*v);
        	*v = NULL;
	}
}


static ErrorCode vectorResize(Void_Vector *v)
{
	v->data = realloc(v->data,sizeof(void*) * v->capacity * 2);
		if(v->data == NULL)
			return E_ALLOCATION_ERROR;
	v->capacity *= 2;
	return E_OK;
}

ErrorCode vectorPush(Void_Vector *v, void* value)
{
	if (v == NULL)
		return E_NULL_PTR;
	
	if (v->total == v->capacity)
	{
		ErrorCode err = vectorResize(v);
		if (err != E_OK)
			return err;			
	}
	v->data[v->total++] = value;
	return E_OK;
}

ErrorCode vectorInsert(Void_Vector *v, void* value, size_t index)
{
	if (v == NULL)
		return E_NULL_PTR;

	if (index > v->total)
		return E_BAD_INDEX;

	if (index ==  v->total)
		return vectorPush(v , value);

		
	if (v->total == v->capacity)
	{
		ErrorCode err = vectorResize(v);
		printf("%d",err);
		if (err != E_OK)
			return err;			
	}

	//moveElementForward();TODO
	for (int i = v->capacity; i < index; --i)
		v->data[i] = v->data[i-1];

	v->data[index] = value;
	++v->total;
	return E_OK;
}

ErrorCode vectorPop(Void_Vector *v, void** item)
{	
	if (v == NULL || item == NULL)
		return E_NULL_PTR;
	
	if (v->total == 0)
		return E_UNDERFLOW;

	*item = v->data[--v->total];			
	return E_OK;
}

ErrorCode vectorRemove(Void_Vector *v, size_t index, void** item)
{	
	int i;
	if (v == NULL || item == NULL)
		return E_NULL_PTR;
		
	if (index >= v->total)
		return E_BAD_INDEX;

	*item =  v->data[index];
	--v->total;

	for(i = index; i < v->capacity; ++i)
		v->data[i] = v->data[i + 1];

	return E_OK;
}

ErrorCode vectorGetElement(Void_Vector *v, size_t index, void** item)
{	
	if (v == NULL || item == NULL)
		return E_NULL_PTR;
										
	if (index >= v->total)
		return E_BAD_INDEX;	

	*item =  v->data[index];
	return E_OK;
}

ErrorCode vectorSetElement(Void_Vector *v, void* value, size_t index)
{			
	if (v == NULL)
		return E_NULL_PTR;
		
	if (index >= v->total)
		return E_BAD_INDEX;	
			
	v->data[index] = value;
	return E_OK;
}

size_t vectorGetSize(Void_Vector *v)
{			
	return (v == NULL) ? 0 : v->total;
}

size_t vectorGetCapacity(Void_Vector *v)
{			
	return (v == NULL) ? 0 : v->capacity;
}

typedef struct 
{
	CompFind comp;
	size_t count;
	void* value;
}CountStruct;

static int countEquals(void* element , void* context)
{
	CountStruct* countStruct = (CountStruct*)context;
	if (countStruct->comp(element, countStruct->value))
		++countStruct->count;
	return 1; 
}

size_t vectorCount(Void_Vector *v, void* value, CompFind compare)
{	
	
	CountStruct context;
	context.comp = compare;
	context.count = 0;
	context.value = value;
	vectorForEach(v, countEquals ,&context);

	return context.count;
}



size_t vectorForEach(Void_Vector *v, ActionFunc action ,void* context)
{
	void** arr_p;
	size_t i;
	if(v == NULL)
		return 0;
		
	arr_p = v->data;
	for(i = 0; i < v->total; ++i, ++arr_p)
	{
		if(action(*arr_p, context) == 0)
			break;
	}	
	return i;
}

static int compInt(void *item , void *toFind)
{
    int *comp_item =(int*)item;
    int *temp =(int*)toFind;
    return (temp==comp_item);
}
static int compStr(void *item , void *toFind)
{
    char *comp_item =(char *)item;
    char *temp =(char *)toFind;
    return (strcmp(temp, comp_item));
}
/*static int compPerson(void *item , void *toFind)
{
    Person *comp_item =(Person*)item;
    Person *tempFind =(Person*)toFind;
    return tempFind->m_id == comp_item->m_id && tempFind->m_age == comp_item->m_age;
}
*/
void vectorPrint(Void_Vector *v,ActionFunc print)
{	
	int i;
	printf("the vector:");
	for(int i = 0; i < v->capacity; i++)
		printf("%p\n",v->data[i]);
	//vectorForEach(v ,print ,);
}

void print_str(void* a, void* dummy)
{
	printf("%s\n",(char*)a);
}

void print_int(void* a, void* dummy)
{
	printf("%ls\n",(int*)a);
}

int print_double(void* a, void* dummy)
{
	printf("%f\n",*(double*)a);
	return 1;
}
