#include <stdio.h>
#include <string.h>
#include "memory_manager.h"

void test_malloc_free(){
    void* ptr1=malloc(100);
void*ptr2=malloc(200);
if(ptr1==NULL||ptr2==NULL){
printf("malloc failed\n");
}
free(ptr1);
free(ptr2);
printf("malloc/free test passed\n");
}

void test_realloc(){
void* ptr =malloc(50);
if(ptr==NULL){
printf("malloc failed\n");
return;
}
ptr =realloc(ptr,100);
if(ptr==NULL){
printf("realloc failed\n");
return;}
printf("realloc test passed\n");
}

int main(){
test_malloc_free();
test_realloc();
return 0;
}
