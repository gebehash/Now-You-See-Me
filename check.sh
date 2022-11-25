#!/bin/bash
# Checher tema 1 SD 2022
NO_TESTS=90
EXEC=tema1
TEST_POINTS=(0 0.6 0.6 0.6 0.6 0.6 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0.6 0.6 0.6 0.6 0.6 0.6 0.6 0.6 0.6 0.6 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 0.7 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1)
TIMEOUT_TIME=(2 0.005 0.005 0.005 0.005 0.005 0.005 0.005 0.005 0.005 0.005 0.005 0.005 0.005 0.005 0.005 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.01 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.05 0.1 0.1 0.1 0.1 0.1 1 1 1 1 1 5 5 5 5 5 1 1 1 1 1 1 1 1 1 1)
VALGRIND_TIMEOUT_TIME=(50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50)
BONUS_POINTS=(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) #valgrind
TOTAL=0
BONUS=0
ERRORS_NUMBER=0
CODING_STYLE_POINTS=10
README_POINTS=20
CURRENT_DIRECTORY=`pwd`
ONE=1
TWO=2
MESSAGE_SIZE=12
PASSED_TESTS_GRADE=0

make build
mkdir "out"

function timeout_test() {
    test_no=$1
    input_path="in/test"$test_no".in"
    out_path="out/test"$test_no".out"

    # Get the input and ref files for the current test
    timeout=${TIMEOUT_TIME[$test_no]}

    (time timeout $timeout ./$EXEC <$input_path >$out_path) 2>time.err
    TEST_RESULT=$?
}

function valgrind_test() {
    test_no=$1
    input_path="in/test"$test_no".in"
    out_path="out/test"$test_no".out"


    # Get the input and ref files for the current test
    timeout=${VALGRIND_TIMEOUT_TIME[$test_no]}

    (time timeout $timeout valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 -q ./$EXEC <$input_path >$out_path) 2>time.err

    TEST_RESULT=$?
}

function check_valgrind_test() {
    test_no=$1

    echo -n "Test: $test_no ...................... "

    valgrind_test $test_no

    if [ "$TEST_RESULT" != "0" ]; then
        echo "DETECTED MEMORY LEAKS"
       	#tail -n 10 time.err
        rm -f time.err
        return
    else
        echo "NO MEMORY LEAKS"
        rm -f time.err
        BONUS=$(expr $BONUS + ${BONUS_POINTS[$test_no]})
        return
    fi
}

# Check a single test and add the result to the total score. This function
# should _always_ receive a test number as the first and only argument
function check_test() {
    test_no=$1

    # check valgrind first
    check_valgrind_test $1

    if [ "$TEST_RESULT" != "0" ]; then
        echo "Test: $test_no ...................... FAILED BECAUSE OF VALGRIND"
        rm -f time.err
        return
    fi

    timeout_test $test_no
    # Run the test, also consider the timeout
    if [ "$TEST_RESULT" != "0" ]; then
        echo "TIMEOUT [$timeout s]"
        rm -f time.err
		return
	fi

	out_path="out/test"$test_no".out"
	ref_path="ref/test"$test_no".ref"

	echo -n "Test: $test_no ...................... "

	# Check the result
	diff -bB -i $ref_path $out_path 2>&1 1> my_diff

	if test $? -eq 0; then
	    echo "PASS [${TEST_POINTS[$test_no]}p]"
	    TOTAL=$(echo "$TOTAL + ${TEST_POINTS[$test_no]}" | bc)
	    PASSED_TESTS_GRADE=$(($PASSED_TESTS_GRADE+1));
	else
	    echo "FAILED"
	    echo "Diff result:"
	    cat my_diff | tail -n 10
	fi

    # Clean up
    rm -f my_diff
    rm -f time.err
}

function checkCodingStyle {
    printf '%*s\n' "${COLUMNS:-$(($(tput cols) - $ONE))}" '' | tr ' ' -
    echo "" > checkstyle.txt

    echo -ne "Coding style errors:\n"
    for entry in *.{c,h}; do
	echo $entry
        if [[ -f $entry ]]; then
            python2.7 cpplint.py --root=$(pwd) --filter=-build/include,-runtime/printf,-runtime/threadsafe_fn,-build/include_what_you_use "$entry" > checkstyle.txt
            YOUR_BONUS=`cat checkstyle.txt | grep "Total errors found: "| tr -dc '0-9'`
            ERRORS_NUMBER=$(( $ERRORS_NUMBER+$YOUR_BONUS ))
        fi
    done

    if [[ $ERRORS_NUMBER != "0" ]]; then
        CODING_STYLE_POINTS=0
        echo -ne "\n\t\tYou have a total of $ERRORS_NUMBER coding style errors. [${CODING_STYLE_POINTS}p]\n"
    else
        CODING_STYLE_POINTS=$(($CODING_STYLE_POINTS))
        echo -ne "\n\tNone? Wow, next level! [${CODING_STYLE_POINTS}p]\n\n"
    fi
    rm -f checkstyle.txt
}

function checkReadme {
    printf '%*s\n' "${COLUMNS:-$(($(tput cols) - $ONE))}" '' | tr ' ' -
    echo -ne "Readme:\n"

    if test -f "./README"; then
        CHAR_NUMBER=$(stat --printf="%s" README)
        if [[ $(($CHAR_NUMBER)) -gt 100 ]]; then
            README_POINTS=$(($README_POINTS))
            echo -e "\tREADME exists [${README_POINTS}p]"
        else
            README_POINTS=0
            echo -e "\tREADME exists, but it's too short [${README_POINTS}p]"
        fi
    elif test -f "./README.md"; then
        CHAR_NUMBER=$(stat --printf="%s" README.md)
        if [[ $(($CHAR_NUMBER)) -gt 100 ]]; then
            README_POINTS=$(($README_POINTS))
            echo -e "\tREADME.md exists [${README_POINTS}p]"
        else
            README_POINTS=0
            echo -e "\tREADME.md exists, but it's too short [${README_POINTS}p]"
        fi
    else
        echo "README does not exist"
        README_POINTS=0
    fi
}

# Check if the the exec exist
if test ! -x $EXEC; then
    echo "Exec file missing"
    exit 1
fi

echo ""
for ((i=1;i<=$NO_TESTS;i++)); do
	check_test $i
    echo ""
done

# And the result is ...
echo "TEST POINTS: $TOTAL/90.0"
echo ""

checkCodingStyle
checkReadme

TOTAL_SCORE=$(echo "$TOTAL + $CODING_STYLE_POINTS + $README_POINTS" | bc)
echo -e "\nTOTAL: $TOTAL_SCORE/120.0"

make clean &> /dev/null
rm -rf out
