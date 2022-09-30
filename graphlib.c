/** @file graphlib.c
 * @author Julio L. Martins & Rubens Zandomenighi
 * @brief Implementação das funções de manipulação de grafos
 * @version 1.0
 * @date 2022-09-6
 */

#include <stdlib.h>
#include <string.h>
#include "graphlib.h"

/**
 * @brief adiciona uma aresta conforme as dependências entre as transações
 * @param graph {Graph *} - um grafo
 * @param schedule {TSchedule *} - um agendamento
 */
static void addDependencyEdge(Graph *graph, TSchedule *schedule) {
    long i, j, k, id;
    TTransaction scheduleTransaction;

    for (k = 1, i = 0; i < schedule->transactionListSize; i++) {
        scheduleTransaction = schedule->transactionList[i];
        id = scheduleTransaction.id;
        if (graph->vertexList[id].adjacentList == NULL) {
            graph->vertexList[id].adjacentList =  malloc(sizeof(TVertex*) * DEFAULT_SIZE * k++);
        }

        for (j = i + 1; j < schedule->transactionListSize; j++) {
            if ((scheduleTransaction.id != schedule->transactionList[j].id) &&
                (strcmp(scheduleTransaction.attribute, schedule->transactionList[j].attribute) == 0)) {

                if ((scheduleTransaction.operation == WRITE) &&
                    (schedule->transactionList[j].operation == READ)) {
                    graph->vertexList[id].adjacentList[graph->vertexList[id].adjacentListSize++] =
                            &graph->vertexList[resolveId(schedule->transactionList[j].id)];
                }

                if ((scheduleTransaction.operation == READ) &&
                    (schedule->transactionList[j].operation == WRITE)) {
                    graph->vertexList[id].adjacentList[graph->vertexList[id].adjacentListSize++] =
                            &graph->vertexList[resolveId(schedule->transactionList[j].id)];
                }

                if ((scheduleTransaction.operation == WRITE) &&
                    (schedule->transactionList[j].operation == WRITE)) {
                    graph->vertexList[id].adjacentList[graph->vertexList[id].adjacentListSize++] =
                            &graph->vertexList[resolveId(schedule->transactionList[j].id)];
                }
            }
            if (graph->vertexList[id].adjacentListSize == DEFAULT_SIZE) {
                graph->vertexList[id].adjacentList = (TVertex **) realloc(graph->vertexList[id].adjacentList,
                                                                        sizeof(TVertex) * DEFAULT_SIZE * k++);
            }
        }
    }
}

/**
 * @brief Cria um grafo a partir de um agendamento de transações
 *
 * @param graph {TGraph *} - um grafo
 * @param schedule {TSchedule *} - um agendamento
 */
void createGraph(Graph *graph, TSchedule *schedule) {
    long i;
    graph->vertexListSize = schedule->transactionQty;
    graph->vertexList = (TVertex *) malloc(sizeof(TVertex) * graph->vertexListSize);
    for (i = 0; i < graph->vertexListSize; i++) {
        graph->vertexList[i].id = i;
        graph->vertexList[i].state = GREEN;
        graph->vertexList[i].adjacentList = NULL;
        graph->vertexList[i].adjacentListSize = 0;
    }
    addDependencyEdge(graph, schedule);
}

void destroyGraph(Graph *graph){
    long i;
    for (i = 0; i < graph->vertexListSize; i++) {
        free(graph->vertexList[i].adjacentList);
    }
    free(graph->vertexList);
}

/**
 * @brief percorre o grafo assinalando os vértices visitados
 * @param vertex {TVertex} - um vértice
 * @param vertexId  {long} - o id do vértice
 */
static void visit(TVertex *vertexList, long vertexId, bool *hasCycle) {
    long i;

    if (vertexList[vertexId].state == RED) {
        return;
    }

    if (vertexList[vertexId].state== YELLOW) {
        (*hasCycle) = true;
    }

    if (vertexList[vertexId].state == GREEN) {
        vertexList[vertexId].state = YELLOW;
        for (i = 0; i < vertexList[vertexId].adjacentListSize; i++) {
            if (vertexList[vertexId].adjacentList[i]->state == GREEN) {
                visit(vertexList, vertexList[vertexId].adjacentList[i]->id, hasCycle);
            }
        }
        vertexList[vertexId].state = RED;
    }
}

bool isDirectedAcyclicGraph(Graph *graph) {
    long vertexId;
    bool hasCycle = false;

    for (vertexId = 0; vertexId < graph->vertexListSize; vertexId++) {
        visit(graph->vertexList, vertexId, &hasCycle);
    }
    return hasCycle;
}