#ifndef ARQREGISTRO_H
#define ARQREGISTRO_H

#include <fstream>
#include <cstring>
#include <type_traits>
#include "Registro.h"
#include "Cabecalho.h"
#include "Serializable.h"

using namespace std;

template <class T>
class ArqRegistro :protected fstream {
	static_assert(std::is_base_of<Serializable, T>::value, "T deve ser subclasse de Serializable");
public:
	ArqRegistro();
	ArqRegistro(const string nome, const string t, ios::openmode mode = ios::in | ios::out | ios::binary | ios::ate);
	bool abrir(const string nome, const string t, ios::openmode mode = ios::in | ios::out | ios::binary | ios::ate);
	bool fechar();
	bool lerRegistro(unsigned long int i, Registro<T>& r);
	bool excluirRegistro(unsigned long int i);
	bool inserirRegistro(Registro<T> r);
	unsigned long int primeiroValido() const;
	unsigned long int primeiroExcluido() const;
	bool aberto();
	virtual ~ArqRegistro();
protected:
	Cabecalho cab;
	bool lerCabecalho();
	bool escreverCabecalho();
	bool verificarTipo(string t);
	unsigned long int calculaPos(unsigned long int i);


};


ArqRegistro(const string _nome, const string _t, ios::openmode mode = ios::in | ios::out | ios::binary | ios::ate) {


}



//Construtor
//abrir arquivo



//Escrever cabecalho




#endif
