# C++ 客户端/后端大厂开发面试题 Q&A

> 本文档包含 128 道精选面试题，涵盖 C++ 开发核心知识点

---

## 一、C++ 基础 (30题)

### Q1: C++11 引入了哪些重要特性？

**A:** C++11 主要特性包括：
- **自动类型推导**: `auto` 和 `decltype`
- **右值引用与移动语义**: `&&`、`std::move`、移动构造/赋值
- **智能指针**: `unique_ptr`、`shared_ptr`、`weak_ptr`
- **Lambda 表达式**: `[capture](params) -> ret { body }`
- **范围 for 循环**: `for (auto& x : container)`
- **nullptr**: 替代 NULL
- **constexpr**: 编译期常量表达式
- **统一初始化**: `{}`
- **委托构造函数和继承构造函数**
- **线程库**: `<thread>`、`<mutex>`、`<atomic>`

**口述回答:**
"C++11 是一个非常重要的版本，引入了很多现代 C++ 的核心特性。首先是自动类型推导，auto 和 decltype 让代码更简洁。其次是右值引用和移动语义，通过 std::move 可以避免不必要的拷贝，提升性能。第三是智能指针，unique_ptr、shared_ptr 和 weak_ptr 帮助我们自动管理内存。还有 Lambda 表达式，让函数式编程更方便。另外还引入了范围 for 循环、nullptr、constexpr 编译期常量、统一初始化语法，以及线程库 thread、mutex、atomic 等。这些特性共同构成了现代 C++ 的基础。"

---

### Q2: 左值和右值的区别是什么？什么是右值引用？

**A:**
- **左值 (lvalue)**: 有持久地址、可取地址的表达式，如变量名
- **右值 (rvalue)**: 临时对象、字面量，没有持久地址

**右值引用 (`&&`)** 用于绑定右值，实现移动语义：

```cpp
int a = 10;        // a 是左值，10 是右值
int& lr = a;       // 左值引用
int&& rr = 10;     // 右值引用
int&& rr2 = std::move(a);  // std::move 将左值转为右值
```

**移动语义的好处**：避免不必要的深拷贝，提升性能。

**口述回答:**
"左值是有持久地址、可以取地址的表达式，比如变量名；右值是临时对象或字面量，没有持久地址。右值引用用双与号表示，它可以绑定到右值上。右值引用最大的作用是实现移动语义，当我们把一个临时对象赋值给另一个对象时，可以直接'窃取'临时对象的资源，而不需要深拷贝。比如 std::string s2 = std::move(s1)，这里 s2 直接接管了 s1 的内存，s1 变成空状态，避免了内存拷贝，大大提升了性能。"

---

### Q3: std::move 的作用是什么？它会移动数据吗？

**A:**
`std::move` **不会移动任何数据**，它只是将左值无条件转换为右值引用（类型转换）。

```cpp
template <typename T>
typename remove_reference<T>::type&& move(T&& arg) {
    return static_cast<typename remove_reference<T>::type&&>(arg);
}
```

真正的移动发生在**移动构造函数或移动赋值运算符**中：

```cpp
std::string s1 = "hello";
std::string s2 = std::move(s1);  // 调用移动构造，s1 变为有效但未定义状态
```

**口述回答:**
"这是一个很重要的概念。std::move 本身不会移动任何数据，它只是一个类型转换，把左值无条件转换成右值引用。真正的移动操作发生在移动构造函数或移动赋值运算符里。比如当我们写 std::move(s1) 时，它只是告诉编译器'可以把 s1 当作右值来处理'，然后如果接收方有移动构造函数，就会调用移动构造函数来真正转移资源。所以 move 的名字有点误导性，它更应该叫 rvalue_cast。使用 move 后，原对象处于有效但未定义的状态，通常只应该对它进行赋值或销毁操作。"

---

### Q4: 完美转发是什么？如何实现？

**A:** 完美转发保持参数的左右值属性传递给另一个函数。

使用 `std::forward` 实现：

```cpp
template<typename T>
void wrapper(T&& arg) {
    // 完美转发：保持 arg 的左/右值属性
    target(std::forward<T>(arg));
}
```

**引用折叠规则**：
- `T& &` → `T&`
- `T& &&` → `T&`
- `T&& &` → `T&`
- `T&& &&` → `T&&`

**口述回答:**
"完美转发是指在转发参数时，保持参数原有的左值或右值属性。这在编写泛型代码，特别是包装函数时非常有用。实现完美转发需要用到万能引用 T&& 配合 std::forward。万能引用可以同时接受左值和右值，而 std::forward 会根据原始参数的类型来决定是否转换成右值。这背后依赖的是引用折叠规则：左值引用加任何引用都是左值引用，只有右值引用加右值引用才是右值引用。典型应用场景是 emplace_back 这类函数，它需要把参数原封不动地转发给构造函数。"

---

### Q5: 智能指针有哪些？各自的使用场景？

**A:**

| 智能指针 | 特点 | 使用场景 |
|---------|------|---------|
| `unique_ptr` | 独占所有权，不可复制，可移动 | 单一所有者，工厂函数返回值 |
| `shared_ptr` | 共享所有权，引用计数 | 多个对象共享资源 |
| `weak_ptr` | 弱引用，不增加引用计数 | 打破循环引用，观察者模式 |

```cpp
// unique_ptr
auto up = std::make_unique<int>(42);

// shared_ptr
auto sp1 = std::make_shared<int>(42);
auto sp2 = sp1;  // 引用计数 = 2

// weak_ptr 打破循环引用
struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;  // 用 weak_ptr 避免循环
};
```

**口述回答:**
"C++11 提供了三种智能指针。unique_ptr 是独占所有权的智能指针，不能复制只能移动，适合用在明确只有一个所有者的场景，比如工厂函数返回值。shared_ptr 是共享所有权的智能指针，内部有引用计数，当最后一个 shared_ptr 销毁时才释放资源，适合多个对象需要共享同一资源的场景。weak_ptr 是弱引用，不增加引用计数，主要用来打破循环引用。比如双向链表中，如果 next 和 prev 都用 shared_ptr，就会循环引用导致内存泄漏，把其中一个改成 weak_ptr 就能解决。使用时推荐用 make_unique 和 make_shared 来创建，效率更高也更安全。"

---

### Q6: shared_ptr 的实现原理？线程安全性如何？

**A:**

**实现原理**：
- 包含两个指针：一个指向对象，一个指向控制块
- 控制块包含：强引用计数、弱引用计数、删除器、分配器

```cpp
// 简化结构
class shared_ptr<T> {
    T* ptr;                    // 指向管理的对象
    ControlBlock* control;     // 控制块
};

struct ControlBlock {
    std::atomic<int> strong_count;
    std::atomic<int> weak_count;
    Deleter deleter;
};
```

**线程安全性**：
- 引用计数操作是**原子的**（线程安全）
- 指向同一对象的不同 shared_ptr 可以在不同线程操作
- **但**：同一个 shared_ptr 实例被多线程读写需要额外同步

**口述回答:**
"shared_ptr 内部包含两个指针：一个指向管理的对象，一个指向控制块。控制块里存储着强引用计数、弱引用计数、删除器等信息。当 shared_ptr 拷贝时，强引用计数加一；析构时减一，减到零就释放对象。关于线程安全性，引用计数的操作本身是原子的，所以多个线程可以安全地拷贝和销毁指向同一对象的不同 shared_ptr 实例。但要注意，如果多个线程同时读写同一个 shared_ptr 变量，比如一个线程在 reset 另一个线程在拷贝，这是不安全的，需要额外加锁。另外，被管理的对象本身也不是线程安全的，访问对象内容还是需要自己同步。"

---

### Q7: 什么是循环引用？如何解决？

**A:** 两个或多个 shared_ptr 相互引用，导致引用计数永远不为 0，内存泄漏。

```cpp
struct A {
    std::shared_ptr<B> b_ptr;
};
struct B {
    std::shared_ptr<A> a_ptr;  // 循环引用！
};

auto a = std::make_shared<A>();
auto b = std::make_shared<B>();
a->b_ptr = b;
b->a_ptr = a;  // 引用计数都是 2，析构后仍为 1，泄漏
```

**解决方案**：将其中一个改为 `weak_ptr`：

```cpp
struct B {
    std::weak_ptr<A> a_ptr;  // 不增加引用计数
};
```

**口述回答:**
"循环引用是指两个或多个对象通过 shared_ptr 相互引用，形成一个闭环。比如 A 持有指向 B 的 shared_ptr，B 又持有指向 A 的 shared_ptr。这样即使外部没有任何指针指向它们，它们的引用计数也不会变成零，因为彼此互相引用，就造成了内存泄漏。解决方法是把其中一个方向的 shared_ptr 改成 weak_ptr。weak_ptr 不增加引用计数，它只是观察对象是否存在。使用前需要通过 lock() 方法转换成 shared_ptr，如果对象已经被释放，lock() 会返回空指针。这在观察者模式、父子关系等场景中很常用。"

---

### Q8: new/delete 与 malloc/free 的区别？

**A:**

| 特性 | new/delete | malloc/free |
|-----|-----------|-------------|
| 类型 | C++ 运算符 | C 库函数 |
| 返回值 | 具体类型指针 | void* |
| 大小计算 | 自动 | 手动指定 |
| 构造/析构 | 调用 | 不调用 |
| 失败处理 | 抛异常 | 返回 NULL |
| 可重载 | 是 | 否 |

```cpp
// new = malloc + 构造函数调用
MyClass* p = new MyClass();

// delete = 析构函数调用 + free
delete p;

// placement new：在已有内存上构造
char buffer[sizeof(MyClass)];
MyClass* p2 = new (buffer) MyClass();
p2->~MyClass();  // 手动析构
```

**口述回答:**
"new 和 delete 是 C++ 的运算符，malloc 和 free 是 C 的库函数，它们有几个重要区别。首先，new 会自动计算对象大小并调用构造函数，delete 会调用析构函数再释放内存，而 malloc/free 只负责分配和释放原始内存。其次，new 失败时抛出异常，malloc 返回 NULL。第三，new 返回具体类型指针，malloc 返回 void* 需要转换。第四，new/delete 可以被重载，malloc/free 不行。还有一个 placement new，它不分配内存，只在已有的内存上调用构造函数，常用于内存池等场景，用完后需要手动调用析构函数。在 C++ 中推荐使用 new/delete 或者更好的智能指针。"

---

### Q9: 虚函数的实现原理？

**A:**
通过**虚函数表 (vtable)** 和**虚表指针 (vptr)** 实现：

1. 每个有虚函数的类有一个 vtable，存放虚函数指针
2. 每个对象有一个 vptr，指向其类的 vtable
3. 调用虚函数时，通过 vptr 找到 vtable，再找到函数地址

```cpp
class Base {
    virtual void foo();  // vtable[0] = &Base::foo
    virtual void bar();  // vtable[1] = &Base::bar
};

class Derived : public Base {
    void foo() override;  // vtable[0] = &Derived::foo
    // bar 继承自 Base
};

// 调用过程
Base* p = new Derived();
p->foo();  // p->vptr->vtable[0]() → Derived::foo
```

**内存布局**：vptr 通常在对象起始位置。

**口述回答:**
"虚函数的实现依赖于虚函数表和虚表指针。编译器会为每个有虚函数的类创建一个虚函数表 vtable，里面按顺序存放虚函数的地址。每个对象内部会有一个虚表指针 vptr，指向它所属类的 vtable。当通过基类指针调用虚函数时，程序会先通过 vptr 找到 vtable，再从 vtable 中取出对应位置的函数指针来调用。派生类如果重写了虚函数，它的 vtable 对应位置就会换成新函数的地址。这就是多态的实现原理。vptr 通常放在对象内存的开头位置，所以有虚函数的对象会比没有的多占一个指针大小的空间。"

---

### Q10: 虚析构函数的作用？什么时候需要？

**A:**
确保通过基类指针删除派生类对象时，正确调用派生类析构函数。

```cpp
class Base {
public:
    ~Base() { cout << "~Base\n"; }  // 非虚析构
};

class Derived : public Base {
public:
    ~Derived() { cout << "~Derived\n"; }
};

Base* p = new Derived();
delete p;  // 只调用 ~Base，Derived 部分泄漏！
```

**规则**：
- 类有虚函数 → 析构函数应为虚函数
- 类作为基类且可能被多态删除 → 虚析构函数
- 不打算继承的类 → 可以用 `final` 防止继承

**口述回答:**
"虚析构函数是为了保证通过基类指针删除派生类对象时，能正确调用派生类的析构函数。如果基类析构函数不是虚函数，通过基类指针 delete 时只会调用基类的析构函数，派生类部分不会被析构，可能造成资源泄漏。一个简单的规则是：只要类中有虚函数，就应该把析构函数声明为虚函数。或者说，如果一个类打算作为多态基类使用，析构函数必须是虚的。如果确定类不会被继承，可以用 final 关键字标记，这样编译器也能做一些优化。"

---

### Q11: 纯虚函数和抽象类？

**A:**
- **纯虚函数**：`virtual void func() = 0;`
- **抽象类**：包含纯虚函数的类，不能实例化

```cpp
class Shape {  // 抽象类
public:
    virtual double area() const = 0;  // 纯虚函数
    virtual ~Shape() = default;
};

class Circle : public Shape {
    double radius;
public:
    double area() const override { return 3.14159 * radius * radius; }
};

// Shape s;  // 错误：不能实例化抽象类
Circle c;    // OK
```

**用途**：定义接口，强制派生类实现特定方法。

**口述回答:**
"纯虚函数是在虚函数声明后面加 = 0，表示这个函数没有实现，必须由派生类来实现。包含纯虚函数的类叫抽象类，不能直接实例化，只能作为基类被继承。抽象类的作用是定义接口规范，强制派生类必须实现某些方法。比如定义一个 Shape 抽象类，里面有纯虚函数 area()，那么 Circle、Rectangle 这些派生类都必须实现自己的 area() 方法。如果派生类没有实现所有纯虚函数，它自己也变成抽象类。这是面向接口编程的重要手段。"

---

### Q12: 多重继承的菱形继承问题及解决方案？

**A:**
菱形继承导致基类被重复继承：

```cpp
class A { public: int data; };
class B : public A {};
class C : public A {};
class D : public B, public C {};  // D 有两份 A::data

D d;
d.data;  // 歧义：B::data 还是 C::data？
```

**解决方案 - 虚继承**：

```cpp
class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};  // D 只有一份 A::data

D d;
d.data;  // OK，只有一份
```

虚继承通过虚基类表 (vbtable) 实现，有一定性能开销。

**口述回答:**
"菱形继承问题是多重继承中的一个经典问题。比如 B 和 C 都继承自 A，D 又同时继承 B 和 C，这样 D 中就会有两份 A 的数据成员，访问时会产生歧义。解决方案是使用虚继承，在 B 和 C 继承 A 时加上 virtual 关键字。这样 D 中就只会有一份 A 的数据，不会有歧义。虚继承的实现原理是通过虚基类表来记录虚基类的偏移量，会有一定的空间和性能开销。实际开发中应该尽量避免菱形继承，它会让类层次变得复杂，可以考虑用组合代替继承来解决。"

---

### Q13: RAII 是什么？有什么优点？

**A:**
**Resource Acquisition Is Initialization** - 资源获取即初始化

核心思想：将资源绑定到对象生命周期，构造时获取，析构时释放。

```cpp
class FileHandle {
    FILE* fp;
public:
    FileHandle(const char* path) : fp(fopen(path, "r")) {
        if (!fp) throw std::runtime_error("Cannot open file");
    }
    ~FileHandle() { if (fp) fclose(fp); }

    // 禁止拷贝
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
};

void process() {
    FileHandle fh("data.txt");  // 获取资源
    // 使用文件...
}  // 自动关闭，即使异常也能正确释放
```

**优点**：
- 异常安全
- 无需手动释放
- 代码更简洁

标准库例子：智能指针、`lock_guard`、`fstream`

**口述回答:**
"RAII 是 Resource Acquisition Is Initialization 的缩写，中文叫资源获取即初始化。核心思想是把资源的生命周期和对象的生命周期绑定：在构造函数中获取资源，在析构函数中释放资源。这样做有几个好处：首先是异常安全，即使函数中途抛出异常，局部对象的析构函数也会被调用，资源不会泄漏。其次是不需要手动释放，减少忘记释放的风险。代码也更简洁清晰。标准库中大量使用这个模式，比如智能指针自动管理内存，lock_guard 自动管理互斥锁，fstream 自动关闭文件。RAII 是 C++ 最重要的编程范式之一。"

---

### Q14: const 的各种用法？

**A:**

```cpp
// 1. 常量变量
const int MAX = 100;

// 2. 指针与 const
const int* p1;      // 指向常量的指针，*p1 不可改
int* const p2;      // 常量指针，p2 不可改
const int* const p3; // 都不可改

// 3. const 成员函数 - 不修改对象状态
class MyClass {
    int value;
public:
    int getValue() const { return value; }  // const 成员函数
    void setValue(int v) { value = v; }
};

// 4. const 引用参数 - 避免拷贝，防止修改
void process(const std::string& s);

// 5. const 返回值
const std::string& getName() const;

// 6. mutable - const 函数中可修改的成员
class Cache {
    mutable int accessCount = 0;  // 可在 const 函数中修改
public:
    int get() const { ++accessCount; return data; }
};
```

**口述回答:**
"const 在 C++ 中用途很广。首先用于定义常量变量，值不可修改。在指针中有两种用法：const int* 表示指向常量的指针，指向的内容不可改；int* const 表示常量指针，指针本身不可改。const 成员函数表示这个函数不会修改对象状态，const 对象只能调用 const 成员函数。函数参数用 const 引用可以避免拷贝同时防止被修改，这在传递大对象时很常用。还有 mutable 关键字，用于标记在 const 函数中也可以修改的成员，比如缓存计数器这种不影响对象逻辑状态的成员。const 正确性是写出高质量 C++ 代码的重要原则。"

---

### Q15: static 关键字的用法？

**A:**

```cpp
// 1. 静态局部变量 - 只初始化一次，程序结束时销毁
void func() {
    static int count = 0;  // 第一次调用时初始化
    ++count;
}

// 2. 静态成员变量 - 类所有对象共享
class Counter {
    static int total;  // 声明
public:
    Counter() { ++total; }
};
int Counter::total = 0;  // 定义（类外）

// 3. 静态成员函数 - 无 this 指针，只能访问静态成员
class Math {
public:
    static int add(int a, int b) { return a + b; }
};
Math::add(1, 2);  // 无需对象

// 4. 静态全局变量/函数 - 内部链接，仅当前文件可见
static int internalVar;
static void internalFunc() {}
```

**口述回答:**
"static 关键字在不同位置有不同含义。在函数内部定义静态局部变量，这个变量只初始化一次，生命周期持续到程序结束，常用于实现单例或缓存。在类中定义静态成员变量，表示这个变量属于类而不是对象，所有对象共享一份，需要在类外单独定义。静态成员函数没有 this 指针，只能访问静态成员，可以通过类名直接调用。在全局作用域用 static 修饰变量或函数，表示内部链接，只在当前编译单元可见，可以避免命名冲突。这几种用法虽然都用 static，但含义完全不同。"

---

