#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

// tamanho máximo definido no enunciado para a capacidade da pilha
#define MAX 10

// estrutura que guarda as informações de uma página web visitada
typedef struct {
    char adress[30];
    int connectionType;
} PageData;

// letra a: struct para abrigar a pilha do tipo LIFO sequencial
// armazena o vetor de páginas (com até MAX posições) e o índice do elemento do topo
typedef struct {
    PageData itens[MAX];
    int topo;
} Stack;

// letra b: função que aloca a pilha na memória dinamicamente
// inicializa o topo com -1, que indica que a pilha começa vazia
Stack* inicializarPilha() {
    Stack* pilha = (Stack*) malloc(sizeof(Stack));
    if (pilha != NULL) {
        pilha->topo = -1; // -1 significa pilha vazia
    }
    return pilha;
}

// letra c: função push para empilhar uma nova página visitada
// retorna 1 se a inserção deu certo ou 0 se a pilha já estiver cheia
int push(Stack* pilha, const char* adress, int connectionType) {
    // se o ponteiro da pilha for nulo, não tem como inserir
    if (pilha == NULL) {
        return 0;
    }

    // verifica se a pilha já atingiu a capacidade máxima de 10 elementos
    if (pilha->topo >= MAX - 1) {
        cout << "[Erro] Pilha cheia! Nao foi possivel adicionar: " << adress << endl;
        return 0; // código de erro indicando pilha cheia
    }

    // como há espaço, incrementamos o topo e copiamos os dados da página
    pilha->topo++;
    strncpy(pilha->itens[pilha->topo].adress, adress, sizeof(pilha->itens[pilha->topo].adress) - 1);
    pilha->itens[pilha->topo].adress[sizeof(pilha->itens[pilha->topo].adress) - 1] = '\0'; // garante o fim da string
    pilha->itens[pilha->topo].connectionType = connectionType;

    return 1; // sucesso
}

// sobrecarga aceitando char* para compatibilidade direta caso passe ponteiro não-const
int push(Stack* pilha, char* adress, int connectionType) {
    return push(pilha, (const char*) adress, connectionType);
}

// letra d: função pop para desempilhar e exibir na tela o último endereço visitado
// retorna 1 se removeu com sucesso ou 0 se a pilha já estiver vazia
int pop(Stack* pilha) {
    // se a pilha não existir, retorna erro
    if (pilha == NULL) {
        return 0;
    }

    // verifica se a pilha está vazia (topo em -1)
    if (pilha->topo == -1) {
        cout << "[Erro] Pilha vazia! Nao ha elementos para remover." << endl;
        return 0; // código de erro indicando pilha vazia
    }

    // mostra o endereço da página que está no topo antes de remover
    cout << "Pagina removida: " << pilha->itens[pilha->topo].adress << endl;

    // decrementa o índice do topo, efetivando a remoção do elemento
    pilha->topo--;

    return 1; // sucesso
}

// função principal executando o fluxo exato solicitado no enunciado da atividade
int main() {
    int errorCode;
    Stack* pilha;

    // inicializa a pilha na memória
    pilha = inicializarPilha(); // pilha criada

    cout << "--- Inicio da simulacao do historico de navegacao ---" << endl;

    // sequência de operações de navegação e retorno (push e pop)
    errorCode = push(pilha, "http://icen.ufpa.br", 2);
    errorCode = push(pilha, "http://www.youtube.com", 2);
    errorCode = push(pilha, "https://www.facebook.com", 1);

    errorCode = pop(pilha);

    errorCode = push(pilha, "https://drive.google.com", 1);

    errorCode = pop(pilha);
    errorCode = pop(pilha);
    errorCode = pop(pilha);

    // tentativa extra apenas para mostrar que a função trata o caso de pilha vazia
    errorCode = pop(pilha);
    (void)errorCode; // evita warning de variável definida mas não utilizada

    cout << "--- Fim da simulacao ---" << endl;

    // libera a memória alocada para a pilha antes de encerrar
    free(pilha);

    return 0;
}
