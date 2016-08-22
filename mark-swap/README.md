### GC-标记清除算法

```

参考代码 https://github.com/wang-long/mark-sweep-GC/blob/master/main.c

```

### 算法描述

```

1. 抽象VM对象，来管理当前堆、栈使用情况,Object 就是所谓的要分配对象

    typedef struct VM {
        Object *stack;              // 栈
        Object *root;               // 初始化根对象
        int num_objects;            // 当前使用的对象数量
        (void)push(Object *obj);    // 栈中压入一个对象
        (Object *)pop();            // 栈顶取一个object
        (VM *)new_vm();             // 分配虚拟机空间
        (void)release_vm();         // 释放VM空间
        (Object *)new_object(ObjectType); // 分配object
        (void)gc();                 // 进行垃圾回收
        (void)mark_all();           // 进行标记
        (void)sweep();              // 进行回收
    };

2. 算法过程

    标记-清除算法是分两个阶段进行的
    
    1. 标记阶段: 对stack中的对象进行遍历(bfs/dfs均可以，如果能够遍历到，那么说明该对象仍然是可用的，不能遍历到的话就是垃圾了
   
    2. 清除阶段: 清除阶段就是把标记阶段不活跃的对象所占用的空间释放掉

```