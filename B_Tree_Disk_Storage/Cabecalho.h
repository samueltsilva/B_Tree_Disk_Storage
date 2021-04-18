#ifndef CABECALHO_H
#define CABECALHO_H

#include <string>
#include "Serializable.h"

class Cabecalho :public Serializable {
public:
	Cabecalho();
	Cabecalho(const string t, const int v);
	Cabecalho(const Cabecalho& c);
	//Cabecalho operator = (const Cabecalho &c);
	unsigned long int primeiroExcluido()const;
	void primeiroExcluido(unsigned long int r);
	unsigned long int primeiroValido()const;
	void primeiroValido(unsigned long int r);
	string tipoArquivo()const;
	void tipoArquivo(string t);
	int versao()const;
	void versao(int v);
	int getSize()const;
	string ToString();
	string ToCSV() {}
	string ToXML() {}
	string ToJSON() {}
	virtual void FromString(string repr);
	virtual void FromCSV(string repr) {}
	virtual void FromXML(string repr) {}
	virtual void FromJSON(string repr) {}



protected:
	string tipo;
	int ver;
	unsigned long int primValido;
	unsigned long int primExcluido;
};

Cabecalho::Cabecalho(const string t, const int v) {
	tipo = t;
	ver = v;
}


unsigned long int Cabecalho::primeiroExcluido() const {
	return primExcluido;

}


void Cabecalho::primeiroExcluido(unsigned long int r) {
	primExcluido = r;
}

unsigned long int Cabecalho::primeiroValido() const {
	return primValido;

}

void Cabecalho::primeiroValido(unsigned long int r) {
	primValido = r;

}

string Cabecalho::tipoArquivo() const {
	return tipo;

}

void Cabecalho::tipoArquivo(string t) {
	tipo = t;

}


int Cabecalho::versao() const {
	return ver;

}

void Cabecalho::versao(int v) {
	ver = v;
}

int Cabecalho::getSize() const {
	int s;
	s = tipo.length();
	s = s + sizeof(ver);
	s = s + primValido;
	s = s + primExcluido;

	return s;

}

string Cabecalho::ToString() {
	string saida = "";
	saida = saida + string(reinterpret_cast<char*>(&tipo), sizeof(tipo)); //Concatena
	saida = saida + string(reinterpret_cast<char*>(&ver), sizeof(ver)); //Concatena
	saida = saida + string(reinterpret_cast<char*>(&primValido), sizeof(primValido)); //Concatena
	saida = saida + string(reinterpret_cast<char*>(&primExcluido), sizeof(primExcluido)); //Concatena
	return saida;

}


void Cabecalho::FromString(string valores) {
	char* aux = new char[valores.length()]; //vetor de bytes auxiliar para a leitura
	int i = 0; //Primeiro byte a ser observado pelo reinterpret_cast

	valores.copy(aux, valores.length(), 0); //copia os bytes

	tipoArquivo(*reinterpret_cast<string*>(aux)); //Converte e seta o tipo arquivo

	i += sizeof(tipo); //avança os bytes

	versao(*reinterpret_cast<int*>(aux + i)); //Converte e seta a versão

	i += sizeof(ver); //Avança os bytes

	primeiroValido(*reinterpret_cast<unsigned long int*>(aux + i)); //Converte e seta o PrimeiroValido

	i += sizeof(primValido); //Avança os bytes

	primeiroExcluido(*reinterpret_cast<unsigned long int*>(aux + i)); //Converte e seta o primeiroExcluido

	delete aux;

}

#endif
