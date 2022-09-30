#include <stdlib.h>
#include "transaction.h"

/* Function to swap values at two pointers */
void swap(tCommand *x, tCommand *y)
{
    tCommand temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* -------------------------------------------------------------------------- */
int transactionNextCommandIdx (int curIdx, int endIdx, int *transactionsOrder){
    int nextIdx =0;
    int myNewTransactionId = transactionsOrder[curIdx]; 
    for (int i=0;i < curIdx;i++){
        if (transactionsOrder[i] == myNewTransactionId){
            nextIdx++; 
        }
    }

    return nextIdx;
}

tCommand getMyTransactionCommand(int commandIdx, int transactionId,escalationT *escalation){
    for (int i=0;i<escalation->transactionsQt;i++){
        if (escalation->transactions[i].id == transactionId ){
            return escalation->transactions[i].commands[commandIdx]; 
        }
    }

}

void translateTransactionsIdxToCommands(tCommand *newCommandsOrder,int *transactionsOrders,escalationT *originalEscalation, int n ){
    for (int i =0;i <= n;i++){
        int commandIdx = transactionNextCommandIdx( i,n, transactionsOrders);
        tCommand myCommand = getMyTransactionCommand(commandIdx, transactionsOrders[i], originalEscalation);
        newCommandsOrder[i]=myCommand; 
    }
}

/**
 * @brief Function to permute the all commands array
 * @param array {tCommand *} Original commands array to get all permutations
 * @param init {int} Init range to be permutated
 * @param end {int} end range to be permutated
 * @param allPerm {tCommand **} Matrix with all possible permutations
 * @param idx {int} - Index of the current permutation to atributte to all permutation mat line
 */
void permute(tCommand *array, int init, int end, tCommand **allPerm, int *idx,escalationT *originalEscalation)
{
    if (init == end)
    {
        int transactionOrderPermutation[end+1];
        int myTransactionsIdx[end+1]; 
        for (int k = 0; k <= end; k++)
        {
            transactionOrderPermutation[k] =array[k].transactionId;
        }
        translateTransactionsIdxToCommands(allPerm[(*idx)], transactionOrderPermutation, originalEscalation,end);
        // allPerm[(*idx)][k] = array[k];
        (*idx)++; 
    }
    else
    {
        for (int i = init; i <= end; i++)
        {
            swap((array + init), (array + i));
            permute(array, init + 1, end, allPerm, idx, originalEscalation);
            swap((array + init), (array + i)); // backtrack
        }
    }
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Function to print all permutations 
 * @param allPermutations {tCommand **} - Matrix with all the permutations
 * @param lines {int} - number of lines in the allPermutations matrix
 * @param cols {int} - number of collumns in the allPermutations matrix
 */
void printAllPermutations(tCommand **allPermutations, int lines, int cols){
    for (int i=0;i < lines;i++){
        for (int j=0;j < cols;j++){

            switch (allPermutations[i][j].type)
                    {
                    case READ:
                        printf("[%d READ %s ]",allPermutations[i][j].transactionId,allPermutations[i][j].atribute);
                        break;
                    case WRITE:
                        printf("[%d WRITE %s ]",allPermutations[i][j].transactionId,allPermutations[i][j].atribute);
                        break;
                    case COMMIT:
                        printf("[%d COMMIT %s ]",allPermutations[i][j].transactionId,allPermutations[i][j].atribute);
                        break;
                    default:
                        break;
                    }
        }
        printf("\n");
    }
}

/* -------------------------------------------------------------------------- */

int fact(int n)
{
    if (n == 1)
    {
        return n;
    }

    return n * fact(n - 1);
}

/* -------------------------------------------------------------------------- */
int **alocateMat(int lin, int col)
{
    int **mat;
    mat = malloc(lin * sizeof(int *));
    mat[0] = malloc(lin * col * sizeof(int));

    for (int i = 1; i < lin; i++)
        mat[i] = mat[0] + i * col;

    return mat;
}

tCommand **alocateMatCommands(int lin, int col)
{
    tCommand **mat;
    mat = malloc(lin * sizeof(tCommand *));
    mat[0] = malloc(lin * col * sizeof(tCommand));

    for (int i = 1; i < lin; i++)
        mat[i] = mat[0] + i * col;

    return mat;
}

void freeMat(tCommand **mat)
{
    free(mat[0]);
    free(mat);
}