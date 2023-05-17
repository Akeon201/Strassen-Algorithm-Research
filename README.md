# Strassen-Algorithm-Research

This README will guide you through setting up and using the program to multiply matrices.

# Summary
    
In this project, we explore the performance of two matrix multiplication algorithms, 
Strassen's and Brute Force, along with a hybrid approach that combines the strengths of both. 
Strassen's algorithm is a recursive method with a time complexity of O(n^2.807...), while the 
Brute Force algorithm has a time complexity of O(n^3). Recursion, as employed by Strassen's 
algorithm, often incurs considerable overhead, which can lead to significant time differences 
when processing smaller inputs. In some cases, Strassen's algorithm can take over ten times as 
long to compute matrix multiplication compared to the Brute Force approach.

The primary objective of this project was to identify an optimal cutoff value for the combination 
of Strassen's and Brute Force algorithms, ultimately maximizing the time saved during matrix 
multiplication. By carefully analyzing the performance of both algorithms under various input sizes, 
the project aimed to find a sweet spot where switching between the two methods would result in 
the most efficient and effective solution for matrix multiplication tasks.

# Setup

    1. Ensure you are in the correct file directory.
    2. Use a Linux machine or have WSL (Windows Subsystem for Linux) installed on your Windows machine.
    3. To create the executable, simply type make into the command line.

# Interactive Mode

    1. Run the executable by typing "./run_algorithms" into the command line.
    2. A menu with 5 options will be displayed. Choose an option by typing a number from 1 to 5 and 
       pressing enter.
    3. If prompted to print the results to the console, respond with 'y' (yes) or 'n' (no) and press 
       enter.
    4. Enter a file name without a file extension for a neat output.
    5. When asked to enter a matrix size, provide a value of n that will be an exponent of 2, ensuring 
       perfectly square matrices for the algorithms.
    6. If you choose an option regarding strassenv2, this is the combined algorithm. Enter an integer 
       to set the cutoff n.
    7. Finally, enter an integer for the number of matrix pairs you want to multiply.

# Import File

    To import file, type "./run_algorithms [file name]" into the command line.
        Note: If your file name contains spaces, please enclose the entire string in quotes.
