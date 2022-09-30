#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include <stdio.h>
#include <stdbool.h>

#define MAX_SCHEDULES 10

typedef enum {
    READ,
    WRITE,
    COMMIT
} typesE;

typedef struct tCommand
{
    typesE type;
    char atribute[20];
    int transactionId;
    int time;
} tCommand;

typedef struct tTransaction
{
    int id;
    tCommand commands[50];
    int commandsQt;
    bool isOpened;
} tTransaction;

typedef struct escalationT
{
    tTransaction transactions[50];
    int openedTransactions;
    int transactionsQt;
} escalationT;

typedef struct tSchedule
{
    escalationT escalations[50];
    int escalationsQt;
    int transactionsQt;

} tSchedule;

tSchedule *createSchedule();

/*================ INICIO - PARA CRIAR O GRAFO DE DEPENDÊNCIAS ======================================*/
/**
 * @struct TTransaction
 * @brief Struct to represent a transaction
 * @field id {int} Transaction id
 * @field operation {typesE *} Array of commands
 * @field attributes {char *} Array of attributes
 */
typedef struct transaction{
    long id;
    typesE operation;
    char attribute[20];
}TTransaction;

/**
 * @struct TSchedule
 * @brief Stores all transactions read
 * @field transactionList {tTransaction *} list of transactions
 * @field transactionsListSize {long} quantity of transactions
 * @field transactionQty {int} quantity of unique transactions ids
 */
typedef struct schedule {
    long transactionListSize;
    long transactionQty;
    TTransaction *transactionList;
} TSchedule;

typedef struct scheduleList {
    long scheduleListSize;
    TSchedule *schedule;
} TScheduleList;

/**
 * @biref cria uma lista de agendamentos
 * @param scheduleList - lista de agendamentos
 */
void createGraphScheduleList(TScheduleList *scheduleList);

/**
 * @brief libera memoria alocada para um agendamento
 * @param schedule um agendamento
 */
void destroyGraphSchedule(TSchedule *schedule);
/**
 * @brief cria uma lista de transações de um agendamento
 * @param schedule
 */
void createTransactionList(TSchedule *schedule);

/**
 * @brief insere uma transação em um agendamento
 * @param schedule uma agendamento
 * @param command um comando
 * @param index posição da transação no agendamento
 */
void insertTransaction(TSchedule *schedule, tCommand command, int index);

/**
 * @brief conta a quantidade de transações únicas em um agendamento
 * @param scheduleList uma lista de agendamentos
 */
void countUniqueTransactions(TScheduleList *scheduleList);
/*================ FIM - PARA CRIAR O GRAFO DE DEPENDÊNCIAS ======================================*/

tSchedule *getConcurrentTransactions(tSchedule *mySchedule);
tCommand *createCommand(char *commandType, char *atribute, int transactionId, int time);
void addCommand(tTransaction *transactions, int transactionsQt, tCommand *command);
tCommand *getCommand(char *line);
tTransaction *createTransaction(int id);

tSchedule *loadSchedule(FILE *fp, TScheduleList *scheduleList);

tTransaction *beginTransaction(int id);
bool isNewTransaction(tSchedule *schedule, int transactionId);
bool checkIfIsThereNextCommandByType(tCommand *commands, typesE commandSearchedType, int idx, int commandsQt);

#endif