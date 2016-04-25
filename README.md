# SVO Naive Frequency
Frequency counter on a SVO{N} file

### SVO File
The SVO files are Tab Separated Values (TSV) with 3 string fields (S, V, O) and an optional integer field (N).
The S, V, O are natural language sentences in the format Subject-Verbal phrase-Object.
N is the occurrence count of a certain S, V, O in a given corpora.

### Algorithm
The naive frequency counter counts which (S, O) pairs occurs the most, or in another words, which (S, O) maximize the value of N.
A full pass on the SVO file produces a hash table (S, O)->Int, which is then partially ordered to give the K-most frequent pairs.
