#!/bin/bash
NRTXT=0
NRTOT=0
for F in `find ~ -type f -name "*.txt"`; do
        NRTXT=`expr $NRTXT + 1`
done
    NRTOT=`ls|wc -l`
echo `expr $NRTOT / $NRTXT`