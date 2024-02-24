#!/bin/bash

# Check if we have enough arguments
if [[ $# -ne 1 ]]; then
    echo "Usage: ./grade.sh <file_name>"
    exit 1
fi
# Delete temporary files
rm ref/*.out
rm subs/*.out
rm subs/*.err
rm *.out
rm $1
# Compile the reference program
total_score=0
total_files=0
# For each in file, generate the corresponding out file
gcc ./ref/sum.c ./ref/utils.c -o "$1"
for file in ref/*.in; do
    ./"$1" < "$file" > "${file}".out
    total_score=$((total_score+1))
done

# Now mark submissions
#
# Note: See Lab02Qn.pdf for format of output file. Marks will be deducted for missing elements.
#
# Test date and time:
echo "Test date and time: $(date +%A), $(date +"%d %B %Y"), $(date +%T)" > result.out
# For each file in subs
for student in subs/*; do
    # Reset mark
    mark=0
    rm subs/$(basename "$student")/*.out
    total_files=$((total_files+1))
    # Compile C code
    gcc $student/*.c -o $student.out
    # if error, print error message to output file and continue to next file
    if [[ $? -ne 0 ]]; then
        echo "Directory $student has a compile error" >> result.out
        echo "Directory $student score $mark/$total_score" >> result.out
        continue
    fi
    # Generate output from C code using *.in files in ref
    for infile in ref/*.in; do
        $student.out < "$infile" > "$student/${infile##*/}.out"
        # Compare with reference output file and award 1 mark if they are identical
        diff -q "${infile}.out" "$student/${infile##*/}.out"
        if [[ $? -eq 0 ]]; then
            mark=$((mark+1))
        fi
    done
    echo "Directory $student score $mark/$total_score" >> result.out
    rm $student/*.out
    
done
# Print marks out of total to result.out e.g. Directory $file score 2/3
rm ref/*.out
# Processed no_of_files files
echo "Processed $total_files files" >> result.out