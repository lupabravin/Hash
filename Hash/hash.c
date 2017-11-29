// vetBTree.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "fileio.h"
#include "data.h"
#include "hashops.h"

int main()
{
	openIndexFile();
	openControlFile();
	openDataFile();
	
	int exit = -1, option, search, code1, code2;

	while (exit == -1)
	{
		printf("\tWELCOME TO DOGCARE\n\n");
		printf("\t1. New Register\n");
		printf("\t2. Remove Register\n");
		printf("\t3. Search By Control \n");
		printf("\t4. Quit \n\n");

		printf("\tOption: ");
		scanf("%d", &option);

		switch (option)
		{
		case 1:
			insertData();
			system("cls");
			break;
		case 2:
			system("cls");
			//removeData();
			printf("\n\nPress Any Key");
			getch();
			system("cls");
			break;
		case 3:
			system("cls");
			printf("Search: ");
			scanf("%d", &search);
			//if (searchRegister() == 0)
				//printf("\n Key %d not found! :(", search);

			printf("\n\nPress Any Key");
			getch();
			system("cls");
			break;
		case 4:
			exit = 0;
			break;
		default:
			printf("Invalid Operation.");
			getch();
			system("cls");
			break;
		}
	}

}

