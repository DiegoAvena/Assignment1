# DNA Sequencer
Takes an input file with any number of DNA strands that each have an even length, and computes the mean, standard deviation, and variance of the lengths. It also computes the probability of each nucleotide and nucleotide pair. Lastly, 1000 DNA strands are generated with nucleotides that are at or near the same frequency as calculated in the inputed file. The lengths of these DNA strands also follow a gaussian distribution. All of this is written onto a file labeled diegoavena.out.

References:
1.) http://www.math.uaa.alaska.edu/~afkjm/csce211/fall2018/handouts/RandomFunctions.pdf - for info on how to generate a random int between 0 and a specified boundary. Also used for for info on RAND_MAX and srand() for seeding the rand() function.

2.) https://www.geeksforgeeks.org/log-function-cpp/ - for info on how to use logs in c++

3.) https://stackoverflow.com/questions/22263674/generate-random-number-between-0-and-1 - for help on getting rid of an overflow error

4.) http://www.cplusplus.com/doc/tutorial/files/ - for help on how to write to files