### Q16: inline 函数的作用和注意事项？

**A:**
建议编译器将函数体展开到调用处，避免函数调用开销。

```cpp
inline int square(int x) { return x * x; }

// C++17 inline 变量
inline int globalVar = 42;  // 可在头文件定义
```

**注意事项**：
- `inline` 只是建议，编译器可能忽略
- 类内定义的函数默认 inline
- 过度内联会增加代码体积
- 递归函数通常不会被内联
- 虚函数通过指针调用时不会内联

**C++17 inline 变量**：解决头文件中定义全局变量的多重定义问题。

**口述回答:**
"inline 函数是建议编译器将函数体直接展开到调用处，避免函数调用的开销，比如压栈、跳转、返回等。但 inline 只是建议，编译器可以忽略，复杂的函数或递归函数通常不会被内联。类内定义的成员函数默认就是 inline 的。需要注意的是，过度内联会导致代码膨胀，反而降低性能。虚函数通过指针调用时不会内联，因为调用目标要到运行时才能确定。C++17 引入了 inline 变量，允许在头文件中定义全局变量而不会导致多重定义错误，每个编译单元看到的是同一个变量。"

---

### Q17: constexpr 与 const 的区别？

**A:**

| 特性 | const | constexpr |
|-----|-------|-----------|
| 求值时机 | 可运行时 | 必须编译时 |
| 适用范围 | 变量、函数参数 | 变量、函数、类 |
| C++ 版本 | C++98 | C++11+ |

```cpp
const int a = 10;           // 编译时常量
const int b = getValue();   // 运行时常量，OK

constexpr int c = 10;       // 编译时常量
// constexpr int d = getValue();  // 错误：必须编译时可计算

// constexpr 函数
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}
constexpr int f5 = factorial(5);  // 编译时计算 = 120
int runtime_val = 5;
int f_runtime = factorial(runtime_val);  // 运行时计算
```

**口述回答:**
"const 和 constexpr 都表示常量，但有重要区别。const 变量可以在编译期初始化，也可以在运行时初始化，比如 const int x = getValue() 是合法的。而 constexpr 变量必须在编译期就能确定值，如果初始值不能在编译期计算，就会报错。constexpr 函数在参数是编译期常量时会在编译期计算结果，参数是运行时值时则在运行时计算。constexpr 的好处是可以把计算提前到编译期，提高运行时性能，还可以用于数组大小、模板参数等需要编译期常量的地方。C++14 放宽了 constexpr 函数的限制，C++17 又引入了 if constexpr 实现编译期条件分支。"

---

### Q18: Lambda 表达式的语法和捕获方式？

**A:**

```cpp
// 完整语法
[capture](params) mutable noexcept -> return_type { body }

// 捕获方式
[a]      // 值捕获 a
[&a]     // 引用捕获 a
[=]      // 值捕获所有外部变量
[&]      // 引用捕获所有
[=, &a]  // 默认值捕获，a 引用捕获
[&, a]   // 默认引用捕获，a 值捕获
[this]   // 捕获 this 指针
[*this]  // C++17，值捕获当前对象副本

// 示例
int x = 10, y = 20;
auto add = [x, &y](int z) -> int {
    y += x;  // 可修改 y（引用）
    return x + y + z;
};

// mutable 允许修改值捕获的变量副本
auto counter = [n = 0]() mutable { return ++n; };
```

**口述回答:**
"Lambda 表达式是 C++11 引入的匿名函数，语法是方括号捕获列表、圆括号参数、可选的返回类型、花括号函数体。捕获列表决定 Lambda 如何访问外部变量：值捕获会复制变量，引用捕获则直接引用原变量。可以用 = 默认值捕获所有变量，用 & 默认引用捕获所有变量，也可以混合使用。值捕获的变量默认是 const 的，加 mutable 关键字才能修改。C++14 支持泛型 Lambda，参数可以用 auto。C++17 支持 *this 值捕获当前对象的副本。Lambda 本质上是编译器生成的一个匿名类，捕获的变量是这个类的成员。Lambda 很适合用于 STL 算法、回调函数等场景。"

---

### Q19: 模板的基本用法？

**A:**

```cpp
// 函数模板
template<typename T>
T max(T a, T b) {
    return a > b ? a : b;
}
max(1, 2);        // T = int
max<double>(1, 2); // 显式指定

// 类模板
template<typename T, int N>
class Array {
    T data[N];
public:
    T& operator[](int i) { return data[i]; }
    constexpr int size() const { return N; }
};
Array<int, 10> arr;

// 模板特化
template<>
class Array<bool, 8> {  // 完全特化
    uint8_t data;
};

// 偏特化
template<typename T>
class Array<T*, 10> {  // 指针类型特化
    // ...
};
```

**口述回答:**
"模板是 C++ 泛型编程的基础。函数模板可以让一个函数处理不同类型的参数，编译器会根据调用时的实参类型自动实例化对应版本。类模板同样可以用类型或非类型参数来参数化一个类。模板支持特化，完全特化是为某个具体类型提供专门实现，偏特化是为一类类型提供实现，比如所有指针类型。模板的实例化发生在编译期，所以模板代码通常要放在头文件中。模板也可以有默认参数，和函数默认参数类似。现代 C++ 大量使用模板，STL 就是模板库的典型代表。"

---

### Q20: SFINAE 是什么？

**A:**
**Substitution Failure Is Not An Error** - 替换失败不是错误

模板参数替换失败时，不报错，而是从重载集中移除该模板。

```cpp
// 只对有 size() 成员的类型启用
template<typename T>
auto getSize(const T& c) -> decltype(c.size()) {
    return c.size();
}

// C++11 enable_if
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
process(T value) {
    return value * 2;
}

// C++17 if constexpr 更简洁
template<typename T>
auto process(T value) {
    if constexpr (std::is_integral_v<T>) {
        return value * 2;
    } else {
        return value;
    }
}

// C++20 concepts 更直观
template<typename T>
concept Integral = std::is_integral_v<T>;

template<Integral T>
T process(T value) { return value * 2; }
```

**口述回答:**
"SFINAE 是 Substitution Failure Is Not An Error 的缩写，意思是替换失败不是错误。在模板参数推导时，如果某个模板的参数替换导致非法的类型或表达式，编译器不会报错，而是把这个模板从候选集中移除，继续尝试其他重载。这个特性可以用来实现编译期的类型检查和条件编译。比如用 enable_if 可以根据类型特征启用或禁用某个函数模板。C++17 的 if constexpr 让这类代码更容易写，C++20 的 concepts 则提供了更直观的语法来约束模板参数。SFINAE 是现代 C++ 模板编程的重要技术。"

---

### Q21: 什么是模板元编程？

**A:**
在编译期通过模板进行计算的技术。

```cpp
// 编译期计算阶乘
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

constexpr int f5 = Factorial<5>::value;  // 120，编译期计算

// 类型计算
template<typename T>
struct RemovePointer {
    using type = T;
};

template<typename T>
struct RemovePointer<T*> {
    using type = T;
};

RemovePointer<int*>::type x;  // x 是 int 类型
```

**用途**：类型萃取、编译期断言、优化。

**口述回答:**
"模板元编程是利用模板在编译期进行计算的技术。因为模板实例化发生在编译期，我们可以通过模板递归来实现编译期计算。比如经典的编译期阶乘，通过模板特化作为递归终止条件。除了数值计算，更常用的是类型计算，比如 type_traits 库中的各种类型萃取。模板元编程的优点是把计算提前到编译期，运行时零开销。缺点是代码可读性差、编译时间长、错误信息难懂。现代 C++ 提供了 constexpr 函数来替代数值计算，用 concepts 来简化类型约束，但在某些复杂场景下模板元编程仍然是必要的。"

---

### Q22: C++ 内存分区？

**A:**

| 区域 | 内容 | 生命周期 |
|-----|------|---------|
| 代码区 | 程序代码 | 程序运行期间 |
| 全局/静态区 | 全局变量、static 变量 | 程序运行期间 |
| 常量区 | 字符串字面量、const 全局 | 程序运行期间 |
| 栈区 | 局部变量、函数参数 | 函数调用期间 |
| 堆区 | new/malloc 分配 | 手动管理 |

```cpp
int global = 1;              // 全局区
static int static_var = 2;   // 全局区
const char* str = "hello";   // str 在栈，"hello" 在常量区

void func() {
    int local = 3;           // 栈
    int* p = new int(4);     // p 在栈，*p 在堆
    static int s = 5;        // 全局区
}
```

**口述回答:**
"C++ 程序的内存主要分为几个区域。代码区存放编译后的机器指令，是只读的。全局/静态区存放全局变量和 static 变量，生命周期从程序启动到结束。常量区存放字符串字面量等常量数据。栈区存放函数的局部变量、参数和返回地址，由系统自动管理，函数结束自动释放。堆区存放 new 或 malloc 动态分配的内存，需要程序员手动管理或用智能指针管理。理解内存分区有助于我们理解变量的生命周期、避免内存问题、优化程序性能。"

---

### Q23: 堆和栈的区别？

**A:**

| 特性 | 栈 | 堆 |
|-----|-----|-----|
| 管理方式 | 系统自动 | 程序员手动 |
| 分配速度 | 快（移动指针） | 慢（查找空闲块） |
| 大小 | 较小（通常 1-8MB） | 较大（受限于虚拟内存） |
| 碎片 | 无 | 可能产生碎片 |
| 生长方向 | 高→低 | 低→高 |
| 使用场景 | 局部变量、函数调用 | 动态分配、大对象 |

```cpp
void example() {
    int stack_arr[100];      // 栈，快速，自动释放
    int* heap_arr = new int[100];  // 堆，需手动 delete[]
}
```

**口述回答:**
"堆和栈是两种不同的内存区域，有很大差异。栈是系统自动管理的，分配释放速度非常快，只需移动栈指针，空间比较小，一般是几 MB。堆是程序员手动管理的，分配需要查找合适的空闲块，比较慢，空间很大，受限于虚拟内存。栈上的数据在函数结束自动释放，堆上的必须手动释放或用智能指针。栈空间连续、没有碎片，堆可能有内存碎片。栈从高地址向低地址生长，堆从低地址向高地址生长。一般来说，小对象、生命周期短的用栈，大对象、生命周期长的用堆。"

---

### Q24: 内存对齐是什么？为什么需要？

**A:**
数据在内存中按特定边界存放。

```cpp
struct A {
    char a;   // 1 byte
    int b;    // 4 bytes
    char c;   // 1 byte
};  // sizeof(A) = 12（不是 6）

// 内存布局：
// a _ _ _ b b b b c _ _ _
// 对齐填充使 b 在 4 字节边界

// 调整顺序优化
struct B {
    int b;    // 4 bytes
    char a;   // 1 byte
    char c;   // 1 byte
};  // sizeof(B) = 8

// 指定对齐
#pragma pack(push, 1)
struct C {
    char a;
    int b;
    char c;
};  // sizeof(C) = 6，紧凑但可能性能下降
#pragma pack(pop)

// C++11 alignas
struct alignas(16) D {
    float data[4];
};  // 16 字节对齐，适合 SIMD
```

**原因**：CPU 访问对齐数据更高效，某些架构要求对齐。

**口述回答:**
"内存对齐是指数据在内存中要放在特定边界上。比如 int 通常要放在 4 字节边界，double 要放在 8 字节边界。结构体中的成员按照各自的对齐要求排列，可能会产生填充字节。比如一个结构体里先是 char 再是 int，char 后面会填充 3 个字节让 int 对齐到 4 字节边界。为什么需要对齐呢？一是性能，CPU 访问对齐的数据更快，可能一次就能读完；二是某些 CPU 架构强制要求对齐，不对齐会报错。我们可以通过调整成员顺序来减少填充、节省空间，也可以用 pragma pack 或 alignas 来控制对齐。SIMD 指令通常要求 16 字节对齐。"

---

### Q25: 如何检测内存泄漏？

**A:**

**工具**：
- **Valgrind** (Linux): `valgrind --leak-check=full ./program`
- **AddressSanitizer**: `-fsanitize=address`
- **Visual Studio CRT**: `_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF)`

```cpp
// Visual Studio 调试
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    int* leak = new int(42);  // 泄漏
    // 程序结束时会报告泄漏
}

// RAII 最佳实践
void safe() {
    auto p = std::make_unique<int>(42);  // 自动释放
}
```

**口述回答:**
"检测内存泄漏有几种常用方法。在 Linux 上最常用的是 Valgrind，运行 valgrind --leak-check=full 加程序名，它会报告所有泄漏的位置和大小。另一个好工具是 AddressSanitizer，编译时加 -fsanitize=address 参数，运行时会检测泄漏、越界等内存错误。Windows 上可以用 Visual Studio 的 CRT 调试功能，在程序开始设置调试标志，结束时会报告未释放的内存。但最好的做法是预防泄漏：使用智能指针管理动态内存，用 RAII 管理其他资源。养成好的编程习惯比事后检测更重要。"

---

### Q26: 深拷贝和浅拷贝？

**A:**
- **浅拷贝**：只复制指针值，两个对象指向同一内存
- **深拷贝**：复制指针指向的内容，各自独立

```cpp
class ShallowCopy {
    int* data;
public:
    ShallowCopy(int v) : data(new int(v)) {}
    // 默认拷贝构造：浅拷贝
    ~ShallowCopy() { delete data; }  // 双重释放！
};

class DeepCopy {
    int* data;
public:
    DeepCopy(int v) : data(new int(v)) {}
    DeepCopy(const DeepCopy& other) : data(new int(*other.data)) {}  // 深拷贝
    DeepCopy& operator=(const DeepCopy& other) {
        if (this != &other) {
            delete data;
            data = new int(*other.data);
        }
        return *this;
    }
    ~DeepCopy() { delete data; }
};
```

**Rule of Three/Five**：定义了析构函数，通常也需要定义拷贝/移动操作。

**口述回答:**
"浅拷贝和深拷贝的区别在于如何处理指针成员。浅拷贝只复制指针的值，两个对象的指针指向同一块内存，这会导致问题：一个对象修改会影响另一个，析构时会重复释放。深拷贝则是复制指针指向的内容，为新对象分配独立的内存，两个对象完全独立。默认的拷贝构造函数和赋值运算符是浅拷贝。如果类有原始指针成员需要管理内存，就必须自己实现深拷贝。这就引出了三法则：如果需要自定义析构函数，通常也需要自定义拷贝构造和拷贝赋值。C++11 扩展成五法则，还包括移动构造和移动赋值。当然，用智能指针就能避免很多这类问题。"

---

### Q27: 异常处理机制？

**A:**

```cpp
// 抛出异常
void divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero");
    }
    return a / b;
}

// 捕获异常
try {
    divide(10, 0);
} catch (const std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << '\n';
} catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << '\n';
} catch (...) {
    std::cerr << "Unknown exception\n";
}

// noexcept 声明
void safe_func() noexcept {
    // 保证不抛异常，若抛出则 std::terminate
}

// C++11 异常规范
void func() noexcept(true);   // 不抛异常
void func() noexcept(false);  // 可能抛异常
```

**最佳实践**：
- 用 RAII 确保异常安全
- catch 异常时用 const 引用
- 析构函数不应抛异常

**口述回答:**
"C++ 的异常处理用 try-catch-throw 三个关键字。throw 用来抛出异常，可以抛出任何类型但通常抛出 std::exception 的派生类。try 块包围可能抛异常的代码，catch 块捕获并处理异常，可以有多个 catch 块处理不同类型。catch(...) 可以捕获所有异常。异常会沿调用栈向上传播，直到被捕获或者程序终止。noexcept 关键字声明函数不会抛异常，如果违反会直接 terminate。使用异常时要注意异常安全，保证异常发生时资源不泄漏、对象状态一致，RAII 是实现异常安全的关键。析构函数绝对不要抛异常，因为在栈展开过程中如果析构又抛异常，程序会直接终止。"

---

### Q28: 类型转换运算符的区别？

**A:**

| 运算符 | 用途 | 安全性 |
|-------|------|--------|
| `static_cast` | 明确类型转换 | 编译时检查 |
| `dynamic_cast` | 多态类型转换 | 运行时检查 |
| `const_cast` | 移除/添加 const | 危险 |
| `reinterpret_cast` | 位模式转换 | 非常危险 |

```cpp
// static_cast - 常规转换
double d = 3.14;
int i = static_cast<int>(d);

// dynamic_cast - 安全向下转型
Base* bp = new Derived();
Derived* dp = dynamic_cast<Derived*>(bp);  // 成功
if (dp) { /* 使用 dp */ }

// const_cast - 移除 const
const int* cp = &i;
int* p = const_cast<int*>(cp);

// reinterpret_cast - 底层转换
int* ip = &i;
uintptr_t addr = reinterpret_cast<uintptr_t>(ip);
```

**口述回答:**
"C++ 提供了四种具名类型转换，比 C 风格转换更安全明确。static_cast 用于常规类型转换，比如数值类型之间、向上转型，编译器会做类型检查。dynamic_cast 用于多态类型的安全向下转型，会在运行时检查，失败返回 nullptr 或抛异常。const_cast 专门用于添加或移除 const 属性，其他转换做不到这点，但修改原本是 const 的对象是未定义行为。reinterpret_cast 是最危险的，直接重新解释比特位，用于底层操作比如指针和整数互转。应该优先用 static_cast，必要时用 dynamic_cast，尽量避免 const_cast 和 reinterpret_cast。"

---

### Q29: 什么是 ODR？如何避免违反？

**A:**
**One Definition Rule** - 单一定义规则

- 变量、函数、类等在整个程序中只能有一个定义
- 内联函数、模板可以在多个翻译单元中定义，但必须完全相同

```cpp
// 违反 ODR
// file1.cpp
int global = 1;
// file2.cpp
int global = 2;  // 链接错误

// 正确做法
// header.h
extern int global;  // 声明
inline int getVal() { return 42; }  // inline 可多处定义

// file1.cpp
int global = 1;  // 定义一次
```

**避免方法**：
- 使用 header guard 或 `#pragma once`
- 全局变量用 `extern` 声明
- 用 `inline` 或放在匿名命名空间

**口述回答:**
"ODR 是 One Definition Rule，单一定义规则。它要求每个变量、函数、类在整个程序中只能有一个定义。内联函数和模板是例外，可以在多个编译单元中定义，但定义必须完全相同。违反 ODR 会导致链接错误或者更糟的未定义行为。常见错误是在头文件中定义全局变量，被多个源文件包含就会多重定义。避免方法：头文件用 include guard 防止重复包含，全局变量在头文件中用 extern 声明、在一个源文件中定义，函数和变量放在匿名命名空间限制作用域，或者用 C++17 的 inline 变量。"

---

### Q30: C++17/20 有哪些重要新特性？

**A:**

**C++17**：
- `std::optional`：可选值
- `std::variant`：类型安全联合
- `std::string_view`：非拥有字符串视图
- 结构化绑定：`auto [x, y] = pair;`
- `if constexpr`：编译期条件
- 折叠表达式
- `inline` 变量

**C++20**：
- Concepts：模板约束
- Ranges：范围库
- Coroutines：协程
- `std::span`：连续内存视图
- 三路比较 `<=>`
- Modules：模块系统
- `std::format`：格式化库

