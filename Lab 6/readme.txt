Ethan Kwan
004899710
Lab 6

1. wget https://web.cs.ucla.edu/classes/winter19/cs35L/assign/srt.tgz
2. tar -xf srt.tgz 
3. I knew I had to link Makefile to the lpthread library
   so I added this:
    LDLIBS = -lm -lpthread
4. First, I had to identify which parts of main.c could be multithreaded.
   I chose to move a lot of the crucial variable initialization into 
   pixelDivide along with the long nested for loop. This way, I could 
   utilize the threads to split up the largest portion of the work. I
   incremeneted the printing loop by numthreads so that each thread
   would cover the offset that the others had not covered. 
5. The variables had to be moved because many of the functions within the 
   loop were dependent on the variables from the main routine.
6. I used a 3D array to store the pixel values, with the 3rd dimension 
   corresponding with the level of sphere recursions. I made the array global
   so that it could be accessed by all threads. 
7. I did not know how to keep track of the thread numbers, but I realized 
   that I could pass in an argument for pixelDivide in pthread_create. 
   Once that was figured out, I was then able to effectively join the threads.
8. After all the threads are finished, I print out the contents of the 3D arr.
9. Time tests:
   
   time ./srt 1-test.ppm > 1-test.ppm

   real    0m47.790s
   user    0m47.764s
   sys     0m0.003s

   time ./srt 2-test.ppm > 2-test.ppm.tmp
   real    0m24.381s
   user    0m24.369s
   sys     0m0.004s

   time ./srt 4-test.ppm > 4-test.ppm.tmp
   real    0m12.039s
   user    0m31.082s
   sys     0m0.004s
   
   time ./srt 8-test.ppm > 8-test.ppm.tmp   
   real    0m6.315s
   user    0m30.536s
   sys     0m0.004s

   
