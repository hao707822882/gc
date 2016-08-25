// refer https://secweb.cs.odu.edu/~zeil/cs361/web/website/Lectures/garbageCollection/page/garbageCollection.html
#include <stdio.h>

template <class T>
class RefCountPointer {
  T* p;
  unsigned* count;

  void checkIfScavengable()
  {
    if (*count == 0)
      {
        delete count;
        delete p;
      }
  }

public:
  // This constructor is used to hand control of a newly
  // allocated object (*s) over to the reference count
  // system.  Example:
  //    RefCountPointer<PersonelRecord> p (new PersonelRecord());
  // It's critical that, once you create a reference counted
  // pointer to something, that you not continue playing with
  // regular pointers to the same object.
  RefCountPointer (T* s)
    : p(s), count(new unsigned)
    {*count = 1;}

  RefCountPointer (const RefCountPointer& rcp)
    : p(rcp.p), count(rcp.count)
    {++(*count);}

  ~RefCountPointer() {
    --(*count); checkIfScavengable();
  }


  RefCountPointer& operator= (const RefCountPointer& rcp)
    {
      ++(*(rcp.count));
      --(*count);
      checkIfScavengable();
      p = rcp.p;
      count = rcp.count;
      return *this;
    }

  T& operator*() const {return *p;}
  T* operator->() const {return p;}


  bool operator== (const RefCountPointer<T>& ptr) const
  {return ptr.p == p;}


  bool operator!= (const RefCountPointer<T>& ptr) const
  {return ptr.p != p;}

  unsigned GetRefCount() const {
    return *count;
  }
};
