#!/bin/bash
#!sudo su
process="ComputerServer.exe"
if test $(ps aux | grep $process | awk '{print $2}' | wc -l) -eq 0 
then
	echo "There is no the PID";
	exit 0
fi
  for pid in $(ps aux | grep $process | awk '{print $2}')
  do
        kill -s 9 $pid;
        echo "Close the PID:"$pid;
  done	
  exit 0
