echo "-----------------DEMO 1-----------------\n"
echo "Compiling demo 1...\n"
if gcc bitmap/harness.c bitmap/bitmap.c bitmap/mymalloc.c bitmap/llist.c -o harness; then
    echo "Successfully compiled.\n"
    echo "Running demo 1...\n"
    ./harness
    rm harness
else
    echo "Compilation failed.\n"
fi
echo "---------------DEMO 1 END---------------\n"

echo "-----------------DEMO 2-----------------\n"
echo "Enter:\n ff for first-fit\n nf for next-fit\n"
read demo2
# Check if the directory exists
if [ ! -d "linkedlist/$demo2" ]; then
    echo "Error: invalid input!"
    exit 1
fi
if gcc "./linkedlist/$demo2/harness-$demo2.c" "./linkedlist/$demo2/llist.c" "./linkedlist/$demo2/mymalloc.c" -o "harness-$demo2"; then
    echo "\nSuccessfully compiled.\n"
    echo "Running demo 2...\n"
    ./"harness-$demo2"
    rm "harness-$demo2"
else
    echo "Compilation failed.\n"
fi
echo "\n---------------DEMO 2 END---------------\n"

echo "-----------------DEMO 3-----------------\n"
echo "Enter:\n bf for best-fit\n wf for worst-fit\n"
read demo3
# Check if the directory exists
if [ ! -d "linkedlist/$demo3" ]; then
    echo "Error: invalid input!"
    exit 1
fi
if gcc "./linkedlist/$demo3/harness-$demo3.c" "./linkedlist/$demo3/llist.c" "./linkedlist/$demo3/mymalloc.c" -o "harness-$demo3"; then
    echo "\nSuccessfully compiled.\n"
    echo "Running demo 3...\n"
    ./"harness-$demo3"
    rm "harness-$demo3"
else
    echo "Compilation failed.\n"
fi
echo "\n---------------DEMO 3 END---------------\n"