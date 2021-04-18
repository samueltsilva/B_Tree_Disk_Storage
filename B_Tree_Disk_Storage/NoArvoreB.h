#ifndef NOARVOREB_H_INCLUDED
#define NOARVOREB_H_INCLUDED
#include "Complexo.h"
//#include "Serializable.h"

using namespace std;



//classe do n� da �rvore
class No_Arvore_B {
private:
    Complexo* chaves;
    int t;
    No_Arvore_B** c;
    int n;
    bool folha;


public:
    //Construtor, acessores
    No_Arvore_B(int _t, bool _folha);
    void setN(int _n);
    void setC(int _pos2, No_Arvore_B* raiz);
    void setC2(No_Arvore_B* c, int _pos3, Complexo _k);
    int getN();
    Complexo getChaves(int i);
    bool getFolha();


    //m�todo procurar
    No_Arvore_B* procurar(Complexo _c);
    No_Arvore_B* procurar_pagina(Complexo _c);


    //m�todos inserir
    No_Arvore_B operator=(No_Arvore_B** c);
    void setChaves(int _pos, Complexo _k);
    void percorrer();
    void insert_non_full(Complexo k);
    void split_child(int i, No_Arvore_B* y);

    //m�todos remover
    int encontrar_chave(Complexo _c);
    void remover(Complexo _c);
    void preencher(int aux);
    void remover_da_folha(int aux);
    Complexo pegar_predecessor(int pos);
    Complexo pegar_sucessor(int pos);
    void remover_nao_folha(int aux);
    void emprestado_anterior(int aux);
    void emprestado_proximo(int aux);
    void juntar(int pos);


};

//Construtor
No_Arvore_B::No_Arvore_B(int _t, bool _folha) {
    t = _t;
    folha = _folha;
    chaves = new Complexo[(2 * t) - 1];
    c = new No_Arvore_B * [(2 * t)];
    n = 0;
}

//Acessores

//Seta uma chave na p�gina
void No_Arvore_B::setChaves(int _pos, Complexo _k) {
    chaves[_pos] = _k;
}

//Seta a quantidade de chaves na p�gina
void No_Arvore_B::setN(int _n) {
    n = _n;

}

//Retorna a quantidade de chaves na p�gina
int No_Arvore_B::getN() {
    return n;

}

//Retorna uma chave na posi��o i da p�gina
Complexo No_Arvore_B::getChaves(int i) {
    return chaves[i];

}

//Seta um filho para ser raiz
void No_Arvore_B::setC(int _pos2, No_Arvore_B* raiz) {
    c[_pos2] = raiz;

}

//inserir a chave k no filho de s
void No_Arvore_B::setC2(No_Arvore_B* s, int i, Complexo _k) {
    s->c[i]->insert_non_full(_k);

}

//Retorna se � folha
bool No_Arvore_B::getFolha() {
    return folha;

}

//M�todo para percorrer a �rvore
void No_Arvore_B::percorrer() {
    int i;
    for (i = 0; i < n; i++) {
        if (folha == false)
            c[i]->percorrer();
        cout << chaves[i] << " ";

    }

    if (folha == false)
        c[i]->percorrer();

}

//Procura uma chave _c na p�gina
No_Arvore_B* No_Arvore_B::procurar(Complexo _c) {
    int i = 0; //contador
    while (i < n && _c > chaves[i])
        i++;

    if (chaves[i] == _c)
        return this; //Se encontrou na p�gina, retorna

    if (folha == true)
        return NULL; //Se n�o encontrar na p�gina, retorna null

    return c[i]->procurar(_c); //Desce para a pr�xima pagina para procurar


}


No_Arvore_B* No_Arvore_B::procurar_pagina(Complexo _c) {
    int i = 0;
    while (i < n && _c > chaves[i])
        i++;

    if (chaves[i] == _c)
        for (int b = 0; b < n; b++)
            cout << chaves[b] << " ";
    if (folha == true)
        return NULL;

    return c[i]->procurar(_c);


}


