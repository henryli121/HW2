<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
    <h1>AMATH 583: High Performance Scientific Computing</h1>
    <p>This is the homework 2 for HPC course at the University of Washington.</p>
    <h2>For Problem 1-4</h2>
    <p>All functions (e.g. dgemv, daxpy) are defined in the <code>func.cpp</code> file with corresponding header file: <code>func.hpp</code></p>
    <p>All functions have been tested via our test files which are named as:</p>
    <ul>
        <li>main_p1.cpp</li>
        <li>main_p2.cpp</li>
        <li>main_p3.cpp</li>
        <li>main_p4.cpp</li>
    </ul>
    <p>To compile them:</p>
    <pre>
g++ -std=c++11 main_p1.cpp func.cpp
./a.out
    </pre>
    <p>All the results/plots are in the <code>hw2.pdf</code> file.</p>
    <h2>For Problem 5-6</h2>
    <p>All template functions (i.e. gemv, axpy, gemm) are defined in the <code>func_temp.cpp</code> file with corresponding header file: <code>refBLAS.hpp</code></p>
    <p>The functions have been tested via another main file: <code>main_p1_p3.cpp</code></p>
    <h3>Creating a Shared Library and Compiling with it</h3>
    <p>Steps to create a shared library and compile main files:</p>
    <ol>
        <li>Compile the <code>func_temp.cpp</code> file into a position-independent object file using the <code>-fPIC</code> flag:
            <pre>
g++ -c -fPIC func_temp.cpp -o func_temp.o
            </pre>
        </li>
        <li>Create the shared library <code>librefBLAS.so</code> from the <code>func.o</code> object file:
            <pre>
g++ -shared -o librefBLAS.so func_temp.o
            </pre>
        </li>
        <li>Compile each of the main (test) files (<code>main_p1_p3.cpp</code>) and link them with the shared library:
            <pre>
g++ -std=c++11 main_p1_p3.cpp -o main_p1_p3 -L. -lrefBLAS
            </pre>
        </li>
        <li>Run the compiled programs:
            <pre>
./main_p1_p3
            </pre>
        </li>
    </ol>
    <p>Note that we only test L1 and L2 in our <code>main_p1_p3.cpp</code> since L3 takes a long time to run and we have already got results from previous problems. So this is just testing that our shared library is working.</
