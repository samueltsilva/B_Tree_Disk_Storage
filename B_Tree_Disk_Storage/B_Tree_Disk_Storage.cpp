//Samuel Trindade Silva RA:0022133
//Corrija com carinho, porque deu trabalho :)


#include <iostream>
#include "NoArvoreB.h"
#include "Arvore.h"


#define t 3

using namespace std;

int main()
{


    int opcao, aux2, aux3;
    double v1, v2;

    cout << "Inicializando a arvore" << endl;
    Arvore_B arvore(t);
    cout << "Arvore construida com sucesso" << endl;

    do
    {
        cout << endl
            << " 1 - Inserir um numero complexo na arvore.\n"
            << " 2 - Remover um numero complexo da arvore.\n"
            << " 3 - Imprimir a pagina da arvore que contem um numero complexo.\n"
            << " 4 - Buscar um numero complexo na arvore.\n"
            << " 5 - Sair.\n" << endl;
        cout << "Por favor, escolha uma opcao: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1: {
            cout << "Por favor, insira um numero complexo (conforme o modelo abaixo):\nParte real:" << endl;
            Complexo* aux = new Complexo();
            cin >> v1;
            aux->setReal(v1);
            cout << "Parte imaginaria: " << endl;
            cin >> v2;
            aux->setImaginario(v2);
            arvore.inserir(*aux);
            cout << "Numero " << *aux << " inserido na arvore com sucesso!" << endl;
        }
              break;

        case 2: {
            cout << "Qual valor voce deseja remover? \nParte real:" << endl;
            cin >> aux2;
            cout << "Parte imaginaria:" << endl;
            cin >> aux3;
            Complexo* remover = new Complexo(aux2, aux3);

            arvore.remover(*remover);
        }
              break;

        case 3: {
            cout << "Qual valor você deseja procurar para obter sua página? \nParte real:" << endl;
            cin >> aux2;
            cout << "Parte imaginaria:" << endl;
            cin >> aux3;
            Complexo* procurar_na_pagina = new Complexo(aux2, aux3);

            arvore.procurar_pagina(*procurar_na_pagina);
        }
              break;

        case 4: {
            cout << "\nQual numero complexo deseja procurar? " << endl;
            cout << "Parte real: " << endl;
            cin >> v1;
            cout << "Parte imaginaria: " << endl;
            cin >> v2;

            Complexo* aux_procurar = new Complexo(v1, v2);

            if (arvore.procurar(*aux_procurar) == NULL) {
                cout << " Valor nao encontrado" << endl;

            }
            else
                cout << "O Valor está na arvore! " << *aux_procurar << endl;
        }
              break;

        case 5: {
            cout << "Saindo do programa..." << endl;

        }
              break;

        default: {
            cout << "Opcao incorreta :(. \n" << "Digite novamente.\n";
        }


               break;
        }

    } while (opcao != 5);

    return 0;
}