#include <iostream>

#pragma region Auxiliary Classes

class BaseClass
{
  public:
    inline void print()
    {
        std::cout << "Base Class" << std::endl;
    }
};

class DerivedClass : public BaseClass
{
  public:
    inline void print()
    {
        std::cout << "Derived Class" << std::endl;
    }
};

class BasePolymorphicClass
{
  public:
    inline virtual void Print()
    {
        std::cout << "Base Polimorphic Class" << std::endl;
    }
};

class DerivedPolymorphicClass : public BasePolymorphicClass
{
  public:
    inline virtual void Print() override
    {
        std::cout << "Derived Polimorphic Class" << std::endl;
    }
};

#pragma endregion Auxiliary Classes

/**
 * Static Cast Test
 * 
 * Use static_cast for ordinary type conversions.
 */
void StaticCastTest()
{

    double pi = 3.14159265358979323846264338327950;
    int casted_pi = static_cast<int>(pi);
    std::cout << "double pi: " << pi << "\n"
              << "casted_pi: " << casted_pi << std::endl;

    {

        BaseClass *bC;
        bC->print();
        DerivedClass *dC;
        dC->print();

        // Upcast
        BaseClass *bC_dc = static_cast<BaseClass *>(dC);
        bC_dc->print();

        // Downcast
        DerivedClass *dC_dc = static_cast<DerivedClass *>(bC);
        dC_dc->print();
    }
}

/**
 * Dynamic Cast Test
 * 
 * Use dynamic_cast for converting pointers/references within an inheritance hierarchy.
 */
void DynamicCastTest()
{
    BasePolymorphicClass *base1 = new BasePolymorphicClass;
    BasePolymorphicClass *base2 = new DerivedPolymorphicClass;

    base1->Print();
    base2->Print();

    auto derived1 = dynamic_cast<DerivedPolymorphicClass*>(base1);
    if(derived1){
        derived1->Print();
    }  

    auto derived2 = dynamic_cast<DerivedPolymorphicClass*>(base2);
    if (derived2) {
        derived2->Print();
    }

    auto base3 = dynamic_cast<BasePolymorphicClass*>(derived2);
    
    if (base3) {
        base3->Print();
    }
    
    
    
}

/**
 * Reinterpret Cast test
 * 
 * Use reinterpret_cast for low-level reinterpreting of bit patterns.
 * Use with extreme caution.
 */
void ReinterpretCastTest()
{

    int *a = new int();
    void *b = reinterpret_cast<void *>(a);
    int *c = reinterpret_cast<int *>(b);

    if (*a == *c)
    {
        std::cout << "Cast Worked" << std::endl;
    }
}

/**
 * Const cast test
 * 
 * Use const_cast for casting away const/volatile. 
 * Avoid this unless you are stuck using a const-incorrect API.
 */
void ConstCastTest()
{
    int non_const_variable = 0;

    const int *const_ptr = &non_const_variable;
    const int &const_ref = non_const_variable;

    // error: assignment of read-only location ‘* const_ptr’
    // *const_ptr = 1;

    // error: assignment of read-only reference ‘const_ref’
    // const_ref = 2;

    auto not_const_ptr = const_cast<int *>(const_ptr);
    *not_const_ptr = 1;
    std::cout << "non_const_variable: " << non_const_variable << std::endl;

    const_cast<int &>(const_ref) = 2;
    std::cout << "non_const_variable: " << non_const_variable << std::endl;
}

/**
 * Regular cast
 * 
 * Classic C casts make no distinction between
 * static_cast, reinterpret_cast, const_cast and dynamic_cast.
 */
void RegularCastTest()
{

    double pi = 3.14159265358979323846264338327950;
    int not_pi = (int)pi;

    std::cout << "pi: " << pi << "\n"
              << "not pi: " << not_pi << std::endl;
}

int main()
{

    StaticCastTest();
    DynamicCastTest();
    ReinterpretCastTest();
    ConstCastTest();
    RegularCastTest();
    return 0;
}