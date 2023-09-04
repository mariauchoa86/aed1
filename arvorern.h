#ifndef ARVORERN_H
#define ARVORERN_H

// Definição das cores dos nós
#define PRETO 0
#define VERMELHO 1

// Estrutura para representar um nó na árvore
typedef struct No 
{
    int valor;
    int cor; // 0 para preto, 1 para vermelho
    struct No *pai;
    struct No *esquerda;
    struct No *direita;
} No;

// Protótipos das funções
No* criarNo(int valor);
void rotacionarEsquerda(No **raiz, No *x);
void rotacionarDireita(No **raiz, No *y);
void inserir(No **raiz, int valor);
void emOrdem(No* raiz);
No* buscar(No* raiz, int valor);
No* encontrarMinimo(No* raiz);
No* deletar(No *raiz, int valor);
No* balancear(No *raiz, No *noExcluido, No *paiDoNoExcluido);

#endif


