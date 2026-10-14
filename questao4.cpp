#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

/*
resolucao completa da questao 4 - arvore avl

neste arquivo estao todas as respostas, analises e o codigo em c++
com as rotacoes, insercao e remocao balanceadas.

----------------------------------------------------------------------
itens c e d: desbalanceamentos durante as insercoes e arvores ajustadas
----------------------------------------------------------------------

sequencia de insercao: 50, 30, 70, 20, 40, 10, 25, 35, 45, 60, 80, 90, 85

1) inserindo o 10:
- situacao: quando insere o 10 a esquerda do 20, o no 50 desbalanceia
- fb do no 50: +2 (altura esq = 3, altura dir = 1)
- tipo de caso: LL (inserido a esquerda do filho esquerdo)
- rotacao: rotacao simples a direita sobre o no 50

arvore antes da rotacao:                 arvore depois da rotacao:
          50 (fb=+2)                                   30 (fb=0)
         /  \                                        /    \
       30    70                                    20      50 (fb=0)
      /  \                                        /       /  \
    20    40                                     10      40   70
   /
  10

2) inserindo o 90:
- situacao: depois de inserir 25, 35, 45, 60 e 80, ao inserir o 90 na direita
  do 80, a raiz 30 fica desbalanceada (altura esq = 2, altura dir = 4)
- fb do no 30: -2
- tipo de caso: RR (inserido a direita do filho direito)
- rotacao: rotacao simples a esquerda sobre o no 30

arvore antes da rotacao:
                  30 (fb=-2)
                /    \
              20      50 (fb=-1)
             /  \    /  \
            10  25  40   70 (fb=-1)
                   /  \  /  \
                  35  45 60  80 (fb=-1)
                               \
                                90

arvore depois da rotacao:
                  50 (fb=0)
                /    \
             30        70 (fb=-1)
           /    \     /   \
         20      40  60    80 (fb=-1)
        /  \    /  \         \
       10  25  35  45         90

3) inserindo o 85:
- situacao: o 85 entra como filho esquerdo do 90. o no 80 desbalanceia
- fb do no 80: -2 (e o filho direito 90 tem fb = +1)
- tipo de caso: RL (inserido a esquerda do filho direito)
- rotacao: rotacao dupla a esquerda (rotacao a direita no 90 e depois a esquerda no 80)

subarvore no 80 antes:          passo 1 (dir no 90):           passo 2 (esq no 80):
      80 (fb=-2)                      80                             85 (fb=0)
        \                               \                           /  \
         90 (fb=+1)                      85                       80    90
        /                                  \
       85                                   90

arvore final completa apos todas as insercoes:
                  50 (fb=0)
               /             \
         30                       70 (fb=-1)
      /      \                  /    \
    20        40              60      85 (fb=0)
   /  \      /  \                    /  \
  10  25    35  45                  80  90

----------------------------------------------------------------------
item e: relatorio da arvore avl final construida
----------------------------------------------------------------------
- pre-ordem: 50, 30, 20, 10, 25, 40, 35, 45, 70, 60, 85, 80, 90
- em-ordem: 10, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 85, 90
- pos-ordem: 10, 25, 20, 35, 45, 40, 30, 60, 80, 90, 85, 70, 50
- altura da arvore: 4
- fatores de balanceamento (fb):
  50: 0 | 30: 0 | 20: 0 | 10: 0 | 25: 0 | 40: 0 | 35: 0 | 45: 0 | 70: -1 | 60: 0 | 85: 0 | 80: 0 | 90: 0

----------------------------------------------------------------------
item f: analise das operacoes de remocao (30, 70 e 50)
----------------------------------------------------------------------

1. removendo o 30:
- substitui pelo sucessor (menor elemento a direita), que e o 35
- remove o 35 da posicao original (ele era folha em 40->esq)
- o no 40 fica com fb = -1 e a arvore continua balanceada sem precisar rodar nada

arvore resultante apos remover o 30:
                  50 (fb=0)
               /             \
         35                       70 (fb=-1)
      /      \                  /    \
    20        40 (fb=-1)      60      85 (fb=0)
   /  \         \                    /  \
  10  25         45                 80  90

2. removendo o 70:
- substitui pelo sucessor, que e o 80 (menor a direita de 70, vindo de 85->esq)
- remove o 80 original. o no 85 fica so com o filho 90 (fb = -1)
- o no 80 passa a ter fb = -1. nenhuma rotacao necessaria

arvore resultante apos remover o 70:
                  50 (fb=0)
               /             \
         35                       80 (fb=-1)
      /      \                  /    \
    20        40 (fb=-1)      60      85 (fb=-1)
   /  \         \                       \
  10  25         45                      90

3. removendo o 50:
- substitui pelo sucessor da raiz, que e o 60 (menor a direita de 50, filho esquerdo do 80)
- quando o 60 e retirado, o no 80 fica sem filho na esquerda (altura 0) e com altura 2 na direita
- desbalanceamento gerado no no 80: fb(80) = 0 - 2 = -2
- como o filho direito 85 tem fb = -1 (<= 0), cai no caso RR
- rotacao necessaria: rotacao simples a esquerda no no 80
- o no 85 sobe como raiz da subarvore direita, tendo 80 a esquerda e 90 a direita
- nova raiz da arvore inteira passa a ser o 60 com fb = +1

arvore final resultante apos remover o 50 e balancear:
                  60 (fb=+1)
               /             \
         35                       85 (fb=0)
      /      \                  /    \
    20        40 (fb=-1)      80      90 (fb=0)
   /  \         \
  10  25         45

----------------------------------------------------------------------
desafio adicional:
----------------------------------------------------------------------
em uma arvore binaria de busca comum, quando os dados entram ordenados
(crescente ou decrescente), ela se degenera completamente virando uma
lista encadeada. com isso, a altura vai pra n e o custo das buscas,
insercoes e remocoes passa a ser O(n) no pior caso.
na arvore avl isso nao acontece porque a regra do balanceamento nao deixa
a diferenca de altura de nenhum no passar de 1. sempre que isso ameaca
acontecer, as rotacoes corrigem a arvore na hora em tempo O(1).
assim, a altura da avl fica sempre limitada por logaritmo do numero de nos,
garantindo que qualquer operacao rode em tempo maximo O(log n).
*/

