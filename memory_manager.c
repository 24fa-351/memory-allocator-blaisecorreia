#include "memory_manager.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <sys/types.h>
void* get_me_blocks(ssize_t how_much) {
    void*ptr = VirtualAlloc(NULL, how_much, MEM_COMMIT| MEM_RESERVE, PAGE_READWRITE);
    if (!ptr){
        fprintf(stderr,"VirtualAlloc failed\n");
        return NULL;
    }
    return ptr;
}
#else
#include <unistd.h>
void* get_me_blocks(ssize_t how_much){
    void*ptr = sbrk(0);
    if (sbrk(how_much) == (void*)-1){
        fprintf(stderr, "sbrk failed\n");
        return NULL;
    }
    return ptr;
}
#endif

#define BLOCK_SIZE 32 

typedef struct Block {
size_t size;
struct Block* next;int is_free;
}Block;

static Block* free_list = NULL;static void*memory_start = NULL;static size_t total_memory = 0;

void* malloc(size_t size){
if (size%BLOCK_SIZE !=0){size += BLOCK_SIZE - (size %BLOCK_SIZE);}
    Block* current = free_list;
Block* prev = NULL;

while(current) {
if (current->size>=size && current->is_free){
current->is_free=0;
return(void*)(current+1);
}
prev=current;
current=current->next;
}
if(!memory_start){
memory_start=get_me_blocks(1024*1024);
if(!memory_start) {
return NULL;}
}

Block* new_block=(Block*)memory_start;
new_block->size=size;
new_block->is_free=0;
new_block->next=NULL;

memory_start=(void*)((char*)memory_start+sizeof(Block)+size);

return (void*)(new_block+1);
}

void free(void* ptr){
if(!ptr)return;
Block*block=(Block*)ptr-1;
block->is_free=1;
block->next=free_list;
free_list=block;
}

void* realloc(void* ptr, size_t size){
if(!ptr)return malloc(size);
if(size==0){free(ptr);return NULL;}
Block*block=(Block*)ptr-1;
size_t old_size=block->size;
if(size<=old_size)return ptr;
void*new_ptr=malloc(size);
if(!new_ptr)return NULL;
memcpy(new_ptr,ptr,old_size);
free(ptr);
return new_ptr;
}
