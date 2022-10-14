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
`query_tree.cc`
- 
`test_tree.cc`
- 
`test_tree_mod.cc`
- 

You will use this exact `Makefile` for your Homework 2. Failure to do so will result in *deduction* of points. Replace this file with a `README.md` for your own project. You can move these instructions to the bottom of the file if you wish.

To compile on terminal, type:

```bash
make
```

You can compile one program individually by just typing `make <Program Name>`, for example:

```bash
make query_tree
```

To delete executables and object files, type:

```bash
make clean
```
