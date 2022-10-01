#include "transaction.h"
#include "auxiliar.h"
#include "viewEquivalentSchedules.h"
#include <stdbool.h>
#include <stdlib.h>


/**
 * @brief 
 * 
 * @param escalation 
 * @return true 
 * @return false 
 */
bool isScheduleEquivalent(escalationT *escalation)
{
    int commandsQt = getCommandQt(escalation); 
    int nPermutations = fact(commandsQt);
    tCommand *allCommands =malloc(sizeof(tCommand)* commandsQt);
    getAllCommands(escalation,allCommands);
    tCommand **allPermutations = alocateMatCommands(nPermutations+1, commandsQt+1);

    int idx =0;
    permute(allCommands,0,commandsQt-1,allPermutations, &idx, escalation);;
    
    for (int i=0;i < nPermutations;i++){
        if (checkLastWriteCondition(allPermutations[i], commandsQt) && checkWriteAfterRead(allPermutations[i],commandsQt)){
            return true; 
        }
    }
    return false;
}

/**
 * @brief 
 * 
 * @param commands 
 * @param n 
 * @return true 
 * @return false 
 */
bool checkLastWriteCondition(tCommand *commands, int n){
    int lastOriginalTransactionCommitTime = 0;
    int curTransactionLastCommitTime = 0;
    for (int i =0;i < n;i++){
        if (commands[i].type == COMMIT){
            curTransactionLastCommitTime=commands[i].time; 
            if (commands[i].time > lastOriginalTransactionCommitTime){
                lastOriginalTransactionCommitTime = commands[i].time;
            }
        }
    }
    return lastOriginalTransactionCommitTime == curTransactionLastCommitTime; 
}

/**
 * @brief Function to check if 
 * 
 * @param commands {tCommand *}
 * @param n {int n}
 * @return true 
 * @return false 
 */
bool checkWriteAfterRead(tCommand *commands, int n){
    for (int i =0;i < n;i++){
        if (commands[i].type == READ){
            if (checkIfIsThereNextCommandByType(commands,WRITE, i, n))
                return false;
        }
    }
    return true; 
}

/**
 * @brief Get the quantity of commands in the escalation
 * @param escalation {escalationT} Escalation to get all commands 
 * @return int - quantity of escalations
 */
int getCommandQt (escalationT *escalation){
    int commandsQt = 0;
    
    for (int i = 0;i< escalation->transactionsQt;i++){
        commandsQt+=escalation->transactions[i].commandsQt; 
    }
    return commandsQt; 
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Get the All Commands object
 * @param escalation {escalationT} The escalation to get the commands
 * @param allCommands {array} Array to receive all commands
 */
void getAllCommands(escalationT *escalation, tCommand *allCommands)
{
    int curCommand = 0;

    for (int i = 0; i < escalation->transactionsQt; i++)
    {
        for (int j = 0; j < escalation->transactions[i].commandsQt; j++)
        {
            allCommands[curCommand] = escalation->transactions[i].commands[j];
            curCommand++;
        }
    }
}
/* -------------------------------------------------------------------------- */