```cpp
// C++17 结构化绑定
std::map<int, std::string> m;
for (auto& [key, value] : m) { }

// C++20 concepts
template<std::integral T>
T add(T a, T b) { return a + b; }

// C++20 ranges
std::vector v{3, 1, 4, 1, 5};
auto result = v | std::views::filter([](int n){ return n > 2; })
                | std::views::transform([](int n){ return n * 2; });
```

**口述回答:**
"C++17 和 C++20 带来了很多重要特性。C++17 主要有：optional 表示可能为空的值；variant 是类型安全的联合体；string_view 是不拥有数据的字符串视图，避免拷贝；结构化绑定可以一次声明多个变量并解构；if constexpr 实现编译期条件分支；fold expressions 简化可变参数模板。C++20 更是一次大更新：concepts 让模板约束更直观；ranges 库提供惰性求值的管道操作；coroutines 支持协程；span 是连续内存的视图；三路比较运算符简化比较操作；modules 解决头文件的问题。这些特性让 C++ 越来越现代化，代码更简洁安全。"

---

## 二、操作系统 (20题)

### Q31: 进程和线程的区别？

**A:**

| 特性 | 进程 | 线程 |
|-----|------|------|
| 定义 | 资源分配基本单位 | CPU 调度基本单位 |
| 地址空间 | 独立 | 共享进程地址空间 |
| 资源 | 独立拥有 | 共享进程资源 |
| 创建开销 | 大 | 小 |
| 通信 | IPC（管道、消息队列等） | 直接读写共享内存 |
| 切换开销 | 大（需切换页表） | 小 |
| 崩溃影响 | 不影响其他进程 | 可能导致整个进程崩溃 |

**口述回答:**
"进程和线程是操作系统中的基本概念。进程是资源分配的基本单位，有独立的地址空间、文件描述符等资源。线程是 CPU 调度的基本单位，同一进程的线程共享地址空间和资源。主要区别在于：进程间相互隔离，一个进程崩溃不影响其他进程；线程共享进程资源，一个线程崩溃可能导致整个进程崩溃。创建进程开销大，需要复制地址空间；创建线程开销小，只需分配栈和寄存器。进程间通信需要 IPC 机制，线程可以直接读写共享内存。选择上，需要隔离性用进程，需要共享数据和高性能用线程。"

---

### Q32: 进程的状态有哪些？

**A:** 五态模型：新建 (New)、就绪 (Ready)、运行 (Running)、阻塞 (Blocked)、终止 (Terminated)

状态转换：就绪→运行（调度选中）、运行→就绪（时间片完）、运行→阻塞（等待I/O）、阻塞→就绪（I/O完成）

**口述回答:**
"进程的状态通常分为五个：新建态是进程刚被创建还未就绪；就绪态是进程已准备好运行，等待 CPU 调度；运行态是进程正在 CPU 上执行；阻塞态是进程在等待某个事件比如 I/O 完成；终止态是进程执行完毕。状态转换过程是：进程创建后进入就绪态，被调度器选中后进入运行态，时间片用完回到就绪态，如果等待 I/O 则进入阻塞态，I/O 完成后回到就绪态。理解进程状态对理解系统调度和性能分析很重要。"

---

### Q33: 进程调度算法有哪些？

**A:** FCFS（先来先服务）、SJF（最短作业优先）、RR（时间片轮转）、优先级调度、多级反馈队列。Linux CFS 基于虚拟运行时间，使用红黑树保证公平。

**口述回答:**
"常见的进程调度算法有几种。先来先服务 FCFS 按到达顺序调度，简单但可能导致短作业等很久。最短作业优先 SJF 优先调度执行时间短的，平均等待时间最短但可能饿死长作业。时间片轮转 RR 每个进程分配固定时间片，时间片用完就切换，响应性好适合交互系统。优先级调度根据优先级选择进程，要注意低优先级饥饿问题。多级反馈队列结合以上优点，有多个不同优先级的队列。Linux 使用的 CFS 完全公平调度器，用红黑树管理进程，按虚拟运行时间调度，保证每个进程获得公平的 CPU 时间。"

---

### Q34: 什么是死锁？如何避免？

**A:** 死锁四个必要条件：互斥、持有并等待、非抢占、循环等待。

```cpp
// 避免方法：使用 std::scoped_lock 同时加锁
std::mutex m1, m2;
std::scoped_lock lock(m1, m2);  // C++17，避免死锁
```

**口述回答:**
"死锁是指多个进程或线程相互等待对方持有的资源，导致都无法继续执行。产生死锁需要四个必要条件同时满足：互斥、持有并等待、非抢占、循环等待。避免死锁的方法是破坏这些条件。最常用的是破坏循环等待，让所有线程按相同顺序加锁。C++ 中可以用 std::lock 或 C++17 的 scoped_lock 同时获取多个锁，它内部会避免死锁。还可以用 try_lock 尝试加锁，失败就释放已有的锁重试。另外，设置锁超时也是一种防御措施。在设计时应该尽量减少锁的粒度和持有时间。"

---

### Q35: 虚拟内存是什么？

**A:** 为每个进程提供独立虚拟地址空间，通过页表映射到物理内存。作用：进程隔离、内存扩展、权限保护、页面共享。

**口述回答:**
"虚拟内存是操作系统提供的内存管理机制，让每个进程都觉得自己独占整个内存空间。进程使用虚拟地址，操作系统通过页表将虚拟地址映射到物理地址。虚拟内存的好处有很多：首先是进程隔离，每个进程有独立地址空间，不能访问其他进程的内存；其次是内存扩展，可以使用比物理内存更大的地址空间，不常用的页可以换出到磁盘；第三是权限保护，可以设置页面的读写执行权限；第四是支持共享，多个进程可以映射同一物理页面来共享代码或数据。当访问的页面不在物理内存时会触发缺页异常，由操作系统处理。"

---

### Q36: 页面置换算法有哪些？

**A:** OPT（理论最优）、FIFO、LRU（最近最少使用）、Clock（LRU近似）、LFU（最不经常使用）。LRU 用哈希表+双向链表实现 O(1) 操作。

**口述回答:**
"当物理内存不足需要换出页面时，就要用页面置换算法决定换哪个。OPT 是理论最优算法，换出将来最长时间不用的页面，但实际无法实现因为不知道未来。FIFO 先进先出，换出最早进入的页面，简单但效果不好，会有 Belady 异常。LRU 最近最少使用，换出最长时间没被访问的页面，效果好但实现开销大，可以用哈希表加双向链表实现 O(1) 操作。Clock 算法是 LRU 的近似，用一个环形链表和访问位，开销小。LFU 最不经常使用，换出访问次数最少的，但对访问模式变化不敏感。实际系统通常用 LRU 的近似算法。"

---

### Q37: 用户态和内核态的区别？

**A:** 用户态权限受限，内核态可执行所有指令和访问所有内存。切换通过系统调用、异常或中断触发，有保存寄存器、切换栈等开销。

**口述回答:**
"用户态和内核态是 CPU 的两种运行级别。用户态权限受限，不能执行特权指令，不能直接访问硬件和内核内存，应用程序运行在用户态。内核态具有完全权限，可以执行所有指令，访问所有内存，操作系统内核运行在内核态。用户程序需要操作系统服务时，通过系统调用陷入内核态。状态切换有开销：要保存用户态寄存器、切换到内核栈、执行内核代码、再切换回去。这种隔离保证了系统安全稳定，用户程序的错误不会直接导致系统崩溃。理解这个对于优化性能很重要，比如减少不必要的系统调用。"

---

### Q38: 什么是系统调用？

**A:** 用户程序请求内核服务的接口。常见：fork/exec（进程）、open/read/write（文件）、socket（网络）、mmap（内存）。

**口述回答:**
"系统调用是用户程序请求操作系统内核服务的接口。用户程序不能直接操作硬件或访问内核数据，必须通过系统调用让内核代为执行。系统调用涉及从用户态切换到内核态。常见的系统调用包括：进程管理的 fork、exec、exit、wait；文件操作的 open、read、write、close；内存管理的 mmap、brk；网络操作的 socket、bind、listen、connect；还有进程间通信的各种调用。库函数如 printf、malloc 底层也是通过系统调用实现的。系统调用是用户程序和内核之间的边界，数量有限且接口稳定。"

---

### Q39: 进程间通信 (IPC) 方式？

**A:** 管道（亲缘进程）、命名管道、消息队列、共享内存（最快）、信号量、套接字（跨网络）、信号。

**口述回答:**
"进程间通信有多种方式，各有适用场景。管道是最简单的，适合父子进程间单向通信。命名管道是管道的扩展，无亲缘关系的进程也能用。消息队列提供有格式的消息传递，可以按类型选择性接收。共享内存是最快的 IPC 方式，多个进程直接读写同一块内存，但需要自己用信号量同步。信号量主要用于同步控制，协调多进程对共享资源的访问。Socket 是最通用的，既能本地通信也能跨网络通信。信号用于通知进程发生了某个事件，比如 SIGKILL、SIGTERM。选择时要考虑性能、同步需求、是否跨机器等因素。"

---

### Q40: 共享内存如何使用？

**A:**
```cpp
// POSIX 共享内存
int fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
ftruncate(fd, size);
void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
// 使用后
munmap(ptr, size);
shm_unlink("/myshm");
```

**口述回答:**
"共享内存是最快的进程间通信方式，因为数据直接在内存中共享，不需要内核拷贝。POSIX 共享内存使用起来分几步：首先用 shm_open 创建或打开共享内存对象，会返回文件描述符；然后用 ftruncate 设置大小；再用 mmap 把它映射到进程地址空间，得到可以直接读写的指针。用完后用 munmap 解除映射，最后一个使用者用 shm_unlink 删除共享内存对象。需要注意的是，共享内存本身不提供同步机制，多进程并发访问需要用信号量或互斥锁来同步，否则会有数据竞争问题。"

---

### Q41: 信号量是什么？

**A:** 同步原语，控制对共享资源的访问。P 操作减一（可能阻塞），V 操作加一（可能唤醒）。C++20 提供 `std::counting_semaphore`。

**口述回答:**
"信号量是一种经典的同步原语，用于控制多进程或多线程对共享资源的访问。信号量有一个计数器，两个原子操作：P 操作会把计数器减一，如果减后小于零就阻塞等待；V 操作把计数器加一，如果有等待的进程就唤醒一个。二值信号量相当于互斥锁，用于互斥访问。计数信号量可以控制同时访问资源的数量，比如限制连接池的并发数。信号量可以用于进程间同步，这点比互斥锁更强大。C++20 引入了 std::counting_semaphore 和 std::binary_semaphore，可以方便地在多线程程序中使用。"

---

### Q42: 什么是内存映射 (mmap)？

**A:** 将文件映射到进程地址空间，像操作内存一样访问文件。优点：减少拷贝、按需加载、多进程共享。用于大文件处理、共享内存、动态库加载。

**口述回答:**
"内存映射 mmap 是把文件或设备映射到进程的虚拟地址空间，之后可以像访问内存一样访问文件内容。优点有几个：一是减少数据拷贝，传统 read 需要从内核缓冲区拷贝到用户缓冲区，mmap 直接访问页缓存；二是按需加载，只有实际访问的页面才会被读入内存；三是多进程可以共享同一映射，用于进程间通信或共享库。mmap 常用于处理大文件、实现共享内存、加载动态库。需要注意的是，mmap 对小文件可能不如 read 高效，因为有页面管理的开销。另外要注意同步问题，可能需要 msync 确保数据写回文件。"

---

### Q43: 什么是写时复制 (COW)？

**A:** 延迟拷贝：fork() 后父子共享页面（只读），写入时才复制该页。C++11 后 std::string 不再使用 COW，改用 SSO（小字符串优化）。

**口述回答:**
"写时复制是一种延迟拷贝的优化技术。当需要复制数据时，不立即执行实际拷贝，而是让多方共享同一份数据，标记为只读。只有当某一方要修改时，才真正复制出一份独立的副本。最典型的应用是 fork 系统调用，父子进程最初共享相同的物理页面，只有当某个进程要写入时才复制那一页，这大大提高了 fork 的效率。过去 C++ 的 std::string 也用 COW 实现，多个字符串可以共享同一缓冲区。但 C++11 后，因为多线程环境下 COW 的引用计数需要原子操作，开销变大，标准库改用小字符串优化 SSO，短字符串直接存在对象内部。"

---

### Q44: 中断和异常的区别？

**A:** 中断来自外部设备（异步），异常由 CPU 执行指令触发（同步）。异常分为：故障（可恢复如缺页）、陷阱（系统调用）、终止（严重错误）。

**口述回答:**
"中断和异常都会打断 CPU 当前执行，但来源不同。中断是外部设备触发的，比如键盘按键、网卡收到数据、定时器到期，是异步的，和当前执行的指令无关。异常是 CPU 执行指令时触发的，是同步的。异常分三类：故障是可以恢复的，比如缺页异常，处理完后重新执行出错指令；陷阱是有意触发的，比如系统调用，处理完后执行下一条指令；终止是严重错误，比如硬件故障，通常导致程序结束。中断和异常都通过中断描述符表 IDT 找到处理程序。理解这些对于理解系统底层行为很重要。"

---

### Q45: 什么是 DMA？

**A:** Direct Memory Access，外设直接与内存交换数据，无需 CPU 参与每字节传输。CPU 只需设置 DMA 参数，传输完成后收中断通知。

**口述回答:**
"DMA 是 Direct Memory Access，直接内存访问。它允许外设直接和内存传输数据，不需要 CPU 参与每个字节的搬运。没有 DMA 的话，CPU 要反复执行读设备、写内存的指令，效率很低。有了 DMA，CPU 只需告诉 DMA 控制器：从哪里读、写到哪里、传多少数据，然后 DMA 控制器自动完成传输，传完后发中断通知 CPU。这样 CPU 就可以在数据传输期间做其他事情，大大提高了系统效率。DMA 广泛用于磁盘、网卡等高速设备的数据传输。"

---

### Q46: 文件系统的 inode？

**A:** 存储文件元数据：类型、权限、大小、时间戳、数据块指针。不含文件名（在目录项中）。硬链接是多个目录项指向同一 inode。

**口述回答:**
"inode 是 Unix/Linux 文件系统的核心概念，每个文件都有一个唯一的 inode。inode 存储文件的元数据：文件类型、权限、所有者、大小、时间戳，还有指向数据块的指针。注意文件名不在 inode 里，而是在目录项中。目录其实是一个特殊文件，内容是文件名到 inode 号的映射。这种设计支持硬链接：多个目录项可以指向同一个 inode，删除一个文件名只是减少 inode 的链接计数，文件内容在链接计数变为零时才删除。软链接则是创建一个新 inode，内容是目标文件的路径名。"

---

### Q47: 什么是文件描述符？

**A:** 内核为进程打开文件维护的非负整数索引。0=stdin，1=stdout，2=stderr。通过 open 获取，close 释放。

**口述回答:**
"文件描述符是内核为进程打开的文件分配的一个非负整数索引。进程通过文件描述符而不是文件名来操作文件，这提供了一层抽象。内核为每个进程维护一个文件描述符表，表中每项指向系统级的文件表项。每个进程默认有三个文件描述符：0 是标准输入，1 是标准输出，2 是标准错误。open 打开文件返回新的文件描述符，close 关闭并释放。文件描述符不仅用于普通文件，socket、管道、设备都用同样的机制，这是 Unix 一切皆文件的体现。文件描述符是有限资源，需要及时关闭，否则可能耗尽。"

---

### Q48: 同步 I/O 和异步 I/O？

**A:** 同步 I/O 等待操作完成才返回；异步 I/O 立即返回，完成后通知。I/O 多路复用（select/poll/epoll）是同步的，只是可以同时等待多个 fd。

**口述回答:**
"同步 I/O 和异步 I/O 的区别在于调用是否等待操作完成。同步 I/O 调用会阻塞或轮询，直到数据准备好并拷贝到用户缓冲区才返回。异步 I/O 调用立即返回，I/O 操作在后台进行，完成后通过回调或信号通知应用程序。需要注意的是，I/O 多路复用如 select、poll、epoll 本质上是同步 I/O，它们只是可以同时等待多个文件描述符就绪，但实际的读写操作仍然是同步的，数据到用户缓冲区期间进程还是要等待。真正的异步 I/O 在 Linux 是 io_uring 或 aio，Windows 是 IOCP。"

---

### Q49: select、poll、epoll 的区别？

**A:**

| 特性 | select | poll | epoll |
|-----|--------|------|-------|
| fd 上限 | 1024 | 无 | 无 |
| 遍历 | O(n) | O(n) | O(1) |
| 触发模式 | LT | LT | LT/ET |

epoll 用红黑树管理 fd，只返回就绪的，支持边缘触发。

**口述回答:**
"select、poll、epoll 都是 I/O 多路复用机制，但效率差很多。select 有几个问题：文件描述符有上限，通常是 1024；每次调用要把 fd 集合从用户态拷贝到内核态；返回后要遍历所有 fd 检查哪些就绪。poll 去掉了 fd 数量限制，但其他问题没解决。epoll 是 Linux 特有的高效方案：用红黑树管理注册的 fd，用链表维护就绪的 fd，所以添加删除是 O(1)，返回的就是就绪的 fd，不用遍历；还支持边缘触发模式，只在状态变化时通知。高并发服务器基本都用 epoll。"

---

### Q50: 什么是惊群问题？

**A:** 多进程等待同一事件，事件发生时全部唤醒但只有一个能处理。解决：`EPOLLEXCLUSIVE`（只唤醒一个）、`SO_REUSEPORT`（独立队列）。

**口述回答:**
"惊群问题是多个进程或线程同时等待同一个事件，当事件发生时全部被唤醒，但只有一个能成功处理，其他的白白唤醒又继续睡眠。这造成不必要的上下文切换，影响性能。典型场景是多进程服务器，多个 worker 都在 accept 同一个监听 socket。解决方法有几种：Linux 4.5 以后的 EPOLLEXCLUSIVE 标志，可以让 epoll_wait 只唤醒一个等待的进程；SO_REUSEPORT 选项可以让多个进程绑定同一端口，内核会负载均衡分发连接到不同进程；也可以用一个进程专门 accept，然后分发给其他进程处理。Nginx 就有专门的机制避免惊群。"

---

## 三、计算机网络 (20题)

### Q51: OSI 七层模型和 TCP/IP 四层模型？

**A:**

| OSI 七层 | TCP/IP 四层 | 协议示例 |
|---------|------------|---------|
| 应用层 | 应用层 | HTTP, FTP, DNS |
| 表示层 | ↑ | SSL/TLS |
| 会话层 | ↑ | RPC |
| 传输层 | 传输层 | TCP, UDP |
| 网络层 | 网络层 | IP, ICMP |
| 数据链路层 | 网络接口层 | Ethernet, ARP |
| 物理层 | ↑ | 物理介质 |

**口述回答:**
"OSI 七层模型从下到上是：物理层处理比特流传输；数据链路层处理帧和 MAC 地址；网络层处理 IP 地址和路由；传输层处理端到端通信，有 TCP 和 UDP；会话层管理会话连接；表示层处理数据格式转换和加密；应用层是具体的应用协议。实际使用更多的是 TCP/IP 四层模型：网络接口层对应物理层和数据链路层；网络层对应网络层；传输层对应传输层；应用层对应上面三层。开发时主要关注传输层和应用层，了解 IP 层的一些概念如 MTU、分片等也很有用。"

