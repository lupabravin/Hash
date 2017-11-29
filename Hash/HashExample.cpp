/*#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 11

void addHash(FILE *pont1, FILE *pont2, FILE *arqHash);
void iniciaHash(FILE *arqHash);
void consultar(FILE *pont1, FILE *pont2, FILE *arqHash);
void deletar(FILE *arqHash);

int autoIncremento = 0;

//dados do arquivo 1
struct DADOS1{
	int codControle;
	int codCachorro;
	char vacina[30];
	char responsavel[30];
}dados1;

//dados do arquivo 2
struct DADOS2{
	int codCachorro;
	char racaCachorro[30];
	char nomeCachorro[30];
}dados2;

//dados da hash
struct HASH{
	int rrn1;
	int codControle1;
	int rrn2;
	int codControle2;
}hash;

int main(){
	FILE *pont1, *pont2, *arqHash;

	int op, i, j;

	//tenta abrir o arquivo, se não existir ele cria  
	if((pont1 = fopen("Arquivo1.dad","r+b")) == NULL){
  		pont1 = fopen("Arquivo1.dad","w+b");
  	}
  
  	if( (pont2 = fopen("Arquivo2.dad","r+b")) == NULL){
    	pont2 = fopen("Arquivo2.dad","w+b");
    	fwrite(&autoIncremento, sizeof(int), 1, pont2); // auto incremento para o código
  	}	
  	else{
	    fread(&autoIncremento, sizeof(int), 1, pont2);
  	}

	if( (arqHash = fopen("indice.dad","r+b")) == NULL){
    	arqHash = fopen("indice.dad","w+b");
    	iniciaHash(arqHash);
  	}

	do{
		system("cls");
		
    	printf("*=========================== MENU HASH ===========================* \n");
    	printf("\n1 - Insercao");
    	printf("\n2 - Remover");
    	printf("\n3 - Buscar");
    	printf("\n4 - Sair");
    	printf("\n\tOpcao: ");
    	scanf("%d", &op);
    	fflush(stdin);
    	
    	switch(op){
    		
      		case 1:
		        addHash(pont1, pont2, arqHash);
		        break;
		        
		    case 2:
	        	deletar(arqHash);
	       		break;
	        
	      	case 3:
	        	consultar(pont1, pont2, arqHash);
	        	break;
	        	
	      	case 4:
	      		printf ("\nEncerrando...");
	        	fclose(pont1); //fechar arquivos os arquivos garante que os dados não sejam perdidos em casos de erro
	        	fclose(pont2);
	        	fclose(arqHash);
	        	exit(0);
	        break;
	        
	        default: 
				printf("\n\nOpcao invalida!!\n");
				system("pause");
  		}
 		
	}while(op != 4);
}

void iniciaHash(FILE *arqHash)
{
	int i = -1;
	
	hash.rrn1 = i;
	hash.codControle1 = i;
	hash.rrn2 = i;
	hash.codControle2 = i;
	
	i=0;
	while(i < TAM){
		fwrite(&hash, sizeof(hash), 1, arqHash);
		i++;
	}
}

void addHash(FILE *pont1, FILE *pont2, FILE *arqHash){
	int i, flag = 0, cont = 0, excluido = 0, key1 = 0, key2 = 0, posControle, primeiraVez=1, volta, rrnRemocao, auxRemocao, repetido = 1, auxBusca = 0;
	long int  posHash;
	
	fseek(pont1, 0, 0);
	fseek(pont2, 0, 0);
	fseek(arqHash, 0, 0);

	while(repetido)
	{
	    printf("Digite o codigo de controle: ");
	    scanf("%d", &dados1.codControle);
	    fflush(stdin);
	    fseek(arqHash, 0, 0);
	    auxBusca=0;
	    
	    while(fread(&hash, sizeof(hash), 1, arqHash) && !auxBusca)
	    {
	      if(hash.codControle1 == dados1.codControle)
	      	{
         		printf("\nCodigo de controle repetido, tente novamente!!");
        		auxBusca = 1;
      		}
        else 
	  		if(hash.codControle2==dados1.codControle)
            	{
        	    	printf("\nCodigo de controle repetido, tente novamente!!");
            		auxBusca = 1;
           		}	
    	}
    	if(!auxBusca) break;
  	}

	printf("Digite o nome da vacina: ");
	gets(dados1.vacina);
	printf("Digite o responsavel pela aplicacao: ");
	gets(dados1.responsavel);
	printf("Digite o nome do cachorro: ");
	gets(dados2.nomeCachorro);
	printf("Digite a raca do cachorro: ");
	gets(dados2.racaCachorro);

	dados1.codCachorro = autoIncremento;

	posHash = dados1.codControle % TAM;
	printf("Endereco %d\n", posHash);

	fseek(arqHash, posHash*sizeof(HASH), SEEK_SET);
	posControle = ftell(arqHash);

	while(!flag)
	{
	    if(!primeiraVez)
    	{
     		if(ftell(arqHash)==posControle)
        	break;
    	}

    	if(!excluido)
    	{
      		if(fread(&hash, sizeof(HASH), 1, arqHash))
      		{
          		if(hash.codControle1 == -2){
            		rrnRemocao = hash.rrn1;
            		excluido = 1;
          		}
			  	else if(hash.codControle2 == -2){
                	rrnRemocao = hash.rrn2;
                  	excluido = 1;
                }
                else if(hash.codControle1==-1){
                  		hash.codControle1 = dados1.codControle;
                  		hash.rrn1 = dados1.codCachorro;
                  		flag = 1;
                  		key1 = 1;
                      }
                      else if(hash.codControle2 == -1){
                              hash.codControle2 = dados1.codControle;
                              hash.rrn2 = dados1.codCachorro;
                              flag = 1;
                              key2 = 1;
                            } 
                            else  if (cont != 0)
									{
										printf("Tentativa %d.\n", cont); cont++;
									}
                                  else{ 
								  	printf("Colisao.\n");
									cont++;
									printf("Tentativa %d.\n", cont);
									cont++;
									}
      		}
      		else{ 
        		fseek(arqHash, 0, 0);
        		primeiraVez = 0;
      		}
    	}
    	else{ 
      		if(fread(&hash, sizeof(HASH), 1, arqHash))
      		{
          		if(hash.codControle1 == dados1.codControle)
            		auxRemocao = 1;
          		else if(hash.codControle2 == dados1.codControle)
                  	auxRemocao = 1;
      		}
      		else{ 
        		if(!auxRemocao)
        		{
          			excluido = 1;
          			auxRemocao = 1;
          			fseek(arqHash, rrnRemocao*sizeof(HASH), 0);
        		}
      		}
    	}
  	}

	if(!flag){
		printf("\nImpossivel fazer a insecao!!");
  	}
  	else {
  		if(!auxRemocao) {
    		volta = ftell(arqHash) - sizeof(hash);
			
			fseek(arqHash, volta, 0);
    	}
    	fwrite(&hash, sizeof(HASH), 1, arqHash);

    	if(key1)
			printf("\nChave %d inserida com sucesso!\n", hash.codControle1);
    	else
			printf("\nChave %d inserida com sucesso!\n", hash.codControle2);

    	fseek(pont1, 0, SEEK_END);
    	fseek(pont2, 0, SEEK_END);

    	fwrite(&dados1, sizeof(DADOS1), 1, pont1);
    	fwrite(&dados2, sizeof(DADOS2), 1, pont2);

    	fseek(pont2, 0, 0);

    	autoIncremento = autoIncremento + 1;
    	fwrite(&autoIncremento, sizeof(int), 1, pont2);
	  }
  
  	system("pause");
}

void consultar(FILE *pont1, FILE *pont2, FILE *arqHash)
{
	int posHash, rrn, volta, codigo, endereco, key1, key2, flag = 0, cont=0;

	printf("\nDigite o codigo a ser buscado: ");
	scanf("%d", &codigo);

	posHash = codigo % TAM;
	fseek(arqHash, posHash*sizeof(hash), SEEK_SET);

	while(!flag)
	{
    	if(fread(&hash, sizeof(hash), 1, arqHash))
    	{
      		cont++;
      		if(hash.codControle1 == codigo)
      		{
	        	rrn = hash.rrn1;
	        	flag = 1;
	        	key1 = 1;
	      	}
    		else if(hash.codControle2 == codigo)
        	  	{
            		rrn = hash.rrn2;
              		flag = 1;
            	  	key2 = 1;
            	}
            	else if (feof(arqHash) && !flag){
            			break;
					}
    	}else{
    		printf("\nChave nao encontrada!\n");
    		system("pause");
      		break;
    	}
    }

	if(flag)
	{
  		fseek(pont1, 0, 0);
	    fseek(pont2, 0, 0);

		volta = ftell(arqHash) - sizeof(hash);
	    fseek(arqHash, volta, SEEK_SET);
    	endereco = ftell(arqHash);
    	fseek(pont1, rrn*sizeof(dados1), SEEK_SET); //posiciona o ponteiro do arquivo 1 na posição correta de leitura
    	fread(&dados1, sizeof(dados1), 1, pont1);
    	fseek(pont2, sizeof(int) + rrn*sizeof(dados2), SEEK_SET); //posiciona o ponteiro do arquivo 2 na posição correta de leitura
    	fread(&dados2, sizeof(dados2), 1, pont2);

		endereco = endereco/16;
		
		system("cls");
		printf("\nDados:\n\n");
		
    	printf("\nChave %d encontrada, endereco %d, %d acessos!!\n\n", codigo, endereco, cont);
    	printf("\nCodigo de controle: %d", dados1.codControle);
    	printf("\nCodigo do cachorro: %d", dados1.codCachorro);
    	printf("\nNome da Vacina: %s", dados1.vacina);
    	printf("\nResponsavel pela aplicacao: %s", dados1.responsavel);
    	printf("\nNome do cachorro: %s", dados2.nomeCachorro);
    	printf("\nRaca do cachorro: %s\n\n", dados2.racaCachorro);
    	system("pause");
	}
}

void deletar(FILE *arqHash)
{
	int excluido = 0, codAux, posAux, posControle, primeiraVez = 1, posHash, volta;

	printf("Digite o codigo que deseja remover: ");
	scanf("%d", &codAux);
	fflush(stdin);
	posHash = codAux % TAM;

	fseek(arqHash, posHash*sizeof(hash), SEEK_SET);
	posControle = ftell(arqHash);

	while(!excluido){
		if(!primeiraVez)
    	{
    		posAux = ftell(arqHash);
      		if(posAux == posControle)
        	break;
    	}	

    if(fread(&hash, sizeof(hash), 1, arqHash))
    {
      	if(hash.codControle1 == codAux)
	    {
    	    hash.codControle1 = -2;
        	excluido = 1;
      	}
      	else if(hash.codControle2 == codAux){
        	      hash.codControle2 = -2;
	              excluido = 1;
    	        }
    	}
    	else{
      		fseek(arqHash, 0, 0);
      	primeiraVez = 0;
    	}
	  }

	if(excluido){
		printf("\n\nCodigo removido!!\n");
		volta = ftell(arqHash) - sizeof(hash);
    	fseek(arqHash, volta, SEEK_SET);
   		fwrite(&hash, sizeof(hash), 1, arqHash);	
   		system("pause");
  	}
	else {
		printf("\n\nImpossivel remover o codigo!!\n");  
		system("pause");
		
  	}
}
*/