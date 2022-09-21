#include<stdio.h>
#include<stdint.h>
#include<time.h>
#include"..\Card\card.h"


typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;


typedef enum EN_terminalError_t
{
	TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

ST_terminalData_t terminalData1;
ST_cardData_t cardData1;


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	uint8_t sysDay = 0;
	uint8_t sysMon = 0;
	uint16_t sysYear = 0;

	struct tm* ptr;
	time_t t;
	time(&t);
	ptr = gmtime(&t);
	sysDay = ptr->tm_mday;
	sysMon = 1 + ptr->tm_mon;
	sysYear = 1900 + ptr->tm_year;
	sprintf(terminalData1.transactionDate, "%02d/%02d/%d", sysDay, sysMon, sysYear);
	//printf("System Date is:\n");
	//puts(terminalData1.transactionDate);
	return TERMINAL_OK;

}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) 
{
	int cardMon,sysDay, sysMon;
	int cardYear, sysYear;
	(void)sscanf(cardData1.cardExpirationDate, "%d/%d",&cardMon,&cardYear);
	(void)sscanf(terminalData1.transactionDate, "%d/%d/%d", &sysDay, &sysMon, &sysYear);
	sysYear -= 2000;
	//printf("System date is %02d/%d and Expiry date is %02d/%d\n", sysMon, sysYear, cardMon, cardYear);
	if (sysYear > cardYear)
	{
		//printf("Card Expired\n");
		return EXPIRED_CARD;
	}
	else if (sysYear == cardYear && sysMon >= cardMon)
	{
		//printf("Card Expired\n");
		return EXPIRED_CARD;
	}
	else
	{
		//printf("Card Expiry is valid\n");
		return TERMINAL_OK;
	}
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Please Enter Transcation Amount:\n");
	(void)scanf("%f",&terminalData1.transAmount);
	if (terminalData1.transAmount <= 0)
	{
		//printf("Input Invalid\n");
		return INVALID_AMOUNT;
	}
	else
		return TERMINAL_OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (terminalData1.transAmount > terminalData1.maxTransAmount)
	{
		//printf("Input Exceed max amount\n");
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		//printf("Amount is valid\n");
		return TERMINAL_OK;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	terminalData1.maxTransAmount = 7000.0;
	return TERMINAL_OK;
}
