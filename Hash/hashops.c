#include "hashops.h"
#include "fileio.h"
#include "data.h"

int insertHash(int key, int fileRRN)
{
	Hash hash;
	int hashAddress = key % TAM;
	int availableAddress = hashAddress + 1;
	int foundSpace = 0;
	fseek(index, hashAddress * sizeof(Hash), 0);
	fread(&hash, sizeof(Hash), 1, index);
	int i = 0, j = 0;

	while (i <= 1)
	{
		if (hash.fileRRN[i] == -1)
		{
			hash.hashCode = hashAddress;
			hash.code[i] = key;
			hash.fileRRN[i] = fileRRN;
			fseek(index, -sizeof(Hash), SEEK_CUR);
			fwrite(&hash, sizeof(Hash), 1, index);
			closeIndexFile();
			openIndexFile();
			return i;
		}

		printf("\nCollision!");
		printf("\nAttempt %d...", i + 1);

		i++;
	}

	rewind(index);

	while (foundSpace == 0)
	{
		if (availableAddress == hashAddress)
			foundSpace = -1;

		fseek(index, availableAddress * sizeof(Hash), 0);
		if (fread(&hash, sizeof(Hash), 1, index) == 0)
			availableAddress = 0;

		while (j <= 1)
		{
			if (hash.fileRRN[j] == -1)
			{
				hash.hashCode = hashAddress;
				hash.code[j] = key;
				hash.fileRRN[j] = fileRRN;
				fseek(index, -sizeof(Hash), SEEK_CUR);
				fwrite(&hash, sizeof(Hash), 1, index);
				closeIndexFile();
				openIndexFile();
				return j;
			}

			printf("\nCollision!");
			printf("\nAttempt %d...", i + 1);

			j++;
			i++;
		}

		j = 0;
		availableAddress++;
		rewind(index);
	}

	return foundSpace;
}

void initHash()
{
	Hash hash;
	int i = 0, j = 0;

	hash.hashCode = NIL;
	hash.fileRRN[0] = NIL;
	hash.code[0] = NIL;
	hash.fileRRN[1] = NIL;
	hash.code[1] = NIL;

	while (i < TAM)
	{
		fwrite(&hash, sizeof(Hash), 1, index);
		i++;
	}

	closeIndexFile();
	openIndexFile();
}

int searchCode(int key)
{
	Hash hash;
	int hashAddress = key % 11;
	openIndexFile();
	int i = 0, j = 0, found = 0;
	int currentAddress = hashAddress + 1;

	fseek(index, hashAddress * sizeof(Hash), 0);
	fread(&hash, sizeof(Hash), 1, index);
	

	while (j <= 1)
	{
		if (hash.code[j] == key)
			return hashAddress;

		j++;
	}

	j = 0;
	rewind(index);
	while (found == 0)
	{
		if (fread(&hash, sizeof(Hash), 1, index) == 0)
			currentAddress = 0;

		if (currentAddress == hashAddress)
			found = -1;

		fseek(index, currentAddress * sizeof(Hash), 0);
		fread(&hash, sizeof(Hash), 1, index);

		while (j <= 1)
		{
			if (hash.code[j] == key)
				return currentAddress;

			j++;
		}

		j = 0;

		currentAddress++;
	}

	return found;
}

int removeHash(int key)
{
	Hash hash;

	int i = 0, j = 0;

	while (i < TAM)
	{
		fread(&hash, sizeof(Hash), 1, index);
		while (j <= 1)
		{
			if (hash.code[j] == key)
			{
				hash.code[j] = NIL;
				hash.fileRRN[j] = NIL;

				if (hash.code[0] == NIL && hash.code[1] == NIL)
					hash.hashCode = NIL;

				rewind(index);
				fseek(index, i * sizeof(Hash), 0);
				fwrite(&hash, sizeof(Hash), 1, index);
				closeIndexFile();
				openIndexFile();
				return i;
			}
			j++;
		}

		i++;
		j = 0;
	}

	return -1;
}