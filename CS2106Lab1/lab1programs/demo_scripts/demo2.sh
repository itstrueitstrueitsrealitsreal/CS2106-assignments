srun gcc ../part3/testlist.c ../part3/llist.c -o ../part3/testlist
srun valgrind ../part3/testlist
rm ../part3/testlist