//Insere na folha se ela n�o estiver cheia
//Observe que quando esse m�todo � chamado, j� sabemos que a chave est� nessa p�gina
void No_Arvore_B::insert_non_full(Complexo _c) {
    int i = n - 1;

    if (folha == true) {

        while (i >= 0 && chaves[i] > _c) {
            chaves[i + 1] = chaves[i];
            i--;
        }

        chaves[i + 1] = _c;
        n = n + 1;
    }

    else { //Quando n�o � folha, deve tomar os cuidados antes de descer a p�gina
        while (i >= 0 && chaves[i] > _c)
            i--;

        if (c[i + 1]->n == (2 * t) - 1) { //Antes de descer, verifica se o filho est� cheio, se estiver, divide
            split_child(i + 1, c[i + 1]);

            if (chaves[i + 1] < _c)
                i++;

        }
        c[i + 1]->insert_non_full(_c);
    }
}


//Divide uma p�gina se estiver cheia em duas
void No_Arvore_B::split_child(int i, No_Arvore_B* y) {
    No_Arvore_B* z = new No_Arvore_B(y->t, y->folha);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->chaves[j] = y->chaves[j + t]; //seta as chaves
    if (!y->folha) {
        for (int j = 0; j < t; j++) { //seta os filhos
            z->c[j] = y->c[j + t];

        }
    }

    y->n = t - 1;
    for (int j = n; j >= i + 1; j--) {
        c[j + 1] = c[j];
    }
    c[i + 1] = z;

    for (int j = n - 1; j >= i; j--) {
        chaves[j + 1] = chaves[j];
    }
    chaves[i] = y->chaves[t - 1];

    n = n + 1;
}


//m�todo para retornar a quantidade n de chaves na p�gina , tal que n < k. Essa "quantidade n de chaves" mais tarde ser� usada como a posi��o direta de onde se encontra a chave. (Minha maior fa�anha :P)
//Por exemplo, na p�gina de inteiros: [1,3,4,5,6] para a chave de valor 5, retorna um aux = 3
int No_Arvore_B::encontrar_chave(Complexo _c) {
    int aux = 0;
    while (aux < n && chaves[aux] < _c)
        aux++;

    return aux;

}

//Est� � a estrutura principal para se remover uma chave. Todo esse corpo faz a remo��o, invocando os m�todos necess�rios ao longo do caminho.
void No_Arvore_B::remover(Complexo _c) {
    int aux = encontrar_chave(_c);

    if (aux < n && chaves[aux] == _c) { //Como visto antes, com o aux, temos a posi��o onde est� a chave
        if (folha)//Agora basta sabermos se � folha ou n�o
            remover_da_folha(aux);
        else
            remover_nao_folha(aux);

    }

    else { //Se n�o der certo a fa�anha, � porque a chave n�o existe, ent�o retorna que a chave n�o est� na �rvore.
        if (folha) {
            cout << "A chave " << _c << "nao esta na arvore" << endl;
            return;

        }

        bool flag = ((aux == n) ? true : false); //Testando nota��o nova que aprendi em paradigmas

        if (c[aux]->t < n)
            preencher(aux);

        if (flag && aux > n)
            c[aux - 1]->remover(_c);
        else
            c[aux]->remover(_c);

    }
    return;
}

//Remove da folha, caso mais simples de remo��o
void No_Arvore_B::remover_da_folha(int aux) {
    for (int i = aux + 1; i < n; i++)
        chaves[i - 1] = chaves[i];

    n = n - 1;

    return;

}