---

### Q52: TCP 和 UDP 的区别？

**A:**

| 特性 | TCP | UDP |
|-----|-----|-----|
| 连接 | 面向连接 | 无连接 |
| 可靠性 | 可靠传输 | 不可靠 |
| 有序性 | 保证顺序 | 不保证 |
| 流控/拥塞 | 有 | 无 |
| 头部开销 | 20+ 字节 | 8 字节 |
| 传输方式 | 字节流 | 数据报 |

TCP 用于 HTTP、文件传输；UDP 用于 DNS、视频流、游戏。

**口述回答:**
"TCP 和 UDP 是传输层的两个主要协议，特点完全不同。TCP 是面向连接的，需要三次握手建立连接；提供可靠传输，有序列号确认重传机制；保证数据顺序；有流量控制和拥塞控制。UDP 是无连接的，直接发送；不保证送达，不保证顺序；没有拥塞控制，发送速度由应用决定；头部只有 8 字节，开销小。选择上，需要可靠传输用 TCP，如 HTTP、文件传输、邮件；需要低延迟可以容忍丢包用 UDP，如 DNS 查询、视频流、实时游戏、VoIP。有些应用在 UDP 上自己实现可靠传输，如 QUIC。"

---

### Q53: TCP 三次握手过程？

**A:**
```
客户端                    服务端
   |----SYN(seq=x)---->|      1. 客户端发 SYN
   |<--SYN+ACK(seq=y,ack=x+1)--|  2. 服务端回 SYN+ACK
   |----ACK(ack=y+1)--->|      3. 客户端发 ACK
   |      连接建立       |
```

**为什么三次？** 防止历史重复连接、同步双方初始序列号、确认双方收发能力。

**口述回答:**
"TCP 三次握手用于建立连接。第一次握手，客户端发送 SYN 包，包含自己的初始序列号 x，进入 SYN_SENT 状态。第二次握手，服务端收到后发送 SYN+ACK 包，包含自己的初始序列号 y，确认号是 x+1，进入 SYN_RECEIVED 状态。第三次握手，客户端发送 ACK 包，确认号是 y+1，双方进入 ESTABLISHED 状态。为什么要三次？一是防止历史的重复连接请求造成混乱，三次握手可以让服务端确认客户端仍然在线；二是同步双方的初始序列号，每一方都需要确认对方收到了自己的序列号；三是确认双方都有收发能力。"

---

### Q54: TCP 四次挥手过程？

**A:**
```
主动方                    被动方
   |----FIN(seq=u)---->|      1. 主动方发 FIN
   |<---ACK(ack=u+1)---|      2. 被动方确认
   |<---FIN(seq=v)-----|      3. 被动方发 FIN
   |----ACK(ack=v+1)--->|     4. 主动方确认
   |   TIME_WAIT(2MSL)  |
```

**为什么四次？** TCP 是全双工，每个方向单独关闭。

**TIME_WAIT**：等待 2MSL 确保最后 ACK 到达，避免新连接收到旧包。

**口述回答:**
"TCP 四次挥手用于关闭连接。第一次挥手，主动关闭方发送 FIN 包，表示不再发送数据，进入 FIN_WAIT_1 状态。第二次挥手，被动方回复 ACK，进入 CLOSE_WAIT 状态，主动方收到后进入 FIN_WAIT_2。第三次挥手，被动方发送完剩余数据后，发送 FIN 包，进入 LAST_ACK 状态。第四次挥手，主动方回复 ACK，进入 TIME_WAIT 状态。为什么要四次？因为 TCP 是全双工，每个方向要单独关闭。收到 FIN 只表示对方不再发数据，但自己可能还有数据要发。TIME_WAIT 要等待 2 倍的最大段生存时间，确保最后的 ACK 送达，也让旧连接的包过期，不会影响新连接。"

---

### Q55: TCP 如何保证可靠传输？

**A:**
1. **序列号和确认号**：跟踪数据顺序
2. **校验和**：检测数据错误
3. **超时重传**：未收到 ACK 则重传
4. **滑动窗口**：流量控制
5. **拥塞控制**：慢启动、拥塞避免、快重传、快恢复

**口述回答:**
"TCP 通过多种机制保证可靠传输。首先是序列号和确认号，每个字节都有序列号，接收方用确认号告诉发送方收到了哪些数据，发送方据此知道哪些需要重传。其次是校验和，检测数据在传输中是否损坏。第三是超时重传，发送数据后启动定时器，如果超时没收到 ACK 就重传。第四是滑动窗口实现流量控制，接收方通过窗口大小告诉发送方自己的接收能力，发送方不会发送超过窗口的数据。第五是拥塞控制，通过慢启动、拥塞避免、快重传、快恢复等算法，根据网络状况调整发送速度，避免网络拥塞。"

---

### Q56: TCP 滑动窗口机制？

**A:** 发送方维护发送窗口，接收方通告接收窗口。窗口内数据可连续发送无需等待 ACK。

**窗口大小** = min(rwnd, cwnd)（接收窗口和拥塞窗口）

**零窗口探测**：接收方窗口为 0 时，发送方定期发探测包。

**口述回答:**
"滑动窗口是 TCP 流量控制的核心机制。发送方维护一个发送窗口，窗口内的数据可以连续发送而不用等待每个 ACK。接收方在 ACK 中通告自己的接收窗口大小 rwnd，告诉发送方还能接收多少数据。实际发送窗口取 rwnd 和拥塞窗口 cwnd 的较小值。窗口随着 ACK 向前滑动，已确认的数据从窗口移出，新数据进入窗口。如果接收方窗口变成 0，发送方会停止发送，并定期发送零窗口探测包，检查窗口是否恢复。滑动窗口机制让 TCP 既能保证可靠性，又能高效利用带宽。"

---

### Q57: TCP 拥塞控制算法？

**A:**
1. **慢启动**：cwnd 从 1 开始指数增长
2. **拥塞避免**：达到阈值后线性增长
3. **快重传**：收到 3 个重复 ACK 立即重传
4. **快恢复**：快重传后 cwnd 减半，进入拥塞避免

现代算法：CUBIC（Linux 默认）、BBR（基于带宽）

**口述回答:**
"TCP 拥塞控制防止发送方发太快导致网络拥塞。传统算法有四个阶段：慢启动阶段，拥塞窗口 cwnd 从 1 开始，每收到一个 ACK 就加倍，指数增长。当 cwnd 达到慢启动阈值后进入拥塞避免阶段，每个 RTT 窗口只增加 1，线性增长。如果发生丢包，说明网络拥塞，cwnd 减半，阈值也减半。快重传是收到三个重复 ACK 就立即重传，不等超时。快恢复是快重传后 cwnd 减半而不是重新慢启动。现代算法如 CUBIC 是 Linux 默认的，用三次函数调整窗口。BBR 是 Google 提出的，基于测量的带宽和 RTT，不依赖丢包来感知拥塞。"

---

### Q58: TCP 粘包问题？

**A:** TCP 是字节流，无消息边界，多个小包可能合并或一个大包分割。

**解决方案**：
1. 固定长度消息
2. 特殊分隔符（如 `\r\n`）
3. 消息头指定长度（length + payload）

```cpp
// 长度前缀协议
struct Message {
    uint32_t length;  // 网络字节序
    char data[];
};
```

**口述回答:**
"TCP 是字节流协议，没有消息边界，这就导致所谓的粘包问题。发送两次 send，接收方可能一次 recv 全收到；发送一次大数据，接收方可能分多次收到。这不是 TCP 的问题，而是应用层需要处理的事情。解决方案有三种：固定长度消息，每个消息固定大小，简单但不灵活；分隔符方式，用特殊字符如换行符分隔消息，适合文本协议，但数据中不能包含分隔符；长度前缀方式，消息头先发送长度，接收方先读长度再读对应字节的数据，这是最常用的方案。HTTP 就是用 Content-Length 或 chunked 编码来界定消息边界的。"

---

### Q59: TCP Keepalive 机制？

**A:** 长时间无数据时发探测包，检测连接是否存活。

```cpp
int keepalive = 1;
setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(keepalive));

// Linux 可设置参数
int idle = 60;      // 空闲 60s 后开始探测
int interval = 5;   // 探测间隔 5s
int count = 3;      // 探测 3 次无响应则断开
setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(idle));
setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(interval));
setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT, &count, sizeof(count));
```

**口述回答:**
"TCP Keepalive 是检测连接是否存活的机制。当连接长时间没有数据传输时，可能连接已经断了但双方都不知道。开启 Keepalive 后，空闲一段时间会发送探测包，如果对方没响应就认为连接断开。使用方法是用 setsockopt 设置 SO_KEEPALIVE 为 1 来开启。在 Linux 上还可以调整三个参数：TCP_KEEPIDLE 是空闲多久后开始探测，TCP_KEEPINTVL 是探测间隔，TCP_KEEPCNT 是探测多少次无响应后断开。默认参数通常是空闲 2 小时才开始，对于实时性要求高的应用需要自己设置更短的时间，或者在应用层实现心跳机制。"

---

### Q60: Socket 编程基本流程？

**A:**
```cpp
// 服务端
int server_fd = socket(AF_INET, SOCK_STREAM, 0);
bind(server_fd, (sockaddr*)&addr, sizeof(addr));
listen(server_fd, SOMAXCONN);
int client_fd = accept(server_fd, nullptr, nullptr);
read(client_fd, buf, size);
write(client_fd, data, len);
close(client_fd);
close(server_fd);

// 客户端
int fd = socket(AF_INET, SOCK_STREAM, 0);
connect(fd, (sockaddr*)&addr, sizeof(addr));
write(fd, data, len);
read(fd, buf, size);
close(fd);
```

**口述回答:**
"TCP Socket 编程的基本流程分服务端和客户端。服务端流程：首先 socket 创建套接字，指定协议族和类型；然后 bind 绑定 IP 和端口；接着 listen 开始监听，指定 backlog 队列大小；循环调用 accept 接受客户端连接，返回新的已连接套接字；在新套接字上 read/write 进行数据收发；完成后 close 关闭。客户端流程简单些：socket 创建套接字；connect 连接服务端；read/write 收发数据；close 关闭。非阻塞模式下，可能需要配合 select/poll/epoll 来处理多个连接，避免一个连接阻塞影响其他连接。"

---

### Q61: 什么是 Nagle 算法？

**A:** 减少小包数量：等待前一个 ACK 或累积足够数据再发送。

可能导致延迟，实时应用可禁用：
```cpp
int flag = 1;
setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));
```

**口述回答:**
"Nagle 算法是 TCP 为减少小包数量设计的优化。原理是：如果有未被确认的数据在传输中，就把后续的小数据攒起来，等收到 ACK 或者累积到足够大再发送。这样可以减少网络中的小包数量，提高带宽利用率。但问题是会增加延迟，对于交互式应用如 SSH、游戏，或者已经做了应用层缓冲的场景，Nagle 反而有害。可以通过设置 TCP_NODELAY 选项来禁用 Nagle。另一个相关的是延迟 ACK，接收方不是立即回复 ACK，而是等一下看能否捎带数据一起发。Nagle 和延迟 ACK 一起可能导致更大的延迟。"

---

### Q62: HTTP/1.0、1.1、2.0 的区别？

**A:**

| 版本 | 特点 |
|-----|------|
| 1.0 | 短连接，每次请求新建连接 |
| 1.1 | 长连接、管道化、Host 头、分块传输 |
| 2.0 | 多路复用、头部压缩、服务器推送、二进制帧 |

**HTTP/2 多路复用**：一个 TCP 连接上并行多个请求/响应，解决队头阻塞。

**口述回答:**
"HTTP 协议经历了几个重要版本的演进。HTTP/1.0 每个请求都要新建 TCP 连接，效率很低。HTTP/1.1 引入了持久连接，可以复用 TCP 连接发送多个请求；支持管道化，可以连续发送请求不等响应，但响应必须按序返回，有队头阻塞问题；还增加了 Host 头支持虚拟主机。HTTP/2 是重大升级：多路复用允许一个 TCP 连接上同时有多个请求和响应，用帧来区分，真正解决了队头阻塞；头部压缩减少了重复头部的传输；支持服务器推送。HTTP/2 用二进制帧而不是文本，解析更高效。HTTP/3 更进一步，用 QUIC 协议替代 TCP。"

---

### Q63: HTTPS 工作原理？

**A:**
1. TCP 握手
2. TLS 握手：协商加密算法、验证证书、交换密钥
3. 使用对称密钥加密通信

**TLS 握手简化流程**：
```
Client: ClientHello (支持的加密套件)
Server: ServerHello + Certificate + ServerHelloDone
Client: 验证证书, ClientKeyExchange
双方: 计算会话密钥, Finished
```

**口述回答:**
"HTTPS 就是 HTTP over TLS，在 HTTP 和 TCP 之间加了一层 TLS 加密。工作过程是：首先完成 TCP 三次握手，然后进行 TLS 握手。TLS 握手过程是：客户端发送 ClientHello，包含支持的加密套件和随机数；服务端回复 ServerHello，选定加密套件，发送证书和自己的随机数；客户端验证证书是否由可信 CA 签发，提取公钥，然后生成预主密钥，用公钥加密发送给服务端；双方用相同的算法从随机数和预主密钥计算出会话密钥；之后的通信用对称加密。HTTPS 保证了机密性、完整性和身份认证，是 Web 安全的基础。"

---

### Q64: DNS 解析过程？

**A:**
1. 查本地缓存
2. 查本地 hosts 文件
3. 查本地 DNS 服务器缓存
4. 递归/迭代查询根域名服务器 → 顶级域 → 权威服务器

```
浏览器 → 本地DNS → 根DNS(.根) → 顶级DNS(.com) → 权威DNS(example.com)
```

**口述回答:**
"DNS 是域名解析服务，把域名转换成 IP 地址。解析过程是：首先查浏览器缓存，没有就查操作系统缓存，再查 hosts 文件；都没有就向本地 DNS 服务器查询，本地 DNS 也有缓存；如果本地 DNS 也没有，就开始递归或迭代查询。递归查询是本地 DNS 帮你问到底；迭代查询是本地 DNS 先问根域名服务器，根服务器告诉你 .com 的服务器地址，再去问 .com 服务器，它告诉你 example.com 的权威服务器地址，最后问权威服务器得到 IP。整个过程会在各级缓存中留下记录，下次查询就快了。DNS 默认用 UDP 协议，端口 53。"

---

### Q65: ARP 协议的作用？

**A:** 将 IP 地址解析为 MAC 地址。

过程：广播 ARP 请求，目标主机单播回复自己的 MAC。缓存在 ARP 表中。

```bash
# 查看 ARP 缓存
arp -a
```

**口述回答:**
"ARP 是地址解析协议，用于将 IP 地址解析成 MAC 地址。网络层用 IP 地址，但数据链路层需要 MAC 地址来传输帧。当主机要发送数据时，如果目标在同一局域网，需要知道目标的 MAC 地址。过程是：主机先检查 ARP 缓存，有就直接用；没有就广播 ARP 请求，问谁是这个 IP，请告诉我你的 MAC；目标主机收到后单播回复自己的 MAC；发送方收到后缓存起来供后续使用。如果目标不在同一网段，ARP 请求的是网关的 MAC，让网关转发。ARP 缓存有超时机制，定期刷新。可以用 arp 命令查看和管理缓存。"

---

### Q66: NAT 是什么？

**A:** Network Address Translation，私有 IP 转换为公网 IP。

**类型**：
- SNAT：源地址转换（内网访问外网）
- DNAT：目的地址转换（外网访问内网服务）

**NAT 穿透**：STUN、TURN、ICE

**口述回答:**
"NAT 是网络地址转换，用于在私有网络和公网之间转换 IP 地址。最常见的场景是家庭或公司的内网设备通过一个公网 IP 访问互联网。主要类型有：SNAT 源地址转换，内网访问外网时把源 IP 换成路由器的公网 IP；DNAT 目的地址转换，外网访问内网服务时把目的 IP 换成内网 IP，常用于端口映射。NAT 节省了 IP 地址，也提供了一定的安全隔离。但 NAT 也带来问题：外网主动连接内网困难，需要穿透技术；某些协议在 NAT 下有问题。NAT 穿透常用 STUN 发现自己的公网地址，TURN 通过中继服务器转发，ICE 综合多种方式找到最佳路径。"

---

### Q67: 什么是 TIME_WAIT 状态？

**A:** TCP 主动关闭方在发送最后 ACK 后进入 TIME_WAIT，持续 2MSL（通常 60s）。

**作用**：确保最后 ACK 到达、等待旧报文消失。

**大量 TIME_WAIT 解决**：
```cpp
// 允许复用 TIME_WAIT 端口
int reuse = 1;
setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
```

**口述回答:**
"TIME_WAIT 是 TCP 四次挥手中主动关闭连接一方进入的状态。发送最后一个 ACK 后进入 TIME_WAIT，持续 2 倍的 MSL，也就是最大段生存时间，通常是 60 秒。为什么要等这么久？一是确保最后的 ACK 能送达，如果丢失，对方会重发 FIN，在 TIME_WAIT 期间可以重发 ACK；二是让旧连接的包都过期，不会被新连接收到。但大量 TIME_WAIT 会占用端口和内存。解决方法：设置 SO_REUSEADDR 允许复用 TIME_WAIT 状态的端口；Linux 下可以开启 tcp_tw_reuse 让新连接复用 TIME_WAIT；也可以缩短 TIME_WAIT 时间，但要谨慎。"

---

### Q68: 什么是 SYN Flood 攻击？

**A:** 攻击者发送大量 SYN 包不完成握手，耗尽服务器半连接队列。

**防御**：SYN Cookie、增大 backlog、减小超时、防火墙限流。

**口述回答:**
"SYN Flood 是一种常见的 DDoS 攻击方式。攻击者发送大量 SYN 包但不完成三次握手，用伪造的源 IP 或者直接不回复 ACK。服务器为每个 SYN 分配资源放入半连接队列等待，攻击量大时队列被占满，正常用户的连接请求被拒绝。防御方法有几种：SYN Cookie 是最有效的，服务端不为 SYN 请求分配资源，而是用特殊算法计算一个 cookie 作为序列号发回去，收到 ACK 后验证 cookie 才建立连接；增大半连接队列大小；减小 SYN_RECV 超时时间；用防火墙限制每个 IP 的连接速率；在前端用专门的 DDoS 防护服务。"

---

### Q69: Cookie 和 Session 的区别？

**A:**

| 特性 | Cookie | Session |
|-----|--------|---------|
| 存储位置 | 客户端 | 服务端 |
| 安全性 | 较低 | 较高 |
| 大小限制 | 4KB | 无 |
| 生命周期 | 可设过期时间 | 会话期间或超时 |

Session ID 通常通过 Cookie 传递。

