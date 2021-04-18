#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED
#include "NoArvoreB.h"
//#include "Arqregistro.h"
#include "Complexo.h"


using namespace std;

//Classe da árvore
class Arvore_B {
private:
    No_Arvore_B* raiz;
    int t;
    //    Arqregistro <No_Arvore_B <Complexo> > arq;


public:
    Arvore_B(int _t);
    void percorrer();
    No_Arvore_B* procurar(Complexo _c);
    No_Arvore_B* procurar_pagina(Complexo _c);
    void inserir(Complexo _c);
    void remover(Complexo _c);

};

Arvore_B::Arvore_B(int _t) {
    raiz = NULL;
    t = _t;


}

void Arvore_B::percorrer() {
    if (raiz != NULL)
        raiz->percorrer();
}

No_Arvore_B* Arvore_B::procurar(Complexo _c) {
    return (raiz == NULL) ? NULL : raiz->procurar(_c);
}


//Fazer if de verificacao se esta na pagina filha

No_Arvore_B* Arvore_B::procurar_pagina(Complexo _c) {
    return (raiz == NULL) ? NULL : raiz->procurar_pagina(_c);

}

//Função primária de inserção. Ela que chama os métodos auxiliares em NoArvoreB.h para inserir
//um valor e tratar a árvore
void Arvore_B::inserir(Complexo _c) {
    if (raiz == NULL) { //se a raiz estiver vazia, crie uma e insere.
        raiz = new No_Arvore_B(t, true);
        raiz->setChaves(0, _c);
        raiz->setN(1);
    }
    else {
        if (raiz->getN() == (2 * t) - 1) { //se a raiz estiver cheia, divide, seta os filhos e insere
            No_Arvore_B* s = new No_Arvore_B(t, false);
            s->setC(0, raiz);
            s->split_child(0, raiz);
            int i = 0;
            if (s->getChaves(i) < _c)
                i++;

            s->setC2(s, i, _c);
            raiz = s;

        }
        else
            raiz->insert_non_full(_c); //Se a raiz não está vazia nem cheia, somente insira o valor

    }




}


//Função primária de remoção. Recebe a chave que precisa ser removida e acessa as métodos em NoArvoreB.h
//para remover e tratar a árvore
void Arvore_B::remover(Complexo _c) {
    if (!raiz) { //se não existe raiz, a árvore está vazia e não há nada a ser removido
        cout << "Não foi possivel remover pois a arvore esta vazia\n";
        return;
    }

    raiz->remover(_c); //início da recursão para remover a chave

    if (raiz->getN() == 0) { //se o número de chaves da raiz for 0
        No_Arvore_B* aux = raiz;
        if (raiz->getFolha())
            raiz = NULL;
        else
            raiz->setC(0, raiz);

        delete aux; //Desaloca espaço da memória

    }
    return;

}


#endif // ARVORE_H_INCLUDED
