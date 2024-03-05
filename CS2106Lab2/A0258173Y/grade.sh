#!/bin/bash

# Check if we have enough arguments
if [[ $# -ne 1 ]]; then
    echo "Usage: ./grade.sh <filename>"
else
# Delete temporary files
rm ./ref/*.out
# Compile the reference program
gcc ./ref/sum.c ./ref/utils.c -o "$1"
# Generate reference output files
for i in ./ref/*.in; do
    ./"$1" < "$i" > "${i%.in}".out
done
# Now mark submissions
echo -e "Test date and time: $(date +%A), $(date +%d) $(date +%B) $(date +%Y), $(date +%T)\n" > results.out
#
# Note: See Lab02Qn.pdf for format of output file. Marks will be deducted for missing elements.
#

# Iterate over every submission directory
for student in ./subs/*; do
    # Compile C code
    # Print compile error message to output file
    gcc "$student"/sum.c "$student"/utils.c -o "$student/$1"
    if [[ $? -ne 0 ]]; then
        echo -e "Directory ${student##*/} has a compile error." >> results.out
    fi
    max_score=$(ls ref/*.in | wc -l)
    score=0
    # Generate output from C code using *.in files in ref
    for i in ./ref/*.in; do
      ref_output="${i%.in}.out"
      student_output="$("$student/$1" < "$i")"
      if diff -q "$ref_output" <(echo "$student_output"); then
         ((score++))
      fi
    done
    # Compare with reference output files and award 1 mark if they are identical
    # print score for student
    echo -e "Directory ${student##*/} score ${score} / ${max_score}" >> results.out
    rm "$student/$1"
done
# print total files marked.
echo -e "\nProcessed $(ls ./subs/ | wc -l) files." >> results.out
rm ./fun
fi