#include "../include/int32.hpp"
#include <iostream>
#include <string>

using namespace std;

// Definição da constante INF
const Int32 INF = Int32(0, true, false);

Int32::Int32() {
    value = 0;
    is_pos_inf = false;
    is_neg_inf = false;
}

Int32::Int32(int value_) {
    value = value_;
    is_pos_inf = false;
    is_neg_inf = false;
}

Int32::Int32(int value_, bool is_pos_inf_, bool is_neg_inf_) {
    value = value_;
    is_pos_inf = is_pos_inf_;
    is_neg_inf = is_neg_inf_;
}

Int32 Int32::operator+(int value_) const {
    return Int32(value + value_, is_pos_inf, is_neg_inf);
}

Int32 Int32::operator+(const Int32& integer) const {
    return Int32(value + integer.value, is_pos_inf || integer.is_pos_inf, is_neg_inf || integer.is_neg_inf);
}

Int32 Int32::operator*(int value_) const {
    return Int32(value * value_, is_pos_inf, is_neg_inf);
}

Int32 Int32::operator*(const Int32& integer) const {
    return Int32(value * integer.value, is_pos_inf || integer.is_pos_inf, is_neg_inf || integer.is_neg_inf);
}

Int32 Int32::operator<<(int value_) const {
    return Int32(value << value_, is_pos_inf, is_neg_inf);
}

Int32 Int32::operator<<(const Int32& integer) const {
    if(integer.is_pos_inf || integer.is_neg_inf) {
        cerr << "Erro: tentando fazer shift para esquerda infinitamente" << endl;
        exit(1);
    }
    return Int32(value << integer.value, is_pos_inf, is_neg_inf);
}

Int32 Int32::operator>>(int value_) const {
    return Int32(value >> value_, is_pos_inf, is_neg_inf);
}

Int32 Int32::operator>>(const Int32& integer) const {
    if(integer.is_pos_inf || integer.is_neg_inf) {
        cerr << "Erro: tentando fazer shift para direita infinitamente" << endl;
        exit(1);
    }
    return Int32(value >> integer.value, is_pos_inf, is_neg_inf);
}

Int32 Int32::operator-() const {
    return Int32(value, is_neg_inf, is_pos_inf);
}

Int32 Int32::operator-(int value_) const {
    return Int32(value - value_, is_pos_inf, is_neg_inf);
}

Int32 Int32::operator-(const Int32& integer) const {
    return Int32(value - integer.value, is_pos_inf || integer.is_neg_inf, is_neg_inf || integer.is_pos_inf);
}

Int32 Int32::operator^(int value_) const {
    return Int32(value ^ value_, is_pos_inf, is_neg_inf);
}

Int32 Int32::operator^(const Int32& integer) const {
    return Int32(value ^ integer.value, is_pos_inf, is_neg_inf);
}

// Implementação dos operadores de comparação
bool Int32::operator==(int value_) const {
    if(is_pos_inf) return false;
    if(is_neg_inf) return false;
    return value == value_;
}

bool Int32::operator==(const Int32& integer) const {
    if(is_pos_inf && integer.is_pos_inf) return true;
    if(is_neg_inf && integer.is_neg_inf) return true;
    if((is_pos_inf || is_neg_inf) || (integer.is_neg_inf || integer.is_pos_inf)) return false;
    return value == integer.value;
}

bool Int32::operator<=(int value_) const {
    if(is_pos_inf) return false;
    if(is_neg_inf) return true;
    return value <= value_;
}

bool Int32::operator<=(const Int32& integer) const {
    if(is_pos_inf && integer.is_pos_inf) return true;
    if(is_neg_inf && integer.is_neg_inf) return true;
    if(is_pos_inf && integer.is_neg_inf) return false;
    if(is_neg_inf && integer.is_pos_inf) return true;
    if(is_pos_inf) return false;
    if(is_neg_inf) return true;
    return value <= integer.value;
}

bool Int32::operator>=(int value_) const {
    if(is_pos_inf) return true;
    if(is_neg_inf) return false;
    return value >= value_;
}

bool Int32::operator>=(const Int32& integer) const {
    if(is_pos_inf && integer.is_pos_inf) return true;
    if(is_neg_inf && integer.is_neg_inf) return true;
    if(is_pos_inf && integer.is_neg_inf) return true;
    if(is_neg_inf && integer.is_pos_inf) return false;
    if(is_pos_inf) return true;
    if(is_neg_inf) return false;
    return value >= integer.value;
}

