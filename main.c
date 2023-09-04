#include <stdio.h>
#include <stdlib.h>
#include "arvorern.h"

int main() 
{
    No *raiz = NULL;

    // Inserindo valores na árvore
    inserir(&raiz, 10);
    inserir(&raiz, 20);
    inserir(&raiz, 30);
    inserir(&raiz, 15);
    inserir(&raiz, 5);

    // Exibindo a árvore em ordem
    printf("Árvore em ordem: ");
    emOrdem(raiz);
    printf("\n");

    // Buscando um valor na árvore
    int valorBuscado = 20;
    No *resultadoBusca = buscar(raiz, valorBuscado);
    if (resultadoBusca != NULL) {
        printf("Valor %d encontrado na árvore.\n", valorBuscado);
    } else {
        printf("Valor %d não encontrado na árvore.\n", valorBuscado);
    }

    // Excluindo um valor da árvore
    int valorExcluir = 20;
    No *noExcluido = buscar(raiz, valorExcluir); // Encontra o nó a ser excluído
    if (noExcluido != NULL) {
        raiz = deletar(raiz, valorExcluir);

        if (raiz != NULL) 
        {
            raiz->cor = PRETO;
        } 
        printf("Valor %d excluído da árvore.\n", valorExcluir);
    } else {
        printf("Valor %d não encontrado para exclusão.\n", valorExcluir);
    }

    // Exibindo a árvore novamente após a exclusão
    printf("Árvore em ordem após a exclusão: ");
    emOrdem(raiz);
    printf("\n");

    // Lembre-se de liberar a memória alocada pela árvore após o uso.
    // Implemente uma função para liberar a memória de forma adequada.

    return 0;
}

