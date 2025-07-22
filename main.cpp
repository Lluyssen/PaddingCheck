#include "padding.hpp"


struct A
{
    char a;
    int b;
    char c;
};

struct B
{
    int b;
    char a;
    char c;
};

struct C
{
    char a;
    char c;
    int b;
};

int main(void)
{
    std::cout << sizeof(A) << std::endl;
    std::cout << sizeof(B) << std::endl;
    std::cout << sizeof(C) << std::endl;
    
    std::cout << "\n--- A struct ---" << std::endl;
    analyse_layout<A>("A Struct");
    ANALYSE_FIELD(A, a);
    ANALYSE_FIELD(A, b);
    ANALYSE_FIELD(A, c);

    std::cout << "\n--- B struct ---" << std::endl;
    analyse_layout<B>("B Struct");
    ANALYSE_FIELD(B, a);
    ANALYSE_FIELD(B, b);
    ANALYSE_FIELD(B, c);

    std::cout << "\n--- C struct ---" << std::endl;
    analyse_layout<C>("C Struct");
    ANALYSE_FIELD(C, a);
    ANALYSE_FIELD(C, b);
    ANALYSE_FIELD(C, c);

    std::cout << "\n--- Attendu ---" << std::endl;
    checkStructPadding<A, char, int, char>("A");
    checkStructPadding<B, int, char, char>("B");
    checkStructPadding<C, char, char, int>("C");

    return 0;
}