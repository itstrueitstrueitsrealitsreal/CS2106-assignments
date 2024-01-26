srun gcc ../part4/llist.c ../part4/dir.c ../part4/testdir.c -o ../part4/testdir
srun valgrind ../part4/testdir
rm ../part4/testdir