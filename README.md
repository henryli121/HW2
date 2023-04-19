<h2> AMATH 583: High Performance Scientific Computing </h2>
This the homework 2 for hpc course at the Univeristy of Washington. Homework details are in the <code>amath483_583_hw2</code> file 
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Creating a Shared Library and Compiling with it</title>
</head>
<body>
  <h1>Steps to create a shared library and compile main files</h1>
  <ol>
    <li>
      <p>Compile the <code>func.cpp</code> file into a position-independent object file using the <code>-fPIC</code> flag:</p>
      <pre><code>g++ -c -fPIC func.cpp -o func.o</code></pre>
    </li>
    <li>
      <p>Create the shared library <code>librefBLAS.so</code> from the <code>func.o</code> object file:</p>
      <pre><code>g++ -shared -o librefBLAS.so func.o</code></pre>
    </li>
    <li>
      <p>Compile each of the main files (<code>main_p1.cpp</code>, <code>main_p3.cpp</code>, and <code>main_p4.cpp</code>) and link them with the shared library:</p>
      <pre><code>g++ main_p1.cpp -o main_p1 -L. -lrefBLAS
g++ main_p3.cpp -o main_p2 -L. -lrefBLAS
g++ main_p4.cpp -o main_p3 -L. -lrefBLAS</code></pre>
    </li>
    <li>
      <p>Run the compiled programs:</p>
      <pre><code>./main_p1
./main_p3
./main_p4</code></pre>
    </li>
  </ol>
</body>
</html>
