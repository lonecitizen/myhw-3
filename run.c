#include <sys/types.h>
#include <limits.h>

#include "run.h"
#include "util.h"

void *base = 0;
void *head = 0;

p_meta find_meta(p_meta *last, size_t size) {
  p_meta index = head;
  p_meta result = base;

  switch(fit_flag){
    case FIRST_FIT:
    {
      while(index && !(index->free && index->size >= size)){
        *last = index;
        index = index->next;
      }
      result = index;
    }
    break;

    case BEST_FIT:
    {
      //BEST_FIT CODE
    }
    break;

    case WORST_FIT:
    {
      //WORST_FIT CODE
    }
    break;

  }
  return result;
}

void *m_malloc(size_t size) {

  p_meta new = base;
  p_meta temp = base;
  p_meta last = base;

  if(head == 0){ 
    new = sbrk(META_SIZE);
    new->free = 0;
    new->data[0] = sbrk(size);
    new->size = size;
    head = new;
    new->next = base;
    new->prev = head;
    
    return new->data[0];
  }

  if(new = find_meta(&last, size)){ //block found
    if(new->size > size + META_SIZE){ //if found block has more space enough to
      temp = new + META_SIZE + size;
      temp->next = new->next;
      new->next = temp;
      temp->prev = new;
      temp->free = 1;
      temp->size = size - META_SIZE;
    }
    new->free = 0;
    new->size = size;
    new->data[0] = new + META_SIZE;
    return new->data[0];
  }
  else{
    new = sbrk(META_SIZE);
    new->free = 0;
    new->data[0] = sbrk(size);
    new->size = size;
    last->next = new;
    new->prev = last;
    new->next = base;
    
    return new->data[0];
  }
}

void m_free(void *ptr) {

}

void* m_realloc(void* ptr, size_t size)
{

}
