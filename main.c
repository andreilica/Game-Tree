#include <stdio.h> 
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFF_MAX 100 // Dimensiunea string-ului de input

typedef struct tree
{	
	char game[3][3];  // Tabla de joc
	char value; // Valoarea de adevar
	int n; // Numarul de copii
	struct tree **children; // Vectorul de pointeri la copii

}tree;

/*Functie care verifica daca un arbore este NULL */

int is_empty_arbore (tree *arbore)
{
	return (arbore == NULL);
}

/* Functie care verifica pentru fiecare nod starea in care se afla */

int state (char game[3][3])
{
	int i,j, k = 0;

	for (i = 0; i < 3; ++i) // Verificare randuri
		if( game[i][0] == game[i][1] && game[i][1] == game[i][2])
		{
			if(game[i][0] == 'X') //Castiga X
				return 10;
			else
				if(game[i][0] == 'O') //Castiga O
					return -10;
		}

	for (j = 0; j < 3; ++j)  // Verificare coloane
		if( game[0][j] == game[1][j] && game[1][j] == game[2][j])
		{	if(game[0][j] == 'X') //Castiga X
				return 10;
			else
				if(game[0][j] == 'O') // Castiga O
					return -10;
		}

	if(game[0][0] == game[1][1] && game[1][1] == game[2][2]) //Verificare diagonala principala
	{
		if(game[0][0] == 'X') //Castiga X
				return 10;
			else
				if(game[0][0] == 'O') //Castiga O
					return -10;
	}

	if(game[2][0] == game[1][1] && game[1][1] == game[0][2]) // Verificare diagonala secundara
	{
		if(game[0][2] == 'X') // Castiga X
				return 10;
			else
				if(game[0][2] == 'O') // Castiga O 
					return -10;
	}

	for ( i = 0; i < 3; ++i)
		for(j = 0; j < 3; ++j)
			if(game[i][j] == '-')
				k++;

	return k; 
}

/* Functie pentru eliberarea de memorie */

void free_memory(tree **arbore)
{
	int i;
	if(is_empty_arbore(*arbore))
		return;

	for ( i = 0; i < (*arbore)->n; ++i)
		free_memory(&((*arbore)->children[i]));

	free((*arbore)->children);
	free(*arbore);
}

/* Functie care initializeaza si creaza un nod */

