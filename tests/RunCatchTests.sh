#!/bin/bash

cd ../tests

#remove any previous working version
rm -f test

# Stop execution on any error
set -e

echo "building tests..."

RP="../debug"
#TODO: can't use wildcards e.g. ../release/*.o because of multiple 'main's... fix!
#g++ -std=gnu++11 -Wall  -DDEBUG -g -o test  *.cpp 
# recommened by chatGPT for arduino: 
g++ -std=c++11 -Wall -DDEBIG -g -o test *.cpp

echo "...success!"  
  
rm -f ../output/*  
cd ../output
echo ""
echo "  now testing.."

../tests/test


echo "NOT cleaning up.."
#rm -f *.txt
#rm -f *.conf
#rm -f *.dat
#rm -f *.cfg

cd ../tests


#############
# todo: consider using cccc to get software metrics..
# todo: consider how to use valgrind within this
