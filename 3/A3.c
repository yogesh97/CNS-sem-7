//Playfair Cipher
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Filters text.txt and saves into text_filtered.txt
void filter()
{
	char ch;
	FILE *f1, *f2;
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
	//printf("\ntext filtered\n");
	return;
}

int encrypt_playfair(char key[])
{
	int len = strlen(key), i, j;
	char keyMatrix[5][5];
	int char_loc_in_key_matrix[26][2];
	int temp1[26]={0};
	char key_updated[len];

	j=0;
	for(i=0;i<len;i++)
	{
		if(key[i]>='A' && key[i]<='Z')
		{
			key_updated[j]=key[i];
			j++;

		}
		else if(key[i]>='a' && key[i]<='z')
		{
			key_updated[j]=key[i]-32;
			j++;
		}
		if(key_updated[j-1]=='J')
		{
			key_updated[j-1]='I';
		}
	}
	key_updated[j]='\0';

	len = strlen(key_updated);
	j=0;
	for(i=0;i<len;i++)
	{
		if(temp1[key_updated[i]-'A'] == 0)
		{
			keyMatrix[j/5][j%5] = key_updated[i];
			temp1[key_updated[i] - 'A'] = 1;
			char_loc_in_key_matrix[key_updated[i]-'A'][0]=j/5;
			char_loc_in_key_matrix[key_updated[i]-'A'][1]=j%5;
			j++;
		}
	}

	temp1['J' - 65] = 1;
	for(i=0;i<26;i++)
	{
		if(temp1[i] == 0)
		{
			keyMatrix[j/5][j%5] = i + 'A';
			temp1[i] = 1;
			char_loc_in_key_matrix[i][0]=j/5;
			char_loc_in_key_matrix[i][1]=j%5;
			j++;
		}
	}
	char_loc_in_key_matrix['J'-65][0] = char_loc_in_key_matrix['I'-65][0];
	char_loc_in_key_matrix['J'-65][1] = char_loc_in_key_matrix['I'-65][1];

	printf("\n");
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%c ",keyMatrix[i][j]);
		}
		printf("\n");
	}
	/*
	for(i=0;i<26;i++)
	{
		printf("%c %d %d\n",i + 'A',char_loc_in_key_matrix[i][0],char_loc_in_key_matrix[i][1]);
	}
	printf("\n");
	*/

	char ch1,ch2,temp;
	int ch1r,ch2r,ch1c,ch2c,flag=0;
	FILE *f1, *f2;
	f1 = fopen("text_filtered.txt","r");
	f2 = fopen("text_encrypted.txt","w");

	filter();
	printf("\nPlain  text: ");
	while((ch1 = fgetc(f1)) != EOF)
	{
		NEXT:
		flag = 0;
		if((ch2 = fgetc(f1)) == EOF)
		{
			if(ch1 != 'X')
				ch2 = 'X';
			else
				ch2 = 'Q';
		}
		else if(ch1 == ch2)
		{
			temp = ch2;
			flag = 1;
			if(ch1 != 'X')
				ch2 = 'X';
			else
				ch2 = 'Q';
		}

		printf("%c%c ",ch1,ch2);

		ch1r = char_loc_in_key_matrix[ch1 - 'A'][0];
		ch1c = char_loc_in_key_matrix[ch1 - 'A'][1];
		ch2r = char_loc_in_key_matrix[ch2 - 'A'][0];
		ch2c = char_loc_in_key_matrix[ch2 - 'A'][1];
		if(ch1r == ch2r)
		{
			fprintf(f2, "%c%c", keyMatrix[ch1r][(ch1c+1)%5], keyMatrix[ch1r][(ch2c+1)%5]);
		}
		else if (ch1c == ch2c)
		{
			fprintf(f2, "%c%c", keyMatrix[(ch1r+1)%5][ch1c], keyMatrix[(ch2r+1)%5][ch1c]);
		}
		else
		{
			fprintf(f2, "%c%c", keyMatrix[ch1r][ch2c], keyMatrix[ch2r][ch1c]);
		}
		if(flag == 1)
		{
			ch1 = temp;
			goto NEXT;
		}
	}
	fclose(f1);
	fclose(f2);
	
	
	f2 = fopen("text_encrypted.txt","r");
	char ch;
	printf("\nCipher text: ");
	while((ch = fgetc(f2)) != EOF)
	{
		printf("%c",ch);
		ch = fgetc(f2);
		printf("%c ",ch);		
	}
	printf("\n");
	fclose(f2);
	
	printf("Plain text encrypted\n");
	return 0;
}

