#!/bin/bash

## CONSTANTS ##
CURRENT_DIRECTORY=`pwd`
RESOURCES_DIRECTORY="checker"
GOOD_TESTS=0
GOOD_CODE_STYLE=`echo -ne "Starting audit...\nAudit done.\n"`
no_tests=15
total_score=0
test_points=1

# ## FUNCTIONS ##
function cleanHomework
{
	rm dummy 2> /dev/null
	rm -rf $RESOURCES_DIRECTORY/out/*
	make clean
}

function compileHomework
{
	make
}

function checkTest
{
    echo -ne "Test\t$1\t.....................................\t"

	if [ $? -eq 0 ]; then
		`./graph < $RESOURCES_DIRECTORY/in/$1.in > $RESOURCES_DIRECTORY/out/$1.out`
        `diff -Bw -u --ignore-all-space $RESOURCES_DIRECTORY/out/$1.out $RESOURCES_DIRECTORY/ref/$1.ref &> /dev/null`
        DIFF_RESULT=$?

        if [ $DIFF_RESULT -eq 0 ]; then
        	echo -ne "OK\n"
			total_score=$((total_score + test_points))

            GOOD_TESTS=$((GOOD_TESTS))
        else
           echo -ne "FAIL (files differ)\n"
        fi
    else
        echo -ne 'FAIL (program error)\n'
    fi
}

function calculateScore
{
	GOOD_TESTS=$((GOOD_TESTS))

	GOOD_TESTS=`echo "scale=2; $GOOD_TESTS" | bc -l`
	#show_points = `echo "scale=2; $((total_score / 4))" | bc -l`
	BAD_CODE_STYLE=`echo "scale=2; $BAD_CODE_STYLE" | bc -l`

	echo -ne "\n$total_score / 15 tests passed\n"
	
}

## MAIN EXECUTION ##
cleanHomework
compileHomework

checkTest "1"
checkTest "2"
checkTest "3"
checkTest "4"
checkTest "5"
checkTest "6"
checkTest "7"
checkTest "8"
checkTest "9"
checkTest "10"
checkTest "11"
checkTest "12"
checkTest "13"
checkTest "14"
checkTest "15"



calculateScore
cleanHomework