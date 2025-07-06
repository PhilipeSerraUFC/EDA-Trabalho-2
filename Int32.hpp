#include <bits/stdc++.h>
#define INF Int32(0, true, false)

using namespace std;

struct Int32{
    uint32_t value;
    bool is_pos_inf;
    bool is_neg_inf;


    Int32(){
        value = 0;
        is_pos_inf = false;
        is_neg_inf = false;
    }

    Int32(int value_){
        value = value_;
        is_pos_inf = false;
        is_neg_inf = false;
    }

    Int32(int value_, bool is_pos_inf_, bool is_neg_inf_){
        value = value_;
        is_pos_inf = is_pos_inf_;
        is_neg_inf = is_neg_inf_;
    }

    Int32 operator+(int value_) const {
        return Int32(value + value_, is_pos_inf, is_neg_inf);
    }

    Int32 operator+(const Int32& integer) const {
        return Int32(value + integer.value, is_pos_inf || integer.is_pos_inf, is_neg_inf || integer.is_neg_inf);
    }

    Int32 operator*(int value_) const {
        return Int32(value*value_, is_pos_inf, is_neg_inf);
    }

    Int32 operator*(const Int32& integer) const {
        return Int32(value*integer.value, is_pos_inf || integer.is_pos_inf, is_neg_inf || integer.is_neg_inf);
    }

    Int32 operator<<(int value_) const {
        return Int32(value<<value_, is_pos_inf, is_neg_inf);
    }

    Int32 operator<<(const Int32& integer) const {
        if(integer.is_pos_inf || integer.is_neg_inf){
            cerr << "Erro: tentando fazer shift para direita infinitamente" << endl;
            exit(1);
        }
        return Int32(value<<integer.value, is_pos_inf, is_neg_inf);
    }

    Int32 operator>>(int value_) const {
        return Int32(value>>value_, is_pos_inf, is_neg_inf);
    }

    Int32 operator>>(const Int32& integer) const {
        if(integer.is_pos_inf || integer.is_neg_inf){
            cerr << "Erro: tentando fazer shift para esquerda infinitamente" << endl;
            exit(1);
        }
        return Int32(value>>integer.value, is_pos_inf, is_neg_inf);
    }

    Int32 operator-() const {
        return Int32(value, !is_pos_inf, !is_neg_inf);
    }

    Int32 operator-(int value_) const {
        return Int32(value - value_, is_pos_inf, is_neg_inf);
    }

    Int32 operator-(const Int32& integer) const {
        return Int32(value - integer.value, is_pos_inf, is_neg_inf);
    }

    bool operator==(int value_) const {
        if(is_pos_inf) return false;
        if(is_neg_inf) return false;

        return value == value_;
    }

    bool operator==(const Int32& integer) const{
        if(is_pos_inf && integer.is_pos_inf) return true;
        if(is_neg_inf && integer.is_neg_inf) return true;

        if((is_pos_inf || is_neg_inf) && (integer.is_neg_inf || integer.is_pos_inf)) return false;
        
        return value == integer.value;
    }

    bool operator<=(int value_) const {
        if(is_pos_inf) return false;
        if(is_neg_inf) return true;

        return value <= value_;
    }

    bool operator<=(const Int32& integer) const{
        if(is_pos_inf && integer.is_pos_inf) return true;
        if(is_neg_inf && integer.is_neg_inf) return true;
        if(is_pos_inf && integer.is_neg_inf) return false;
        if(is_neg_inf && integer.is_pos_inf) return true;
        
        return value <= integer.value;
    }

    bool operator>=(int value_) const {
        if(is_pos_inf) return true;
        if(is_neg_inf) return false;

        return value >= value_;
    }

    bool operator>=(const Int32& integer) const{
        if(is_pos_inf && integer.is_pos_inf) return true;
        if(is_neg_inf && integer.is_neg_inf) return true;
        if(is_pos_inf && integer.is_neg_inf) return true;
        if(is_neg_inf && integer.is_pos_inf) return false;
        
        return value >= integer.value;
    }