bool Int32::operator>(int value_) const {
    if(is_pos_inf) return true;
    if(is_neg_inf) return false;
    return value > value_;
}

bool Int32::operator>(const Int32& integer) const {
    if(is_pos_inf && integer.is_pos_inf) return false;
    if(is_neg_inf && integer.is_neg_inf) return false;
    if(is_pos_inf && integer.is_neg_inf) return true;
    if(is_neg_inf && integer.is_pos_inf) return false;
    if(is_pos_inf) return true;
    if(is_neg_inf) return false;
    return value > integer.value;
}

bool Int32::operator<(int value_) const {
    if(is_pos_inf) return false;
    if(is_neg_inf) return true;
    return value < value_;
}

bool Int32::operator<(const Int32& integer) const {
    if(is_pos_inf && integer.is_pos_inf) return false;
    if(is_neg_inf && integer.is_neg_inf) return false;
    if(is_pos_inf && integer.is_neg_inf) return false;
    if(is_neg_inf && integer.is_pos_inf) return true;
    if(is_pos_inf) return false;
    if(is_neg_inf) return true;
    return value < integer.value;
}

bool Int32::operator!=(int value_) const {
    if(is_pos_inf) return true;
    if(is_neg_inf) return true;
    return value != value_;
}

bool Int32::operator!=(const Int32& integer) const {
    if(is_pos_inf && integer.is_pos_inf) return false;
    if(is_neg_inf && integer.is_neg_inf) return false;
    if((is_pos_inf || is_neg_inf) || (integer.is_neg_inf || integer.is_pos_inf)) return true;
    return value != integer.value;
}

// Implementação dos operadores de módulo
int Int32::operator%(const Int32& integer) const {
    if(integer.is_pos_inf || integer.is_neg_inf) {
        cerr << "Erro: tentando calcular número modulo infinito" << endl;
        exit(1);
    }
    if(is_pos_inf || is_neg_inf) {
        cerr << "Erro: tentando calcular infinito modulo alguma coisa" << endl;
        exit(1);
    }
    return value % integer.value;
}

int Int32::operator%(int value_) const {
    if(is_pos_inf || is_neg_inf) {
        cerr << "Erro: tentando calcular infinito modulo alguma coisa" << endl;
        exit(1);
    }
    return value % value_;
}

// Operador de conversão explícita
Int32::operator int() const {
    return value;
}

// Operador de stream (friend)
ostream& operator<<(ostream& os, const Int32& integer) {
    if(integer.is_pos_inf) os << "INF";
    else if(integer.is_neg_inf) os << "-INF";
    else os << integer.value;
    return os;
}

// Implementação dos operadores globais
string to_string(const Int32& integer) {
    if(integer.is_pos_inf) return "INF";
    else if(integer.is_neg_inf) return "-INF";
    else return std::to_string(integer.value);
}

bool operator==(int value_, const Int32& integer) {
    if(integer.is_pos_inf) return false;
    if(integer.is_neg_inf) return false;
    return integer.value == value_;
}

Int32 operator+(int value_, const Int32& integer) {
    return Int32(integer.value + value_, integer.is_pos_inf, integer.is_neg_inf);
}

Int32 operator%(int value_, const Int32& integer) {
    if(integer.is_pos_inf || integer.is_neg_inf) {
        cerr << "Erro: tentando calcular número modulo infinito" << endl;
        exit(1);
    }
    return Int32(value_ % integer.value);
}

Int32 operator*(int value_, const Int32& integer) {
    return Int32(integer.value * value_, integer.is_pos_inf, integer.is_neg_inf);
}

Int32 operator-(int value_, const Int32& integer) {
    return Int32(value_ - integer.value, integer.is_neg_inf, integer.is_pos_inf);
}

bool operator<=(int value_, const Int32& integer) {
    if(integer.is_pos_inf) return true;
    if(integer.is_neg_inf) return false;
    return value_ <= integer.value;
}

bool operator>=(int value_, const Int32& integer) {
    if(integer.is_pos_inf) return false;
    if(integer.is_neg_inf) return true;
    return value_ >= integer.value;
}

bool operator>(int value_, const Int32& integer) {
    if(integer.is_pos_inf) return false;
    if(integer.is_neg_inf) return true;
    return value_ > integer.value;
}

bool operator<(int value_, const Int32& integer) {
    if(integer.is_pos_inf) return true;
    if(integer.is_neg_inf) return false;
    return value_ < integer.value;
}

Int32 operator^(int value_, const Int32& integer) {
    return Int32(value_ ^ integer.value, integer.is_pos_inf, integer.is_neg_inf);
}
