#include "vm.h"
#include <assert.h>

static void mark_all(VM* vm);
static void mark(Object* object, int level);
static void sweep(VM *vm);

VM *new_vm() {
  VM * vm = malloc(sizeof(VM));
  assert(vm != NULL);
  vm->stack_size = 0;
  vm->root = NULL;
  vm->num_objects = 0;
  vm->max_objects = MAX_OBJECTS;
  return vm;
}

void relase_vm(VM *vm) {
  free(vm);
}

Object *pop(VM* vm) {
  assert(vm->stack_size > 0);
  return vm->stack[--vm->stack_size];
}

Object* new_object(VM* vm, ObjectType type) {
  if(vm->num_objects == vm->max_objects) gc(vm);
  Object* object = malloc(sizeof(Object));
  object->type = type;
  object->marked = 0;
  object->next = vm->root;
  vm->root = object;
  vm->num_objects++;
  return object;
}

void push(VM* vm, Object *value) {
  assert(vm->stack_size < MAX_STACK);
  vm->stack[vm->stack_size++] = value;
}

void gc(VM* vm) {
  int num_objects = vm->num_objects;
  mark_all(vm);
  sweep(vm);
  vm->max_objects = vm->num_objects * 2;
  printf("Collected %d objects, %d remaining.\n", num_objects - vm->num_objects,
         vm->num_objects);
}

static void mark_all(VM *vm) {
  printf("mark all current stack size %d remaining\n", vm->stack_size);
  for(int i = 0; i < vm->stack_size; i++) {
    mark(vm->stack[i], 0);
  }
}

static void mark(Object *object, int level) {
  if(object == NULL) return;
  if(object->marked) return;
  object->marked = 1;
  printf("mark %d level = %d value = %d\n", object->type, level, object->value);
  if(object->type == OBJECT_PAIR) {
    mark(object->head, level + 1);
    mark(object->tail, level + 1);
  } else {
    mark(object->next, level + 1);
  }
}

static void sweep(VM *vm) {
  Object* o = vm->root;
  while(o) {
    if(!o->marked) {
      Object *unreached = o;
      o = unreached->next;
      free(unreached);
      vm->num_objects--;
    } else {
      o->marked = 0;
      o = o->next;
    }
  }
}
