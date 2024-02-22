#!/bin/bash

# Check if we have enough arguments
if [[ $# != 1 ]]; then
    echo "Usage: ./grade.sh <file_name>"
    exit 1
fi
# Delete temporary files
rm *.out
# Compile the reference program
gcc ref/*.c -o $1
# Generate reference output files

# Now mark submissions

#
# Note: See Lab02Qn.pdf for format of output file. Marks will be deducted for missing elements.
#

# Iterate over every submission directory
count=0
for dir in */
do
    # Compile C code
    gcc -o $1 $1.c 2> $1.err
    # Print compile error message to output file
    cat $1.err > $1.out
    # Generate output from C code using *.in files in ref
    $1 < ref/1.in > $1.out
    # Compare with reference output files  and award 1 mark if they are identical
    diff -q $1.out ref/1.out > /dev/null
    if [[ $? -eq 0 ]]; then
        echo "1" >> $1.out
    else
        echo "0" >> $1.out
    fi
    # Increment count
    let count=count+1
done
# Clean up
rm $1 $1.err
# print score for student
cat $1.out
# print total files marked.
echo "Total files marked: $count"

