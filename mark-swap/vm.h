#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 256
#define MAX_OBJECTS 256

typedef enum {
  OBJECT_INT,
  OBJECT_PAIR
} ObjectType;

typedef struct object_s {
  ObjectType type;
  unsigned char marked;
  struct object_s *next;
  struct object_s *head;
  struct object_s *tail;
  int value;
} Object;

typedef struct {
  Object *stack[MAX_STACK];
  Object *root;
  int num_objects;
  int max_objects;
  int stack_size;
} VM;

VM *new_vm();
void relase_vm();
Object *pop(VM* vm);
Object* new_object(VM* vm, ObjectType type);
void push(VM* vm, Object *value);
void gc(VM* vm);
