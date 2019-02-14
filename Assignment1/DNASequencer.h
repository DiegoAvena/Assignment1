#include "ManageWritingToFile.h" //so that I can declare an object of this class I made in order to use the methods in it that allow me to write things onto another file

/*

This class allows the program to gather information from each DNA string in the input file and calculate the
wanted values, such as the mean, standard deviation, variance, and sum of the lengths. It also calculates the
relative probabilities of both each nucleotide and each nucleotide pair.

*/
class DNASequencer {

ManageWritingToFile dataRecorder; //Used to record the statistics calculated onto a file named diegoavena.out

float numberOfNucleotides; //this is really just the sum of the lengths of the DNA strings, used to calculate probability of each nucleotide
float numberOfNucleotidePairs; //used to calculate probability of each nucleotide pair

int numberOfLines; //This is the number of DNA strings that there are in the given file
std::string lengthsOfEachDNAString; //stores each length of every DNA string given so that things like the mean, variance, and standard deviation can be calculated later

//the amount individual nucleotides:
float numberOfA;
float numberOfC;
float numberOfT;
float numberOfG;

//the amount of every possible nucleotide pair found in file:
float numberOfAA;
float numberOfAC;
float numberOfAT;
float numberOfAG;

float numberOfCC;
float numberOfCA;
float numberOfCT;
float numberOfCG;

float numberOfTT;
float numberOfTA;
float numberOfTC;
float numberOfTG;

float numberOfGG;
float numberOfGA;
float numberOfGC;
float numberOfGT;

//probability values for each nucleotide:
float probabilityOfA;
float probabilityOfG;
float probabilityOfC;
float probabilityOfT;

//probability values for nucleotide pairs:
float probabilityOfAA;
float probabilityOfAC;
float probabilityOfAT;
float probabilityOfAG;

float probabilityOfCC;
float probabilityOfCA;
float probabilityOfCT;
float probabilityOfCG;

float probabilityOfTT;
float probabilityOfTA;
float probabilityOfTC;
float probabilityOfTG;

float probabilityOfGG;
float probabilityOfGA;
float probabilityOfGC;
float probabilityOfGT;

float meanOfDNALengths;
float varianceOfDNALengths;
float standardDeviationOfDNALengths;

bool thereIsAtLeastOneValidLineInTheInputFile; //indicates whether or not there was at least one valid line in the file

//methods to calculate statistics
void calculateProbabilities(); //calculates both the probability of each individual nucleotide and each nucleotide pair
void calculateMeanOfLengthOfDNAStrings();
void calculateStandardDeviationOfLengthOfDNAStrings();
void calculateVarianceOfLengthOfDNAStrings();

std::string makeStringLowerCase(std::string lineToMakeLowerCase); //insures the given string is all lowercase since capitalization is not gauranteed
void incrementNumberForEachNucleotide(char nucleotide);
void incrementNumberForEachNucleotidePair(int currentIndex, std::string dnaStrand);
void logOutDataToConsole(); //for debugging reasons, just logs out all of the stats calculated for the inputed dna file
bool checkIfStringIsADNAString(std::string dnaStringToCheck); //used to check if the given dna strand is valid (has only nucleotides in it, no spaces or invalid characters like numbers)
void resetAllValuesToDefault(); //used to refresh all values after the full sequence is complete, just in case the user decides to process another file, they begin with default values

public:
  DNASequencer(); //default constructor
  ~DNASequencer(); //destructor
  void sequenceThisDNAString(std::string dnaString); //will go over the dna string given to compute the amount of each nucleotide and amount of each nucleotide pair
  void doCalculationsForThisDNAFile(); //will calculate
  bool CheckIfThereWasAtLeastOneValidLine(); //an accessor method for getting the boolean which indicates whether or not there was at least 1 valid line in the file
  void SetThereIsAtLeastOneValidLine(bool yesOrNo); //a mutator method for setting this boolean from other classes

};
