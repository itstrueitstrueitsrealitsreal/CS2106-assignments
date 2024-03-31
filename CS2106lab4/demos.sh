echo "Compiling demo 1...\n"
if gcc bitmap/harness.c bitmap/bitmap.c bitmap/mymalloc.c bitmap/llist.c -o harness; then
    echo "Successfully compiled.\n"
    echo "Running demo 1...\n"
    ./harness
    rm harness
else
    echo "Compilation failed.\n"
fi