tree *create_node(char game[3][3])
{
	int i,j;
	int nr = state(game);
	tree *aux = (tree*)malloc(sizeof(tree));

	aux -> value = '!';

	for (i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			aux->game[i][j] = game[i][j];

	if (nr != 10 && nr != -10)
		aux -> n = nr;
	else
		aux -> n = 0;

	aux->children = (tree **) malloc (aux->n * sizeof(tree*));

	for( i = 0; i < aux -> n; i++) 
		aux->children[i] = NULL;

	return aux;
}

/* Functie care insereaza copii intr-un arbore */

tree *insert_children(tree *arbore, char game[3][3])
{
	if(is_empty_arbore(arbore))
		return arbore;

	for (int i = 0; i < arbore -> n ; ++i)
		if(is_empty_arbore(arbore->children[i]))
		{
			arbore -> children[i] = create_node(game);
			break;
		}

	return arbore;
}

/* Functie care returneaza valoarea de adevar a starii */

char truefalse(char first, int flag)
{
	if(first == 'X')
		if(flag == 10)
			return 'T'; // Daca s-a inceput cu X si a castigat X 

	if(first == 'O')
		if(flag == -10)
			return 'T'; // Daca s-a inceput cu O si a castigat O

	return 'F'; // Restul cazurilor
}

/* Functie care creaza copiii arborelui */

void create_children(tree **arbore, char first, char turn)
{
	int flag = state((*arbore)->game);
	if(flag == 10 || flag == -10 || flag == 0)
	{
		(*arbore) -> value = truefalse(first, flag); // Stabileste valoarea de adevar a frunzelor
		return;
	}

	char aux_board[3][3];
	int i,j;

	for(i = 0; i < 3; ++i)
		for(j = 0; j < 3; ++j)
			aux_board[i][j] = (*arbore) -> game[i][j];

	for(i = 0; i < 3; ++i)
		for(j = 0; j < 3; ++j)
			if(aux_board[i][j] == '-')
			{
				aux_board[i][j] = turn;
				(*arbore) = insert_children(*arbore,aux_board);
				int x,y;
				for(y = 0; y < 3; y++)
					for(x = 0; x < 3; x++)
						aux_board[y][x] = (*arbore) -> game[y][x];
			}
}

/* Functie de creare a arborelui in sine pentru cerinta 1 */

void create_tree(tree **arbore, char first, char turn)
{
	char next;
	int i;
	if(turn == 'O')
		next = 'X';
	else
		if(turn == 'X')
			next = 'O';

	create_children(arbore, first, turn);

	for(i = 0; i < (*arbore) -> n; i++)
		create_tree(&((*arbore)->children[i]), first, next);
}

/* Functie care afiseaza o matrice in fisierul de output */

void print_matrix(char game[3][3], FILE *output, int nr_tab)
{
	int i,j,x;
	for (i = 0; i < 3; ++i)
	{
		for(x = 0; x < nr_tab; x++)
			fprintf(output, "\t");
		for (j = 0; j < 2; ++j)
			fprintf(output, "%c ", game[i][j]);
		fprintf(output, "%c\n", game[i][2]);
	}

	fprintf(output, "\n");
}

/* Functie de afisare a arborelui in fisierul de output */

void display_tree(tree *arbore, int nr_tab, FILE *output, int cerinta)
{
	int i, x;

	if(cerinta == 1)
		print_matrix(arbore -> game, output, nr_tab);

	if(cerinta == 2)
	{
		for(x = 0; x < nr_tab; x++)
			fprintf(output, "\t");
		fprintf(output, "%c\n", arbore -> value);
	}

	for(i = 0; i < arbore -> n; i++)
		display_tree(arbore->children[i], nr_tab + 1, output, cerinta);

}

/* Functie pentru cerinta 2 care creaza arborele SI/SAU */

void boolean_tree(tree **arbore, char first, char turn)
{
	char next;
	int i;
	if(turn == 'O')
		next = 'X';
	else
		if(turn == 'X')
			next = 'O';
	if(is_empty_arbore(*arbore))
		return;

	int steag = 0; // Contor pentru verificare
	if(turn == first) // Se realizeaza SAU logic 
	{
		for (i = 0; i < (*arbore) -> n; ++i)
		{
			if ((*arbore) -> children[i] -> value == '!')
				boolean_tree(&(*arbore)->children[i],first,next); // Daca se gasesc stari pentru care nu a fost calculata valoarea de adevar

			if ((*arbore) -> children[i] -> value == 'T') // In caz ca se gaseste o valoare TRUE in copii, nodul curent primeste valoarea TRUE.
			{
				steag = 1; // Tine minte daca s-a gasit o valoare TRUE
				(*arbore) -> value = 'T';
			}
		}		
		if(!steag)
			(*arbore) -> value = 'F';
	}
	else // Se realizeaza SI logic
	{
		for (i = 0; i < (*arbore) -> n; ++i)
		{
			if ((*arbore) -> children[i] -> value == '!')
				boolean_tree(&(*arbore)->children[i],first,next); // Daca se gasesc stari pentru care nu a fost calculata valoarea de adevar

			if ((*arbore) -> children[i] -> value == 'F') // In caz ca se gaseste o valoare FALSE in copii, nodul curent primeste valoarea FALSE.
			{
				steag = 1; // Tine minte daca s-a gasit o valoare FALSE
				(*arbore) -> value = 'F';
			}
			
		}	
		if(!steag)
			(*arbore) -> value = 'T';
	}	
}


int main(int argc, char const *argv[])
{
	FILE *input; 
	FILE *output;

	char buff[BUFF_MAX];
	
	input = fopen(argv[2], "r"); // Fisierul de input
	output = fopen(argv[3], "w"); // Fisierul de output

	if (!output)
   	{
       fprintf(stderr, "Eroare! Nu am putut deschide fisierul destinatie!\n");
       return 0;
   	}


	if(input == NULL)
	{
		fprintf(stderr, "Eroare, nu s-a putut deschide fisierul de input\n");
		return 0;
	}

	if (!strcmp(argv[1],"-c1")) // Cerinta 1 
	{
		char first;
		char game[3][3];

		/* Parsarea fisierului de intrare */

		if (fgets(buff, BUFF_MAX, input) != NULL)
		{
			/* Se verifica cine incepe jocul */ 
			switch(buff[0])
			{
				case 'O' : 
					first = buff[0];
					printf("%c\n",first );
					break;

				case 'X' :
					first = buff[0];
					printf("%c\n",first );
					break;

				default: 
					break;
			}
		}

		/* Crearea unei matrici din fisierul de intrare */

		int i = 0, j = 0;
		while(fgets(buff, BUFF_MAX, input) != NULL)
		{
			int pos = 0;
			int l = strlen(buff);
			printf("%d\n", l);
			
			while(buff[pos] == 'X' || buff[pos] == 'O' || buff[pos] == '-' || pos < l)
			{
				
				if(buff[pos] != ' ' && buff[pos] != '\n')
				{
					game[i][j] = buff[pos];
					j++;
				}
				pos++;
			}

			j = 0;
			i++;
		}
		
		
		tree *xsizero = create_node(game); 
		create_tree(&xsizero,first,first);
		display_tree(xsizero, 0, output, 1);
		free_memory(&xsizero);
	}

	


	if (!strcmp(argv[1],"-c2")) // Cerinta 2 
	{
		/* Parsarea fisierului de intrare */

				char first;
		char game[3][3];
		if (fgets(buff, BUFF_MAX, input) != NULL)
		{
			/* Se verifica cine incepe jocul */

			switch(buff[0])
			{
				case 'O' : 
					first = buff[0];
					printf("%c\n",first );
					break;

				case 'X' :
					first = buff[0];
					printf("%c\n",first );
					break;

				default: 
					break;
			}
		}
			/* Crearea unei matrici din fisierul de intrare */

		int i = 0, j = 0;
		while(fgets(buff, BUFF_MAX, input) != NULL)
		{
			int pos = 0;
			int l = strlen(buff);
			printf("%d\n", l);
			
			while(buff[pos] == 'X' || buff[pos] == 'O' || buff[pos] == '-' || pos < l)
			{
				
				if(buff[pos] != ' ' && buff[pos] != '\n')
				{
					game[i][j] = buff[pos];
					j++;
				}
				pos++;
			}

			j = 0;
			i++;
		}
		
		
		tree *xsizero = create_node(game);
		create_tree(&xsizero,first,first);
		boolean_tree(&xsizero,first,first);
		display_tree(xsizero, 0, output, 2);
		free_memory(&xsizero);
	}

	if (!strcmp(argv[1],"-c3"))
	{
				//cerinta3
	}

	if (!strcmp(argv[1],"-b"))
	{
				//bonus
	}
	fclose(input);
	fclose(output);

	return 0;
}