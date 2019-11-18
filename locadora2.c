#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>





int main() {
int escolha;


typedef struct filme
{

	char id[1000];
	char id_cliente[1000];
	char nome[1000];

} ;
struct filme filmes;



typedef struct cliente
{

	char id[1000];
	char nome[1000];
} ;
struct cliente clientes;





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
			system ("clear");
	FILE *f;
	f = fopen("movies.txt","a");
	printf("digite nome do filme\n");
	setbuf(stdin, NULL);
	fgets(filmes.nome,1000,stdin);
	printf("digite o ID do filme\n");
	setbuf(stdin, NULL);
	fgets(filmes.id,1000,stdin);
	fwrite(&filmes, sizeof(filmes),1000,f);
	fclose(f);

	break;


	case 2:
			system ("clear");

		FILE *c;
	c = fopen("client.txt","a");
	printf("digite nome do cliente\n");
	setbuf(stdin, NULL);
	fgets(clientes.nome,1000,stdin);
	printf("digite o ID do cliente\n");
	setbuf(stdin, NULL);
	fgets(clientes.id,1000,stdin);
	fwrite(&clientes, sizeof(clientes),1000,c);
	fclose(c);
	
	break;
	
	case 3:



	FILE *fl = fopen("movies.txt", "rb");
 

	if (fl == NULL)
	{
		printf("\nFalha ao abrir arquivo(s) ou ");
		printf("Nenhum filme encontrado.\n");
		printf("\nPressione <Enter> para continuar...");
		scanf("%*c");
 
		
		fseek(stdin, 0, SEEK_END);
		return;
	}

	int encontrou_filmes = 0;
	filme filmes;
 
	printf("\nLista\n");

	while(1)
	{

		size_t result = fread(&filmes, sizeof(filme), 1, fl);
 
	
		if(result == 0)
			break;
 
		encontrou_filmes = 1;
 
	
		printf("\nID do filme: %d\n", filme.id);
		printf("Nome do filme: %s\n", filme.nome);
	}
 
	if(encontrou_filmes == 0)
		printf("\nNenhum filme cadastrado.\n");
 
	fclose(fl);
 
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
 

	fseek(stdin, 0, SEEK_END);

	    
	break;

	case 4:
			system ("clear");
	
	break;

	case 5:
			system ("clear");
	
	break;
	
	case 0:
	        exit(0);
	
	default:
	printf("entrada invalida\n");
	
	
	
	
}
	
return (0);

}