**口述回答:**
"Cookie 和 Session 都是用于跟踪用户会话状态的机制，但实现方式不同。Cookie 存储在客户端浏览器中，每次请求自动带上，有大小限制约 4KB，可以设置过期时间，相对不安全因为客户端可以查看和修改。Session 存储在服务端，更安全，大小无限制。通常的做法是把 Session ID 存在 Cookie 中，服务端根据 Session ID 查找用户数据。纯用 Cookie 的话，用户信息都在客户端，要注意加密和防篡改。Session 的问题是服务端要存储数据，集群环境需要共享 Session。现代方案是 JWT，把用户信息编码成 token 发给客户端，服务端无需存储，通过签名验证完整性。"

---

### Q70: WebSocket 与 HTTP 的区别？

**A:**
- HTTP：请求-响应模式，半双工
- WebSocket：全双工，持久连接，双向实时通信

```
HTTP Upgrade 请求 → 101 Switching Protocols → WebSocket 连接
```

用于聊天、实时推送、游戏等场景。

**口述回答:**
"WebSocket 和 HTTP 都是应用层协议，但设计目标不同。HTTP 是请求-响应模式，客户端发请求，服务端回响应，是半双工的，服务端不能主动推送。WebSocket 是全双工协议，建立连接后双方可以随时发送数据，服务端可以主动推送。WebSocket 连接的建立借助 HTTP：客户端发送带 Upgrade 头的 HTTP 请求，服务端同意后返回 101 状态码，然后协议切换成 WebSocket，之后就不再是 HTTP 了。WebSocket 适合需要实时双向通信的场景，如聊天、实时通知、股票行情、在线游戏等。相比轮询和长轮询，WebSocket 效率更高、延迟更低。"

---

## 四、并发编程 (20题)

### Q71: C++11 线程库基本用法？

**A:**
```cpp
#include <thread>

void task(int id) { /* ... */ }

// 创建线程
std::thread t1(task, 1);
std::thread t2([](){ /* lambda */ });

// 等待线程结束
t1.join();

// 分离线程（后台运行）
t2.detach();

// 获取线程 ID
std::thread::id id = std::this_thread::get_id();

// 让出 CPU
std::this_thread::yield();

// 休眠
std::this_thread::sleep_for(std::chrono::milliseconds(100));
```

**口述回答:**
"C++11 引入了标准线程库，在 thread 头文件中。创建线程很简单，用 std::thread 构造函数，传入函数和参数，线程就开始执行。线程创建后必须调用 join 等待结束，或者 detach 让它后台运行。join 会阻塞当前线程直到目标线程结束；detach 后线程变成守护线程，主线程结束程序就结束，不会等待它。可以用 get_id 获取线程 ID，yield 让出 CPU 时间片，sleep_for 休眠指定时间。注意向线程函数传引用参数要用 std::ref 包装。通常建议用 join 而不是 detach，或者用线程池管理线程生命周期。"

---

### Q72: 互斥锁的使用？

**A:**
```cpp
#include <mutex>

std::mutex mtx;
int shared_data = 0;

void increment() {
    std::lock_guard<std::mutex> lock(mtx);  // RAII 加锁
    ++shared_data;
}  // 自动解锁

// unique_lock 更灵活
void flexible() {
    std::unique_lock<std::mutex> lock(mtx);
    // 可手动解锁
    lock.unlock();
    // 重新加锁
    lock.lock();
}

// 尝试加锁
if (mtx.try_lock()) {
    // 成功
    mtx.unlock();
}
```

**口述回答:**
"互斥锁 mutex 用于保护共享数据，保证同一时刻只有一个线程能访问临界区。基本用法是 lock 加锁、unlock 解锁。但直接用 lock/unlock 不安全，如果中间抛异常就不会解锁，造成死锁。推荐用 RAII 包装类：lock_guard 最简单，构造时加锁，析构时解锁；unique_lock 更灵活，可以手动 unlock、重新 lock，还可以配合条件变量使用。try_lock 是非阻塞的尝试加锁，失败立即返回 false。C++17 的 scoped_lock 可以同时锁定多个互斥量且避免死锁。在性能敏感场景要注意锁的粒度，尽量减少临界区的范围和持有时间。"

---

### Q73: 读写锁的使用场景？

**A:** 读多写少场景，多个读者可并发，写者独占。

```cpp
#include <shared_mutex>

std::shared_mutex rw_mutex;
int data = 0;

void reader() {
    std::shared_lock<std::shared_mutex> lock(rw_mutex);  // 共享锁
    // 读取 data
}

void writer() {
    std::unique_lock<std::shared_mutex> lock(rw_mutex);  // 独占锁
    data = 42;
}
```

**口述回答:**
"读写锁 shared_mutex 是针对读多写少场景的优化。普通互斥锁不管读写都互斥，但实际上多个读操作可以并发，只有写操作需要独占。shared_mutex 支持两种加锁方式：共享锁用 shared_lock 包装，多个读者可以同时持有；独占锁用 unique_lock 包装，写者独占，与其他读者写者互斥。适用场景比如配置数据，读取频繁但很少修改；缓存数据，大量查询偶尔更新。使用时要注意写者饥饿问题，如果读请求不断可能写者一直拿不到锁，某些实现会有写者优先策略。如果读写比例不够悬殊，读写锁开销可能比普通互斥锁还大。"

---

### Q74: 条件变量的使用？

**A:**
```cpp
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> queue;

// 生产者
void producer() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(42);
    }
    cv.notify_one();  // 唤醒一个等待者
}

// 消费者
void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return !queue.empty(); });  // 等待条件
    int val = queue.front();
    queue.pop();
}
```

**注意**：必须用 unique_lock（wait 需要解锁再加锁）。

**口述回答:**
"条件变量用于线程间的同步等待，让线程可以等待某个条件成立再继续执行。配合互斥锁使用：等待方先加锁，然后调用 wait，wait 会原子地释放锁并进入等待状态；当其他线程调用 notify_one 或 notify_all 时，等待的线程被唤醒，重新获得锁，检查条件是否满足。wait 要传入一个 lambda 检查条件，因为可能有虚假唤醒，被唤醒后条件不一定满足。典型应用是生产者消费者：生产者放入数据后 notify_one，消费者 wait 直到有数据。必须用 unique_lock 不能用 lock_guard，因为 wait 需要能解锁和重新加锁。"

---

### Q75: 原子操作是什么？

**A:** 不可分割的操作，无需锁也能保证线程安全。

```cpp
#include <atomic>

std::atomic<int> counter(0);

// 原子操作
counter++;                           // 原子递增
counter.fetch_add(1);               // 同上
counter.store(10);                  // 原子存储
int val = counter.load();           // 原子加载
int old = counter.exchange(5);      // 原子交换

// CAS (Compare And Swap)
int expected = 10;
bool success = counter.compare_exchange_strong(expected, 20);
// 如果 counter == expected，则设为 20，返回 true
// 否则 expected 更新为当前值，返回 false
```

**口述回答:**
"原子操作是不可分割的操作，在执行过程中不会被其他线程打断。对于简单的计数器、标志位等，用原子变量可以避免加锁的开销。C++11 提供了 std::atomic 模板，支持整型和指针类型。常用操作有：load 读取，store 存储，fetch_add/fetch_sub 加减，exchange 交换。最重要的是 compare_exchange_strong，即 CAS 操作，如果当前值等于期望值就更新，否则把当前值写入期望值变量，这是无锁编程的基础。还有 compare_exchange_weak，可能虚假失败但在循环中效率更高。原子操作也可以指定内存序来控制可见性和重排。"

---

### Q76: 内存序（Memory Order）是什么？

**A:** 控制原子操作的内存可见性和指令重排。

| 内存序 | 说明 |
|-------|------|
| `memory_order_relaxed` | 只保证原子性 |
| `memory_order_acquire` | 后续读写不能重排到此之前 |
| `memory_order_release` | 之前读写不能重排到此之后 |
| `memory_order_acq_rel` | acquire + release |
| `memory_order_seq_cst` | 全局顺序一致（默认） |

```cpp
std::atomic<bool> ready(false);
int data = 0;

// 线程 1
data = 42;
ready.store(true, std::memory_order_release);

// 线程 2
while (!ready.load(std::memory_order_acquire));
assert(data == 42);  // 保证能看到 data = 42
```

**口述回答:**
"内存序控制原子操作的内存可见性和指令重排。现代 CPU 和编译器会对指令重排来优化性能，但在多线程环境下可能导致问题。C++ 定义了几种内存序：relaxed 最宽松，只保证操作本身原子性，不限制重排；acquire 用于读操作，后面的读写不会重排到它之前；release 用于写操作，前面的读写不会重排到它之后；acq_rel 同时具有 acquire 和 release 语义；seq_cst 是顺序一致性，最严格，也是默认值，所有线程看到的操作顺序一致。常见模式是生产者用 release 写，消费者用 acquire 读，保证消费者能看到生产者之前的所有写入。"

---

### Q77: 什么是无锁编程？

**A:** 使用原子操作代替锁实现线程安全。

```cpp
// 无锁栈（简化版）
template<typename T>
class LockFreeStack {
    struct Node {
        T data;
        Node* next;
    };
    std::atomic<Node*> head{nullptr};

public:
    void push(T val) {
        Node* new_node = new Node{val, nullptr};
        new_node->next = head.load();
        while (!head.compare_exchange_weak(new_node->next, new_node));
    }

    bool pop(T& val) {
        Node* old_head = head.load();
        while (old_head && !head.compare_exchange_weak(old_head, old_head->next));
        if (old_head) {
            val = old_head->data;
            delete old_head;  // 注意：实际需要延迟回收
            return true;
        }
        return false;
    }
};
```

**挑战**：ABA 问题、内存回收。

**口述回答:**
"无锁编程是使用原子操作代替锁来实现线程安全，核心是 CAS 操作。优点是避免了锁的开销、不会死锁、对中断和信号友好。典型的无锁结构有无锁栈、无锁队列。基本思路是读取当前状态、计算新状态、用 CAS 尝试更新，如果失败说明被其他线程修改了，重试。但无锁编程有很多挑战：ABA 问题，值从 A 变 B 又变回 A，CAS 检测不到中间的变化；内存回收困难，其他线程可能还在访问要删除的节点。解决方案有引用计数、风险指针、RCU 等。无锁编程很难写对，除非性能要求很高且有专业经验，否则用锁更安全。"

---

### Q78: 什么是 ABA 问题？

**A:** CAS 操作中，值从 A 变 B 再变 A，CAS 认为没变化。

```cpp
// 问题场景
// 线程1：读取 head = A
// 线程2：pop A, pop B, push A (新节点)
// 线程1：CAS 成功，但 A 已是不同对象
```

**解决方案**：
- 带版本号的指针（tagged pointer）
- 风险指针（Hazard Pointers）
- RCU（Read-Copy-Update）

**口述回答:**
"ABA 问题是无锁编程中的经典陷阱。假设线程 1 读取值是 A，准备做 CAS 把它改成 C。在这期间，线程 2 把 A 改成 B，又改回 A。线程 1 的 CAS 会成功，因为当前值确实是 A，但实际上状态已经变化过了。在链表操作中，这可能导致指向已被释放和重用的内存。解决方案有几种：带版本号的指针，也叫 tagged pointer，把计数器和指针打包，每次修改递增计数，即使值相同计数不同也能检测到；风险指针，声明正在使用的指针，其他线程不能回收；RCU，读操作无锁，写操作复制修改再替换，等所有读者退出后回收旧数据。"

---

### Q79: std::async 和 std::future 的使用？

**A:**
```cpp
#include <future>

// 异步执行
auto future = std::async(std::launch::async, [](){
    return 42;
});

// 获取结果（阻塞等待）
int result = future.get();

// std::promise 手动设置结果
std::promise<int> prom;
std::future<int> fut = prom.get_future();

std::thread t([&prom](){
    prom.set_value(100);
});

int val = fut.get();  // 等待结果
t.join();
```

**口述回答:**
"std::async 和 std::future 提供了一种高层的异步编程模型。async 接受一个函数，可以在新线程或当前线程中执行，返回一个 future 对象。future 代表一个将来会有的值，调用 get 会阻塞等待结果。async 可以指定启动策略：launch::async 强制在新线程执行，launch::deferred 延迟到 get 时在当前线程执行，默认由实现决定。std::promise 更底层，可以手动设置值，与 future 配合实现一次性的跨线程通信。promise 设置值后，对应的 future 的 get 就返回。注意 get 只能调用一次。如果需要多次获取或者多个等待者，可以用 shared_future。"

---

### Q80: 线程池的实现思路？

**A:**
```cpp
class ThreadPool {
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop = false;

public:
    ThreadPool(size_t n) {
        for (size_t i = 0; i < n; ++i) {
            workers.emplace_back([this]{
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx);
                        cv.wait(lock, [this]{ return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    template<typename F>
    void enqueue(F&& f) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            tasks.emplace(std::forward<F>(f));
        }
        cv.notify_one();
    }

    ~ThreadPool() {
        { std::lock_guard<std::mutex> lock(mtx); stop = true; }
        cv.notify_all();
        for (auto& w : workers) w.join();
    }
};
```

**口述回答:**
"线程池预先创建一组工作线程，任务提交到队列，工作线程循环从队列取任务执行。实现的核心组件有：任务队列，存放待执行的任务，通常是 std::function<void()>；工作线程数组；互斥锁保护任务队列；条件变量通知有新任务。工作线程的循环逻辑是：加锁，如果队列空就等条件变量，被唤醒后取任务，解锁，执行任务。提交任务时加锁放入队列，然后 notify_one 唤醒一个工作线程。析构时设置停止标志，notify_all 唤醒所有线程，等它们结束。进阶优化有：任务窃取、线程本地队列减少竞争、返回 future 获取结果、优雅关闭等待任务完成。"

---

### Q81: 什么是伪共享（False Sharing）？

**A:** 不同线程访问不同变量，但这些变量在同一缓存行，导致缓存失效。

```cpp
struct Bad {
    int a;  // 线程1访问
    int b;  // 线程2访问
};  // a, b 在同一缓存行，互相影响

// 解决：缓存行对齐
struct alignas(64) Good {
    int a;
};
struct alignas(64) Good2 {
    int b;
};

// 或使用 C++17 hardware_destructive_interference_size
struct Padded {
    alignas(std::hardware_destructive_interference_size) int a;
    alignas(std::hardware_destructive_interference_size) int b;
};
```

**口述回答:**
"伪共享是缓存层面的性能问题。CPU 缓存是按缓存行操作的，通常 64 字节。如果两个变量被不同线程频繁访问，虽然访问的是不同变量，但如果它们在同一缓存行，每次写入都会导致另一个 CPU 核的缓存行失效，造成不必要的缓存同步开销。比如一个结构体里有两个 int，分别被两个线程递增，虽然没有数据竞争，但会互相影响性能。解决方法是让这些变量分布在不同缓存行：用对齐让每个变量占满一个缓存行，或者添加填充字节。C++17 提供了 hardware_destructive_interference_size 常量表示缓存行大小，可以用 alignas 对齐到这个大小。"

---

### Q82: std::call_once 的作用？

**A:** 保证函数只被调用一次，用于线程安全的单例初始化。

```cpp
std::once_flag flag;
Singleton* instance = nullptr;

Singleton* getInstance() {
    std::call_once(flag, [](){
        instance = new Singleton();
    });
    return instance;
}
```

**口述回答:**
"std::call_once 保证一个函数只被调用一次，即使多个线程同时调用。它配合 std::once_flag 使用，once_flag 记录是否已执行过。这对于延迟初始化和单例模式非常有用。传统的双检锁实现单例有数据竞争的风险，而 call_once 内部处理了同步问题，使用起来更安全简洁。用法是：声明一个全局或静态的 once_flag，在需要初始化的地方调用 call_once，传入 flag 和初始化函数。第一个到达的线程执行函数，其他线程会阻塞等待，直到初始化完成。如果初始化抛异常，flag 不会被设置，下次调用还会重试。"

---

### Q83: volatile 与多线程？

**A:** `volatile` 不能保证线程安全！它只防止编译器优化，不保证原子性和内存可见性。

```cpp
volatile int flag = 0;  // 不安全！

// 正确做法
std::atomic<int> flag(0);
```

`volatile` 用于硬件寄存器访问，不用于多线程同步。

**口述回答:**
"这是一个常见的误解，volatile 在 C++ 中不能保证线程安全。volatile 的作用是告诉编译器不要优化这个变量的访问，每次都要从内存读取，不能用寄存器缓存。这主要用于内存映射的硬件寄存器，寄存器的值可能被硬件改变。但 volatile 不保证原子性，也不保证内存可见性，不能阻止 CPU 的指令重排。多线程同步需要用 std::atomic 或者互斥锁。Java 和 C# 的 volatile 有同步语义，但 C++ 的 volatile 没有。这是一个需要注意的语言差异。只有在嵌入式编程访问硬件寄存器时才需要 volatile。"

---

### Q84: 自旋锁 vs 互斥锁？

**A:**

| 特性 | 自旋锁 | 互斥锁 |
|-----|--------|--------|
| 等待方式 | 忙等（循环检查） | 阻塞（让出CPU） |
| 适用场景 | 短临界区 | 长临界区 |
| 开销 | 无上下文切换 | 有切换开销 |

```cpp
class SpinLock {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire));
    }
    void unlock() {
        flag.clear(std::memory_order_release);
    }
};
```

**口述回答:**
"自旋锁和互斥锁都用于保护临界区，但等待方式不同。互斥锁在获取失败时会让出 CPU，线程进入阻塞状态，由操作系统调度，有上下文切换的开销。自旋锁获取失败时会在循环里不断尝试，占着 CPU 不放，没有上下文切换。所以自旋锁适合临界区很短、锁持有时间短的场景，等待时间比上下文切换开销还小。互斥锁适合临界区较长、可能有 I/O 等待的场景。自旋锁的实现用 atomic_flag 的 test_and_set，设置成功就获得锁，否则循环重试。注意单核 CPU 上自旋锁会浪费 CPU，因为持有锁的线程没机会执行。"

---

### Q85: 什么是屏障（Barrier）？

**A:** 让多个线程在某点同步，都到达后才继续。

```cpp
// C++20 std::barrier
#include <barrier>

std::barrier barrier(3);  // 3 个线程

void worker() {
    // 阶段 1 工作
    barrier.arrive_and_wait();  // 等所有线程到达
    // 阶段 2 工作
}
```

**口述回答:**
"屏障 Barrier 是一种同步原语，让多个线程在某个点上同步，所有线程都到达屏障后才能继续执行。典型应用是分阶段并行计算，比如每个线程处理一部分数据，都处理完后进入下一阶段汇总。如果一个线程先完成，它在屏障等待其他线程；所有线程到齐后，屏障打开，大家继续下一阶段。C++20 提供了 std::barrier 和 std::latch。barrier 可以重复使用，适合多阶段同步；latch 是一次性的，计数减到零后就不再阻塞。使用时创建 barrier 指定线程数，每个线程工作完调用 arrive_and_wait，等所有线程到达后一起释放。"

---

### Q86: 如何实现读写锁？

**A:**
```cpp
class RWLock {
    std::mutex mtx;
    std::condition_variable cv;
    int readers = 0;
    bool writing = false;

public:
    void read_lock() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]{ return !writing; });
        ++readers;
    }

    void read_unlock() {
        std::lock_guard<std::mutex> lock(mtx);
        if (--readers == 0) cv.notify_all();
    }

    void write_lock() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]{ return !writing && readers == 0; });
        writing = true;
    }

    void write_unlock() {
        std::lock_guard<std::mutex> lock(mtx);
        writing = false;
        cv.notify_all();
    }
};
```

