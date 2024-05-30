// Lívia Ferreira dos Santos - Turma AED - RER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 45

typedef struct Livro {
  int codigo;
  char titulo[45];
  int tipo;
  char autor[45];
  struct Livro *proximo;
} Livro;

Livro *inicializarLivro(int codigo, char titulo[], int tipo, char autor[]) {
  Livro *novoLivro = (Livro *)malloc(sizeof(Livro));
  novoLivro->codigo = codigo;
  strcpy(novoLivro->titulo, titulo);
  novoLivro->tipo = tipo;
  strcpy(novoLivro->autor, autor);
  novoLivro->proximo = NULL;
  return novoLivro;
}

void inserirLivro(Livro **inicio, Livro *novoLivro) {
  if (*inicio == NULL) {
    *inicio = novoLivro;
  } else {
    Livro *atual = *inicio;
    while (atual->proximo != NULL) {
      atual = atual->proximo;
    }
    atual->proximo = novoLivro;
  }
}

void removerLivro(Livro **inicio, int codigo) {
  Livro *aux = *inicio, *anterior = NULL;

  if (aux != NULL && aux->codigo == codigo) {
    *inicio = aux->proximo;
    free(aux);
    return;
  }

  while (aux != NULL && aux->codigo != codigo) {
    anterior = aux;
    aux = aux->proximo;
  }

  if (aux == NULL)
    return;

  anterior->proximo = aux->proximo;
  free(aux);
}

void exibirLivrosPorTipo(Livro *inicio, int tipo) {
  Livro *atual = inicio;
  while (atual != NULL) {
    if (atual->tipo == tipo) {
      printf("Código: %d\nTítulo: %s\nAutor(es): %s\n\n", atual->codigo,
             atual->titulo, atual->autor);
    }
    atual = atual->proximo;
  }
}

int main() {
  Livro *prateleira[3] = {NULL};
  int totalLivros = 0;

  while (1) {
    int opcao;
    printf(
        "Escolha uma opção:\n1. Inserir livro\n2. Remover livro\n3. Sair - "
        "Livros na prateleira de livros \nDigite o código da opção desejada: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
      if (totalLivros >= MAX_LIVROS) {
        printf("A prateleira está cheia!\n");
        continue;
      }
      int codigo, tipo;
      char titulo[50], autor[50];
      printf("Digite o código do livro: ");
      scanf("%d", &codigo);
      printf("Digite o título do livro: ");
      scanf(" %[^\n]s", titulo);
      printf("Digite o tipo do livro (1 - Romance, 2 - Policial, 3 - Não "
             "ficção): ");
      scanf("%d", &tipo);
      printf("Digite o(s) autor(es) do livro: ");
      scanf(" %[^\n]s", autor);

      if (tipo < 1 || tipo > 3) {
        printf("Tipo de livro inválido!\n");
        continue;
      }

      inserirLivro(&prateleira[tipo - 1],
                   inicializarLivro(codigo, titulo, tipo, autor));
      totalLivros++;
      printf("Livro inserido com sucesso!\n");
    } else if (opcao == 2) {
      int codigo, tipo;
      printf("Digite o código do livro que deseja remover: ");
      scanf("%d", &codigo);
      printf("Digite o tipo do livro que deseja remover (1 - Romance, 2 - "
             "Policial, 3 - Não ficção): ");
      scanf("%d", &tipo);

      if (tipo < 1 || tipo > 3) {
        printf("Dado inválido!\n");
        continue;
      }

      removerLivro(&prateleira[tipo - 1], codigo);
      totalLivros--;
      printf("Livro removido!\n");
    } else if (opcao == 3) {
      break;
    } else {
      printf("Opção inválida!\n");
    }
  }

  printf("\nLivros de Romance:\n");
  exibirLivrosPorTipo(prateleira[0], 1);
  printf("Livros Policiais:\n");
  exibirLivrosPorTipo(prateleira[1], 2);
  printf("Livros de Não Ficção:\n");
  exibirLivrosPorTipo(prateleira[2], 3);

  for (int i = 0; i < 3; i++) {
    Livro *atual = prateleira[i];
    while (atual != NULL) {
      Livro *aux = atual;
      atual = atual->proximo;
      free(aux);
    }
  }

  return 0;
}
