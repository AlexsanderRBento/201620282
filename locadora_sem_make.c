
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct filme
{

  int id;
  int id_cliente;
  char nome[1000];
  float preco;
} t_filme;



typedef struct cliente
{

  int id;
  char nome[1000];
} t_cliente;



char menu ();

void cadastrar_cliente ();


void cadastrar_filme ();


void listar_filmes ();

void listar_clientes ();


t_filme *obter_filme (FILE * arq_filmes, int id_filme);


t_cliente *obter_cliente (FILE * arq_clientes, int id_cliente);


void pesquisar_filme ();


void pesquisar_cliente ();


int existe_filme (FILE * arq_filmes, int id_filme);



int existe_cliente (FILE * arq_clientes, int id_cliente);


void atualizar_filmes (FILE * arq_filmes, t_filme * filme_alugado);


void alugar_filme ();


void entregar_filme ();




int str_somente_numeros (char str[]);


int
main (int argc, char *argv[])
{
  char resp;


  while (1)
    {

      resp = menu ();


      if (resp == '1')
	cadastrar_filme ();
      else if (resp == '2')
	cadastrar_cliente ();
      else if (resp == '3')
	listar_filmes ();
      else if (resp == '4')
	listar_clientes ();
      else if (resp == '5')
	pesquisar_filme ();
      else if (resp == '6')
	pesquisar_cliente ();
      else if (resp == '7')
	alugar_filme ();
      else if (resp == '8')
	entregar_filme ();
      else if (resp == '9')
    PDF();

      else if (resp == '0')

	break;
      else
	{
	  printf ("\nOpcao invalida!");
	  scanf ("%*c");

	  fseek (stdin, 0, SEEK_END);
	}
      system ("clear");
    }


  return 0;
}



char
menu ()
{
  char resp[2];


  printf ("1 - Cadastrar um filme\n");
  printf ("2 - Cadastrar um cliente\n");
  printf ("3 - Listar todos os filmes\n");
  printf ("4 - Listar todos os clientes\n");
  printf ("5 - Pesquisar por filme\n");
  printf ("6 - Pesquisar por cliente\n");
  printf ("7 - Alugar um filme\n");
  printf ("8 - Entregar um filme\n");
  printf ("9 - gerar PDF\n");
  printf ("0 - Sair\n");
  printf ("Digite o numero da opcao: ");
  scanf ("%1s%*c", resp);


  fseek (stdin, 0, SEEK_END);


  return resp[0];
}



int
str_somente_numeros (char str[])
{
  int i = 0;
  int len_str = strlen (str);

  for (i = 0; i < len_str; i++)
    {
      if (str[i] < '0' || str[i] > '9')
	return 0;
    }
  return 1;
}



void
cadastrar_cliente ()
{

  FILE *arq_clientes = fopen ("clientes.txt", "a+b");


  if (arq_clientes == NULL)
    {
      printf ("\nFalha ao abrir arquivo(s)!\n");
      exit (1);
    }

  int cont_bytes = 0;


  fseek (arq_clientes, 0, SEEK_END);

  cont_bytes = ftell (arq_clientes);

  t_cliente cliente;

  if (cont_bytes == 0)
    {

      cliente.id = 1;
    }
  else
    {
      t_cliente ultimo_cliente;

      fseek (arq_clientes, cont_bytes - sizeof (t_cliente), SEEK_SET);


      fread (&ultimo_cliente, sizeof (t_cliente), 1, arq_clientes);


      cliente.id = ultimo_cliente.id + 1;
    }

  printf ("\nDigite o nome do cliente: ");
  scanf ("%99[^\n]%*c", cliente.nome);


  fseek (stdin, 0, SEEK_END);


  fseek (arq_clientes, 0, SEEK_END);

  fwrite (&cliente, sizeof (t_cliente), 1, arq_clientes);


  fclose (arq_clientes);

  printf ("\nCliente \"%s\" cadastrado com sucesso!\n", cliente.nome);
  printf ("\nPressione <Enter> para continuar...");
  scanf ("%*c");


  fseek (stdin, 0, SEEK_END);
}



