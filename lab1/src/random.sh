#!/bin/bash

MAXCOUNT=150
count=1

while [ "$count" -le $MAXCOUNT ]     
do
  number=$(($RANDOM%10))
  echo $number >> number.txt
  let "count += 1"  
done