//N�o � de Deus. Remover de p�gina interna, e manter estrutura da �rvore
void No_Arvore_B::remover_nao_folha(int aux) {
    Complexo _c = chaves[aux];

    if (c[aux]->n >= t) { //Se a quantidade de chaves do filho � esquerda for maior que t, podemos pegar a chave antecessora (que est� nesse filho) para subirmos para a p�gina que estamos removendo
        Complexo anterior = pegar_predecessor(aux);
        chaves[aux] = anterior;
        c[aux]->remover(anterior);

    }

    else if (c[aux + 1]->n >= t) { //Se a quantidade de chaves do filho � direita for maior que t, podemos pegar a chave sucessora (que est� nesse filho) para subirmos para a p�gina que estamos removendo
        Complexo sucessor = pegar_sucessor(aux);
        chaves[aux] = sucessor;
        c[aux + 1]->remover(sucessor);

    }

    else { //Se n�o podemos pegar de nenhum filho, ent�o junta eles e depois remove a chave
        juntar(aux);
        c[aux]->remover(_c);

    }

    return;
}






//Esse m�todo pega o predecessor
Complexo No_Arvore_B::pegar_predecessor(int pos) {
    No_Arvore_B* pagina_aux;
    pagina_aux = c[pos];

    while (!pagina_aux->folha)
        pagina_aux = pagina_aux->c[pagina_aux->n];

    return pagina_aux->chaves[pagina_aux->n - 1];

}


//Esse m�todo pega o sucessor
Complexo No_Arvore_B::pegar_sucessor(int pos) {
    No_Arvore_B* pagina_aux;
    pagina_aux = c[pos + 1];

    while (!pagina_aux->folha)
        pagina_aux = pagina_aux->c[0];

    return pagina_aux->chaves[0];

}

//Estrutura para juntar p�ginas
void No_Arvore_B::preencher(int aux) {
    if (aux != 0 && c[aux - 1]->n >= t)
        emprestado_anterior(aux);

    else
        if (aux != n && c[aux + 1]->n >= t)
            emprestado_proximo(aux);

        else
        {
            if (aux != n)
            {
                juntar(aux);
            }
            else
                juntar(aux - 1);
        }

    return;

}


//Emprestado da p�gina anterior
void No_Arvore_B::emprestado_anterior(int aux) {
    No_Arvore_B* filho = c[aux];
    No_Arvore_B* irmao = c[aux - 1];

    for (int i = filho->n - 1; i >= 0; i--)
        filho->chaves[i + 1] = filho->chaves[i];


    if (!filho->folha) {
        for (int i = filho->n; i >= 0; i--)
            filho->c[i + 1] = filho->c[i];

    }


    filho->chaves[0] = chaves[aux - 1];

    if (!folha)
        filho->c[0] = irmao->c[irmao->n];


    chaves[aux - 1] = irmao->chaves[irmao->n - 1];

    filho->n += 1;
    irmao->n -= 1;

    return;
}

//Emprestado da p�gina sucessora
void No_Arvore_B::emprestado_proximo(int aux) {
    No_Arvore_B* filho = c[aux];
    No_Arvore_B* irmao = c[aux + 1];

    filho->chaves[(filho->n)] = chaves[aux];


    if (!(filho->folha))
    {
        filho->c[(filho->n) + 1] = irmao->c[0];
    }


    chaves[aux] = irmao->chaves[0];

    for (int i = 1; i < irmao->n; i++)
        irmao->chaves[i - 1] = irmao->chaves[i];


    if (!irmao->folha) {
        for (int i = 1; i <= irmao->n; i++);

    }


    filho->n += 1;
    irmao->n -= 1;

}

//junta duas p�ginas
void No_Arvore_B::juntar(int pos) {
    No_Arvore_B* filho = c[pos];
    No_Arvore_B* irmao = c[pos + 1];

    filho->chaves[t - 1] = chaves[pos];

    for (int i = 0; i < irmao->n; i++)
    {
        filho->chaves[i + t] = irmao->chaves[i];
    }


    if (!filho->folha) {
        for (int i = 0; i <= irmao->n; i++)
            filho->c[i + t] = irmao->c[i];

    }


    for (int i = pos + 1; i < n; i++)
        chaves[i - 1] = chaves[i];

    for (int i = pos + 2; i <= n; i++)
        c[i - 1] = c[i];

    filho->n += irmao->n + 1;
    n = n - 1;

    delete(irmao);
    return;




}




#endif // NOARVOREB_H_INCLUDED