    bool operator>(int value_) const {
        if(is_pos_inf) return true;
        if(is_neg_inf) return false;

        return value > value_;
    }

    bool operator>(const Int32& integer) const{
        if(is_pos_inf && integer.is_pos_inf) return false;
        if(is_neg_inf && integer.is_neg_inf) return false;
        if(is_pos_inf && integer.is_neg_inf) return true;
        if(is_neg_inf && integer.is_pos_inf) return false;
        
        return value > integer.value;
    }

    bool operator<(int value_) const {
        if(is_pos_inf) return false;
        if(is_neg_inf) return true;

        return value < value_;
    }

    bool operator<(const Int32& integer) const{
        if(is_pos_inf && integer.is_pos_inf) return false;
        if(is_neg_inf && integer.is_neg_inf) return false;
        if(is_pos_inf && integer.is_neg_inf) return false;
        if(is_neg_inf && integer.is_pos_inf) return true;
        
        return value < integer.value;
    }

    bool operator!=(int value_) const {
        if(is_pos_inf) return true;
        if(is_neg_inf) return true;

        return value != value_;
    }

    bool operator!=(const Int32& integer) const{
        if(is_pos_inf && integer.is_pos_inf) return false;
        if(is_neg_inf && integer.is_neg_inf) return false;

        if((is_pos_inf || is_neg_inf) && (integer.is_neg_inf || integer.is_pos_inf)) return true;
        
        return value != integer.value;
    }


    int operator%(const Int32& integer) const {
        if(integer.is_pos_inf || integer.is_neg_inf){
            cerr << "Erro: tentando calcular número modulo infinito" << endl;
            exit(1);
        }

        if(is_pos_inf || is_neg_inf){
            cerr << "Erro: tentando calcular infinito modulo alguma coisa" << endl;
            exit(1);
        }
        return value;
    }

    int operator%(int value_) const {

        if(is_pos_inf || is_neg_inf){
            cerr << "Erro: tentando calcular infinito modulo alguma coisa" << endl;
            exit(1);
        }
        return value % value_;
    }

    Int32 operator^(int value_) const {
        return Int32(value^value_, is_pos_inf, is_neg_inf);
    }

    Int32 operator^(const Int32& integer) const {
        return Int32(value^integer.value, is_pos_inf, is_neg_inf);
    }

    friend ostream& operator<<(ostream& os, const Int32& integer){
        if(integer.is_pos_inf) os << "INF";
        else if(integer.is_neg_inf) os << "-INF";
        else os << integer.value;

        return os;
    }

    //Não vale a pena adicionar uma conversão Implicita de Int32 para int, pois isto pode causar comportamento inesperado
    
    explicit operator int() const {
        return value;
    }

};

//Operadores globais
string to_string(const Int32& integer) {
        if(integer.is_pos_inf) return "INF";
        else if(integer.is_neg_inf) return "-INF";
        else return to_string(integer.value);
    }

bool operator==(int value_, const Int32& integer){
    if(integer.is_pos_inf) return false;
    if(integer.is_neg_inf) return false;

    return integer.value == value_;
}

Int32 operator+(int value_, const Int32& integer){
    return Int32(integer.value + value_, integer.is_pos_inf, integer.is_neg_inf);
}

Int32 operator%(int value_, const Int32& integer) {
    if(integer.is_pos_inf || integer.is_neg_inf){
        cerr << "Erro: tentando calcular número modulo infinito" << endl;
        exit(1);
    }
    return Int32(value_ % integer.value);
}

Int32 operator*(int value_, const Int32& integer) {
    return Int32(integer.value*value_, integer.is_pos_inf, integer.is_neg_inf);
}

Int32 operator-(int value_, const Int32& integer) {
    return Int32(value_ - integer.value, integer.is_pos_inf, integer.is_neg_inf);
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
    return Int32(value_^integer.value, integer.is_pos_inf, integer.is_neg_inf);
}