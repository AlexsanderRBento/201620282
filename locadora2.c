
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main() {
int escolha;

typedef struct filme
{
	
	int id[];
	int id_cliente[];
	char nome[1000];

} t_filme;
 
 

typedef struct cliente
{
	
	int id[];
	char nome[1000];
} t_cliente;




 
	printf("\n\n1 - Cadastrar um filme\n");
	printf("2 - Cadastrar um cliente\n");
	printf("3 - Listar todos os filmes\n");
	printf("4 - Listar todos os clientes\n");
	printf("5 - Pesquisar por filme\n");
	printf("6 - Pesquisar por cliente\n");
	printf("7 - Alugar um filme\n");
	printf("8 - Entregar um filme\n");
	printf("9 - Excluir um filme\n");
	printf("0 - Sair\n");
	printf("Digite o numero da opcao: ");
	scanf("%d", &escolha);
	switch(escolha)
{
	case 1:
	printf("digite nome do filme\n");
	break;
}
return (0);

}