int decrypt_playfair(char key[])
{
	int len = strlen(key), i, j;
	char keyMatrix[5][5];
	int char_loc_in_key_matrix[26][2];
	int temp1[26]={0};
	char key_updated[len];

	j=0;
	for(i=0;i<len;i++)
	{
		if(key[i]>='A' && key[i]<='Z')
		{
			key_updated[j]=key[i];
			j++;

		}
		else if(key[i]>='a' && key[i]<='z')
		{
			key_updated[j]=key[i]-32;
			j++;
		}
		if(key_updated[j-1]=='J')
		{
			key_updated[j-1]='I';
		}
	}
	key_updated[j]='\0';

	len = strlen(key_updated);
	j=0;
	for(i=0;i<len;i++)
	{
		if(temp1[key_updated[i]-'A'] == 0)
		{
			keyMatrix[j/5][j%5] = key_updated[i];
			temp1[key_updated[i] - 'A'] = 1;
			char_loc_in_key_matrix[key_updated[i]-'A'][0]=j/5;
			char_loc_in_key_matrix[key_updated[i]-'A'][1]=j%5;
			j++;
		}
	}

	temp1['J' - 65] = 1;
	for(i=0;i<26;i++)
	{
		if(temp1[i] == 0)
		{
			keyMatrix[j/5][j%5] = i + 'A';
			temp1[i] = 1;
			char_loc_in_key_matrix[i][0]=j/5;
			char_loc_in_key_matrix[i][1]=j%5;
			j++;
		}
	}
	char_loc_in_key_matrix['J'-65][0] = char_loc_in_key_matrix['I'-65][0];
	char_loc_in_key_matrix['J'-65][1] = char_loc_in_key_matrix['I'-65][1];

	printf("\n");
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%c ",keyMatrix[i][j]);
		}
		printf("\n");
	}
	/*
	for(i=0;i<26;i++)
	{
		printf("%c %d %d\n",i + 'A',char_loc_in_key_matrix[i][0],char_loc_in_key_matrix[i][1]);
	}
	printf("\n");
	*/

	char ch1,ch2;
	int ch1r,ch2r,ch1c,ch2c;
	FILE *f1, *f2;
	f1 = fopen("text_encrypted.txt","r");
	f2 = fopen("text_decrypted.txt","w");

	printf("\nCipher text: ");
	while((ch1 = fgetc(f1)) != EOF)
	{
		ch2 = fgetc(f1);
		printf("%c%c ",ch1,ch2);

		ch1r = char_loc_in_key_matrix[ch1 - 'A'][0];
		ch1c = char_loc_in_key_matrix[ch1 - 'A'][1];
		ch2r = char_loc_in_key_matrix[ch2 - 'A'][0];
		ch2c = char_loc_in_key_matrix[ch2 - 'A'][1];
		if(ch1r == ch2r)
		{
			fprintf(f2, "%c%c ",keyMatrix[ch1r][(ch1c+4)%5],keyMatrix[ch1r][(ch2c+4)%5]);
		}
		else if (ch1c == ch2c)
		{
			fprintf(f2, "%c%c ",keyMatrix[(ch1r+4)%5][ch1c],keyMatrix[(ch2r+4)%5][ch1c]);
		}
		else
		{
			fprintf(f2, "%c%c ",keyMatrix[ch1r][ch2c],keyMatrix[ch2r][ch1c]);
		}
	}
	fclose(f1);
	fclose(f2);
	
	f2 = fopen("text_decrypted.txt","r");
	char ch;
	printf("\nPlain  text: ");
	while((ch = fgetc(f2)) != EOF)
	{
		printf("%c",ch);
	}
	printf("\n");
	fclose(f2);

	printf("Cipher text decrypted\n");
	return 0;
}

//main function
int main()
{
	int choice;
	char key[101];
	while(1)
	{
		printf("\nWhich operation do  you want perform ?");
		printf("\n0.Exit");
		printf("\n1.Encryption using Playfair cipher");
		printf("\n2.Decrption using Playfair cipher");
		printf("\nEnter your choice:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 0:
				return 0;
			case 1:
				printf("\nEnter En_key(signle word max lentgh 100 characters):");
				scanf("%s",key);
				if(strlen(key) == 0 )
					printf("\nZero length key is not valid.");
				else
					encrypt_playfair(key);
				break;
			case 2:
				printf("\nEnter De_key(single word max lentgh 100 characters):");
				scanf("%s",key);
				if(strlen(key) == 0 )
					printf("\nZero length key is not valid.");
				else
					decrypt_playfair(key);
				break;
			default:
				printf("\nWronfg choice......\nEnter Number from 0 to 2.");
		}
	}
}