#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <climits>

using namespace std;

// estrutura do nó da árvore binária de busca (abb) sugerida na atividade
typedef struct arv {
    int info;
    struct arv *esq;
    struct arv *dir;
} Arv;

// função auxiliar simples para criar e alocar um novo nó
Arv* cria_no(int valor) {
    Arv *novo = (Arv*) malloc(sizeof(Arv));
    if (novo != NULL) {
        novo->info = valor;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

// 1. inserção: insere um valor na abb respeitando a regra
// valores menores ficam na subárvore esquerda e maiores na direita
Arv* abb_insere(Arv *raiz, int valor) {
    // se chegamos num ponto vazio, aqui é onde o novo nó deve ser criado
    if (raiz == NULL) {
        return cria_no(valor);
    }

    // se o valor for menor, insere recursivamente para o lado esquerdo
    if (valor < raiz->info) {
        raiz->esq = abb_insere(raiz->esq, valor);
    }
    // se for maior, insere recursivamente para o lado direito
    else if (valor > raiz->info) {
        raiz->dir = abb_insere(raiz->dir, valor);
    }
    // obs: valores iguais são ignorados conforme enunciado (chaves distintas)

    return raiz;
}

// 2. busca recursiva: procura um valor na árvore
// retorna o ponteiro para o nó onde o valor foi encontrado ou NULL se não existir
Arv* abb_busca(Arv *raiz, int valor) {
    // se a raiz for nula ou se encontramos o valor no nó atual, já temos a resposta
    if (raiz == NULL || raiz->info == valor) {
        return raiz;
    }

    // se o valor procurado for menor, procura na subárvore da esquerda
    if (valor < raiz->info) {
        return abb_busca(raiz->esq, valor);
    }

    // caso contrário, procura na subárvore da direita
    return abb_busca(raiz->dir, valor);
}

// função auxiliar para encontrar o maior elemento de uma subárvore
// esse elemento é o predecessor imediato (o elemento mais à direita da subárvore esquerda)
Arv* maior_elemento(Arv *raiz) {
    Arv *atual = raiz;
    while (atual != NULL && atual->dir != NULL) {
        atual = atual->dir;
    }
    return atual;
}

// 3. remoção: remove um nó cobrindo obrigatoriamente os três casos
// caso 1: nó folha (sem filhos)
// caso 2: nó com apenas um filho (esquerdo ou direito)
// caso 3: nó com dois filhos (substitui pelo predecessor da subárvore esquerda)
Arv* abb_remove(Arv *raiz, int valor) {
    if (raiz == NULL) {
        return NULL; // elemento não foi encontrado na árvore
    }

    // primeiro, navegamos pela árvore até encontrar o nó que tem o valor desejado
    if (valor < raiz->info) {
        raiz->esq = abb_remove(raiz->esq, valor);
    } else if (valor > raiz->info) {
        raiz->dir = abb_remove(raiz->dir, valor);
    } else {
        // encontramos o nó a ser removido! agora tratamos os 3 casos:

        // caso 1: o nó é uma folha (não tem filho nem na esquerda nem na direita)
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }

        // caso 2a: o nó só tem o filho direito
        if (raiz->esq == NULL) {
            Arv *filho = raiz->dir;
            free(raiz);
            return filho;
        }

        // caso 2b: o nó só tem o filho esquerdo
        if (raiz->dir == NULL) {
            Arv *filho = raiz->esq;
            free(raiz);
            return filho;
        }

        // caso 3: o nó tem dois filhos
        // conforme a regra da questão, pegamos o predecessor (maior elemento da subárvore esquerda)
        Arv *predecessor = maior_elemento(raiz->esq);

        // copiamos a informação do predecessor para o nó atual
        raiz->info = predecessor->info;

        // agora removemos o nó predecessor original da subárvore esquerda
        raiz->esq = abb_remove(raiz->esq, predecessor->info);
    }

    return raiz;
}

// 4. altura da árvore: considera que uma árvore só com a raiz tem altura 0
// uma árvore vazia (NULL) tem altura -1 por convenção matemática
int abb_altura(Arv *raiz) {
    if (raiz == NULL) {
        return -1; // árvore vazia tem altura -1; assim a raiz única resulta em 0
    }

    int alt_esq = abb_altura(raiz->esq);
    int alt_dir = abb_altura(raiz->dir);

    return 1 + max(alt_esq, alt_dir);
}

// 5. quantidade de folhas: calcula recursivamente o total de nós folha
int abb_folhas(Arv *raiz) {
    if (raiz == NULL) {
        return 0; // árvore vazia não tem folhas
    }

    // se o nó não tem filhos à esquerda e nem à direita, ele é uma folha
    if (raiz->esq == NULL && raiz->dir == NULL) {
        return 1;
    }

    // senão, somamos as folhas do lado esquerdo com as do lado direito
    return abb_folhas(raiz->esq) + abb_folhas(raiz->dir);
}

// função auxiliar recursiva para encontrar o k-ésimo menor elemento
// faz percurso em-ordem incrementando o contador até atingir k, sem criar vetores adicionais
bool kesimo_menor_aux(Arv *raiz, int k, int &contador, int *valor) {
    if (raiz == NULL) {
        return false;
    }

    // primeiro visita tudo que está à esquerda (valores menores)
    if (kesimo_menor_aux(raiz->esq, k, contador, valor)) {
        return true;
    }

    // visita a raiz atual e conta este elemento
    contador++;
    if (contador == k) {
        *valor = raiz->info; // encontramos exatamente o k-ésimo menor elemento!
        return true;
    }

    // por fim, visita a subárvore da direita
    return kesimo_menor_aux(raiz->dir, k, contador, valor);
}

// 6. k-ésimo menor elemento: armazena em 'valor' o k-ésimo elemento em ordem crescente
// retorna 1 se encontrou ou 0 se k for inválido / maior que o número de nós
int abb_kesimo_menor(Arv *raiz, int k, int *valor) {
    if (k <= 0 || valor == NULL) {
        return 0;
    }

    int contador = 0;
    if (kesimo_menor_aux(raiz, k, contador, valor)) {
        return 1; // sucesso
    }

    return 0; // não encontrado (árvore tem menos nós que k)
}

// função auxiliar para validar se a árvore inteira respeita os limites mínimo e máximo
bool eh_abb_aux(Arv *raiz, long min_val, long max_val) {
    if (raiz == NULL) {
        return true; // árvore vazia é considerada válida
    }

    // o valor do nó precisa estar estritamente dentro do intervalo permitido
    if (raiz->info <= min_val || raiz->info >= max_val) {
        return false;
    }

    // para o filho esquerdo, o teto passa a ser a info do nó atual
    // para o filho direito, o piso passa a ser a info do nó atual
    return eh_abb_aux(raiz->esq, min_val, raiz->info) &&
           eh_abb_aux(raiz->dir, raiz->info, max_val);
}

// 7. verificação de abb: checa se a estrutura inteira respeita as regras de abb
// retorna 1 se for abb válida ou 0 caso contrário
int eh_abb(Arv *raiz) {
    return eh_abb_aux(raiz, LONG_MIN, LONG_MAX) ? 1 : 0;
}

// 8. percurso em ordem: imprime os elementos em ordem crescente (esquerda -> raiz -> direita)
void abb_imprime_em_ordem(Arv *raiz) {
    if (raiz != NULL) {
        abb_imprime_em_ordem(raiz->esq);
        cout << raiz->info << " ";
        abb_imprime_em_ordem(raiz->dir);
    }
}

// função para liberar toda a memória alocada para os nós da árvore
void libera_arvore(Arv *raiz) {
    if (raiz != NULL) {
        libera_arvore(raiz->esq);
        libera_arvore(raiz->dir);
        free(raiz);
    }
}

int main() {
    Arv *raiz = NULL;

    // construção da árvore inicial conforme o enunciado:
    // 50, 30, 70, 20, 40, 60, 80, 10, 25, 65
    int iniciais[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 65};
    int total_iniciais = sizeof(iniciais) / sizeof(iniciais[0]);

    for (int i = 0; i < total_iniciais; i++) {
        raiz = abb_insere(raiz, iniciais[i]);
    }

    cout << "Arvore inicial construida com sucesso.\n";

    // sequência de operações do enunciado:
    // 1. inserir 35
    raiz = abb_insere(raiz, 35);

    // 2. inserir 75
    raiz = abb_insere(raiz, 75);

    // 3. remover 20
    raiz = abb_remove(raiz, 20);

    // 4. remover 70
    raiz = abb_remove(raiz, 70);

    // 5. remover 50
    raiz = abb_remove(raiz, 50);

    // 6. inserir 55
    raiz = abb_insere(raiz, 55);

    // 7. inserir 15
    raiz = abb_insere(raiz, 15);

    cout << "Sequencia de operacoes (1 a 7) finalizada com sucesso.\n";

    // libera a memória alocada
    libera_arvore(raiz);

    return 0;
}
