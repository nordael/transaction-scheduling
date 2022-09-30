#ifndef _AUXILIAR_H_
#define _AUXILIAR_H_

int fact(int n);
int **alocateMat(int lin, int col); 
void swap(tCommand *x, tCommand *y);
void printAllPermutations(tCommand **allPermutations, int lines, int cols);
void permute(tCommand *array, int init, int end, tCommand **allPerm, int *idx,escalationT *originalEscalation); 
void translateTransactionsIdxToCommands(tCommand *newCommandsOrder,int *transactionsOrders,escalationT *originalEscalation, int n );
tCommand **alocateMatCommands(int lin, int col);

#endif