
#define limpar_tela "cls"
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct filme
{
	
	int id;
	int id_cliente;
	char nome[100];
	float preco;
} t_filme;
 
 

typedef struct cliente
{
	
	int id;
	char nome[100];
} t_cliente;
 

char menu();
 

void c_cliente();
 

void c_filme();
 

void lista_filme();
 

void lista_cliente();
 

t_filme *obter_filme(FILE *arq_filmes, int id_filme);
 

t_cliente *obter_cliente(FILE *arq_clientes, int id_cliente);
 

void procurar_filme();
 

void procurar_cliente();
 

int existe_filme(FILE *arq_filmes, int id_filme);
 

int existe_cliente(FILE *arq_clientes, int id_cliente);

void atualizar_filmes(FILE *arq_filmes, t_filme *filme_alugado);
 

void alugar_filme();

void entregar_filme();
 

void excluir_filme();
 

 
int main(int argc, char *argv[])
{
	char escolha;
 
	while(1)
	{
		escolha = menu();
 

		if(escolha == '1')
			c_filme();
		else if(escolha == '2')
			c_cliente();
		else if(escolha == '3')
			lista_filme();
		else if(escolha == '4')
			lista_cliente();
		else if(escolha == '5')
			procurar_filme();
		else if(escolha == '6')
			procurar_cliente();
		else if(escolha == '7')
			alugar_filme();
		else if(escolha == '8')
			entregar_filme();
		else if(escolha == '9')
			excluir_filme();
		else if(escolha == '0') 
			break;
		else
		{
			printf("\nOpcao invalida! Pressione <Enter> para continuar...");
			scanf("%*c");
		}
		system(limpar_tela);
	}
 

	return 0;
}
 
 

char menu()
{
	char escolha[2];
 
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
	scanf("%1s%*c", escolha);
 

	return escolha[0];
}
 