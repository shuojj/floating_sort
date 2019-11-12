A C program that sorts a set of 4-byte float point values in ascending order using radix sort. 
The values are saved in a file. The program should read/write the file through memory mapping. 
When the program finishes, the sorted values should be saved in the same file.

The program should take one argument, which is the pathname of the file containing the data to be sorted. For example, to sort the float point values saved in ./file5k, you can use the following command:
```
./radixsort ./file5k
```

You can compile gendata.c attached with this assignment and use it to generate random values and save them into a file. The executable file can also be found in /bin in the virtual machine. The program also reports the sum of the values. For example, to generate 5000 random values and save them into ./file5kvalues, you can use the following command
```
./gendata 5000 ./file5kvalues
```

You can compile checkdata.c attached with this assignment and use it to check whether the float point values have been sorted in ascending order. The executable file can also be found in /bin in the virtual machine. The tool also calculates a sum of the values in the file. Thus, you can compare the sum with the sum reported by gendata. The two sums should be very similar with minor numerical error caused by limited precisions.
```
./checkdata ./file5kvalues
```