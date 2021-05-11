Mia Belliveau 10824752

Graded

C++

Linux

Parses inputs and recursively applies chain rule and conditional probability,
using only the values given in the diagram for the bayesian network. For instance, the program should reduce 
P(A,B,C) 
to P(A|B,C)P(B,C) 
to P(A|B,C)P(B|C)P(C)
and using Bayes' Rule to calculate the conditional probabilities:
	P(A|B) = P(B|A)P(A)/P(B)

1. On a linux machine open terminal
2. cd into P5 directory
3. type:
	 make
	 ./bnet <args>
	 	where <args> are your arguments

   the output should be a floating point number calculating the event 		probability
