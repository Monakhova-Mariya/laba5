#include <iostream>

using std::cout;
using std::endl;
using std::string;

// Класс - целое число
class Int
{
private:
    int d;

public:
    // Конструктор
    Int(int _d) : d(_d) { }

    // Методы доступа: Геттер и Сеттер
    int Get() { return d; }
    void Set(int _d)
    {
        d = _d;
    }

    // Метод Print()
    void Print(string msg)
    {
        cout << msg.c_str() << d << endl;
    }
};

// Класс умного указателя на обобщенный тип T
template <typename T>
class SmartPtr
{
private:
    T* p; // указатель на обобщенный тип T
    int count; // количество копий

public:
    // Конструктор
    SmartPtr(T* _p = nullptr)
    {
        // Записываем 0 - копий нет
        count = 0;
        p = _p;
    }

    // Конструктор копирования
    SmartPtr(const SmartPtr& obj)
    {
        // Создается копия
        p = obj.p;

        // Увеличить счетчик
        count++;
    }

    // Оператор копирования
    SmartPtr operator=(const SmartPtr& obj)
    {
        // Создается копия
        p = obj.p;
        count++;
        return *this;
    }

    // Деструктор - уничтожает объект-оригинал,
    // объекты-копии не уничтожаются.
    ~SmartPtr()
    {
        // Если есть объект и нету копий,
        // то просто уничтожаем это объект.
        if ((p != nullptr) && (count == 0))
        {
            cout << "Delete object" << endl;
            delete[] p;
        }
        else
        {
            // иначе, просто уничтожается копия
            cout << "Delete copy" << endl;
            count--; // уменьшить счетчик копий
        }
    }

    // Переопределить оператор -> доступа по указателю
    T* operator->()
    {
        return p;
    }
};

void main()
{
    // 1. Создать объект класса Int
    Int* obj1 = new Int(10);
    obj1->Print("obj1: ");

    // 2. Инициализировать этим объектом умный указатель
    SmartPtr<Int> ptr(obj1);
    ptr->Print("ptr->obj: ");

    // 3. Создать копию умного указателя
    SmartPtr<Int> ptr2 = ptr; // вызывается конструктор копирования
    ptr2->Print("ptr2->obj: ");

    // 4. Создать еще одну копию умного указателя
    SmartPtr<Int> ptr3;
    ptr3 = ptr2; // вызывается оператор копирования
    ptr3->Print("ptr3->obj: ");
}
