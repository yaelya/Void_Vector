#ifndef __VOID_VECTOR_H__
#include <stddef.h>

typedef int (*CompFind)(void* item, void* toFind); 
typedef int (*ActionFunc)(void* corrent, void* context);
typedef struct Void_Vector Void_Vector;
typedef enum
{
	E_OK,//THAT WILL BE = 0 -->THE FIRST VALUE IN ENUM IS 0
	E_NULL_PTR,
	E_UNDERFLOW,
	E_ALLOCATION_ERROR,
	E_BAD_INDEX
}ErrorCode;

Void_Vector *vectorGenerate(size_t capty);
void vectorDestroy(Void_Vector **v);

ErrorCode vectorPush(Void_Vector *v, void* value);
ErrorCode vectorInsert(Void_Vector *v, void* value, size_t index);
ErrorCode vectorPop(Void_Vector *v, void** item);
ErrorCode vectorRemove(Void_Vector *v, size_t index, void** item);

ErrorCode vectorGetElement(Void_Vector *v, size_t index, void** item);
ErrorCode vectorSetElement(Void_Vector *v,void* value, size_t index);

size_t vectorGetSize(Void_Vector *v);
size_t vectorGetCapacity(Void_Vector *v);
size_t vectorCount(Void_Vector *v, void* value, int(*CompFind)(void* a, void* b));
size_t vectorForEach(Void_Vector *v, ActionFunc action,void* context);
#ifdef _DEBUG
void vectorPrint(Void_Vector *v , ActionFunc print);
#endif /* DEBUG */
#endif
