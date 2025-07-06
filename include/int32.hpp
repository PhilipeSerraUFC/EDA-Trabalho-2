#ifndef INT32_HPP
#define INT32_HPP

#include <iostream>
#include <string>
#include <stdint.h>

using namespace std;

// Declaração da constante INF
extern const struct Int32 INF;

struct Int32{

    uint32_t value;
    bool is_pos_inf;
    bool is_neg_inf;

    Int32();
    Int32(int value_);
    Int32(int value_, bool is_pos_inf_, bool is_neg_inf_);

    // Operadores de membro
    Int32 operator+(int value_) const;
    Int32 operator+(const Int32& integer) const;
    Int32 operator*(int value_) const;
    Int32 operator*(const Int32& integer) const;
    Int32 operator<<(int value_) const;
    Int32 operator<<(const Int32& integer) const;
    Int32 operator>>(int value_) const;
    Int32 operator>>(const Int32& integer) const;
    Int32 operator-() const;
    Int32 operator-(int value_) const;
    Int32 operator-(const Int32& integer) const;
    Int32 operator^(int value_) const;
    Int32 operator^(const Int32& integer) const;
    
    // Operadores de comparação
    bool operator==(int value_) const;
    bool operator==(const Int32& integer) const;
    bool operator<=(int value_) const;
    bool operator<=(const Int32& integer) const;
    bool operator>=(int value_) const;
    bool operator>=(const Int32& integer) const;
    bool operator>(int value_) const;
    bool operator>(const Int32& integer) const;
    bool operator<(int value_) const;
    bool operator<(const Int32& integer) const;
    bool operator!=(int value_) const;
    bool operator!=(const Int32& integer) const;
    
    // Operadores de módulo
    int operator%(const Int32& integer) const;
    int operator%(int value_) const;
    
    // Operador de conversão explícita
    explicit operator int() const;
    
    // Operador de stream 
    friend ostream& operator<<(ostream& os, const Int32& integer);
};

// Operadores globais
string to_string(const Int32& integer);
bool operator==(int value_, const Int32& integer);
Int32 operator+(int value_, const Int32& integer);
Int32 operator%(int value_, const Int32& integer);
Int32 operator*(int value_, const Int32& integer);
Int32 operator-(int value_, const Int32& integer);
bool operator<=(int value_, const Int32& integer);
bool operator>=(int value_, const Int32& integer);
bool operator>(int value_, const Int32& integer);
bool operator<(int value_, const Int32& integer);
Int32 operator^(int value_, const Int32& integer);

#endif
