#include<stdio.h>
#include<stdint.h>
#include"..\Card\card.h"
#include"..\Terminal\terminal.h"
#include"..\Server\server.h"

void appStart()
{
	ST_cardData_t cardData1;
	ST_cardData_t* pCard;
	pCard = &cardData1;
	getCardHolderName(pCard);
	getCardExpiryDate(pCard);
	getCardPAN(pCard);
	ST_terminalData_t terminalData1;
	ST_terminalData_t* pTerminal;
	pTerminal = &pTerminal;
	getTransactionDate(pTerminal);
	if (isCardExpired(pCard, pTerminal) == TERMINAL_OK)
	{
		getTransactionAmount(pTerminal);
		setMaxAmount(pTerminal);
		if (isBelowMaxAmount(pTerminal)==TERMINAL_OK)
		{
			ST_transaction_t transData1;
			ST_transaction_t* pTrans;
			pTrans = &transData1;
			if (recieveTransactionData(pTrans) == APPROVED)
			{
				if (saveTransaction(pTrans) == SERVER_OK)
				{
					printf("Transcation Saved");
				}
				else
					printf("Saving Failed");
			}
			else if (recieveTransactionData(pTrans) == DECLINED_STOLEN_CARD)
			{
				printf("Declined Invalid Account");
			}
			else if (recieveTransactionData(pTrans) == DECLINED_INSUFFECIENT_FUND)
				printf("Insuffecient Funds");
			//getTransaction(0, pTrans);
		}
		else
			printf("Declined Amount Exceeding Limit");
	}
	else
		printf("Declined Expired Card");

}