void
cadastrar_filme ()
{

  FILE *arq_filmes = fopen ("filmes.txt", "a+b");


  if (arq_filmes == NULL)
    {
      printf ("\nFalha ao abrir arquivo(s)!\n");
      exit (1);
    }
  t_filme filme;

  int cont_bytes = 0;


  fseek (arq_filmes, 0, SEEK_END);

  cont_bytes = ftell (arq_filmes);

  if (cont_bytes == 0)
    {

      filme.id = 1;
    }
  else
    {
      t_filme ultimo_filme;


      fseek (arq_filmes, cont_bytes - sizeof (t_filme), SEEK_SET);


      fread (&ultimo_filme, sizeof (t_filme), 1, arq_filmes);


      filme.id = ultimo_filme.id + 1;
    }

  printf ("\nDigite o nome do filme: ");
  scanf ("%99[^\n]%*c", filme.nome);


  fseek (stdin, 0, SEEK_END);

  do
    {
      char str_preco[5];
      float float_preco;
      int somente_numeros = 1;


      printf ("Digite o preco do filme: ");
      scanf ("%4s%*c", str_preco);

      fseek (stdin, 0, SEEK_END);


      somente_numeros = str_somente_numeros (str_preco);

      if (somente_numeros == 1)
	{

	  int int_preco;

	  sscanf (str_preco, "%d", &int_preco);
	  float_preco = int_preco / 100.0;
	  filme.preco = float_preco;
	  break;
	}
    }
  while (1);


  filme.id_cliente = -1;


  fseek (arq_filmes, 0, SEEK_END);

  fwrite (&filme, sizeof (t_filme), 1, arq_filmes);


  fclose (arq_filmes);

  printf ("\nFilme \"%s\" cadastrado com sucesso!\n", filme.nome);
  printf ("\nPressione <Enter> para continuar...");
  scanf ("%*c");


  fseek (stdin, 0, SEEK_END);
}



void
listar_clientes ()
{

  FILE *arq_clientes = fopen ("clientes.txt", "rb");


  if (arq_clientes == NULL)
    {
      printf ("\nFalha ao abrir arquivo(s) ou ");
      printf ("Nenhum cliente cadastrado.\n");
      printf ("\nPressione <Enter> para continuar...");
      scanf ("%*c");


      fseek (stdin, 0, SEEK_END);
      return;
    }


  int encontrou_clientes = 0;
  t_cliente cliente;

  printf ("\nListando todos os clientes...\n");

  while (1)
    {

      size_t result = fread (&cliente, sizeof (t_cliente), 1, arq_clientes);


      if (result == 0)
	break;


      encontrou_clientes = 1;

      printf ("\nID do cliente: %d\n", cliente.id);
      printf ("Nome do cliente: %s\n", cliente.nome);
    }

  if (encontrou_clientes == 0)
    printf ("\nNenhum cliente cadastrado.\n");

  fclose (arq_clientes);

  printf ("\nPressione <Enter> para continuar...");
  scanf ("%*c");


  fseek (stdin, 0, SEEK_END);
}



t_cliente *
obter_cliente (FILE * arq_clientes, int id_cliente)
{

  rewind (arq_clientes);

  t_cliente *cliente;


  cliente = (t_cliente *) malloc (sizeof (t_cliente));
  while (1)
    {


      size_t result = fread (cliente, sizeof (t_cliente), 1, arq_clientes);


      if (result == 0)
	{
	  free (cliente);
	  return NULL;
	}

      if (cliente->id == id_cliente)
	break;
    }
  return cliente;
}



void
listar_filmes ()
{

  FILE *arq_filmes = fopen ("filmes.txt", "rb");
  FILE *arq_clientes = fopen ("clientes.txt", "rb");


  if (arq_filmes == NULL)
    {
      printf ("\nFalha ao abrir arquivo ou ");
      printf ("Nenhum filme cadastrado.\n");
      printf ("\nPressione <Enter> para continuar...");
      scanf ("%*c");


      fseek (stdin, 0, SEEK_END);
      return;
    }

  int encontrou_filmes = 0;
  printf ("\nListando todos os filmes...\n");

  t_filme filme;
  while (1)
    {

      size_t result = fread (&filme, sizeof (t_filme), 1, arq_filmes);


      if (result == 0)
	break;

      encontrou_filmes = 1;


      printf ("\nID do filme: %d\n", filme.id);
      printf ("Nome do filme: %s\n", filme.nome);
      printf ("Preco: %.2f\n", filme.preco);


      if (filme.id_cliente != -1)
	{

	  if (arq_clientes == NULL)
	    {
	      printf ("\nFalha ao abrir arquivo!\n");
	      fclose (arq_filmes);
	      exit (1);
	    }
	  t_cliente *cliente = obter_cliente (arq_clientes, filme.id_cliente);
	  printf ("Cliente: %s\n", cliente->nome);
	  free (cliente);
	}
      else
	printf ("Alugado? Nao\n");
    }


  if (encontrou_filmes == 0)
    printf ("\nNenhum filme cadastrado.\n");


  if (arq_clientes != NULL)
    fclose (arq_clientes);
  fclose (arq_filmes);

  printf ("\nPressione <Enter> para continuar...");
  scanf ("%*c");


  fseek (stdin, 0, SEEK_END);
}



