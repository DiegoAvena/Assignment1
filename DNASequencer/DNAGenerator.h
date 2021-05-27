#include<string> //for access to std

/*

This class allows the program to generate 1000 different DNA string lengths and a string chunk of DNA nucleotides that match
the frequency of nucleotides calculated for the inputed file. This amount of nucleotides also equals the sum of the 1000 generated string lengths to
insure the nucleotides can make 1000 DNA strings. This class does not divide the generated string chunk of DNA into its 1000 lines, the ManageWritingToFile class handles this.

*/
class DNAGenerator {

//store how much of each nucleotide there can be across the 1000 generated DNA lines so that their relative frequency matches the probability calculated from the inputed file
int amountOfAThatCanBeUsed;
int amountOfCThatCanBeUsed;
int amountOfTThatCanBeUsed;
int amountOfGThatCanBeUsed;

//stores the probability calculated for the nucleotides in the inputed DNA file
float probOfA;
float probOfC;
float probOfT;
float probOfG;

std::string lengthsOfGeneratedDNAStrands; //stores the 1000 generated lengths for the 1000 DNA strings that are to be created.
void checkWhichNucleotideCanBeAddedWithoutCausingASignificantChangeToTheRelativeFrequencyOfTheNucleotides(int numberOfNucleotidesThatNeedToBeGenerated); //insures there is enough nucleotides to fill the 1000 strings in the case that the rounding of the number of nucleotides caused some to be knocked off

public:
  DNAGenerator(); //default constructor
  ~DNAGenerator(); //destructor
  std::string generateDNA(float theMeanLength, float standardDeviationOfDNALengths); //will generate 1000 dna lengths and create 1 big string chunk of DNA with a frequency of nucleotides that matches the probability calculated from the inputed file
  void initializeProbabilitiesOfEachNucleotide(float aProb, float cProb, float tProb, float gProb); //will get the probabilites calulated for each nucleotide in the inputed DNA file
  std::string getTheLengthsOfTheGeneratedDNAStrands(); //an accessor method for obtaining the 1000 generated lengths for each DNA string

};