// item a: definicao do no da avl guardando a chave, altura e os ponteiros pros filhos
typedef struct No {
    int chave;
    int altura;
    struct No *esq;
    struct No *dir;
} No;

// item b: devolve a altura guardada no no, ou 0 se o ponteiro for nulo
int altura(No *no) {
    if (no == NULL) {
        return 0;
    }
    return no->altura;
}

// item b: calcula a diferenca da altura da subarvore esquerda pela direita
int fatorBalanceamento(No *no) {
    if (no == NULL) {
        return 0;
    }
    return altura(no->esq) - altura(no->dir);
}

// funcao simples pra ver qual dos dois valores e o maior
int maximo(int a, int b) {
    return (a > b) ? a : b;
}

// item b: rotacao simples pra direita (caso ll) quando pesa no lado esquerdo
No* rotacaoDireita(No *y) {
    No *x = y->esq;
    No *T2 = x->dir;

    // mexe nos ponteiros pra descer o y e subir o x
    x->dir = y;
    y->esq = T2;

    // recalcula as alturas comecando de quem ficou mais embaixo
    y->altura = 1 + maximo(altura(y->esq), altura(y->dir));
    x->altura = 1 + maximo(altura(x->esq), altura(x->dir));

    return x; // x agora virou a raiz dessa subarvore
}

// item b: rotacao simples pra esquerda (caso rr) quando pesa no lado direito
No* rotacaoEsquerda(No *x) {
    No *y = x->dir;
    No *T2 = y->esq;

    // mexe nos ponteiros pra descer o x e subir o y
    y->esq = x;
    x->dir = T2;

    // recalcula as alturas
    x->altura = 1 + maximo(altura(x->esq), altura(x->dir));
    y->altura = 1 + maximo(altura(y->esq), altura(y->dir));

    return y; // y agora virou a raiz dessa subarvore
}

