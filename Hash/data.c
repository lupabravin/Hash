#include "data.h"
#include "hashops.h"
#include "fileio.h"

typedef struct dogcontrol DogControl;
typedef struct dogdata DogData;

void insertData() {
	system("cls");

	openDataFile();
	rewind(data);
	DogControl newControl;
	DogData newData;

	printf("Control Code: ");
	scanf("%d", &newControl.controlCode);
	getc(stdin);
	printf("\n");

	printf("Hash Address: %d \n", newControl.controlCode % TAM);

	if (searchCode(newControl.controlCode, 0) != -1)
	{
		printf("Key %d has already been inserted!", newControl.controlCode);
		getch();
		return 0;
	}

	newControl.dogCode = newData.dogCode = getLastCode() + 1;
	setLastCode(newControl.dogCode);

	printf("Medicine Name: ");
	gets(&newControl.medicine);
	printf("\n");

	printf("Doctor's Name: ");
	gets(&newControl.doctor);
	printf("\n");

	printf("Dog's Race: ");
	gets(&newData.race);
	printf("\n");

	printf("Dog's Name: ");
	gets(&newData.name);
	printf("\n");

	fseek(data, 0, SEEK_END);
	int fileRRN = ftell(data);

	if (insertHash(newControl.controlCode, fileRRN) != -1)
	{
		writeData(newControl, newData);
		printf("Key %d inserted!", newControl.controlCode);
	}
	getch();
	system("cls");

	closeDataFile();

}


int getLastCode()
{
	int code = 0;
	openDataFile();
	rewind(data);
	fread(&code, sizeof(int), 1, data);
	return code;
}


int setLastCode(int code)
{
	openDataFile();
	rewind(data);
	fwrite(&code, sizeof(int), 1, data);
	closeDataFile();
	openDataFile();
}

int writeData(DogControl newControl, DogData newData)
{
	openControlFile();
	openDataFile();

	int fileRRN = fseek(control, 0, SEEK_END);
	fseek(data, 0, SEEK_END);

	fwrite(&newControl, sizeof(DogControl), 1, control);
	fwrite(&newData, sizeof(DogData), 1, data);

	return fileRRN;

}

