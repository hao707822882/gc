#include "vm.h"

void assert(int condition, const char* message) {
  if (!condition) {
    printf("%s\n", message);
    exit(1);
  }
}

void pushInt(VM* vm, int value) {
  Object* o = new_object(vm, OBJECT_INT);
  o->value = value;
  push(vm, o);
}

Object* pushPair(VM* vm) {
  Object *o = new_object(vm, OBJECT_PAIR);
  o->tail = pop(vm);
  o->head = pop(vm);
  push(vm, o);
  return o;
}

void test1() {
  printf("Test 1: Objects on stack are preserved.\n");
  VM* vm = new_vm();
  pushInt(vm, 1);
  pushInt(vm, 2);

  gc(vm);
  assert(vm->num_objects == 2, "Should have preserved objects.");
  relase_vm(vm);
}

void test2() {
  printf("Test 2: Unreached objects are collected.\n");
  VM* vm = new_vm();
  pushInt(vm, 1);
  pushInt(vm, 2);
  pop(vm);
  pop(vm);

  gc(vm);
  assert(vm->num_objects == 0, "Should have collected objects.");
  relase_vm(vm);
}

void test3() {
  printf("Test 3: Reach nested objects.\n");
  VM* vm = new_vm();
  pushInt(vm, 1);
  pushInt(vm, 2);
  pushPair(vm);
  pushInt(vm, 3);
  pushInt(vm, 4);
  pushPair(vm);
  pushPair(vm);

  gc(vm);
  assert(vm->num_objects == 7, "Should have reached objects.");
  relase_vm(vm);
}

void test4() {
  printf("Test 4: Handle cycles.\n");
  VM* vm = new_vm();
  pushInt(vm, 1);
  pushInt(vm, 2);
  Object* a = pushPair(vm);
  pushInt(vm, 3);
  pushInt(vm, 4);
  Object* b = pushPair(vm);

  a->tail = b;
  b->tail = a;

  gc(vm);
  assert(vm->num_objects == 4, "Should have collected objects.");
  relase_vm(vm);
}



int main(int argc, const char * argv[]) {
    printf("begin\n");
    test1();
    test2();
    test3();
    test4();
    printf("end\n");
    return 0;
};
