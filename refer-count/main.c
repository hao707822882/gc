#include "refCount.h"
#include <stdlib.h>

void assert(int condition, const char* message) {
  if (!condition) {
    printf("    .........Failed(%s)\n", message);
    exit(1);
  }
}

void test1() {
  printf("Test1: 测试当前被引用对象的次数\n");
  unsigned *obj = new unsigned;
  unsigned *obj2 = new unsigned;
  unsigned *obj3 = new unsigned;
  unsigned *obj4 = new unsigned;
  RefCountPointer<unsigned> p(obj);
  RefCountPointer<unsigned> p2(obj2);
  RefCountPointer<unsigned> p3(obj3);
  RefCountPointer<unsigned> p4(obj4);
  p = p2;
  assert(p.GetRefCount() == 2, "被引用的次数为2");
  assert(p2.GetRefCount() == 2, "被引用的次数为2");
  p3 = p4;
  p = p3;
  assert(p3.GetRefCount() == 3, "被引用的次数为3");
  printf("    ...............Pass\n");
}

void m_stack(RefCountPointer<unsigned>&ptr) {
  unsigned *obj = new unsigned;
  RefCountPointer<unsigned> p(obj);
  p = ptr;
  assert(p.GetRefCount() == 2, "被引用的次数为2");
}

void test2() {
  printf("Test2: 测试对象被移除时引用次数\n");
  unsigned *obj = new unsigned;
  RefCountPointer<unsigned> p(obj);
  m_stack(p);
  assert(p.GetRefCount() == 1, "被引用的次数为1");
  printf("    ...............Pass\n");
}

int main() {
  test1();
  test2();
}
