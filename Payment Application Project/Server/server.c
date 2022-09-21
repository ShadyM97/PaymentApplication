#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include"..\Terminal\terminal.h"
#include"..\Card\card.h"

typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;
typedef enum EN_serverError_t
{
	SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;

typedef enum EN_accountState_t
{
	RUNNING,
	BLOCKED
}EN_accountState_t;
typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;



typedef struct ST_accountsDB_t
{
	float balance;
	EN_accountState_t state;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;


ST_accountsDB_t accountsDB1[255] = {5000.0,BLOCKED, "9896985698796525",
									2000.0,RUNNING, "8989374615436851", 
									100000.0, BLOCKED, "5807007076043875",
									50000.0,RUNNING,"5807007058043898",
									3000.0, BLOCKED, "5808800076043875",
									9000,RUNNING,"7057374615436851",
									80000,RUNNING,"8989374618899851",
									1000,RUNNING,"7057374615430077",
									90000,RUNNING,"7057378889436851",
									200000,RUNNING,"8989374789499851" ,
									60000,RUNNING,"7057374331436851" };

ST_transaction_t transDataBase[255]={0};
ST_cardData_t cardData1;
ST_terminalData_t terminalData1;
int transcationNum = 0;
//int i=0;

int accountNum = 0;//Used to identify the location of the account in the database

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	for (int i = 0; i < 11; i++)
	{
		if (strcmp(cardData1.primaryAccountNumber, accountsDB1[i].primaryAccountNumber) == 0)
		{
			//printf("Account found\n");
			accountNum = i;
			i = 11;
			return SERVER_OK;
		}

		else if (i == 10 && strcmp(cardData1.primaryAccountNumber, accountsDB1[i].primaryAccountNumber) != 0)
		{
			//printf("Not Found\n");
			return ACCOUNT_NOT_FOUND;
		}
	}
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if (accountsDB1[accountNum].state == BLOCKED)
	{
		//printf("CARD STOLEN\n");
		return BLOCKED_ACCOUNT;
	}
	else;
	{
		//printf("CARD Running\n");
		return SERVER_OK;
	}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (terminalData1.transAmount > accountsDB1[accountNum].balance)
	{
		//printf("Low Balance\n");
		return LOW_BALANCE;
	}
	else
	{
		accountsDB1[accountNum].balance -= terminalData1.transAmount;
		//printf("Balance Available\n");
		return SERVER_OK;
	}
}
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{	
	ST_cardData_t cardData1;
	ST_cardData_t* pCard;
	pCard = &cardData1;
	ST_terminalData_t terminalData1;
	ST_terminalData_t* pTerminal1;
	pTerminal1 = &terminalData1;
	ST_accountsDB_t accountsDB1;
	ST_accountsDB_t* paccountsDB;
	paccountsDB = &accountsDB1;

	if (isValidAccount(pCard, paccountsDB) == SERVER_OK)
	{
		if (isBlockedAccount(paccountsDB) == SERVER_OK)
		{
			if (isAmountAvailable(pTerminal1) == SERVER_OK)
			{
				//printf("Approved\n");
				return APPROVED;
			}
			else
				return DECLINED_INSUFFECIENT_FUND;
		}
		else
			return DECLINED_STOLEN_CARD;
	}
	else
		return FRAUD_CARD;
	
	

}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	if (1) {
		//Save cardHolder Data
		memcpy(&transDataBase[transcationNum].cardHolderData.cardHolderName, cardData1.cardHolderName, sizeof(cardData1.cardHolderName));
		memcpy(&transDataBase[transcationNum].cardHolderData.cardExpirationDate, cardData1.cardExpirationDate, sizeof(cardData1.cardExpirationDate));
		memcpy(&transDataBase[transcationNum].cardHolderData.primaryAccountNumber, cardData1.primaryAccountNumber, sizeof(cardData1.primaryAccountNumber));
		//Save Terminal Data
		transDataBase[transcationNum].terminalData.transAmount = terminalData1.transAmount;
		transDataBase[transcationNum].terminalData.maxTransAmount = terminalData1.maxTransAmount;
		memcpy(&transDataBase[transcationNum].terminalData.transactionDate, terminalData1.transactionDate, sizeof(terminalData1.transactionDate));
		//Save Transcation State
		transDataBase[transcationNum].transState = recieveTransactionData(transData);
		transDataBase[transcationNum].transactionSequenceNumber = transcationNum;

		//printf("Card Data is %s,%s,%s\n", transDataBase[transcationNum].cardHolderData.cardHolderName,
			//transDataBase[transcationNum].cardHolderData.cardExpirationDate,
			//transDataBase[transcationNum].cardHolderData.primaryAccountNumber);
		//printf("Terminal Data is %f,%f\n", transDataBase[transcationNum].terminalData.maxTransAmount, transDataBase[transcationNum].terminalData.transAmount);
		//puts(transDataBase[transcationNum].terminalData.transactionDate);
		//printf("Transcation State %d,Transnum %d\n", transDataBase[transcationNum].transState, transDataBase[transcationNum].transactionSequenceNumber);
		return SERVER_OK;
	}
	else
		return SAVING_FAILED;
	
	transcationNum++;
}

getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{

	if (transactionSequenceNumber == transDataBase[transactionSequenceNumber].transactionSequenceNumber)
	{
		//printf("TRANSCATION FOUNND\n");
		return SERVER_OK;
	}
	else
	{	
		//printf("TRANSCATION NOT FOUND\n");
		return TRANSACTION_NOT_FOUND;
	}
		
}