// item b: insere a chave na arvore e faz o rebalanceamento automatico subindo na recursao
No* inserir(No *raiz, int chave) {
    // se achou o ponto vazio, cria o no com altura 1
    if (raiz == NULL) {
        No *novo = (No*) malloc(sizeof(No));
        if (novo != NULL) {
            novo->chave = chave;
            novo->altura = 1;
            novo->esq = NULL;
            novo->dir = NULL;
        }
        return novo;
    }

    // navegacao normal de arvore binaria de busca
    if (chave < raiz->chave) {
        raiz->esq = inserir(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = inserir(raiz->dir, chave);
    } else {
        return raiz; // chave repetida nao insere
    }

    // atualiza a altura deste no na volta da recursao
    raiz->altura = 1 + maximo(altura(raiz->esq), altura(raiz->dir));

    // calcula o fb pra ver se desbalanceou
    int balanco = fatorBalanceamento(raiz);

    // caso 1: rotacao simples a direita (LL)
    if (balanco > 1 && chave < raiz->esq->chave) {
        return rotacaoDireita(raiz);
    }

    // caso 2: rotacao simples a esquerda (RR)
    if (balanco < -1 && chave > raiz->dir->chave) {
        return rotacaoEsquerda(raiz);
    }

    // caso 3: rotacao dupla a direita (LR)
    if (balanco > 1 && chave > raiz->esq->chave) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    // caso 4: rotacao dupla a esquerda (RL)
    if (balanco < -1 && chave < raiz->dir->chave) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// item f: acha o menor no de uma subarvore pra achar o sucessor
No* noMinimo(No *no) {
    No *atual = no;
    while (atual != NULL && atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

// item f: remove a chave da avl e aplica as rotacoes se precisar
No* remover(No *raiz, int chave) {
    if (raiz == NULL) {
        return raiz;
    }

    // procura o valor pra remover
    if (chave < raiz->chave) {
        raiz->esq = remover(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = remover(raiz->dir, chave);
    } else {
        // achou o no! agora trata os casos:
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
            // caso de folha ou com apenas 1 filho
            No *temp = raiz->esq ? raiz->esq : raiz->dir;

            if (temp == NULL) {
                // se for folha, so apaga ele
                temp = raiz;
                raiz = NULL;
            } else {
                // se tem 1 filho, passa as informacoes do filho pra ca
                *raiz = *temp;
            }
            free(temp);
        } else {
            // no com dois filhos: pega o sucessor (menor no da direita)
            No *temp = noMinimo(raiz->dir);

            // copia a chave do sucessor pra ca
            raiz->chave = temp->chave;

            // e manda remover o sucessor la na direita
            raiz->dir = remover(raiz->dir, temp->chave);
        }
    }

    // se a arvore ficou vazia apos a remocao
    if (raiz == NULL) {
        return raiz;
    }

    // atualiza a altura
    raiz->altura = 1 + maximo(altura(raiz->esq), altura(raiz->dir));

    // checa o fb
    int balanco = fatorBalanceamento(raiz);

    // caso 1: rotacao simples a direita (LL)
    if (balanco > 1 && fatorBalanceamento(raiz->esq) >= 0) {
        return rotacaoDireita(raiz);
    }

    // caso 2: rotacao dupla a direita (LR)
    if (balanco > 1 && fatorBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    // caso 3: rotacao simples a esquerda (RR)
    if (balanco < -1 && fatorBalanceamento(raiz->dir) <= 0) {
        return rotacaoEsquerda(raiz);
    }

    // caso 4: rotacao dupla a esquerda (RL)
    if (balanco < -1 && fatorBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// percurso pre-ordem: raiz -> esquerda -> direita
void preOrdem(No *raiz) {
    if (raiz != NULL) {
        cout << raiz->chave << " ";
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

// percurso em-ordem: esquerda -> raiz -> direita (imprime ordenado)
void emOrdem(No *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        cout << raiz->chave << " ";
        emOrdem(raiz->dir);
    }
}

// percurso pos-ordem: esquerda -> direita -> raiz
void posOrdem(No *raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        cout << raiz->chave << " ";
    }
}

// imprime o fator de balanceamento de cada no em ordem crescente
void imprimeFatores(No *raiz) {
    if (raiz != NULL) {
        imprimeFatores(raiz->esq);
        cout << raiz->chave << ": " << fatorBalanceamento(raiz) << " | ";
        imprimeFatores(raiz->dir);
    }
}

// funcao pra limpar a memoria alocada de todos os nos antes de fechar
void liberaArvore(No *raiz) {
    if (raiz != NULL) {
        liberaArvore(raiz->esq);
        liberaArvore(raiz->dir);
        free(raiz);
    }
}

int main() {
    No *raiz = NULL;

    // sequencia exata do enunciado: 50, 30, 70, 20, 40, 10, 25, 35, 45, 60, 80, 90, 85
    int valores[] = {50, 30, 70, 20, 40, 10, 25, 35, 45, 60, 80, 90, 85};
    int total = sizeof(valores) / sizeof(valores[0]);

    cout << "--- Inserindo valores na Arvore AVL ---\n";
    for (int i = 0; i < total; i++) {
        raiz = inserir(raiz, valores[i]);
    }

    cout << "\n--- Item e) Relatorio Final da Arvore AVL Construida ---\n";
    cout << "- Pre-ordem: ";
    preOrdem(raiz);
    cout << "\n- Em-ordem: ";
    emOrdem(raiz);
    cout << "\n- Pos-ordem: ";
    posOrdem(raiz);
    cout << "\n- Altura da Arvore: " << altura(raiz) << "\n";
    cout << "- Fatores de Balanceamento (FB):\n";
    imprimeFatores(raiz);
    cout << "\n\n";

    // item f: remocoes na ordem do enunciado (30, 70 e 50)
    cout << "--- Item f) Operacoes de Remocao ---\n";

    cout << "\n>>> 1. Removendo 30...\n";
    raiz = remover(raiz, 30);
    cout << "Arvore em-ordem: ";
    emOrdem(raiz);
    cout << "\nFB dos nos: ";
    imprimeFatores(raiz);
    cout << "\n";

    cout << "\n>>> 2. Removendo 70...\n";
    raiz = remover(raiz, 70);
    cout << "Arvore em-ordem: ";
    emOrdem(raiz);
    cout << "\nFB dos nos: ";
    imprimeFatores(raiz);
    cout << "\n";

    cout << "\n>>> 3. Removendo 50...\n";
    raiz = remover(raiz, 50);
    cout << "Arvore em-ordem: ";
    emOrdem(raiz);
    cout << "\nFB dos nos: ";
    imprimeFatores(raiz);
    cout << "\n";

    // libera toda a memoria alocada
    liberaArvore(raiz);

    return 0;
}
