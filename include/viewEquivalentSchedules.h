#include "transaction.h"
#ifndef _VIEWEQUIVALENTSCHEDULES_H_
#define _VIEWEQUIVALENTSCHEDULES_H_

bool isScheduleEquivalent(escalationT *escalation);
void getAllCommands(escalationT *escalation, tCommand *allCommands);
int getCommandQt (escalationT *escalation); 
bool checkLastWriteCondition(tCommand *commands, int n);
bool checkWriteAfterRead(tCommand *commands, int n);

#endif