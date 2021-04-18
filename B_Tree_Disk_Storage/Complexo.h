#ifndef COMPLEXO_H_INCLUDED
#define COMPLEXO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <math.h>
//#include "Serializable.h"



using namespace std;

class Complexo {
private:
    double a, b; //Estrutura do número complexo será: a + bi

public:
    Complexo(); //Construtor default
    Complexo(double _a); //Construtor quando a parte imaginária é 0
    Complexo(double _a, double _b); //Construtor completo
    double getReal() const;
    double getImaginario() const;
    void setReal(double _a);
    void setImaginario(double _b);
    Complexo adicao(Complexo _c);
    Complexo subtracao(Complexo _c);
    Complexo multiplicacao(Complexo _c);
    Complexo divisao(Complexo _c);
    void exibir_completo();
    void exibir_sem_real();
    friend ostream& operator<<(ostream& os, const Complexo& c);
    friend bool operator> (const Complexo& c1, const Complexo& c2);
    friend bool operator==(const Complexo& c1, const Complexo& c2);
    friend bool operator< (const Complexo& c1, const Complexo& c2);

    string ToString();
    void FromString(string valores);



};

ostream& operator<<(ostream& os, const Complexo& c) {
    os << c.a << "+" << c.b << "i";
    return os;

}

bool operator>(const Complexo& c1, const Complexo& c2) {
    return sqrt(pow(c1.getReal(), 2) + pow(c1.getImaginario(), 2)) > sqrt(pow(c2.getReal(), 2) + pow(c2.getImaginario(), 2));
}

bool operator==(const Complexo& c1, const Complexo& c2) {
    return c1.a == c2.a && c1.b == c2.b;
}

bool operator<(const Complexo& c1, const Complexo& c2) {
    return sqrt(pow(c1.getReal(), 2) + pow(c1.getImaginario(), 2)) < sqrt(pow(c2.getReal(), 2) + pow(c2.getImaginario(), 2));

}

Complexo::Complexo() {
    a = 0;
    b = 0;
}

Complexo::Complexo(double _a) {
    a = _a;
    b = 0;
}

Complexo::Complexo(double _a, double _b) {
    a = _a;
    b = _b;

}

double Complexo::getReal() const {
    return a;
}

double Complexo::getImaginario() const {
    return b;
}

void Complexo::setReal(double _a) {
    a = _a;
}

void Complexo::setImaginario(double _b) {
    b = _b;
}

Complexo Complexo::adicao(Complexo _c) {
    Complexo somar;
    somar.a = a + _c.a;
    somar.b = b + _c.b;
    return somar;

}

Complexo Complexo::subtracao(Complexo _c) {
    Complexo subtrair;
    subtrair.a = a - _c.a;
    subtrair.b = b - _c.b;
    return subtrair;


}

Complexo Complexo::multiplicacao(Complexo _c) {
    Complexo multiplicar;
    multiplicar.a = a * _c.a - b * _c.b;
    multiplicar.b = b * _c.b - _c.a * b;
    return multiplicar;
}

Complexo Complexo::divisao(Complexo _c) {
    Complexo dividir;
    dividir.a = (a * _c.a + b * _c.b) / (_c.a * _c.a + _c.b * _c.b);
    dividir.b = (b * _c.a + a * _c.b) / (_c.a * _c.a + _c.b * _c.b);
    return dividir;
}


void Complexo::exibir_completo() {
    if (a == 0) {
        exibir_sem_real();
    }
    else
        cout << a << "+" << b << "i" << endl;
}

void Complexo::exibir_sem_real() {
    cout << b << "i" << endl;


}


//
string Complexo::ToString() {
    string saida;
    saida + string(reinterpret_cast<char*>(&a), sizeof(a)); //Concatena
    saida = saida + string(reinterpret_cast<char*>(&b), sizeof(b)); //Concatena
    return saida;

}

void Complexo::FromString(string valores) {
    char* aux = new char[valores.length()]; //Vetor de bytes auxiliar
    int i = 0;

    valores.copy(aux, valores.length(), 0); //Copya os bytes

    setReal(*reinterpret_cast<double*>(aux)); //Converte e seta o número real

    i += sizeof(a); //Avança os bytes

    setImaginario(*reinterpret_cast<double*>(aux + i)); //Converte e seta o número imaginário

    delete aux;

}


#endif // COMPLEXO_H_INCLUDED