void
pesquisar_filme ()
{
  char nome[1000];
  int encontrou_filme = 0;


  FILE *arq_filmes = fopen ("filmes.txt", "rb");
  FILE *arq_clientes = fopen ("clientes.txt", "rb");


  if (arq_filmes == NULL)
    {
      printf ("\nFalha ao abrir arquivo(s)!\n");
      exit (1);
    }

  printf ("\nDigite o nome do filme: ");
  scanf ("%99[^\n]%*c", nome);

  printf ("\nFilmes com o nome \"%s\":\n\n", nome);

  t_filme filme;
  while (1)
    {

      size_t result = fread (&filme, sizeof (t_filme), 1, arq_filmes);


      if (result == 0)
	break;

      char nome_aux[1000];

      strcpy (nome_aux, filme.nome);


      if (strcmp ((nome_aux),  (nome)) == 0)
	{

	  printf ("ID do filme: %d\n", filme.id);
	  printf ("Preco: %.2lf\n", filme.preco);
	  if (filme.id_cliente != -1)
	    {

	      if (arq_clientes == NULL)
		{
		  printf ("\nFalha ao abrir arquivo!\n");
		  fclose (arq_filmes);
		  exit (1);
		}
	      t_cliente *cliente =
		obter_cliente (arq_clientes, filme.id_cliente);
	      printf ("Alugado? Sim. Cliente: %s\n", cliente->nome);
	      free (cliente);
	    }
	  else
	    printf ("Alugado? Nao\n");
	  encontrou_filme = 1;
	  printf ("\n");
	}
    }

  if (encontrou_filme == 0)
    printf ("Nenhum filme encontrado.\n\n");

  fclose (arq_filmes);

  printf ("Pressione Enter para continuar");
  scanf ("%*c");


  fseek (stdin, 0, SEEK_END);
}



void
pesquisar_cliente ()
{
  char nome[1000];
  int encontrou_cliente = 0;


  FILE *arq_clientes = fopen ("clientes.txt", "rb");


  if (arq_clientes == NULL)
    {
      printf ("\nFalha ao abrir arquivo(s)!\n");
      exit (1);
    }

  printf ("\nDigite o nome do cliente: ");
  scanf ("%99[^\n]%*c", nome);

  printf ("\nClientes com o nome \"%s\":\n\n", nome);

  t_cliente cliente;
  while (1)
    {

      size_t result = fread (&cliente, sizeof (t_cliente), 1, arq_clientes);


      if (result == 0)
	break;

      char nome_aux[1000];

      strcpy (nome_aux, cliente.nome);


      if (strcmp ((nome_aux),  (nome)) == 0)
	{

	  printf ("ID do cliente: %d\n\n", cliente.id);
	  encontrou_cliente = 1;
	}
    }

  if (encontrou_cliente == 0)
    printf ("Nenhum cliente encontrado.\n\n");


  fclose (arq_clientes);

  printf ("Pressione Enter para continuar");
  scanf ("%*c");


  fseek (stdin, 0, SEEK_END);
}



int
existe_filme (FILE * arq_filmes, int id_filme)
{

  rewind (arq_filmes);

  t_filme filme;

  while (1)
    {

      size_t result = fread (&filme, sizeof (t_filme), 1, arq_filmes);


      if (result == 0)
	break;


      if (filme.id == id_filme)
	return 1;
    }


  return 0;
}



int
existe_cliente (FILE * arq_clientes, int id_cliente)
{

  rewind (arq_clientes);

  t_cliente cliente;

  while (1)
    {

      size_t result = fread (&cliente, sizeof (t_cliente), 1, arq_clientes);


      if (result == 0)
	break;


      if (cliente.id == id_cliente)
	return 1;
    }


  return 0;
}



t_filme *
obter_filme (FILE * arq_filmes, int id_filme)
{

  rewind (arq_filmes);


  t_filme *filme;


  filme = (t_filme *) malloc (sizeof (t_filme));
  while (1)
    {


      size_t result = fread (filme, sizeof (t_filme), 1, arq_filmes);


      if (result == 0)
	break;


      if (filme->id == id_filme)
	return filme;
    }
  free (filme);
  return NULL;
}



