#pragma once
#include <iostream>
#include <iomanip>

template <typename... Members>
constexpr std::size_t sumMemberSize() 
{
    return (0 + ... + sizeof(Members));
}

template <typename T, typename... Members>
void checkStructPadding(const char* name) 
{
    constexpr std::size_t realSize = sizeof(T);
    constexpr std::size_t expectedSize = sumMemberSize<Members...>();
    std::cout << "Analyse de " << name << "\n";
    std::cout << "Taille réelle  = " << realSize << " octets\n";
    std::cout << "Taille attendue = " << expectedSize << " octets\n";
    if (realSize > expectedSize)
        std::cout << "Padding détecté (" << (realSize - expectedSize) << " octets)\n\n";
    else
        std::cout << "Pas de padding\n\n";
}

template <typename T>
void analyse_layout(const char* name) 
{
    std::cout << "Layout de " << name << " (taille = " << sizeof(T) << " octets)\n";
    std::cout << "---------------\n";
}

#define ANALYSE_FIELD(T, field) \
    std::cout << std::setw(15) << #field << " offset = " << offsetof(T, field) \
              << ", size = " << sizeof(((T*)nullptr)->field) << " octets\n";

template <typename T>
void checkStructPaddingRecursive() 
{
    analyse_layout<T>(typeid(T).name());
}

template <typename T, typename... Members>
void checkStructPaddingWithSubtypes(const char* name) 
{
    checkStructPadding<T, Members...>(name);
    ((checkStructPaddingRecursive<Members>()), ...);
}
