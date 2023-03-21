#include "AdptArray.h"
#include "Person.h"
#include "book.h"
#include <stdio.h>
#include <stdlib.h>

/*  
    The AdptArray structure contains the following fields:

    copy_func: A function pointer to copy an element in the array.
    del_func: A function pointer to delete an element in the array.
    print_func: A function pointer to print an element in the array.
    len: The current length (i.e., the number of elements) of the array.
    data: An array of PElement pointers that points to the elements stored in the array.
*/
typedef struct AdptArray_
{
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
    int len;
    PElement* data;
}AdptArray;


/*      @CreateAdptArray:
    creating a new AdptArray instance and initializes its properties , 
    it takes three function pointers as argument and return a pointer to the created AdaptArray.
*/ 

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


/*      @DeleteAdptArray
    This function deletes an existing AdptArray instance and its associated elements.
    It first iterates over the elements in the array and deletes each element using the DEL_FUNC function pointer.
    Then it frees the memory used by the array and the AdptArray instance.
*/
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

/*      @SetAdaptArray
    This function sets an element at a specific index in the AdptArray.
    If the index is beyond the current length of the array, 
    the function resizes the array to accommodate the new element.
    It returns a SUCCESS result if the element is set successfully, otherwise a FAIL result.
*/
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


/*      @GetAdaptArrayAt
     This function gets an element from the AdptArray at a specific index.
     It first checks if the index is within the range of the array and the element at that index is not NULL.
     If so, it copies the element using the COPY_FUNC function pointer and returns the copy.
*/
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

/*      @GetAdaptArraySize
    This function returns the current size of the AdptArray.
*/
int GetAdptArraySize(PAdptArray arr)
{
    if (arr == NULL)
    {
        return -1;
    }
    return arr->len;
    
}

/*      @PrintDB
     This function prints all the elements in the AdptArray using the PRINT_FUNC function pointer.     
*/
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



