# Assignment 2

## Information about the repository

This repository contains the following:
- `avl_tree.h`
- `avl_tree_p2c.h`
- `sequence_map.h`
- `query_tree.cc`
- `test_tree.cc`
- `test_tree_mod.cc`

## Parts of the program completed

All parts completed.

`avl_tree.h`
- insert(): unmodified.
- remove(): return value is now boolean (used to determine if remove was successful), and increments the recursion_counter member variable for every recursive call.
- contains(): unmodified.
- findMin(): modified to count recursive calls (towards recursion_counter).
- findMax(): unmodified.
- isEmpty(): unmodified.
- makeEmpty(): unmodified.
- printTree(): unmodified.
- getElement(): added function to access element of node.
- numberOfNodes(): counts the number of nodes in the tree (size_t).
- internalPathLength(): calculates (and returns internal path length (size_t). Formula: internal path length of left + internal path length of right + nodes - 1.
- averageDepth(): calculates and returns average depth (float). Formula: internal path length / nodes.
- find(): returns true if element is found and false if not. Recursive calls are counted towards recursion_counter.
- getTotalRecursionCalls(): getter function for the accumulated recursive calls of findMin(), find(), and remove().
- resetRecursionCounter(): resets the recursion counter member to 0.

`avl_tree_p2c.h`
- doubleRotateWithLeftChild(): double rotation now happens in one go without calling 2 single rotation functions.
- doubleRotateWithRightChild(): double rotation now happens in one go without calling 2 single rotation functions.

`sequence_map.h`
- The big five: all set to default.
- One-parameter constructor: initializes recognition_sequence_ only.
- Two-parameter constructor: initializes recognition_sequence_ and adds one enzyme acronym to vector.
- setRecognitionSequence: mutator to set recognition sequence member.
- operator<: regular string comparison (string class), if lhs < rhs return true; else false.
- operator>: regular string comparison (string class), if lhs > rhs return true; else false.
- Merge(): appends supplied SequenceMap object's enzyme_acronyms_ vector to current SequenceMap object's enzyme_acronyms_ vector.
- PrintEnzymeAcronyms(): cout the enzyme_acronyms_ vector. Output format: AasI AabI etc...
- PrintRecognitionSequence(): cout the recognition_sequence_ member.
- operator<<: similar print format to PrintEnzymeAcronyms() function. Output format: AasI AabI etc...
- operator>>: takes in enzyme acronyms in a list format from a file or user input and puts it in the enzyme_acronyms_ vector member.

`query_tree.cc` `test_tree.cc` `test_tree_mod.cc`
- The above 3 files all use a helper parsing function: **GetNextRecognitionSequence()** to help separate and retreive the recognition sequences and enzyme acronyms in each line from the database. The function's return value is boolean and returns true if there are more enzyme acronyms to retreive and false if not. The function utilizes the '/' separators to determine how to split the line and '//' to determine when to stop. The function updates the a_reco_seq string via reference.
- To reduce the cost of object creation, SequenceMap has an added function **setRecognitionSequence()**. This was added to allow for the possibility of a variable outside of the while loop (to read user/file input) to be used for comparison purposes. This allows for the comparison variable's recognition_sequence_ to be adjusted for comparisons (for querying, finding, and removing nodes in the tree).

## Input File

`rebase210.txt`
`input_part2a.txt`
`sequences.txt`

## Output file

`output_part2a.txt`
`output_part2b.txt`

## Running the assignment

Use provided `Makefile` for Homework 2.

To compile on terminal, type:

```bash
make
```

You can compile one program individually by just typing `make <Program Name>`, for example:

```bash
make query_tree
```

```bash
make test_tree
```

```bash
make test_tree_mod
```

To delete executables and object files, type:

```bash
make clean
```
