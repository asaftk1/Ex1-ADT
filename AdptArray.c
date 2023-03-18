#include "AdptArray.h"
#include "Person.h"
#include "book.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct AdptArray_
{
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
    int len;
    PElement* data;
}AdptArray;
 


PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func,PRINT_FUNC print_func)
{
    
    PAdptArray arr = (PAdptArray)calloc(1,sizeof(AdptArray));

    if(arr == NULL)
    {
        printf("Falid to allocate memory");
        exit(1);
    } 
    else
    {
    arr->copy_func = copy_func;
    arr->del_func = del_func;
    arr->print_func = print_func;
    arr->data = NULL;
    arr->len = 0;
    }
    return arr;
}



void DeleteAdptArray(PAdptArray AdptArray)
{

    if(AdptArray->data == NULL) return;
    for (int i = 0; i < AdptArray->len; i++)
    {
        if(AdptArray->data[i] != NULL)
        {
        AdptArray->del_func(AdptArray->data[i]);

        }
    }

    free(AdptArray->data);
    free(AdptArray);
    
}

Result SetAdptArrayAt(PAdptArray AdptArray, int index, PElement element)
{
    if(index < 0){
        return FAIL;
    }
    int len  = AdptArray->len;

    if(index > len)
    {
        PElement* new_arr = (PElement*)realloc(AdptArray->data,sizeof(PElement)*(index+1));
        if(new_arr == NULL)
        {
        printf("Falid to allocate memory");
        exit(1);
        }
        int old_index = AdptArray->len; 
        AdptArray->data = new_arr;
        AdptArray->len = index+1;

        for (size_t i = old_index; i <= index; i++)
        {
            AdptArray->data[i] = NULL;
        }

        AdptArray->data[index] = AdptArray->copy_func(element);  
    }
    return SUCCESS;
    
}

PElement GetAdptArrayAt(PAdptArray arr, int index)
{
    if(index > (arr->len)) 
    {
        return NULL;
    }
    else if (arr->data[index] == NULL)return NULL;
    PElement copy = arr->copy_func(arr->data[index]);
    
    return copy;

}

int GetAdptArraySize(PAdptArray arr)
{
    if (arr == NULL)
    {
        return -1;
    }
    return arr->len;
    
}

void PrintDB(PAdptArray arr)
{
    if(arr != NULL)
    {
    for (int i = 0; i < arr->len; i++)
    {
        if(arr->data[i] != NULL) 
        {
            arr->print_func(arr->data[i]);
            
        }
    }
    
    }
    
}



