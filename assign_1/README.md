# COT5405_Analysis-of-Algorithms

**Problem 1**: Weighted approximate common substring. 

Given two input strings, not necessarily of the same length, based on alphanumeric characters [A-Z], determine the best common substring. A substring is a contiguous sequence of characters within a string, and the score that determines the best substring is defined as the sum of the weights  for each character in the sequence (i.e. $w_A$ is the weight of matching letter A) and a penalty $\lambda$ for each mismatch (negative penalty term to drive down the score). In your experiments, consider situations in which $w_l=1$ and $\lambda=10$ and in which $w_l$ is proportional to the frequency of the letter in English and $\lambda$ takes values between the smallest and the largest weight (multiple experiments for 10 intermediate values). Note: you are now allowed to add gaps in the solution, i.e. both matched substring have the same length. 

**Problem 2**: Interval-based constant best approximation. 

Given a set of $N$ points $(x_i,y_i)$ with integer values for $x_i$ between $1$ and $M$ and real values for $y_i$,  find a partitioning of the interval $[1,M]$ into contiguous intervals such that the error of approximating points in each interval element by the average value of $y$ in the interval is minimized. You need to add a penalty factor proportional to the total number of intervals the solution has.