**口述回答:**
"手动实现读写锁的核心是管理读者计数和写者状态。用一个互斥锁保护状态变量，用条件变量来等待。读加锁时：等待没有写者，然后读者计数加一。读解锁时：读者计数减一，如果变成零就唤醒可能等待的写者。写加锁时：等待没有写者且没有读者，然后设置写者标志。写解锁时：清除写者标志，唤醒所有等待者。这个实现可能有写者饥饿问题，不断来的读者让写者一直等。可以加一个写者等待标志，有写者等待时新读者也等待。实际使用中直接用 C++17 的 shared_mutex 更可靠。"

---

### Q87: 什么是协程？C++20 协程？

**A:** 可暂停和恢复的函数，比线程更轻量。

```cpp
// C++20 协程
#include <coroutine>

struct Task {
    struct promise_type {
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

Task myCoroutine() {
    std::cout << "Hello\n";
    co_await std::suspend_always{};  // 暂停
    std::cout << "World\n";
}
```

用于异步 I/O、生成器、状态机等。

**口述回答:**
"协程是可以暂停和恢复执行的函数，比线程更轻量。线程切换需要操作系统参与，开销大；协程切换只是保存恢复寄存器，在用户态完成。C++20 引入了无栈协程，通过 co_await、co_yield、co_return 三个关键字使用。co_await 暂停协程等待一个异步操作完成；co_yield 产出一个值然后暂停，适合生成器；co_return 返回值并结束。C++20 协程是底层机制，需要自己定义 promise_type 来控制行为，比较复杂。实际使用通常配合库如 Boost.Asio 的协程支持。协程非常适合异步 I/O，可以用同步的写法实现异步逻辑，代码可读性好。"

---

### Q88: 生产者消费者问题实现？

**A:**
```cpp
template<typename T>
class BlockingQueue {
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable not_empty, not_full;
    size_t max_size;

public:
    BlockingQueue(size_t max) : max_size(max) {}

    void push(T item) {
        std::unique_lock<std::mutex> lock(mtx);
        not_full.wait(lock, [this]{ return queue.size() < max_size; });
        queue.push(std::move(item));
        not_empty.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        not_empty.wait(lock, [this]{ return !queue.empty(); });
        T item = std::move(queue.front());
        queue.pop();
        not_full.notify_one();
        return item;
    }
};
```

**口述回答:**
"生产者消费者是经典的并发模式，一方产生数据放入缓冲区，另一方从缓冲区取数据处理，缓冲区是共享资源。实现要点是：用队列作为缓冲区，用互斥锁保护队列，用两个条件变量分别处理队列满和队列空的情况。生产者流程：加锁，如果队列满就在 not_full 条件变量上等待，放入数据，解锁，通知 not_empty 唤醒消费者。消费者流程：加锁，如果队列空就在 not_empty 上等待，取出数据，解锁，通知 not_full 唤醒可能等待的生产者。条件变量的 wait 要传入判断条件的 lambda，防止虚假唤醒。"

---

### Q89: 什么是 happens-before 关系？

**A:** 如果操作 A happens-before 操作 B，则 A 的结果对 B 可见。

**建立 happens-before 的方式**：
- 同一线程内，按程序顺序
- 解锁 happens-before 后续加锁
- release 操作 happens-before 对应的 acquire
- join 前的操作 happens-before join 后的操作

**口述回答:**
"happens-before 是 C++ 内存模型中定义的顺序关系，如果操作 A happens-before 操作 B，那么 A 的结果对 B 可见。这不一定是时间上的先后，而是逻辑上的可见性保证。建立 happens-before 的方式有：同一线程内按程序顺序执行，前面的 happens-before 后面的；一个线程的 unlock 操作 happens-before 后续任何线程的 lock 操作；release 语义的写 happens-before acquire 语义的读；线程的所有操作 happens-before 对它 join 后的操作；call_once 中的函数执行 happens-before 其他调用返回。理解 happens-before 是理解并发程序正确性的基础。"

---

### Q90: double-checked locking 问题？

**A:** 传统 DCL 有数据竞争问题：

```cpp
// 错误示例
Singleton* instance;
Singleton* getInstance() {
    if (instance == nullptr) {        // 第一次检查
        std::lock_guard<std::mutex> lock(mtx);
        if (instance == nullptr) {    // 第二次检查
            instance = new Singleton();  // 可能重排序！
        }
    }
    return instance;
}

// 正确做法：使用 atomic
std::atomic<Singleton*> instance;
Singleton* getInstance() {
    Singleton* tmp = instance.load(std::memory_order_acquire);
    if (tmp == nullptr) {
        std::lock_guard<std::mutex> lock(mtx);
        tmp = instance.load(std::memory_order_relaxed);
        if (tmp == nullptr) {
            tmp = new Singleton();
            instance.store(tmp, std::memory_order_release);
        }
    }
    return tmp;
}

// 最简单：C++11 局部静态变量
Singleton& getInstance() {
    static Singleton instance;  // 线程安全
    return instance;
}
```

**口述回答:**
"双检锁是一种优化单例模式的技术，先检查实例是否存在，不存在才加锁再检查一次。但传统的实现有问题：new 操作分为分配内存、调用构造函数、赋值指针三步，编译器或 CPU 可能重排为分配、赋值、构造。这样另一个线程可能看到非空但未构造完成的对象。解决方法是用 atomic：读取用 acquire 语义，保证能看到完整构造的对象；存储用 release 语义，保证构造完成后再更新指针。但 C++11 后最简单的方法是用局部静态变量，标准保证局部静态变量的初始化是线程安全的，只会执行一次，代码也最简洁。"

---

## 五、数据结构与算法 (15题)

### Q91: STL 容器的时间复杂度？

**A:**

| 容器 | 访问 | 插入/删除 | 查找 |
|-----|------|----------|------|
| vector | O(1) | O(n)/末尾O(1) | O(n) |
| deque | O(1) | 首尾O(1) | O(n) |
| list | O(n) | O(1) | O(n) |
| set/map | - | O(log n) | O(log n) |
| unordered_set/map | - | O(1)平均 | O(1)平均 |

**口述回答:**
"STL 容器的时间复杂度要熟记。vector 是连续数组，随机访问 O(1)，尾部插入删除均摊 O(1)，中间插入删除 O(n)。deque 双端队列，两端操作 O(1)，随机访问 O(1)。list 双向链表，任意位置插入删除 O(1)，但访问和查找是 O(n)。set 和 map 基于红黑树，插入删除查找都是 O(log n)，有序遍历。unordered_set 和 unordered_map 基于哈希表，平均 O(1)，最坏 O(n)，无序。选择容器时要根据操作频率来选：频繁随机访问用 vector，频繁头尾操作用 deque，频繁中间插入删除用 list，需要有序用 set/map，只要快速查找用 unordered 系列。"

---

### Q92: vector 的实现原理？

**A:** 连续内存数组，自动扩容。

- `size()`：当前元素数
- `capacity()`：已分配空间
- 扩容：通常 1.5x 或 2x，申请新内存，拷贝/移动元素，释放旧内存

```cpp
// 预分配避免频繁扩容
std::vector<int> v;
v.reserve(1000);  // 预分配

// 收缩内存
v.shrink_to_fit();
```

**口述回答:**
"vector 是最常用的容器，内部是一块连续的动态数组。它有两个重要概念：size 是当前元素数量，capacity 是已分配的空间能容纳的元素数。当 size 达到 capacity 需要扩容时，vector 会申请更大的内存，通常是 1.5 倍或 2 倍，然后把旧元素移动或拷贝过去，释放旧内存。扩容开销较大，所以如果知道大概需要多少元素，最好用 reserve 预先分配空间。push_back 均摊是 O(1)，虽然单次扩容是 O(n)，但平摊下来每个元素平均移动次数是常数。shrink_to_fit 可以请求释放多余容量，但不保证一定执行。"

---

### Q93: map 和 unordered_map 的区别？

**A:**

| 特性 | map | unordered_map |
|-----|-----|---------------|
| 底层 | 红黑树 | 哈希表 |
| 有序 | 是 | 否 |
| 查找 | O(log n) | O(1) 平均 |
| 迭代 | 有序遍历 | 无序 |

```cpp
// map：需要有序或范围查询
std::map<int, std::string> ordered;

// unordered_map：只需快速查找
std::unordered_map<int, std::string> fast;
```

**口述回答:**
"map 和 unordered_map 都是键值对容器，但底层实现不同。map 基于红黑树，保持元素有序，插入查找删除都是 O(log n)，可以按顺序遍历，可以进行范围查询。unordered_map 基于哈希表，元素无序，平均情况下插入查找删除是 O(1)，但最坏是 O(n)，遍历顺序不确定。选择依据：如果需要有序性、范围查询，或者没有好的哈希函数，用 map；如果只需要快速查找，数据量大，用 unordered_map 更快。另外 map 的迭代器稳定，插入删除不影响其他迭代器；unordered_map 在 rehash 时所有迭代器失效。"

---

### Q94: 红黑树的性质？

**A:**
1. 节点是红色或黑色
2. 根是黑色
3. 叶子（NIL）是黑色
4. 红节点的子节点都是黑色
5. 从任一节点到叶子的所有路径，黑色节点数相同

**特点**：近似平衡，插入/删除/查找 O(log n)。

**口述回答:**
"红黑树是一种自平衡二叉搜索树，STL 的 map 和 set 就是用它实现的。它有五条性质保证平衡：每个节点是红色或黑色；根节点是黑色；所有叶子节点是黑色的空节点 NIL；红节点的两个子节点都是黑色，也就是不能有连续的红节点；从任意节点到其所有叶子节点的路径上，黑色节点数量相同。这些性质保证了最长路径不超过最短路径的两倍，所以是近似平衡的，最坏情况下操作复杂度也是 O(log n)。相比 AVL 树，红黑树平衡条件更宽松，旋转次数更少，插入删除效率更高，所以被广泛使用。"

---

### Q95: 哈希表冲突解决方法？

**A:**
1. **链地址法**：每个桶一个链表（STL 使用）
2. **开放定址法**：冲突后探测下一位置
   - 线性探测
   - 二次探测
   - 双重哈希

```cpp
// 自定义哈希函数
struct MyHash {
    size_t operator()(const MyKey& k) const {
        return std::hash<int>()(k.id) ^ std::hash<std::string>()(k.name);
    }
};
std::unordered_map<MyKey, Value, MyHash> map;
```

**口述回答:**
"哈希冲突是不同的键算出相同的哈希值，主要有两类解决方法。链地址法是每个桶挂一个链表，冲突的元素加到链表里，STL 的 unordered_map 就用这个方法。查找时先定位桶，再遍历链表。开放定址法是冲突时按某种规则找下一个位置：线性探测是依次往后找；二次探测是按 1、4、9 这样的平方距离找；双重哈希是用另一个哈希函数算步长。开放定址法在负载因子低时效率高，但删除复杂，要标记而不是真删。链地址法实现简单，适合负载因子高的情况。好的哈希函数应该让键均匀分布，减少冲突。"

---

### Q96: 堆的实现和应用？

**A:** 完全二叉树，父节点大于（或小于）子节点。

```cpp
// STL priority_queue（默认最大堆）
std::priority_queue<int> maxHeap;
std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

// 堆操作
std::vector<int> v = {3, 1, 4, 1, 5};
std::make_heap(v.begin(), v.end());   // 建堆 O(n)
std::push_heap(v.begin(), v.end());   // 插入 O(log n)
std::pop_heap(v.begin(), v.end());    // 删除最大 O(log n)
```

**应用**：优先队列、Top-K、堆排序、定时器管理。

**口述回答:**
"堆是完全二叉树，最大堆的每个节点都不小于其子节点，最小堆则相反。因为是完全二叉树，可以用数组存储，节点 i 的左子节点是 2i+1，右子节点是 2i+2，父节点是 (i-1)/2。主要操作有：上浮是插入元素后向上调整，O(log n)；下沉是删除堆顶后把最后元素放到顶部再向下调整，O(log n)；建堆是从最后一个非叶子节点开始依次下沉，O(n)。STL 提供了 priority_queue，默认是最大堆，用 greater 可以变成最小堆。也可以用 make_heap、push_heap、pop_heap 直接操作 vector。应用包括优先队列、找 Top-K 问题、堆排序、定时器按到期时间管理。"

---

### Q97: 快速排序的实现和优化？

**A:**
```cpp
void quickSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    // 三数取中选 pivot
    int mid = left + (right - left) / 2;
    if (arr[left] > arr[mid]) swap(arr[left], arr[mid]);
    if (arr[left] > arr[right]) swap(arr[left], arr[right]);
    if (arr[mid] > arr[right]) swap(arr[mid], arr[right]);
    swap(arr[mid], arr[right - 1]);
    int pivot = arr[right - 1];

    int i = left, j = right - 1;
    while (true) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i < j) swap(arr[i], arr[j]);
        else break;
    }
    swap(arr[i], arr[right - 1]);

    quickSort(arr, left, i - 1);
    quickSort(arr, i + 1, right);
}
```

**优化**：三数取中、小数组用插入排序、尾递归优化。

**口述回答:**
"快速排序是分治算法，选择一个基准元素，把数组分成小于基准和大于基准两部分，递归排序。平均 O(n log n)，但最坏是 O(n²)，发生在数组已有序且每次选的基准是最值。优化方法有几种：三数取中选基准，取首尾中三个数的中位数作为基准，避免最坏情况；小数组切换到插入排序，因为插入排序在小规模数据上更快；尾递归优化，先递归短的那半，长的改成循环，避免栈太深。partition 实现上可以用双指针，一个从左往右找大于基准的，一个从右往左找小于基准的，然后交换。STL 的 sort 是 introsort，结合了快排、堆排和插入排序。"

---

### Q98: 二分查找的变体？

**A:**
```cpp
// 查找第一个等于 target 的位置
int lowerBound(vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) left = mid + 1;
        else right = mid;
    }
    return left;
}

// 查找第一个大于 target 的位置
int upperBound(vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= target) left = mid + 1;
        else right = mid;
    }
    return left;
}

// STL
std::lower_bound(arr.begin(), arr.end(), target);
std::upper_bound(arr.begin(), arr.end(), target);
```

**口述回答:**
"二分查找的基本形式是在有序数组中找目标值，但面试中更常见的是变体。lower_bound 找第一个大于等于目标的位置，也就是插入位置；upper_bound 找第一个大于目标的位置。实现时关键是处理好边界：用左闭右开区间 [left, right)，循环条件是 left < right，如果 mid 的值小于目标，left = mid + 1，否则 right = mid。这样找的是第一个满足条件的位置。还可以变形为找最后一个满足条件的，或者找旋转数组的最小值，找峰值元素等。二分的核心是每次排除一半的搜索空间，只要能判断目标在哪半边，就能用二分。"

---

### Q99: 图的存储方式？

**A:**

| 方式 | 空间 | 查边 | 适用 |
|-----|------|------|------|
| 邻接矩阵 | O(V²) | O(1) | 稠密图 |
| 邻接表 | O(V+E) | O(degree) | 稀疏图 |

```cpp
// 邻接矩阵
vector<vector<int>> matrix(n, vector<int>(n, 0));

// 邻接表
vector<vector<int>> adj(n);
adj[u].push_back(v);

// 带权邻接表
vector<vector<pair<int, int>>> adj(n);  // {neighbor, weight}
```

**口述回答:**
"图的存储主要有两种方式。邻接矩阵用二维数组 matrix[i][j] 表示 i 到 j 有没有边或者边的权重，空间 O(V²)，查询两点是否有边是 O(1)，适合稠密图，或者需要频繁查询边的场景。邻接表用每个顶点维护一个邻居列表，空间 O(V+E)，遍历某点所有邻居是 O(degree)，适合稀疏图。在 C++ 中，邻接矩阵用 vector<vector<int>>，邻接表也用 vector<vector<int>>，每个 adj[u] 存储 u 的所有邻居。带权图的邻接表可以用 vector<vector<pair<int,int>>>，存储邻居和边权。实际中大多数图都是稀疏的，所以邻接表更常用。"

---

### Q100: BFS 和 DFS 的区别和应用？

**A:**

| 特性 | BFS | DFS |
|-----|-----|-----|
| 数据结构 | 队列 | 栈/递归 |
| 空间 | O(V) | O(h) |
| 最短路径 | 无权图可求 | 不能 |

```cpp
// BFS
void bfs(int start) {
    queue<int> q;
    vector<bool> visited(n, false);
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

// DFS
void dfs(int u, vector<bool>& visited) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs(v, visited);
    }
}
```

**口述回答:**
"BFS 和 DFS 是图遍历的两种基本方式。BFS 广度优先，用队列实现，先访问所有邻居再访问邻居的邻居，一层一层向外扩展。特点是找到的路径是最短的（无权图），空间复杂度是 O(V)。DFS 深度优先，用递归或栈实现，沿一条路走到底再回溯。特点是代码简单，空间是 O(h) 取决于深度，但找到的路径不一定最短。应用上，BFS 适合最短路径、层序遍历、广播传播等；DFS 适合路径搜索、连通性检测、拓扑排序、回溯算法等。无向图检测环用并查集或 DFS，有向图检测环用 DFS 的三色标记法。"

---

### Q101: 最短路径算法？

**A:**

| 算法 | 复杂度 | 适用 |
|-----|--------|------|
| Dijkstra | O((V+E)logV) | 非负权 |
| Bellman-Ford | O(VE) | 可有负权 |
| Floyd | O(V³) | 所有点对 |

```cpp
// Dijkstra
vector<int> dijkstra(int start) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

**口述回答:**
"最短路径算法要根据场景选择。Dijkstra 适用于非负权图，从起点开始，每次选距离最近的未访问节点，更新其邻居的距离，用优先队列优化后复杂度是 O((V+E)log V)，不能处理负权边。Bellman-Ford 可以处理负权边，对所有边进行 V-1 轮松弛，还能检测负权环，复杂度 O(VE)。SPFA 是 Bellman-Ford 的优化，用队列只处理距离更新过的点，平均效果好但最坏还是 O(VE)。Floyd 用于求所有点对之间的最短路径，动态规划思想，三层循环，复杂度 O(V³)。单源最短路首选 Dijkstra，有负权用 Bellman-Ford，多源用 Floyd。"

---

### Q102: 动态规划的基本思想？

**A:** 将问题分解为重叠子问题，保存子问题结果避免重复计算。

**步骤**：
1. 定义状态
2. 写状态转移方程
3. 确定边界条件
4. 确定计算顺序

```cpp
// 斐波那契
int fib(int n) {
    if (n <= 1) return n;
    vector<int> dp(n + 1);
    dp[0] = 0; dp[1] = 1;
    for (int i = 2; i <= n; ++i)
        dp[i] = dp[i-1] + dp[i-2];
    return dp[n];
}

