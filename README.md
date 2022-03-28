
			#CSCE611 Project 1: Multi dimensional producer-consumer problem.
			
	Submission by: Karthik Eswar Krishnamoorthy Natarajan
				   630008438 | karthik047@tamu.edu
	List of people worked with: None

			
Overview:	
	The typical instance of the coordination problem is the producer-consumer problem. Here, the producers and consumers communicate by message passing rather than using a shared buffer or memory. The implementation of the problem must be coordinated so that the consumers does not run ahead of the producers and also the producers do not overwrite records before the consumers consume them. The P&S primitives (Pass and Signal) are used here to handle the above stated problems.

Files:
	- prod_cons.h: Header files and function declaration.
	- prod_cons.c: Source Code.
	- makefile:    The recipe for the compilation of source code with appropriate flags. 
	- prod_cons.exe: The executable generated after the compilation.
	
Compilation:

	- make/make all: Generate the executable file.
	- make clean: Delete the executable file.
	
Usage:

	- ./prod_cons.exe <number of producer-consumer pairs>
	- default value for arg[1] = 5.