void
atualizar_filmes (FILE * arq_filmes, t_filme * filme_alugado)
{

  rewind (arq_filmes);

  t_filme filme;
  while (1)
    {


      size_t result = fread (&filme, sizeof (t_filme), 1, arq_filmes);


      if (result == 0)
	break;


      if (filme.id == filme_alugado->id)
	{

	  fseek (arq_filmes, -sizeof (t_filme), SEEK_CUR);

	  fwrite (filme_alugado, sizeof (t_filme), 1, arq_filmes);
	  break;
	}
    }
}



void
alugar_filme ()
{
  char str_id_cliente[10];
  int id_cliente;


  FILE *arq_filmes = fopen ("filmes.txt", "rb+");
  FILE *arq_clientes = fopen ("clientes.txt", "rb+");


  if (arq_filmes == NULL)
    {
      arq_filmes = fopen ("filmes.txt", "wb+");
      if (arq_filmes == NULL)
	{
	  printf ("\nFalha!\n");
	  exit (1);
	}
    }

  if (arq_clientes == NULL)
    {
      arq_clientes = fopen ("clientes.txt", "wb+");
      if (arq_clientes == NULL)
	{
	  printf ("\nFalha!\n");
	  exit (1);
	}
    }


  printf ("\nDigite o ID do cliente: ");
  scanf ("%10s%*c", str_id_cliente);

  fseek (stdin, 0, SEEK_END);

  if (str_somente_numeros (str_id_cliente) == 1)
    {

      sscanf (str_id_cliente, "%d", &id_cliente);


      if (existe_cliente (arq_clientes, id_cliente))
	{
	  char str_id_filme[10];
	  int id_filme;

	  printf ("\nDigite o ID do filme: ");
	  scanf ("%10s%*c", str_id_filme);

	  fseek (stdin, 0, SEEK_END);

	  if (str_somente_numeros (str_id_filme) == 1)
	    {

	      sscanf (str_id_filme, "%d", &id_filme);


	      t_filme *filme = obter_filme (arq_filmes, id_filme);


	      if (filme != NULL)
		{

		  if (filme->id_cliente != -1)
		    printf ("\nO filme \"%s\" ja esta alugado!\n",
			    filme->nome);
		  else
		    {

		      filme->id_cliente = id_cliente;
		      atualizar_filmes (arq_filmes, filme);
		      printf ("\nFilme \"%s\" alugado com sucesso!\n",
			      filme->nome);
		    }
		  free (filme);
		}
	      else
		printf ("\nNao existe filme com o ID \"%d\".\n", id_filme);
	    }
	  else
	    printf ("\nO ID so pode conter numeros!\n");
	}
      else
	printf ("\nNao existe cliente com o ID \"%d\".\n", id_cliente);
    }
  else
    printf ("\nO ID so pode conter numeros!\n");


  fclose (arq_clientes);
  fclose (arq_filmes);

  printf ("\nPressione <Enter> para continuar...");
  scanf ("%*c");

  fseek (stdin, 0, SEEK_END);
}
void PDF ()
   {

    system ("$ enscript -p output.ps clientes.txt");
    system ("$ enscript -p output2.ps filmes.txt");
    system ("$ ps2pdf output.ps output.pdf");
    system ("$ ps2pdf output2.ps output2.pdf");
   }


void
entregar_filme ()
{
  char str_id_filme[10];
  int id_filme;


  FILE *arq_filmes = fopen ("filmes.txt", "rb+");


  if (arq_filmes == NULL)
    {
      arq_filmes = fopen ("filmes.txt", "wb+");
      if (arq_filmes == NULL)
	{
	  printf ("\nFalha ao criar arquivo(s)!\n");
	  exit (1);
	}
    }

  printf ("\nDigite  ID do filme: ");
  scanf ("%10s%*c", str_id_filme);

  fseek (stdin, 0, SEEK_END);

  if (str_somente_numeros (str_id_filme) == 1)
    {

      sscanf (str_id_filme, "%d", &id_filme);


      t_filme *filme = obter_filme (arq_filmes, id_filme);


      if (filme != NULL)
	{

	  if (filme->id_cliente == -1)
	    printf ("\nO filme \"%s\"  esta disponivel!\n", filme->nome);
	  else
	    {

	      filme->id_cliente = -1;
	      atualizar_filmes (arq_filmes, filme);
	      printf ("\nFilme \"%s\" entregue !\n", filme->nome);
	    }
	  free (filme);
	}
      else
	printf ("\nNao existe filme com o ID \"%d\".\n", id_filme);
    }
  else
    printf ("\nO ID so pode conter numeros!\n");


  fclose (arq_filmes);

  printf ("\nPressione <Enter> para continuar...");
  scanf ("%*c");

  fseek (stdin, 0, SEEK_END);
}
