/**@file
 * @brief biblioteca de funções para manipulação de grafos
 * @author Julio L. Martins & Rubens Zandomenighi
 * @version 1.0
 * @date 2022-09-6
 */

#ifndef GRAPHLIB_H
#define GRAPHLIB_H

#include <stdbool.h>
#include "transaction.h"

#define DEFAULT_SIZE 10
#define resolveId(id) (id - 1)

typedef enum { GREEN, YELLOW, RED } TVisitState;

typedef struct vertex {
    long id;
    TVisitState state;
    TTransaction transaction;
    long adjacentListSize;
    struct vertex **adjacentList;
} TVertex;

typedef struct graph {
    TVertex *vertexList;
    long vertexListSize;
}Graph;

/**
 * @brief Cria um grafo a partir de um agendamento de transações
 *
 * @param graph - um grafo
 * @param schedule - um agendamento
 */
void createGraph(Graph *graph, TSchedule *schedule);

/**
 * @brief Verifica se o grafo tem ciclo
 *
 * @param graph - um grafo
 * @return true - se o grafo tem ciclo
 * @return false - se o grafo não tem ciclo
 */
bool isDirectedAcyclicGraph(Graph *graph);

/**
 * @brief destroi um grafo liberando a memória alocada
 * @param graph {Graph *} - um grafo
 */
void destroyGraph(Graph *graph);


#endif //GRAPHLIB_H
