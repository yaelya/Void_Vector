#include "void_vector.h"
#include <stdio.h>
#define CHECK_FUNC(func) if (func != E_OK) printf("ERROR IN LINE: %d\n",__LINE__);
int printNum(void *s, void* context)
{
	int* num = (int*)s;
    printf("%d\n", *num);
    return 1;
}

 int printStr(void *s, void* context)
{
	char **str =(char**)s;
    printf("%s\n", *str);
    return 1;
}


int main(){
	printf("********  START OF MAIN!!!  ******\n");
	void *res;
	
	int n1=8;
	int n2=4;
	char* s1="hello";
	char* s2="yaelll";
	char* s3="lolol ";
	char* s4="yael";
	char* s5="byebye";
	
	Void_Vector *str_vec = vectorGenerate(2);
	Void_Vector *int_vec= vectorGenerate(2);
	
	printf("\ninvalid pop:\n");
	CHECK_FUNC(vectorPop(str_vec,(void**)&res));
	
	CHECK_FUNC(vectorPush(int_vec ,&n1));
	CHECK_FUNC(vectorPush(int_vec ,&n2));
	printf("\nint vector:\n");
	vectorForEach(int_vec, NULL, printNum); 
	printf("int vector capacity: %lu\n",vectorGetCapacity(int_vec));
	CHECK_FUNC(vectorGetElement(int_vec,1,(void**)&res));
	printf("got from pos 1: %d\n",*((int*)res));
	
	CHECK_FUNC(vectorPush(str_vec, &s1));
	CHECK_FUNC(vectorPush(str_vec, &s3));
	printf("\nstring vector:\n");
	vectorForEach(str_vec, NULL, printStr); 
	printf("string vector capacity: %lu\n",vectorGetCapacity(str_vec));
	
	printf("\ninvalid insert:\n");
	CHECK_FUNC(vectorInsert(str_vec,&s2,4));
	
	CHECK_FUNC(vectorInsert(str_vec,&s2,1));
     CHECK_FUNC(vectorInsert(str_vec,&s4,1));
     printf("\nafter insert string vector:\n");
     vectorForEach(str_vec, NULL, printStr); 
	printf("string vector capacity: %lu\n",vectorGetCapacity(str_vec));
	
	CHECK_FUNC(vectorPop(str_vec,(void**)&res));
	printf("\npopped: %s\n",*((char**)res));
	printf("num of elements : %lu\n",vectorGetSize(str_vec));
	printf("after pop string vector:\n");
     vectorForEach(str_vec, NULL, printStr); 
    
    	CHECK_FUNC(vectorRemove(str_vec,1,(void**)&res));
	printf("\nremoved: %s\n",*((char**)res));
	printf("after remove string vector:\n");
     vectorForEach(str_vec, NULL, printStr); 
	printf("capacity %lu\n",vectorGetCapacity(str_vec));
	printf("num of elements : %lu\n",vectorGetSize(str_vec));
	
	CHECK_FUNC(vectorGetElement(str_vec,1,(void**)&res));
	printf("\ngot from pos 1: %s\n",*((char**)res));
	
	CHECK_FUNC(vectorSetElement(str_vec,&s3,0));
	printf("\nafter set:\n");
	vectorForEach(str_vec, NULL, printStr);
	
	CHECK_FUNC(vectorPush(str_vec ,&s4)); 
	CHECK_FUNC(vectorPush(str_vec ,&s1));
	CHECK_FUNC(vectorPush(str_vec ,&s5));
	printf("\nafter push: \n");
	vectorForEach(str_vec, NULL, printStr);
	printf("capacity %lu\n",vectorGetCapacity(str_vec));
	
	printf("\namount of noami's: %lu\n",vectorCount(str_vec,"noami",cmpStr));
	
	vectorDestroy(&str_vec);
	vectorDestroy(&int_vec);
		
	printf("\n********  END OF MAIN!!!  ******\n");	
	return 0;
}
