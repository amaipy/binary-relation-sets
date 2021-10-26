# binary-relation-sets

Binary Relation Sets algorithm implemented in C.

It was made as an assignment for the Discrete Mathematics course at UFMG in the second term of 2020 (02/2020).

# Instructions

* To compile the algorithm, execute in a terminal that has `gcc` installed:

`gcc -o tp tp.c`

* And to run:

`./tp exemplos/exemplo.txt`


## Implementation

As it is necessary to read the test file (a .txt), the file path is passed as an argument to the function. The first line of the file defines 
how the matrix will be, with the first number defining both the number of columns and the number of lines. Because it is necessary 
to have control of when the line skips, `fgetc` was used until the end of the file was found. 

Each char read is passed to a variable. It is expected that after reading a digit (a char that is different from space or end of 
file or newline or tab), it is preceded by a space to form the complete number that will be treated when assembling the array. Each 
digit is inserted into an auxiliary array. When a char other than a digit is found, the array is disassembled, and the number is 
treated according to other relations. 

The matrix structure is set up so that the first row and column will contain all the numbers that are part of the problem. Therefore, 
the matrix has rows and columns equal to `n + 1`. The following rows after the first will define the matrix as popular by indicating 
the relationship between the numbers (entering 1 in the row and column), with the first number being the position row and the second 
number the column position in the matrix. A function is used to find the real index where each number is in the matrix structure, 
that is, what is its position in the first row, which consequently is its position in the column. Thus, it is possible to populate 
the matrix with the relations correctly. 

Some analyzes need to print the ordered pairs that make it `False`, so a struct was created to represent the pair and a matrix (with 6 
rows and `n^2` columns) that will have all the cases to be tested. For each case, there is a counter, which is incremented when it finds 
a pair that makes the case test `False`. 

Each case was analyzed based on the information previously given to solve the problem. To print the tests, it checks if the counter 
for that case is equal to `0`, which determines that the property is `true`. Otherwise, it prints which is `false` and prints the pairs 
depending on the case. The relation of equivalence and partial order, on the other hand, verifies the previous cases. Moreover, to 
print the transitive closure, the matrix is transformed to its transitive version if necessary.