// 空间优化
int fib_opt(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int c = a + b;
        a = b; b = c;
    }
    return b;
}
```

**口述回答:**
"动态规划的核心思想是将大问题分解成重叠的子问题，保存子问题的解避免重复计算。解题步骤：首先定义状态，确定 dp[i] 或 dp[i][j] 表示什么含义；然后找状态转移方程，当前状态如何由之前的状态推导；接着确定边界条件，最简单的子问题的解；最后考虑计算顺序，保证计算当前状态时依赖的状态已经计算过。优化上，如果当前状态只依赖有限的前几个状态，可以用滚动数组降低空间复杂度，比如斐波那契只需要两个变量。判断能否用 DP：问题有最优子结构，子问题的最优解能组成原问题的最优解；有重叠子问题，同一子问题被多次求解。"

---

### Q103: 常见 DP 问题类型？

**A:**
- **背包问题**：01背包、完全背包、多重背包
- **最长子序列**：LCS、LIS
- **区间 DP**：矩阵链乘、合并石子
- **树形 DP**：树的最大独立集
- **状态压缩 DP**：旅行商问题

```cpp
// 01背包
int knapsack(vector<int>& weights, vector<int>& values, int W) {
    int n = weights.size();
    vector<int> dp(W + 1, 0);
    for (int i = 0; i < n; ++i) {
        for (int w = W; w >= weights[i]; --w) {
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    return dp[W];
}
```

**口述回答:**
"动态规划题目可以分几类。背包问题：01 背包每个物品最多选一次，完全背包可以无限选，多重背包每个物品有数量限制。序列问题：最长递增子序列 LIS、最长公共子序列 LCS、最长回文子序列等。区间 DP：合并石子、矩阵链乘，状态是区间两端点。树形 DP：在树结构上做 DP，比如树的最大独立集。状态压缩 DP：状态用位掩码表示，如旅行商问题。01 背包的状态转移是 dp[w] = max(dp[w], dp[w-weight[i]] + value[i])，注意倒序遍历容量保证每个物品只选一次；完全背包正序遍历。LCS 的状态转移是两个字符相等就等于左上角加一，不等就取左边和上边的最大值。"

---

### Q104: 字符串匹配算法？

**A:**

| 算法 | 复杂度 | 特点 |
|-----|--------|------|
| 暴力 | O(nm) | 简单 |
| KMP | O(n+m) | 利用前缀函数 |
| Boyer-Moore | O(n/m) 最好 | 从右往左匹配 |
| Rabin-Karp | O(n+m) 平均 | 哈希滚动 |

```cpp
// KMP
vector<int> computePrefix(const string& pattern) {
    int m = pattern.size();
    vector<int> pi(m, 0);
    for (int i = 1, j = 0; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) j = pi[j-1];
        if (pattern[i] == pattern[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

int kmp(const string& text, const string& pattern) {
    auto pi = computePrefix(pattern);
    for (int i = 0, j = 0; i < text.size(); ++i) {
        while (j > 0 && text[i] != pattern[j]) j = pi[j-1];
        if (text[i] == pattern[j]) ++j;
        if (j == pattern.size()) return i - j + 1;
    }
    return -1;
}
```

**口述回答:**
"字符串匹配是在文本中找模式串的问题。暴力算法是依次比对，最坏 O(nm)。KMP 算法的核心是利用模式串的前缀信息，当匹配失败时不回退文本指针，只回退模式串指针到一个合适的位置继续比较，复杂度 O(n+m)。KMP 需要预处理模式串得到 next 数组，也叫前缀函数，表示每个位置最长的相等的真前缀和真后缀长度。Boyer-Moore 从右往左比较，失配时跳过更多字符，实践中往往比 KMP 快。Rabin-Karp 用滚动哈希，每次 O(1) 计算下一个窗口的哈希值，哈希相等再验证，适合多模式匹配。实际应用中可以直接用 string::find 或 strstr。"

---

### Q105: Trie 树的实现？

**A:**
```cpp
class Trie {
    struct Node {
        Node* children[26] = {};
        bool isEnd = false;
    };
    Node* root = new Node();

public:
    void insert(const string& word) {
        Node* node = root;
        for (char c : word) {
            int i = c - 'a';
            if (!node->children[i])
                node->children[i] = new Node();
            node = node->children[i];
        }
        node->isEnd = true;
    }

    bool search(const string& word) {
        Node* node = find(word);
        return node && node->isEnd;
    }

    bool startsWith(const string& prefix) {
        return find(prefix) != nullptr;
    }

private:
    Node* find(const string& s) {
        Node* node = root;
        for (char c : s) {
            int i = c - 'a';
            if (!node->children[i]) return nullptr;
            node = node->children[i];
        }
        return node;
    }
};
```

用于前缀搜索、自动补全、词典实现。

**口述回答:**
"Trie 树也叫前缀树或字典树，专门用于字符串的存储和检索。每个节点代表一个字符，从根到某节点的路径组成一个前缀。节点有一个子节点数组（26 个字母对应 26 个槽位），还有一个标记表示是否是某个单词的结尾。插入操作是从根开始，沿着每个字符向下走，没有就创建新节点，最后标记结束。查找是沿着字符向下走，看最后是否有结束标记。前缀查询只需要走到前缀末尾看能不能到达。Trie 的优点是前缀相关操作高效，适合自动补全、拼写检查、IP 路由等。缺点是空间开销大，可以用压缩 Trie 优化。"

---

## 六、Boost.Asio 专题 (10题)

### Q106: io_context 的作用？

**A:** `io_context` 是 Asio 的核心，事件循环和 I/O 服务的调度器。

```cpp
#include <boost/asio.hpp>

boost::asio::io_context io;

// 添加任务
io.post([]{ std::cout << "Task 1\n"; });
io.dispatch([]{ std::cout << "Task 2\n"; });

// 运行事件循环
io.run();  // 阻塞直到所有任务完成

// 多线程运行
std::vector<std::thread> threads;
for (int i = 0; i < 4; ++i) {
    threads.emplace_back([&io]{ io.run(); });
}
```

**口述回答:**
"io_context 是 Boost.Asio 的核心，相当于事件循环。所有异步操作都注册到 io_context，它负责调度和分发这些操作的完成事件。使用流程是：创建 io_context，创建 socket 等 I/O 对象并关联到 io_context，发起异步操作并传入回调，调用 io_context.run() 进入事件循环。run() 会阻塞，不断处理完成的异步操作、调用回调，直到没有待处理的工作。可以在多个线程中调用同一个 io_context 的 run()，实现多线程处理，Asio 会保证线程安全。也可以用 post() 把任务投递到 io_context 在事件循环中执行。"

---

### Q107: post、dispatch、defer 的区别？

**A:**

| 方法 | 行为 |
|-----|------|
| `post` | 总是排队到 io_context 稍后执行 |
| `dispatch` | 如果在 io_context 线程则立即执行，否则排队 |
| `defer` | 类似 post，但保证在当前处理器完成后执行 |

```cpp
io.post([]{});     // 总是延迟
io.dispatch([]{});  // 可能立即执行
asio::defer(io, []{});  // 延迟到当前任务后
```

**口述回答:**
"post、dispatch 和 defer 都是向 io_context 投递任务，但执行时机不同。post 总是把任务放入队列稍后执行，即使当前就在 io_context 的线程中也不会立即执行，保证了调用者可以先完成其他事情。dispatch 会检查：如果当前就在 io_context 线程中就立即执行，否则和 post 一样放入队列。dispatch 在回调中调用时可以减少一次排队，但要注意递归深度。defer 和 post 类似总是排队，但它保证在当前处理器完成后才执行，用于确保某些清理工作最后执行。日常使用 post 最多，dispatch 用于性能优化，defer 较少用。"

---

### Q108: strand 的作用和使用？

**A:** 保证在 strand 上投递的任务串行执行，无需加锁。

```cpp
boost::asio::io_context io;
boost::asio::io_context::strand strand(io);

// 多线程安全操作共享数据
int shared_data = 0;

strand.post([&]{ shared_data++; });  // 串行执行
strand.post([&]{ shared_data++; });  // 不会并发

// 绑定到异步操作
socket.async_read_some(buffer,
    boost::asio::bind_executor(strand, handler));
```

**口述回答:**
"strand 是 Asio 提供的一种同步机制，保证通过它提交的任务串行执行，不会并发。当多线程运行 io_context 时，多个回调可能同时在不同线程执行，如果它们操作同一个连接的数据就会有竞争。strand 解决这个问题：把该连接的所有回调都通过 strand 提交，这些回调就会一个接一个执行，不需要加锁。用法是创建 strand 对象，然后用 post 或 bind_executor 把回调绑定到 strand。同一个 strand 的任务串行，不同 strand 的任务可以并发。这比用锁更高效，因为任务在同一线程执行就不需要切换，只有在不同线程时才排队。"

---

### Q109: 异步 TCP 服务器示例？

**A:**
```cpp
class Session : public std::enable_shared_from_this<Session> {
    tcp::socket socket_;
    std::array<char, 1024> buffer_;

public:
    Session(tcp::socket socket) : socket_(std::move(socket)) {}

    void start() { do_read(); }

private:
    void do_read() {
        auto self = shared_from_this();
        socket_.async_read_some(boost::asio::buffer(buffer_),
            [this, self](boost::system::error_code ec, size_t length) {
                if (!ec) {
                    do_write(length);
                }
            });
    }

    void do_write(size_t length) {
        auto self = shared_from_this();
        boost::asio::async_write(socket_, boost::asio::buffer(buffer_, length),
            [this, self](boost::system::error_code ec, size_t) {
                if (!ec) {
                    do_read();
                }
            });
    }
};

class Server {
    tcp::acceptor acceptor_;

public:
    Server(boost::asio::io_context& io, short port)
        : acceptor_(io, tcp::endpoint(tcp::v4(), port)) {
        do_accept();
    }

private:
    void do_accept() {
        acceptor_.async_accept([this](auto ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket))->start();
            }
            do_accept();
        });
    }
};
```

**口述回答:**
"异步 TCP 服务器的典型模式是这样的：Server 类持有 acceptor 监听端口，循环调用 async_accept；每接受一个连接，创建一个 Session 对象处理它；Session 继承 enable_shared_from_this，在异步操作的回调中用 shared_from_this() 保持自身存活。Session 的处理循环是：async_read_some 读取数据，在回调中处理数据，async_write 发送响应，在回调中继续读取。关键点是用 shared_ptr 管理 Session 生命周期，在所有异步操作完成前不会被销毁；回调中捕获 shared_from_this() 而不是 this 裸指针；错误处理，读写出错时让 Session 自然销毁，关闭连接。"

---

### Q110: async_read 和 async_read_some 的区别？

**A:**
- `async_read_some`：读取 1 到 buffer_size 字节，可能不满
- `async_read`：读取直到满足条件（填满、遇到分隔符等）

```cpp
// 读取一些数据
socket.async_read_some(buffer, handler);

// 读取直到填满
boost::asio::async_read(socket, buffer, handler);

// 读取直到遇到 '\n'
boost::asio::async_read_until(socket, streambuf, '\n', handler);

// 读取精确 100 字节
boost::asio::async_read(socket, boost::asio::buffer(data, 100), handler);
```

**口述回答:**
"async_read_some 和 async_read 是 Asio 中两个常用的读操作，区别很重要。async_read_some 是 socket 的成员函数，只保证读取至少 1 字节，可能读取到 buffer 大小，也可能更少，具体取决于内核缓冲区有多少数据。这是最底层的操作，需要应用层自己处理不完整的消息。async_read 是自由函数，会反复调用底层读取直到满足条件：填满整个 buffer，或者用 completion condition 指定条件。async_read_until 读取直到遇到分隔符。应用层协议处理时，通常用 async_read 读取固定长度的消息头，用 async_read_until 读取以分隔符结束的消息。"

---

### Q111: steady_timer 的使用？

**A:**
```cpp
boost::asio::steady_timer timer(io);

// 设置超时
timer.expires_after(std::chrono::seconds(5));
timer.async_wait([](const boost::system::error_code& ec) {
    if (!ec) {
        std::cout << "Timer expired\n";
    } else if (ec == boost::asio::error::operation_aborted) {
        std::cout << "Timer cancelled\n";
    }
});

// 取消定时器
timer.cancel();

// 周期定时器
void periodic_task(boost::asio::steady_timer& timer) {
    timer.expires_after(std::chrono::seconds(1));
    timer.async_wait([&timer](auto ec) {
        if (!ec) {
            std::cout << "Tick\n";
            periodic_task(timer);
        }
    });
}
```

**口述回答:**
"steady_timer 是 Asio 提供的定时器，基于 chrono 的 steady_clock，不受系统时间调整影响。用法是：创建 timer 关联到 io_context，用 expires_after 设置多久后触发或 expires_at 设置绝对时间，然后 async_wait 等待触发。回调会收到 error_code，如果是成功就是正常到期，如果是 operation_aborted 就是被取消了。可以调用 cancel() 取消定时器。实现周期定时器的方法是在回调中重新设置到期时间并再次 async_wait。常用场景包括：超时控制，在发起读写的同时启动定时器，先触发的那个取消另一个；心跳检测；定时任务。"

---

### Q112: 如何处理连接超时？

**A:**
```cpp
class Connection {
    tcp::socket socket_;
    boost::asio::steady_timer timer_;

public:
    void connect_with_timeout(const tcp::endpoint& ep, int timeout_sec) {
        timer_.expires_after(std::chrono::seconds(timeout_sec));

        timer_.async_wait([this](auto ec) {
            if (!ec) socket_.close();  // 超时关闭
        });

        socket_.async_connect(ep, [this](auto ec) {
            timer_.cancel();  // 连接成功取消定时器
            if (!ec) {
                // 连接成功
            }
        });
    }
};
```

**口述回答:**
"Asio 的异步操作本身没有超时机制，需要配合定时器实现。典型模式是同时发起异步操作和定时器，谁先完成就取消另一个。比如连接超时：先设置定时器，然后发起 async_connect；如果定时器先触发，关闭 socket，这会导致 connect 操作以 operation_aborted 错误完成；如果连接先成功，在回调中取消定时器。读写超时也类似：每次读写前重置定时器的到期时间，读写完成后取消定时器；定时器触发说明超时了，关闭 socket。可以封装成通用的超时机制，或者使用 Asio 的 async_compose 组合异步操作。"

---

### Q113: buffer 的使用方式？

**A:**
```cpp
// 从数组
char arr[128];
auto buf1 = boost::asio::buffer(arr);

// 从 vector
std::vector<char> vec(128);
auto buf2 = boost::asio::buffer(vec);

// 指定大小
auto buf3 = boost::asio::buffer(arr, 64);

// 动态缓冲区
boost::asio::streambuf streambuf;
std::ostream os(&streambuf);
os << "Hello";

// 多个缓冲区（scatter/gather I/O）
std::vector<boost::asio::const_buffer> buffers = {
    boost::asio::buffer(header),
    boost::asio::buffer(body)
};
boost::asio::async_write(socket, buffers, handler);
```

**口述回答:**
"Asio 的 buffer 是对内存的轻量级包装，只存指针和大小，不拥有内存。创建 buffer 的方式有很多：从数组 buffer(arr) 会自动推导大小；从 vector buffer(vec)；指定大小 buffer(arr, size)。buffer 分为 mutable_buffer 可写和 const_buffer 只读。streambuf 是动态 buffer，可以像流一样读写，适合协议解析。Scatter/Gather I/O 是一次操作多个 buffer：可以把多个 buffer 放入 vector 传给 async_write，系统会依次发送；读取也可以分散到多个 buffer。关键点是 buffer 不管理内存生命周期，你要保证在异步操作完成前底层内存有效，通常用 shared_ptr 或者把 buffer 作为成员。"

---

### Q114: 如何实现优雅关闭？

**A:**
```cpp
void graceful_shutdown(tcp::socket& socket) {
    boost::system::error_code ec;

    // 关闭发送端
    socket.shutdown(tcp::socket::shutdown_send, ec);

    // 继续读取直到对方关闭
    std::array<char, 128> buf;
    while (socket.read_some(boost::asio::buffer(buf), ec) > 0);

    // 关闭 socket
    socket.close(ec);
}

// 异步版本
void async_graceful_shutdown(std::shared_ptr<tcp::socket> socket) {
    socket->shutdown(tcp::socket::shutdown_send);

    auto buf = std::make_shared<std::array<char, 128>>();
    socket->async_read_some(boost::asio::buffer(*buf),
        [socket, buf](auto ec, auto) {
            if (ec) socket->close();
            else async_graceful_shutdown(socket);
        });
}
```

**口述回答:**
"TCP 的优雅关闭是让双方都正常结束，不丢数据。流程是：发起关闭的一方先调用 shutdown(shutdown_send) 关闭发送端，发送 FIN，表示我不再发数据了；然后继续读取，直到对方也关闭发送端，read 返回 0 或 EOF 错误；最后 close socket。这样可以确保对方发送中的数据都收到了。如果直接 close 而不 shutdown，可能发送 RST 给对方，对方未处理的数据就丢了。在 Asio 中，调用 socket.shutdown(tcp::socket::shutdown_send)，然后继续 async_read，在收到 EOF 或错误后 close。如果有超时需求，可以配合定时器在一定时间内没完成就强制 close。"

---

### Q115: Asio 协程支持？

**A:**
```cpp
// C++20 协程
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>

boost::asio::awaitable<void> echo(tcp::socket socket) {
    try {
        char data[1024];
        for (;;) {
            size_t n = co_await socket.async_read_some(
                boost::asio::buffer(data), boost::asio::use_awaitable);
            co_await boost::asio::async_write(socket,
                boost::asio::buffer(data, n), boost::asio::use_awaitable);
        }
    } catch (std::exception& e) {
        // 处理异常
    }
}

boost::asio::awaitable<void> listener() {
    auto executor = co_await boost::asio::this_coro::executor;
    tcp::acceptor acceptor(executor, {tcp::v4(), 8080});
    for (;;) {
        tcp::socket socket = co_await acceptor.async_accept(
            boost::asio::use_awaitable);
        boost::asio::co_spawn(executor, echo(std::move(socket)),
            boost::asio::detached);
    }
}
```

**口述回答:**
"Asio 从 Boost 1.77 开始支持 C++20 协程，让异步代码写起来像同步一样自然。关键类型是 awaitable<T>，表示可以 co_await 的异步操作的返回类型。使用时在异步操作后面传入 use_awaitable 作为 completion token，就可以用 co_await 等待。比如 co_await socket.async_read_some(buffer, use_awaitable)。协程函数返回 awaitable<T>。用 co_spawn 启动协程，需要指定 executor 和协程函数，可以选择 detached 忽略结果或者用 callback 获取结果。协程的好处是代码流程清晰，没有回调地狱，错误处理可以用 try-catch。性能上和回调差不多，但代码可读性大大提高。"

---

## 七、设计模式 (5题)

### Q116: 单例模式的线程安全实现？

**A:**
```cpp
// 方法1：C++11 静态局部变量（推荐）
class Singleton {
    Singleton() = default;
public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

// 方法2：std::call_once
class Singleton2 {
    static std::unique_ptr<Singleton2> instance;
    static std::once_flag flag;
    Singleton2() = default;
public:
    static Singleton2& getInstance() {
        std::call_once(flag, []{ instance.reset(new Singleton2()); });
        return *instance;
    }
};

// 方法3：模板单例
template<typename T>
class SingletonHolder {
public:
    static T& getInstance() {
        static T instance;
        return instance;
    }
};
```

**口述回答:**
"单例模式保证一个类只有一个实例。C++11 之后最推荐的实现方式是局部静态变量：在 getInstance 函数中定义 static 局部变量，标准保证它的初始化是线程安全的，而且是懒加载的，第一次调用时才创建。代码简洁，不需要锁，也不需要 double-checked locking。另一种方式是 call_once 配合 once_flag，显式控制只初始化一次。如果需要更多控制，比如可以销毁重建，可以用指针配合 mutex。记得禁用拷贝构造和赋值运算符防止复制。模板单例可以复用逻辑：SingletonHolder<T>::getInstance() 返回任意类型的单例。"

---

### Q117: 观察者模式的实现？

**A:**
```cpp
#include <functional>
#include <vector>
#include <algorithm>

template<typename... Args>
class Signal {
    std::vector<std::function<void(Args...)>> slots;

public:
    void connect(std::function<void(Args...)> slot) {
        slots.push_back(std::move(slot));
    }

    void emit(Args... args) {
        for (auto& slot : slots) {
            slot(args...);
        }
    }
};

// 使用
Signal<int, const std::string&> onDataReceived;
onDataReceived.connect([](int id, const std::string& msg) {
    std::cout << "Observer 1: " << id << " " << msg << "\n";
});
onDataReceived.emit(1, "Hello");
```

**口述回答:**
"观察者模式是一种一对多的依赖关系，当被观察者状态改变时，所有观察者都会收到通知。现代 C++ 可以用 std::function 来实现灵活的观察者。定义一个 Signal 模板类，内部维护一个 function 的 vector。connect 方法添加观察者，emit 方法遍历调用所有观察者。Signal 可以模板化支持任意参数类型。这种实现比传统的接口继承方式更灵活，观察者可以是普通函数、lambda、成员函数、函数对象。如果需要取消订阅功能，connect 可以返回一个 ID 或连接对象，用于后续 disconnect。要注意线程安全和观察者生命周期管理的问题。"

---

### Q118: 工厂模式的实现？

**A:**
```cpp
// 简单工厂
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape { void draw() override { } };
class Square : public Shape { void draw() override { } };

class ShapeFactory {
public:
    static std::unique_ptr<Shape> create(const std::string& type) {
        if (type == "circle") return std::make_unique<Circle>();
        if (type == "square") return std::make_unique<Square>();
        return nullptr;
    }
};

// 注册式工厂（更灵活）
class Factory {
    std::map<std::string, std::function<std::unique_ptr<Shape>()>> creators;

public:
    void registerType(const std::string& name,
                      std::function<std::unique_ptr<Shape>()> creator) {
        creators[name] = std::move(creator);
    }

    std::unique_ptr<Shape> create(const std::string& name) {
        if (auto it = creators.find(name); it != creators.end()) {
            return it->second();
        }
        return nullptr;
    }
};
```

**口述回答:**
"工厂模式用于封装对象创建的逻辑。简单工厂是一个静态方法，根据参数创建不同类型的对象，问题是添加新类型需要修改工厂代码。工厂方法是定义创建对象的接口，具体工厂子类决定创建什么。抽象工厂创建一系列相关的对象。在现代 C++ 中，注册式工厂很灵活：维护一个 map，键是类型名，值是创建函数；提供 register 方法注册新类型；create 方法根据类型名查找并调用创建函数。创建函数可以是 lambda 或 make_unique。这样添加新类型不需要修改工厂代码，只需要注册。工厂返回 unique_ptr 表达所有权转移。"

---

### Q119: 对象池模式的实现？

**A:**
```cpp
template<typename T>
class ObjectPool {
    std::vector<std::unique_ptr<T>> pool;
    std::vector<T*> available;
    std::mutex mtx;

public:
    ObjectPool(size_t initial_size) {
        for (size_t i = 0; i < initial_size; ++i) {
            pool.push_back(std::make_unique<T>());
            available.push_back(pool.back().get());
        }
    }

    T* acquire() {
        std::lock_guard<std::mutex> lock(mtx);
        if (available.empty()) {
            pool.push_back(std::make_unique<T>());
            return pool.back().get();
        }
        T* obj = available.back();
        available.pop_back();
        return obj;
    }

    void release(T* obj) {
        std::lock_guard<std::mutex> lock(mtx);
        available.push_back(obj);
    }

    // RAII 包装
    class Borrowed {
        ObjectPool& pool;
        T* obj;
    public:
        Borrowed(ObjectPool& p) : pool(p), obj(p.acquire()) {}
        ~Borrowed() { pool.release(obj); }
        T* operator->() { return obj; }
    };
};
```

**口述回答:**
"对象池模式用于复用对象，避免频繁创建销毁的开销。适用场景是对象创建成本高、需要频繁使用、数量可控，比如数据库连接、线程、网络连接。实现思路是：预先创建一批对象放入池中；acquire 获取对象，池中有就取出，没有就新建；release 归还对象，放回池中而不是销毁。用 vector 存所有对象保证不释放，用另一个 vector 记录可用的对象指针。需要加锁保证线程安全。更好的做法是提供 RAII 包装，构造时 acquire，析构时 release，防止忘记归还。也可以用 unique_ptr 配合自定义 deleter，deleter 中调用 release。"

---

### Q120: CRTP（奇异递归模板模式）？

**A:** 基类模板以派生类作为模板参数，实现静态多态。

```cpp
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }

    // 静态多态，无虚函数开销
    static void static_interface() {
        Derived::static_implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() {
        std::cout << "Derived implementation\n";
    }

    static void static_implementation() {
        std::cout << "Derived static\n";
    }
};

// 应用：enable_shared_from_this
class MyClass : public std::enable_shared_from_this<MyClass> {
public:
    std::shared_ptr<MyClass> getShared() {
        return shared_from_this();
    }
};
```

**口述回答:**
"CRTP 是 Curiously Recurring Template Pattern，基类模板以派生类作为模板参数。典型形式是 class Derived : public Base<Derived>。这样基类可以通过 static_cast<Derived*>(this) 访问派生类的成员，实现静态多态。和虚函数的动态多态相比，CRTP 在编译期解析调用，没有虚表查找的开销。典型应用是 enable_shared_from_this，它需要知道派生类的类型才能返回正确的 shared_ptr。另一个应用是 mixin，通过 CRTP 向派生类注入功能。CRTP 也用于实现静态接口，在基类中调用派生类必须提供的方法。缺点是代码可读性稍差，不支持运行时多态。"

---

## 八、项目深度问题 (8题)

### Q121: 如何进行性能调优？

**A:**

**1. 定位瓶颈**：
- CPU profiling：perf、VTune、gprof
- 内存分析：Valgrind、AddressSanitizer
- I/O 分析：strace、iostat

**2. 常见优化方向**：
- 算法优化：降低时间复杂度
- 内存优化：减少分配、提高缓存命中
- I/O 优化：批量处理、异步、缓冲
- 并发优化：减少锁竞争、无锁结构

**3. C++ 特定优化**：
```cpp
// 移动语义避免拷贝
std::vector<std::string> vec;
vec.push_back(std::move(str));

// 预分配
vec.reserve(1000);

// 避免频繁分配
std::string buf;
buf.reserve(1024);

// 内联和 constexpr
constexpr int compute() { return 42; }
```

**口述回答:**
"性能调优首先要找到瓶颈，不要凭感觉优化。CPU 密集型问题用 profiler 分析热点函数，Linux 上有 perf、gprof，Windows 有 Visual Studio Profiler。内存问题用 Valgrind 的 massif 或 AddressSanitizer。I/O 问题用 strace 看系统调用。找到瓶颈后针对性优化：算法优化是最有效的，比如 O(n²) 改成 O(n log n)；内存优化减少分配次数、使用预分配、注意缓存友好；I/O 优化用缓冲、批量操作、异步 I/O；并发优化减少锁竞争、用无锁结构、避免伪共享。C++ 特定优化包括移动语义避免拷贝、reserve 预分配、constexpr 编译期计算等。"

---

### Q122: 如何排查内存问题？

**A:**

**工具**：
- **Valgrind**：`valgrind --leak-check=full ./prog`
- **AddressSanitizer**：`-fsanitize=address`
- **mtrace**：跟踪 malloc/free

**常见问题**：
1. **内存泄漏**：分配后未释放
2. **野指针**：访问已释放内存
3. **重复释放**：double free
4. **缓冲区溢出**：越界访问

**预防措施**：
```cpp
// 使用智能指针
auto p = std::make_unique<int>(42);

// RAII 管理资源
class File {
    FILE* fp;
public:
    File(const char* path) : fp(fopen(path, "r")) {}
    ~File() { if (fp) fclose(fp); }
};

// 使用容器代替原始数组
std::vector<int> arr(100);
```

**口述回答:**
"内存问题是 C++ 中最常见也最难排查的问题。工具方面：Valgrind 的 memcheck 可以检测泄漏、越界、未初始化使用等；AddressSanitizer 编译时加 -fsanitize=address，运行时检测，性能比 Valgrind 好很多；Visual Studio 的 CRT 调试可以检测泄漏。常见问题：内存泄漏是分配后没释放，用智能指针自动管理；野指针是访问已释放的内存，释放后置空指针可以早发现；重复释放，用智能指针避免；越界访问，用 vector.at() 或 AddressSanitizer 检测。预防是最重要的：用 RAII 和智能指针管理资源，用容器代替原始数组，用 string 代替 char*。"

---

### Q123: 如何排查 crash 问题？

**A:**

**1. 生成 core dump**：
```bash
ulimit -c unlimited
./program  # 崩溃后生成 core 文件
gdb ./program core
```

**2. 分析调用栈**：
```bash
(gdb) bt        # 查看调用栈
(gdb) frame 2   # 切换到第2帧
(gdb) info locals  # 查看局部变量
```

**3. 常见崩溃原因**：
- 空指针解引用
- 数组越界
- 栈溢出（递归太深）
- 野指针
- 多线程竞争

**4. 预防**：
```cpp
// 断言检查
assert(ptr != nullptr);

// 边界检查
arr.at(i);  // 抛异常而非未定义行为
```

**口述回答:**
"程序崩溃时首先要获取崩溃现场信息。Linux 上设置 ulimit -c unlimited 开启 core dump，崩溃后用 gdb 调试 core 文件，bt 命令查看调用栈。Windows 上可以配置生成 dump 文件，用 WinDbg 或 Visual Studio 分析。常见崩溃原因：空指针解引用，检查指针前先判空；数组越界，用 at() 或 AddressSanitizer；栈溢出，检查递归深度或大数组；野指针，释放后置空；多线程竞争，用 ThreadSanitizer 检测。分析时先看崩溃点的代码，检查指针、数组、参数是否合法。如果是第三方库崩溃，往上找调用栈看传了什么参数。加断言 assert 可以尽早发现问题。"

---

### Q124: 多线程问题如何调试？

**A:**

**工具**：
- **ThreadSanitizer**：`-fsanitize=thread`
- **Helgrind**：Valgrind 工具
- **GDB**：`info threads`、`thread N`

**常见问题**：
1. **数据竞争**：多线程无同步访问共享数据
2. **死锁**：循环等待
3. **活锁**：不断重试但无进展
4. **竞态条件**：执行顺序依赖

**调试技巧**：
```cpp
// 日志记录
std::cerr << std::this_thread::get_id() << ": " << msg << std::endl;

// 原子变量检查
std::atomic<int> debug_counter(0);

// 使用 TSan 检测
// g++ -fsanitize=thread -g program.cpp
```

**口述回答:**
"多线程问题最难调试，因为具有不确定性，可能偶发难以复现。工具方面：ThreadSanitizer 编译时加 -fsanitize=thread，运行时检测数据竞争；Helgrind 是 Valgrind 的线程检测工具；GDB 可以调试多线程，info threads 列出线程，thread N 切换线程。常见问题：数据竞争是多线程无同步访问共享数据，用锁或原子变量保护；死锁是循环等待，按固定顺序加锁或用 scoped_lock；活锁是不断重试但无进展；竞态条件是结果依赖执行顺序。调试技巧：加日志输出线程 ID 和关键操作；尽量复现，增加线程数或加 sleep 制造冲突；代码审查关注共享数据的访问。"

---

### Q125: 网络问题如何排查？

**A:**

**工具**：
- **tcpdump**：抓包 `tcpdump -i eth0 port 8080 -w capture.pcap`
- **Wireshark**：分析抓包
- **netstat/ss**：连接状态 `ss -tunap`
- **lsof**：文件描述符 `lsof -i :8080`

**常见问题**：
1. 连接超时：检查网络、防火墙
2. 连接被拒：服务未启动、端口错误
3. 数据错误：协议解析问题
4. 性能问题：Nagle、缓冲区大小

```bash
# 检查连接状态
ss -s
netstat -an | grep TIME_WAIT | wc -l

# 检查端口监听
ss -tlnp | grep 8080
```

**口述回答:**
"网络问题排查需要用多种工具。tcpdump 和 Wireshark 抓包分析，可以看到实际发送和接收的数据包；netstat 或 ss 查看连接状态、端口监听；lsof 查看进程打开的网络连接；telnet 或 nc 测试端口连通性。常见问题：连接超时，检查防火墙、路由、服务是否启动；连接被拒绝，服务未监听或端口错误；数据收发异常，抓包分析协议是否正确；性能问题，检查 TIME_WAIT 数量、缓冲区设置、Nagle 算法。排查流程：先确认网络连通 ping；再确认端口监听 ss；然后抓包看数据交互；最后分析应用层协议。日志和监控也很重要。"

---

### Q126: 如何设计高可用系统？

**A:**

**原则**：
1. **冗余**：多副本、多实例
2. **故障检测**：心跳、健康检查
3. **故障转移**：自动切换
4. **限流熔断**：防止雪崩

**实现**：
- 负载均衡：Nginx、HAProxy
- 服务发现：Consul、etcd
- 熔断器模式：
```cpp
class CircuitBreaker {
    enum State { CLOSED, OPEN, HALF_OPEN };
    State state = CLOSED;
    int failures = 0;
    std::chrono::steady_clock::time_point lastFailure;

public:
    bool allowRequest() {
        if (state == CLOSED) return true;
        if (state == OPEN) {
            if (elapsed() > timeout) {
                state = HALF_OPEN;
                return true;
            }
            return false;
        }
        return true;  // HALF_OPEN
    }

    void recordSuccess() { state = CLOSED; failures = 0; }
    void recordFailure() {
        if (++failures >= threshold) state = OPEN;
    }
};
```

**口述回答:**
"高可用系统设计的核心是消除单点故障。冗余是基础：服务多实例部署，数据多副本存储，网络多路径。故障检测用心跳和健康检查，要能及时发现问题。故障转移要自动化，用负载均衡器检测后端健康状态，不健康的自动移出。熔断器模式防止故障扩散：服务调用失败率超过阈值就熔断，快速失败而不是等待超时；过一段时间尝试恢复。限流保护系统不被压垮。数据一致性要考虑：强一致性牺牲可用性，最终一致性接受短暂不一致。监控告警要完善，快速发现和响应问题。测试要包括故障注入测试，验证系统在各种故障下的行为。"

---

### Q127: 如何进行代码审查？

**A:**

**关注点**：

1. **正确性**：
   - 边界条件处理
   - 错误处理
   - 资源管理

2. **安全性**：
   - 输入验证
   - 缓冲区溢出
   - 注入攻击

3. **性能**：
   - 时间复杂度
   - 内存使用
   - 不必要的拷贝

4. **可维护性**：
   - 代码清晰度
   - 命名规范
   - 适当的抽象

**检查清单**：
```
□ 是否处理所有错误情况？
□ 资源是否正确释放？
□ 是否有数据竞争？
□ 边界条件是否正确？
□ 是否有内存泄漏？
□ 是否遵循项目规范？
```

**口述回答:**
"代码审查是保证代码质量的重要环节。审查重点包括几个方面：正确性，逻辑是否正确，边界条件是否处理，错误情况是否考虑；安全性，输入是否验证，是否有注入风险，敏感数据是否保护；性能，时间空间复杂度是否合理，是否有不必要的拷贝，锁的范围是否最小；可维护性，代码是否清晰，命名是否表意，是否有必要的注释；资源管理，内存是否正确释放，文件句柄是否关闭，是否有泄漏风险；并发安全，共享数据是否正确同步，是否可能死锁。审查时要具体指出问题和建议改进方案，保持建设性的态度。"

---

### Q128: 如何设计测试策略？

**A:**

**测试金字塔**：
- **单元测试**（底层，最多）：测试单个函数/类
- **集成测试**（中层）：测试模块交互
- **系统测试**（顶层，最少）：端到端测试

**C++ 测试框架**：
- Google Test
- Catch2
- doctest

```cpp
// Google Test 示例
#include <gtest/gtest.h>

TEST(CalculatorTest, Addition) {
    Calculator calc;
    EXPECT_EQ(calc.add(2, 3), 5);
    EXPECT_EQ(calc.add(-1, 1), 0);
}

// Mock 对象
class MockDatabase : public Database {
public:
    MOCK_METHOD(bool, connect, (), (override));
    MOCK_METHOD(std::string, query, (const std::string&), (override));
};

TEST(ServiceTest, UsesDatabase) {
    MockDatabase mockDb;
    EXPECT_CALL(mockDb, query("SELECT 1")).WillOnce(Return("1"));

    Service svc(&mockDb);
    EXPECT_EQ(svc.getData(), "1");
}
```

**测试覆盖率**：
```bash
# 使用 gcov/lcov
g++ --coverage -o test test.cpp
./test
gcov test.cpp
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory out
```

**口述回答:**
"测试策略应该遵循测试金字塔模型。底层是单元测试，数量最多，测试单个函数或类的功能，用 Google Test 或 Catch2 框架，应该快速、独立、可重复。中层是集成测试，测试多个组件之间的交互，比如测试数据库访问层、网络通信。顶层是端到端测试，模拟真实用户场景，覆盖整个系统流程。Mock 对象用于隔离依赖，比如 Mock 数据库、Mock 网络，让测试更可控。代码覆盖率用 gcov/lcov 统计，目标通常是 80% 以上，但不要为了覆盖率而写无意义的测试。测试应该作为开发流程的一部分，提交代码前运行单元测试，持续集成上运行所有测试。"

---

## 总结

本文档涵盖了 C++ 客户端/后端开发面试的核心知识点：

| 主题 | 题数 | 重点 |
|-----|------|------|
| C++ 基础 | 30 | 内存管理、智能指针、模板、新特性 |
| 操作系统 | 20 | 进程线程、虚拟内存、IPC |
| 计算机网络 | 20 | TCP/IP、Socket、HTTP |
| 并发编程 | 20 | 线程同步、原子操作、无锁编程 |
| 数据结构算法 | 15 | STL、排序查找、图算法、DP |
| Boost.Asio | 10 | io_context、异步 I/O、协程 |
| 设计模式 | 5 | 单例、观察者、工厂、对象池 |
| 项目深度 | 8 | 性能调优、调试、测试 |

**面试建议**：
1. 理解原理，不只是背诵
2. 动手实践，写代码验证
3. 结合项目经验举例
4. 关注性能和安全性
5. 保持学习新特性（C++17/20/23）

祝面试顺利！ 
