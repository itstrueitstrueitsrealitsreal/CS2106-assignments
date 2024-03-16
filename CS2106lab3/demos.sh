echo "Compiling demo 1:"
gcc part1/lab3p1-shm-counter.c -o demo1 -lpthread
echo "Running demo 1:"
./demo1
rm demo1

echo "Compiling demo 2:"
gcc part2/barrier.c part2/test_barrier.c -o demo2 -lpthread
echo "Running demo 2:"
./demo2
rm demo2

echo "Compiling demo 3:"
gcc part3/barrier.c part3/sum-par.c -o demo3 -lpthread
echo "Running demo 3:"
./demo3
echo "Running sum.c:"
gcc part3/sum.c -o sum
./sum
rm sum
rm demo3
