#!/bin/sh
freq=20000 #28800  #7031

tmp=/tmp/$$_$RANDOM.wav
sox $1 -r $freq -b -c 1 $tmp avg
sox $tmp $2

rm $tmp
