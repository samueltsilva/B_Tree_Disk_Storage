#ifndef NOARVOREB_H_INCLUDED
#define NOARVOREB_H_INCLUDED
#include "Complexo.h"
//#include "Serializable.h"

using namespace std;



//classe do nó da árvore
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


    //método procurar
    No_Arvore_B* procurar(Complexo _c);
    No_Arvore_B* procurar_pagina(Complexo _c);


    //métodos inserir
    No_Arvore_B operator=(No_Arvore_B** c);
    void setChaves(int _pos, Complexo _k);
    void percorrer();
    void insert_non_full(Complexo k);
    void split_child(int i, No_Arvore_B* y);

    //métodos remover
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

//Seta uma chave na página
void No_Arvore_B::setChaves(int _pos, Complexo _k) {
    chaves[_pos] = _k;
}

//Seta a quantidade de chaves na página
void No_Arvore_B::setN(int _n) {
    n = _n;

}

//Retorna a quantidade de chaves na página
int No_Arvore_B::getN() {
    return n;

}

//Retorna uma chave na posição i da página
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

//Retorna se é folha
bool No_Arvore_B::getFolha() {
    return folha;

}

//Método para percorrer a árvore
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

//Procura uma chave _c na página
No_Arvore_B* No_Arvore_B::procurar(Complexo _c) {
    int i = 0; //contador
    while (i < n && _c > chaves[i])
        i++;

    if (chaves[i] == _c)
        return this; //Se encontrou na página, retorna

    if (folha == true)
        return NULL; //Se não encontrar na página, retorna null

    return c[i]->procurar(_c); //Desce para a próxima pagina para procurar


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


//Insere na folha se ela não estiver cheia
//Observe que quando esse método é chamado, já sabemos que a chave está nessa página
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

    else { //Quando não é folha, deve tomar os cuidados antes de descer a página
        while (i >= 0 && chaves[i] > _c)
            i--;

        if (c[i + 1]->n == (2 * t) - 1) { //Antes de descer, verifica se o filho está cheio, se estiver, divide
            split_child(i + 1, c[i + 1]);

            if (chaves[i + 1] < _c)
                i++;

        }
        c[i + 1]->insert_non_full(_c);
    }
}


//Divide uma página se estiver cheia em duas
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


//método para retornar a quantidade n de chaves na página , tal que n < k. Essa "quantidade n de chaves" mais tarde será usada como a posição direta de onde se encontra a chave. (Minha maior façanha :P)
//Por exemplo, na página de inteiros: [1,3,4,5,6] para a chave de valor 5, retorna um aux = 3
int No_Arvore_B::encontrar_chave(Complexo _c) {
    int aux = 0;
    while (aux < n && chaves[aux] < _c)
        aux++;

    return aux;

}

//Está é a estrutura principal para se remover uma chave. Todo esse corpo faz a remoção, invocando os métodos necessários ao longo do caminho.
void No_Arvore_B::remover(Complexo _c) {
    int aux = encontrar_chave(_c);

    if (aux < n && chaves[aux] == _c) { //Como visto antes, com o aux, temos a posição onde está a chave
        if (folha)//Agora basta sabermos se é folha ou não
            remover_da_folha(aux);
        else
            remover_nao_folha(aux);

    }

    else { //Se não der certo a façanha, é porque a chave não existe, então retorna que a chave não está na árvore.
        if (folha) {
            cout << "A chave " << _c << "nao esta na arvore" << endl;
            return;

        }

        bool flag = ((aux == n) ? true : false); //Testando notação nova que aprendi em paradigmas

        if (c[aux]->t < n)
            preencher(aux);

        if (flag && aux > n)
            c[aux - 1]->remover(_c);
        else
            c[aux]->remover(_c);

    }
    return;
}

//Remove da folha, caso mais simples de remoção
void No_Arvore_B::remover_da_folha(int aux) {
    for (int i = aux + 1; i < n; i++)
        chaves[i - 1] = chaves[i];

    n = n - 1;

    return;

}

//Não é de Deus. Remover de página interna, e manter estrutura da árvore
void No_Arvore_B::remover_nao_folha(int aux) {
    Complexo _c = chaves[aux];

    if (c[aux]->n >= t) { //Se a quantidade de chaves do filho à esquerda for maior que t, podemos pegar a chave antecessora (que está nesse filho) para subirmos para a página que estamos removendo
        Complexo anterior = pegar_predecessor(aux);
        chaves[aux] = anterior;
        c[aux]->remover(anterior);

    }

    else if (c[aux + 1]->n >= t) { //Se a quantidade de chaves do filho à direita for maior que t, podemos pegar a chave sucessora (que está nesse filho) para subirmos para a página que estamos removendo
        Complexo sucessor = pegar_sucessor(aux);
        chaves[aux] = sucessor;
        c[aux + 1]->remover(sucessor);

    }

    else { //Se não podemos pegar de nenhum filho, então junta eles e depois remove a chave
        juntar(aux);
        c[aux]->remover(_c);

    }

    return;
}






//Esse método pega o predecessor
Complexo No_Arvore_B::pegar_predecessor(int pos) {
    No_Arvore_B* pagina_aux;
    pagina_aux = c[pos];

    while (!pagina_aux->folha)
        pagina_aux = pagina_aux->c[pagina_aux->n];

    return pagina_aux->chaves[pagina_aux->n - 1];

}


//Esse método pega o sucessor
Complexo No_Arvore_B::pegar_sucessor(int pos) {
    No_Arvore_B* pagina_aux;
    pagina_aux = c[pos + 1];

    while (!pagina_aux->folha)
        pagina_aux = pagina_aux->c[0];

    return pagina_aux->chaves[0];

}

//Estrutura para juntar páginas
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


//Emprestado da página anterior
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

//Emprestado da página sucessora
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

//junta duas páginas
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
