// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha

    //----------------------------------------------------------------------------------------------

//--CODIGO

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//--globais
#define MAX_FILA 10 //tamanho maximo da fila
#define MAX_PILHA 3 //tamanho maximo da pilha
#define QTD_PECAS 5 //quantidade inicial fixa de peças

//--struct do elemento (Peças)
typedef struct{
    char nome; //tipo da peça 
    int idPeca; //id unico da peça
} Pecas;

//--struct da fila (Fila)
typedef struct{
    Pecas tetris[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

//--struct da pilha (Pilha)
typedef struct{
    Pecas tetrisPilha[MAX_PILHA];
    int topo; //--representa o índice do último elemento inserido.
    //--quando a pilha está vazia, o topo é -1.
} Pilha;

//--funçao gerarId para gerar o proximo id
int gerarId(){
    static int idAtual = 1;
    return idAtual++;
}

//--funçao gerarPeca para gerar a proxima peça aleatoriamente
//--as peças tem um tipo (como 'I', 'O', 'T', 'L’), que representa suas formas
Pecas gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Pecas novaPeca;
    novaPeca.nome = tipos[rand() % 4];
    novaPeca.idPeca = gerarId();
    return novaPeca;
}

//---limpar buffer de entrada para evitar problema de leitura consecutiva de scanf e getchar
void limparBuffer(){
    int buffer;
    while ((buffer = getchar()) != '\n' && buffer != EOF);
}

//--inicializar fila
//--antes de usar a fila, seus indices e contadores precisam ser configurados
void inicializarFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
    //--inicializar a fila de peças com um número fixo de elementos (por exemplo, 5)
    for(int i = 0; i < QTD_PECAS; i++){
        Pecas p = gerarPeca();
        f->tetris[f->fim] = p;
        f->fim = (f->fim +1) % MAX_FILA;
        f->total++;
    }
} //--a inicializacao define o ponto de partida, visando seu funcionamento correto desde o inicio

//--inicializar pilha
//--a pilha deve ser inicializada com o valor de topo = -1, indicando que está vazia.
void inicializarPilha(Pilha *p){
    p->topo = -1;
}

//--verificar fila cheia ou vazia
//--fila cheia
int filaCheia(Fila *f){
    return f->total == MAX_FILA;
} //--fila cheia impede novas insercoes, evitando sobreposiçao de dados

//--fila vazia
int filaVazia(Fila *f){
    return f->total == 0;
} //--fila vazia impede remoçoes, evitando acesso a posiçoes invalidas

//-verificar pilha cheia ou vazia
//--pilha cheia
int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1; //--o valor retorna verdadeiro (1) se o topo estiver no último índice possível do vetor.
}

//--a seguir, verificamos se a pilha está vazia, ou seja, se não há elementos inseridos.
int pilhaVazia(Pilha *p) {
    return p->topo == -1; //--O valor retorna verdadeiro (1) se o topo for igual a -1.
}

/*
Enqueue e dequeue são as funções que trazem a característica FIFO para a estrutura de dados fila.
A primeira adiciona novo item no final da fila, enquanto a outra remove o item que representa o início da fila.
Portanto, inserções e remoções não seriam possíveis sem essas duas implementações.
*/

//--enqueue - adiciona um novo item ao final da fila, se houver espaço
void inserir(Fila *f, Pecas p){
    if(filaCheia(f)){
        printf("\nFila cheia. Nao é possivel adicionar mais peças.\n\n");
        return;
    }

    f->tetris[f->fim] = p;
    f->fim = (f->fim +1) % MAX_FILA;
    f->total++;
}

//--dequeue - remove o elemento da frente da fila
void remover(Fila *f, Pecas *p){
    if(filaVazia(f)){
        printf("\nFila vazia. Nao é possivel jogar mais peças.\n\n");
        return;
    }

    *p = f->tetris[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
}
//--o dequeue insere no final e atualiza os controles da fila, e o uso do modulo mantem a circularidade
//--a remoçao retorna o primeiro elemento e ajusta a posiçao de incio da fila

//--inserir (push)
//--adiciona um novo elemento no topo da pilha.
void push(Pilha *p, Pecas novaPeca) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia. Não é possível inserir.\n");
        return;
    }
 
    p->topo++;
    p->tetrisPilha[p->topo] = novaPeca;
} //--o método verifica se a pilha está cheia.
//--em caso negativo, o método incrementa o topo e insere o novo elemento naquela posição.

//--remover (pop)
//--retira o elemento do topo da pilha.
void pop(Pilha *p, Pecas *novaPeca) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Não é possível remover.\n");
        return;
    }

    *novaPeca = p->tetrisPilha[p->topo];
    p->topo--;
} //--o método verifica se a pilha está vazia antes de tentar remover.
//--a função copia o conteúdo do topo para o ponteiro removido, e então reduz o topo.

//--mostrar fila
void mostrarFila(Fila *f){
    printf("Fila atual (%d peças):\n", f->total);
    //--se a fila estiver vazia
    if(filaVazia(f)){
        printf("\nFila vazia.\n");
        return;
    }

    for(int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX_FILA){
        printf("[%c %d] ", f->tetris[idx].nome, f->tetris[idx].idPeca);
    }
    printf("\n");
} //--essa funcao percorre a fila desde o inicio ate o total visto atualmente

//--mostrar pilha
void mostrarPilha(Pilha *p) {
    printf("Pilha de peças reserva (%d) (topo -> base):\n", p->topo + 1);
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c, %d] ", p->tetrisPilha[i].nome, p->tetrisPilha[i].idPeca);
    }
    printf("\n");
}

//--declaracao e exibicao no main
int main(){
    Fila f;
    Pilha p;
    int opcao;
    srand(time(NULL)); //--para gerar peças aleatórias
    inicializarFila(&f); //--inicializa a fila
    inicializarPilha(&p); //--inicializa a pilha

    printf("=================================================\n");
    printf("                  Tetris Stack\n");
    printf("=================================================\n");

     do {
        mostrarFila(&f);
        mostrarPilha(&p);
        printf("\nEscolha uma opção:\n");
        printf("1 - Jogar peça (remover da fila)\n");
        printf("2 - Reservar peça (mover para a pilha)\n");
        printf("3 - Usar peça reservada (do topo da pilha)\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                Pecas jogada;
                remover(&f, &jogada);
                printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.idPeca);
                break;
            case 2:
                Pecas reservada;
                remover(&f, &reservada);
                push(&p, reservada);
                printf("Peça reservada: [%c %d]\n", reservada.nome, reservada.idPeca);
                Pecas novaPeca = gerarPeca();
                inserir(&f, novaPeca);
                break;
            case 3:
                Pecas usada;
                pop(&p, &usada);
                printf("Peça reservada usada: [%c %d]\n", usada.nome, usada.idPeca);
                break;

            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
