//Ceaser Cipher

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int FC[26][2],fc[26][2];
int ref_FC0=-1,ref_FC1=-1;

//frequency counter for reference file article.txt
void frequency_counter_for_reference_file()
{
	int i;
	for(i=0;i<26;i++)
	{
		FC[i][0]=65+i;
		FC[i][1]=0;
	}

	char ch;
	FILE *f1;
	f1=fopen("article.txt","r");
	while((ch=fgetc(f1))!=EOF)
	{
		if((ch>='A'&&ch<='Z'))
			FC[ch-65][1]++;
		else if(ch>='a'&&ch<='z')
			FC[ch-97][1]++;
	}
	fclose(f1);

	for(i=0;i<26;i++)
	{
		if(FC[i][1] > ref_FC1)
		{
			ref_FC1 = FC[i][1];
			ref_FC0 = FC[i][0];
		}
	}

	/*
	for(i=0;i<26;i++)
	{
		printf("%c->%5d\n",FC[i][0],FC[i][1]);
	}
	*/
	printf("character:%c and frequency:%5d\n",ref_FC0,ref_FC1);

	printf("\nFrequency of Alphabets in reference file calculated\n");
	return;	
}

//frequency counter for encrypted file text_encrypted.txt
void frequency_counter_for_encrypted_file()
{
	int i;
	for(i=0;i<26;i++)
	{
		fc[i][0]=65+i;
		fc[i][1]=0;
	}

	char ch;
	FILE *f1;
	f1=fopen("text_encrypted.txt","r");
	while((ch=fgetc(f1))!=EOF)
	{
		if((ch>='A'&&ch<='Z'))
			fc[ch-65][1]++;
		else if(ch>='a'&&ch<='z')
			fc[ch-97][1]++;
	}
	fclose(f1);	

	int temp1,temp0,j;
	for(i=1;i<26;i++)
	{
		temp1=fc[i][1];
		temp0=fc[i][0];
		j=i-1;
		while(j>=0 && fc[j][1] < temp1)
		{
				fc[j+1][1]=fc[j][1];
				fc[j+1][0]=fc[j][0];
				j=j-1;
		}
		fc[j+1][1]=temp1;
		fc[j+1][0]=temp0;
	}

	printf("\n");
	for(i=0;i<26;i++)
	{
		printf("%c->%5d\n",fc[i][0],fc[i][1]);
	}

	printf("\nFrequency of Alphabets in encrypted file is calculated\n");
	return;	
}

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

//Encryption
void encrypt()
{
	int key;
	printf("Enter encryption key(must be integer from 1 to 25)");
	scanf("%d",&key);
	char ch;
	FILE *f1,*f2;
	f1=fopen("text_filtered.txt","r");
	f2=fopen("text_encrypted.txt","w");
	while((ch=fgetc(f1))!=EOF)
	{
		ch = ch + key;
		if(ch>90)
			ch=ch-26;
		fprintf(f2,"%c",ch);
	}
	fclose(f1);
	fclose(f2);
	printf("\nPlain text encrypted\n");
	return;
}

//Decryption
void decrypt()
{
	int key;
	printf("Enter decryption key(must be integer from 1 to 25)");
	scanf("%d",&key);
	char ch;
	FILE *f1,*f2;
	f1=fopen("text_encrypted.txt","r");
	f2=fopen("text_decrypted.txt","w");
	while((ch=fgetc(f1))!=EOF)
	{
		ch = ch + key;
		if(ch>90)
			ch=ch-26;
		fprintf(f2,"%c",ch);
	}
	fclose(f1);
	fclose(f2);
	printf("\nCipher text decrypted\n");
	return;
}

//Brute Force Attack
void Brute_force()
{
	int key,cho;
	printf("\nStarting Brute Force(max 26 trials).\n");
	key=1;
	Again:
	printf("\nTrying next key.");
	printf("\nTrail no:%d and de_key:%d",key,key);
	char ch;
	FILE *f1,*f2;
	f1=fopen("text_encrypted.txt","r");
	f2=fopen("text_decrypted.txt","w");
	while((ch=fgetc(f1))!=EOF)
	{
		ch = ch + key;
		if(ch>90)
			ch=ch-26;
		fprintf(f2,"%c",ch);
	}
	fclose(f1);
	fclose(f2);
	C1:
	printf("\nOpen file text_decrypted.txt\nIf text is readable then\n\tEnter 0\nelse\n\tEnter 1:");
	scanf("%d",&cho);
	if(cho == 0)
		{
			printf("\nCipher text Decrypted.Trail no:%d\n",key);
			printf("Decryption key:%d\nEncryption key:%d\n",key,26-key);
		}
	else if(cho == 1)
		{
			key++;
			if(key ==27)
			{
				C2:
				key=1;
				int cho2;
				printf("\nall possible keys are tested.want to try again ?\n0 for yes and 1 for no:");
				scanf("%d",&cho2);
				if(cho2 == 0)
					goto Again;
				else if(cho2 == 1)
					return;
				else
					goto C2;
			}
			else
				goto Again;
		}
	else
		goto C1;
	return;
}

//Frequency Analysis Attack
void Frequency_analysis()
{
	frequency_counter_for_encrypted_file();

	int key,cho,trno=1;
	printf("\nGuessing keys by Frequency Analysis(max 26 trials).\n");
	
	Again:
	
	key = (26 -(fc[trno-1][0]-ref_FC0))%26;

	printf("\nTrying next key.");
	printf("\nTrail no:%d and de_key:%d",trno,key);
	
	char ch;
	FILE *f1,*f2;
	f1=fopen("text_encrypted.txt","r");
	f2=fopen("text_decrypted.txt","w");
	while((ch=fgetc(f1))!=EOF)
	{
		ch = ch + key;
		if(ch>90)
			ch=ch-26;
		fprintf(f2,"%c",ch);
	}
	fclose(f1);
	fclose(f2);
	
	C1:
	printf("\nOpen file text_decrypted.txt\nIf text is readable then\n\tEnter 0\nelse\n\tEnter 1:");
	scanf("%d",&cho);
	if(cho == 0)
		{
			printf("\nCipher text Decrypted.Trail no:%d\n",trno);
			printf("Decryption key:%d\nEncryption key:%d\n",key,26-key);
		}
	else if(cho == 1)
		{
			trno++;
			if(trno == 27)
			{
				C2:
				trno=1;
				int cho2;
				printf("\nall possible keys are tested.want to try again ?\n0 for yes and 1 for no:");
				scanf("%d",&cho2);
				if(cho2 == 0)
					goto Again;
				else if(cho2 == 1)
					return;
				else
					goto C2;
			}
			else
				goto Again;
		}
	else
		goto C1;
	return;
}

//main function
int main()
{
	filter();
	frequency_counter_for_reference_file();
	int choice;
	CHOICE:
	printf("\nWhich operation do  you want perform ?");
	printf("\n0.Exit");
	printf("\n1.Encryption");
	printf("\n2.Decrption");
	printf("\n3.Brute Force Attack");
	printf("\n4.Frequency Analysis Attack");
	printf("\nEnter your choice:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 0:
			return 0;
		case 1:
			encrypt();
			break;
		case 2:
			decrypt();
			break;
		case 3:
			Brute_force();
			break;
		case 4:
			Frequency_analysis();
			break;
		default:
			printf("\nWronfg choice......\nEnter Number From 0 to 4.");
			goto CHOICE;
	}
	goto CHOICE;
	return 0;
}
