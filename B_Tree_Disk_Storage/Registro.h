#ifndef REGISTRO_H
#define REGISTRO_H

#include "Serializable.h"

template <class T>
class Registro :public Serializable {
private:
	T dados;
	bool apagado;
	unsigned long int prox;
public:
	Registro();
	Registro(T i);
	Registro(const Registro& r);
	//Registro<T> operator = (const Registro<T> &r);
	//bool operator == (const Registro<T> &r);
	//T info() const;
	//void info(T i);
	unsigned long int proximo() const;
	void proximo(unsigned long int p);
	bool excluido() const;
	//void excluir();
	//string ToString();
	string ToCSV() {}
	string ToXML() {}
	string ToJSON() {}
	//void fromString(string repr);
	void FromCSV(string repr) {}
	void fromXML(string repr) {}
	void FromJSON(string repr) {}


};



unsigned long int Registro::proximo() {
	return prox;
}


void Registro::proximo(unsigned long int p) {
	prox = p;

}

Registro::Registro(T i) {
	dados = i;


}



#endif
