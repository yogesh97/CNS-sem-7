//Transposition Cipher & Vigenère Cipher
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Filters text.txt and saves into text_filtered.txt
void filter()
{
	char ch;
	FILE *f1,*f2;
	f1=fopen("text.txt","r");
	f2=fopen("text_filtered.txt","w");
	while((ch=fgetc(f1))!=EOF)
	{
		if((ch>='A'&&ch<='Z'))
			fprintf(f2,"%c",ch);
		else if(ch>='a'&&ch<='z')
			fprintf(f2,"%c",ch-32);
	}
	fclose(f1);
	fclose(f2);

	printf("\nPlain text Filtered\n");
}

int encrypt_transposition(char key[])
{
	int key_length = strlen(key), plaintxt_length = 0, i, j;
	char ch;
	FILE *f1,*f2;
	f1 = fopen("text_filtered.txt","r");
	f2 = fopen("text_encrypted.txt","w");
	while((ch = fgetc(f1)) != EOF)
	{
		plaintxt_length++;
	}
	
	int nrows;
	if(plaintxt_length / (float)key_length == (int)(plaintxt_length / key_length))
	{
		nrows = plaintxt_length / key_length;
	}
	else
	{
		nrows = plaintxt_length / key_length + 1;
	}
	
	char mat[nrows][key_length];	
	fseek(f1,0,SEEK_SET);
	i = 0;j = 0;
	while((ch = fgetc(f1)) != EOF)
	{
		mat[i][j++] = ch;
		if(j >= key_length)
		{
			i++;
			j=0;
		}
	}

	while(j != key_length)
		{
			mat[i][j++] = 'X';
		}
	
	int jumbleOrder[key_length], orderNo = 1;

	for(j = (int)'A';j <= (int)'Z';++j)
	{
		for(i = 0;i < key_length;++i)
		{
			if((int)key[i] == j)
				jumbleOrder[i] = orderNo++;
		}
	}

	for(orderNo = 1;orderNo <= key_length;++orderNo)
	{
		for(j = 0;j < key_length;++j)
		{
			if(jumbleOrder[j] == orderNo)
			{
				for(i = 0;i < nrows;++i)
				{
					fprintf(f2, "%c", mat[i][j]);
				}
				fprintf(f2, " ");
				break;
			}
		}
	}

	fprintf(f2,"\n");
	fclose(f1);
	fclose(f2);
	printf("\nPlain text encrypted\n");
	return 0;
}

int decrypt_transposition(char key[])
{
	int key_length = strlen(key), ciphertxt_length = 0, i, j;
	char ch;
	FILE *f1,*f2;
	f1=fopen("text_encrypted.txt","r");
	f2=fopen("text_decrypted.txt","w");
	while((ch=fgetc(f1))!=EOF)
	{
		if(ch >= 'A' && ch <= 'Z')
		{
			ciphertxt_length++;
		}
	}

	int nrows = ciphertxt_length/key_length;
	char mat[nrows][key_length], decrypted[nrows][key_length];
	
	fseek(f1,0,SEEK_SET);
	i = 0;j = 0;
	while((ch=fgetc(f1))!=EOF)
	{
		if(ch >= 'A' && ch <= 'Z')
		{
			mat[i++][j] = ch;
			if(i >= nrows)
			{
				j++;i=0;
			}
		}
	}
	
	int jumbleOrder[key_length], orderNo = 1;

	for(j = (int)'A';j <= (int)'Z';++j)
	{
		for(i = 0;i < key_length;++i)
		{
			if((int)key[i] == j)
				jumbleOrder[i] = orderNo++;
		}
	}
	
	for(orderNo = 1;orderNo <= key_length;++orderNo)
	{
		for(j = 0;j < key_length;++j)
		{
			if(jumbleOrder[j] == orderNo)
			{
				for(i = 0;i < nrows;++i)
				{
					decrypted[i][j] = mat[i][orderNo-1];
				}
				break;
			}
		}
	}

	for(j = key_length-1;j >= 0;--j)
	{
		if (decrypted[nrows-1][j] == 'X')
			decrypted[nrows-1][j] == ' ';
		else
			break;
	}
	for(i = 0;i < nrows;++i)
	{
		for(j = 0;j < key_length;++j)
		{
			fprintf(f2, "%c", decrypted[i][j]);
		}
	}

	fprintf(f2,"\n");
	fclose(f1);
	fclose(f2);

	printf("\nCipher text decrypted\n");
	return 0;
}

int encrypt_vigenere(char key[])
{
	char ch;
	int i=0,len;
	len = strlen(key);
	while(key[i])
	{
		key[i]=toupper(key[i]);
		i++;
	}
	puts(key);
	i=0;
	FILE *f1,*f2;
	f1=fopen("text_filtered.txt","r");
	f2=fopen("text_encrypted.txt","w");
	while((ch=fgetc(f1))!=EOF)
	{
		ch=ch+key[i]-65;
		if(ch>90)
			ch=ch-26;
		fprintf(f2,"%c",ch);
		if(i==len-1)
			i=0;
		else
			i++;
	}
	fclose(f1);
	fclose(f2);
	printf("\nPlain text encrypted\n");
	return 0;
}

int decrypt_vigenere(char key[])
{
	char ch;
	int i=0,len;
	len = strlen(key);
	while(key[i])
	{
		key[i]=toupper(key[i]);
		i++;
	}
	i=0;
	FILE *f1,*f2;
	f1=fopen("text_encrypted.txt","r");
	f2=fopen("text_decrypted.txt","w");
	while((ch=fgetc(f1))!=EOF)
	{
		ch=ch-key[i]+65;
		if(ch<65)
			ch=ch+26;
		fprintf(f2,"%c",ch);
		if(i==len-1)
			i=0;
		else
			i++;
	}
	fclose(f1);
	fclose(f2);
	printf("\nCipher text decrypted\n");
	return 0;
}

//main function
int main()
{
	filter();
	int choice;
	char key[101];
	while(1)
	{
		printf("\nWhich operation do  you want perform ?");
		printf("\n0.Exit");
		printf("\n1.Encryption using Transposition cipher");
		printf("\n2.Decrption using Transposition cipher");
		printf("\n3.Encryption using Vigenère cipher");
		printf("\n4.Decrption using Vigenère cipher");
		printf("\nEnter your choice:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 0:
				return 0;
			case 1:
				printf("\nEnter En_key(single word max lentgh 100 characters):");
				scanf("%s",key);
				encrypt_transposition(key);
				break;
			case 2:
				printf("\nEnter De_key(single word max lentgh 100 characters):");
				scanf("%s",key);
				decrypt_transposition(key);
				break;
			case 3:
				printf("\nEnter En_key(single word max lentgh 100 characters):");
				scanf("%s",key);
				encrypt_vigenere(key);
				break;
			case 4:
				printf("\nEnter De_key(single word max lentgh 100 characters):");
				scanf("%s",key);
				decrypt_vigenere(key);
				break;
			default:
				printf("\nWronfg choice......\nEnter Number From 0 to 4.");
		}
	}
}