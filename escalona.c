#include <stdio.h>
#include <stdlib.h>
#include "transaction.h"
#include "viewEquivalentSchedules.h"
#include "graphlib.h"

/**
 * @brief Function to loop through schedule, print the escalations and print if is view equivalent and if is serializable
 * @param schedule {tSchedule *} - Schedule received
 */
void loopThroughSchedule(tSchedule *schedule, TScheduleList *graphScheduleList) {
    Graph graph[schedule->escalationsQt];
    TSchedule graphSchedule;

    for (int i=0;i < schedule->escalationsQt;i++){
        escalationT *curEscalation = &schedule->escalations[i];
        graphSchedule = graphScheduleList->schedule[i];
        createGraph(&graph[i], &graphSchedule);

        printf("%d ",i+1);
        for (int j=0;j < curEscalation->transactionsQt-1;j++){
            printf("%d,",curEscalation->transactions[j].id);
        }
        printf("%d ",curEscalation->transactions[curEscalation->transactionsQt-1].id);

        if (isDirectedAcyclicGraph(&graph[i])){
            printf("SS ");
        }else{
            printf("NS ");
        }

        if (isScheduleEquivalent(curEscalation)){
            printf("SV\n");
        }else{
            printf("NV\n");
        }
        destroyGraph((graph+i));
    }

}

int main(int argc, char **argv)
{
    TScheduleList scheduleList; //used to build the graph
    tSchedule *mySchedule = loadSchedule(stdin, &scheduleList);

    loopThroughSchedule(mySchedule, &scheduleList);

    free(mySchedule);
    destroyGraphSchedule(scheduleList.schedule);
    return 0;
};