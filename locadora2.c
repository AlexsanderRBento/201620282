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
	FILE *fp;
	fp = fopen("movies.txt","ab");
	printf("digite nome do filme\n");
	setbuf(stdin, NULL);
	fgets(filmes.nome,1000,stdin);
	printf("digite o ID do filme\n");
	setbuf(stdin, NULL);
	fgets(filmes.id,1000,stdin);
	fwrite(&filmes, sizeof(filmes),1000,fp);
	fclose(fp);

	break;


	case 2:
			system ("clear");
	printf("digite nome do cliente\n");
		FILE *cp;
	cp = fopen("client.txt","ab");
	printf("digite nome do cliente\n");
	setbuf(stdin, NULL);
	fgets(clientes.nome,1000,stdin);
	printf("digite o ID do cliente\n");
	setbuf(stdin, NULL);
	fgets(clientes.id,1000,stdin);
	fwrite(&clientes, sizeof(clientes),1000,cp);
	fclose(cp);
	
	break;
	
	case 3:
			system ("clear");
	
	break;

	case 4:
			system ("clear");
	
	break;

	case 5:
			system ("clear");
	
	break;
	
	default:
	printf("entrada invalida\n");
	
	
}
	
return (0);

}
	
	break;

	case 4:
			system ("clear");
	
	break;

	case 5:
			system ("clear");
	
	break;
	
	default:
	printf("entrada invalida\n");
	
	
}
	
return (0);

}
