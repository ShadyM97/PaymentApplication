#include<stdint.h>
#include<stdio.h>
#include<string.h>

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

ST_cardData_t cardData1;



EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{	
	uint8_t i = 0;
	printf("Please enter your name\n");
	gets(cardData1.cardHolderName);

	if (strlen(cardData1.cardHolderName) <= 24 && strlen(cardData1.cardHolderName) >= 20)
	{
		for (i = 0; i < strlen(cardData1.cardHolderName); i++)
		{
			// Check if the user input only contains alphabatical characters and only one space between names
			if ((cardData1.cardHolderName[i] >= 65 && cardData1.cardHolderName[i] <= 90) ||
				(cardData1.cardHolderName[i] >= 97 && cardData1.cardHolderName[i] <= 122) ||
					(cardData1.cardHolderName[i] == ' '&& cardData1.cardHolderName[i]!='  ')) { }
			else
				return WRONG_NAME;
		}
		//printf("Name Accepted\n");
		return CARD_OK;
	}
	else if (strlen(cardData1.cardHolderName) == 0 || strlen(cardData1.cardHolderName) < 20 || strlen(cardData1.cardHolderName)>24)
	{
		//printf("Name not accepted\n");
		return WRONG_NAME;
	}

}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	int mon = 0;
	int i = 0;
	printf("Please Enter Expiry Date (MM/YY)\n");
	gets(cardData1.cardExpirationDate);
	(void)sscanf(cardData1.cardExpirationDate, "%d/", &mon); // For validation of month entered.
	if (strlen(cardData1.cardExpirationDate) == 5 && cardData1.cardExpirationDate[2] == '/' && (mon > 0 && mon <= 12)) //Validate input format.
	{
		for (i = 0; i < strlen(cardData1.cardExpirationDate); i++)
		{
			//Check whether Expiry date input has only numaric characters according to ASCII Table from '0' to '9' and character '/'
			if(cardData1.cardExpirationDate[i] >= 47 && cardData1.cardExpirationDate[i] <= 57)
			{ }
			else
			{
				//printf("Expiry Not Accepted\n");
				return WRONG_EXP_DATE;
			}
		}
		//printf("Expiry Accepted\n");
		return CARD_OK;
	}
	else
	{
		//printf("Expiry Not Accepted\n");
		return WRONG_EXP_DATE;
	}

	
	
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	int i = 0;
	printf("Please Enter  Primary Account Number\n");
	gets(cardData1.primaryAccountNumber);
	if (strlen(cardData1.primaryAccountNumber) <= 19 && strlen(cardData1.primaryAccountNumber) >= 16)
	{
		for (i = 0; i < strlen(cardData1.primaryAccountNumber); i++)
		{
			//Check whether PAN has only numaric characters according to ASCII Table from '0' to '9'
			if (cardData1.primaryAccountNumber[i] >=48 && cardData1.primaryAccountNumber[i] <= 57)
			{ }
			else
			{
				//printf("PAN Not Accepted\n");
				return WRONG_PAN;
			}
		}
		//printf("PAN Accepted\n");
		return CARD_OK;
	}
	else if (strlen(cardData1.primaryAccountNumber) == 0 || strlen(cardData1.primaryAccountNumber) < 16 || strlen(cardData1.primaryAccountNumber)>19)
	{
		//printf("PAN Not Accepted\n");
		return WRONG_PAN;
	}
}

