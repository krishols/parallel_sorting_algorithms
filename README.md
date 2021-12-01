# Parallel Sorting Algorithms
A group pursuit to parallelize sorting algorithms and subsequent reflection. 

# Table of Contents 
- Introduction
- Requirements
- Recommended Modules
- Installation
- Configuration
- FAQ and Troubleshooting
- Maintainers

# Introduction 
Sorting Algorithms can vary greatly by: 
- Runtime
- Memory usage
- Comparison versus non-comparison 
- Stability 

We ask: 

How do these characteristics affect sorting algorithms’ ability to be parallelized or accelerated? 

Is there a pattern to which algorithms are most able to be parallelized (CPUs) or accelerated (GPUs)? 

Our work explores possible answers to these questions. 


# Requirements
- GNU GCC Compiler (We used 10.2)
- NVIDIA HPC SDK Compiler (We used 21.7)
- OpenACC
- OpenMP 
- Multicore System with at least one GPU 

# Installation 
``` git clone https://github.com/krishols/parallel_sorting_algorithms.git ```

# Frequently Asked Questions
1. Why is my code not speeding up? 

Make sure you're using compiler flags! 
- OpenMP: -fopenmp (gcc) -mp (nvhpc)
- OpenACC: -fopenacc (gcc) -acc (nvhpc) 

Additionally, code does not always go as expected. We suggest **troubleshooting** by profiling to understand compute/memory use with tools such as GProf, NVIDIA Nsight Compute or System 

# Maintainers 
Michael Carr (Merge Sort)
Kristina Holsapple (Bucket Sort)
Jayson Morgado (Bubble Sort) 
