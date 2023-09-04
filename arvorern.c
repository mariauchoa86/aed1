#include <stdio.h>
#include <stdlib.h>
#include "arvorern.h" // Incluindo o arquivo de cabeçalho

// Função para obter a cor de um nó
int obterCor(No *n) 
{
    if (n == NULL) 
    {
        return PRETO; // Nós nulos são considerados pretos
    }
    return n->cor;
}

// Função para definir a cor de um nó
void definirCor(No *n, int cor) 
{
    if (n != NULL) {
        n->cor = cor;
    }
}

// Função para criar um novo nó
No* criarNo(int valor) 
{
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->cor = VERMELHO; // Novos nós são sempre vermelhos
    novoNo->pai = NULL;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para rotacionar à esquerda
void rotacionarEsquerda(No **raiz, No *x) 
{
    No *y = x->direita;
    x->direita = y->esquerda;
    if (y->esquerda != NULL) 
    {
        y->esquerda->pai = x;
    }
    y->pai = x->pai;
    if (x->pai == NULL) 
    {
        *raiz = y;
    } else if (x == x->pai->esquerda) 
    {
        x->pai->esquerda = y;
    } else {
        x->pai->direita = y;
    }
    y->esquerda = x;
    x->pai = y;
}

// Função para rotacionar à direita
void rotacionarDireita(No **raiz, No *y) 
{
    No *x = y->esquerda;
    y->esquerda = x->direita;
    if (x->direita != NULL) 
    {
        x->direita->pai = y;
    }
    x->pai = y->pai;
    if (y->pai == NULL) {
        *raiz = x;
    } else if (y == y->pai->esquerda) 
    {
        y->pai->esquerda = x;
    } else {
        y->pai->direita = x;
    }
    x->direita = y;
    y->pai = x;
}


// Função para inserir um nó na árvore rubro-negra
void inserir(No **raiz, int valor) 
{
    No *novoNo = criarNo(valor);
    No *x = *raiz;
    No *y = NULL;

    while (x != NULL) 
    {
        y = x;
        if (novoNo->valor < x->valor) 
        {
            x = x->esquerda;
        } else {
            x = x->direita;
        }
    }

    novoNo->pai = y;
    if (y == NULL) 
    {
        *raiz = novoNo; // Árvore vazia
    } else if (novoNo->valor < y->valor) 
    {
        y->esquerda = novoNo;
    } else {
        y->direita = novoNo;
    }

   // Balanceamento
    while (novoNo != *raiz && novoNo->pai->cor == VERMELHO) 
    {
        if (novoNo->pai == novoNo->pai->pai->esquerda) 
        {
            No *tio = novoNo->pai->pai->direita;
            if (tio != NULL && tio->cor == VERMELHO) 
            {
                novoNo->pai->cor = PRETO;
                tio->cor = PRETO;
                novoNo->pai->pai->cor = VERMELHO;
                novoNo = novoNo->pai->pai;
            } else {
                if (novoNo == novoNo->pai->direita) 
                {
                    novoNo = novoNo->pai;
                    rotacionarEsquerda(raiz, novoNo);
                }
                novoNo->pai->cor = PRETO;
                novoNo->pai->pai->cor = VERMELHO;
                rotacionarDireita(raiz, novoNo->pai->pai);
            }
        } else {
            No *tio = novoNo->pai->pai->esquerda;
            if (tio != NULL && tio->cor == VERMELHO) 
            {
                novoNo->pai->cor = PRETO;
                tio->cor = PRETO;
                novoNo->pai->pai->cor = VERMELHO;
                novoNo = novoNo->pai->pai;
            } else {
                if (novoNo == novoNo->pai->esquerda) 
                {
                    novoNo = novoNo->pai;
                    rotacionarDireita(raiz, novoNo);
                }
                novoNo->pai->cor = PRETO;
                novoNo->pai->pai->cor = VERMELHO;
                rotacionarEsquerda(raiz, novoNo->pai->pai);
            }
        }
    }
    (*raiz)->cor = PRETO;
}

// Função para percorrer a árvore em ordem
void emOrdem(No* raiz) 
{
    if (raiz != NULL) 
    {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}
// Função para buscar um valor na árvore
No* buscar(No* raiz, int valor) 
{
    if (raiz == NULL || raiz->valor == valor) 
    {
        return raiz;
    }

    if (valor < raiz->valor) 
    {
        return buscar(raiz->esquerda, valor);
    }

    return buscar(raiz->direita, valor);
}

No* encontrarMinimo(No* no) 
{
    while (no->esquerda != NULL) 
    {
        no = no->esquerda;
    }
    return no;
}
     
// Balanceamento
// Função auxiliar para balancear a árvore após a exclusão
No* balancear(No *raiz, No *noExcluido, No *paiDoNoExcluido) 
{
    if (noExcluido != NULL) 
    {
        if (obterCor(noExcluido) == VERMELHO || obterCor(paiDoNoExcluido) == VERMELHO) 
        {
            definirCor(noExcluido, PRETO);
        } else {
            No* irmao;

            while (noExcluido != raiz && obterCor(noExcluido) == PRETO) 
            {
                if (noExcluido == paiDoNoExcluido->esquerda) 
                {
                    irmao = paiDoNoExcluido->direita;

                    if (irmao != NULL && obterCor(irmao) == VERMELHO) 
                    {
                        definirCor(irmao, PRETO);
                        definirCor(paiDoNoExcluido, VERMELHO);
                        rotacionarEsquerda(&raiz, paiDoNoExcluido);
                        irmao = paiDoNoExcluido->direita;
                    }

                    if (irmao != NULL && (irmao->esquerda == NULL || obterCor(irmao->esquerda) == PRETO) && (irmao->direita == NULL || obterCor(irmao->direita) == PRETO)) 
                    {
                        definirCor(irmao, VERMELHO);
                        noExcluido = paiDoNoExcluido;
                        paiDoNoExcluido = noExcluido->pai;
                    } else {
                        if (irmao != NULL && (irmao->direita == NULL || obterCor(irmao->direita) == PRETO)) 
                        {
                            definirCor(irmao->esquerda, PRETO);
                            definirCor(irmao, VERMELHO);
                            rotacionarDireita(&raiz, irmao);
                            irmao = paiDoNoExcluido->direita;
                        }

                        definirCor(irmao, obterCor(paiDoNoExcluido));
                        definirCor(paiDoNoExcluido, PRETO);
                        definirCor(irmao->direita, PRETO);
                        rotacionarEsquerda(&raiz, paiDoNoExcluido);

                        noExcluido = raiz;
                    }
                } else {
                    irmao = paiDoNoExcluido->esquerda;

                    if (irmao != NULL && obterCor(irmao) == VERMELHO) 
                    {
                        definirCor(irmao, PRETO);
                        definirCor(paiDoNoExcluido, VERMELHO);
                        rotacionarDireita(&raiz, paiDoNoExcluido);
                        irmao = paiDoNoExcluido->esquerda;
                    }

                    if (irmao != NULL && (irmao->esquerda == NULL || obterCor(irmao->esquerda) == PRETO) && (irmao->direita == NULL || obterCor(irmao->direita) == PRETO)) 
                    {
                        definirCor(irmao, VERMELHO);
                        noExcluido = paiDoNoExcluido;
                        paiDoNoExcluido = noExcluido->pai;
                    } else {
                        if (irmao != NULL && (irmao->esquerda == NULL || obterCor(irmao->esquerda) == PRETO)) 
                        {
                            definirCor(irmao->direita, PRETO);
                            definirCor(irmao, VERMELHO);
                            rotacionarEsquerda(&raiz, irmao);
                            irmao = paiDoNoExcluido->esquerda;
                        }

                        definirCor(irmao, obterCor(paiDoNoExcluido));
                        definirCor(paiDoNoExcluido, PRETO);
                        definirCor(irmao->esquerda, PRETO);
                        rotacionarDireita(&raiz, paiDoNoExcluido);

                        noExcluido = raiz;
                    }
                }
            }

            if (noExcluido != NULL) 
            {
                definirCor(noExcluido, PRETO);
            }
        }
    }

    return raiz;
}


No* deletar(No *raiz, int valor) 
{
    if (raiz == NULL) 
    {
        return raiz;
    }

    if (valor < raiz->valor) 
    {
        raiz->esquerda = deletar(raiz->esquerda, valor);
    } else if (valor > raiz->valor) 
    {
        raiz->direita = deletar(raiz->direita, valor);
    } else {
        // Caso o nó tenha um ou nenhum filho
        if (raiz->esquerda == NULL || raiz->direita == NULL) 
        {
            No *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            // Caso o nó não tenha filho
            if (temp == NULL) 
            {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }

            free(temp);
        } else {
            // Caso o nó tenha dois filhos
            No *temp = encontrarMinimo(raiz->direita);
            raiz->valor = temp->valor;
            raiz->direita = deletar(raiz->direita, temp->valor);
        }
    }

    // Se a árvore tinha apenas um nó (raiz)
    if (raiz == NULL) 
    {
        return raiz;
    }

    // Balanceamento
    if (obterCor(raiz) == PRETO) 
    {
        raiz = balancear(raiz, raiz, raiz->pai);
    }

    return raiz;
}
