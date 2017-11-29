#include "fileio.h"
#include "data.h"
#include "hashops.h"


void openDataFile()
{
	//data = fopen("data.dat", "a+b");

	if ((data = fopen("data.dat", "r+")) == 0)
		data = fopen("data.dat", "w+");
}

void closeDataFile()
{
	fclose(data);
}

void openControlFile()
{
	//control = fopen("control.dat", "a+b");
	if ((control = fopen("control.dat", "r+")) == 0)
		control = fopen("control.dat", "w+");
}

void closeControlFile()
{
	fclose(control);
}

void openIndexFile()
{
	if ((index = fopen("index.dat", "r+b")) == 0)
	{
		index = fopen("index.dat", "w+b");
		initHash();
	}
}

void closeIndexFile()
{
	fclose(index);
}

/*
int insertRegister(DogControl newControl, DogData newData)
{
	openControlFile();
	openDataFile();
	int hashAddress, success;

	hashAddress = newControl.controlCode % TAM;

	success = insertHash(newControl.controlCode, hashAddress, fileRRN);

	if (sucess != -1)
		printf("\nCode %d successfully added to Hash Address %d in position %d", newControl.controlCode, hashAddress, sucess);
	else
		printf("\nThere is no space for key %d", newControl.controlCode);

	return success;
}

*/