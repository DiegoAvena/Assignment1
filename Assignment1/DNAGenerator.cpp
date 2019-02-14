#include "DNAGenerator.h" //for access to the definitions made here
#include <stdlib.h> // for access to the rand method
#include <cstdlib> //for access to RAND_MAX constant
#include <math.h> //for access to M_PI constant, sqrt(), log(), and cos()
#include <iostream>

using namespace std;

//default constructor
DNAGenerator::DNAGenerator() {



}

//sets the probabilities of each nucleotide to the same value as the one calculated from the inputed DNA file so that the frequency of the nucleotides can follow these statistics
void DNAGenerator::initializeProbabilitiesOfEachNucleotide(float aProb, float cProb, float tProb, float gProb) {

  probOfA = aProb;
  probOfC = cProb;
  probOfT = tProb;
  probOfG = gProb;

}

//deconstructor
DNAGenerator::~DNAGenerator() {

}


/*

will generate 1000 dna lengths and return 1 big string chunk of DNA with a frequency of nucleotides that
matches the probability calculated from the inputed file

*/
string DNAGenerator::generateDNA(float theMeanLength, float standardDeviationOfDNALengths) {

  string generatedDNAStrand; //this will store a massive chunk of the 1000 DNA strands that still need to be divided into their respective lines

  lengthsOfGeneratedDNAStrands = ""; //will store the generated lengths for each dna strand

  int sumOfTheGeneratedLengths = 0; //sums up the generated length values so that the correct amounts of A, C, T, G can be calculated correctly.

  int numberOfLengthsMade = 0; //keeps track of how many strands have been generated

  while (numberOfLengthsMade <= 1000) { //generate 1000 different lengths that follow a gaussian distribution with the same mean and variance as calculated from the input file

    while (true) {

      //generates a random number between 0 and 1 (exclusive)
      float a = rand() / (float)(RAND_MAX + 1.0);   //for info on RAND_MAX, I used http://www.math.uaa.alaska.edu/~afkjm/csce211/fall2018/handouts/RandomFunctions.pdf, and for help on getting rid of an overflow error, I used https://stackoverflow.com/questions/22263674/generate-random-number-between-0-and-1
      float b = rand() / (float)(RAND_MAX + 1.0);

      float standardGaussian = sqrt(-2*(log(a))) * cos(2 * M_PI * b); //info on how to use logs in c++ is referenced from: https://www.geeksforgeeks.org/log-function-cpp/

      int lengthOfThisDNAStrand = abs(rint((theMeanLength * standardGaussian) + standardDeviationOfDNALengths)); //I take the abs value to insure there are not negative lengths

      if (lengthOfThisDNAStrand > 0) { //prevents the creation of strings with a length of 0, otherwise there would be empty DNA strings created

        sumOfTheGeneratedLengths += lengthOfThisDNAStrand;
        numberOfLengthsMade++; //this corresponds to the amount of DNA lines generated, so that the while loop knows to end when 1000 lines have been made
        lengthsOfGeneratedDNAStrands += " "+to_string(lengthOfThisDNAStrand); //stores the generated length in a string, seperated by a space so that the program is able to gather length numbers that have more than 1 digit in them
        break;

      }

    }

  }

  //keeps the frequency of each nucleotide roughly the same as the frequency of each nucleotide in the original file
  amountOfAThatCanBeUsed = rint((probOfA / 100) * sumOfTheGeneratedLengths);
  amountOfCThatCanBeUsed = rint((probOfC / 100) * sumOfTheGeneratedLengths);
  amountOfTThatCanBeUsed = rint((probOfT / 100) * sumOfTheGeneratedLengths);
  amountOfGThatCanBeUsed = rint((probOfG / 100) * sumOfTheGeneratedLengths);

  int initialAmountOfAThatCanBeUsed = amountOfAThatCanBeUsed;
  int initialAmountOfCThatCanBeUsed = amountOfCThatCanBeUsed;
  int initialAmountOfTThatCanBeUsed = amountOfTThatCanBeUsed;
  int initialAmountOfGThatCanBeUsed = amountOfGThatCanBeUsed;

  checkWhichNucleotideCanBeAddedWithoutCausingASignificantChangeToTheRelativeFrequencyOfTheNucleotides(sumOfTheGeneratedLengths);

  //So that the user can check, on the console, if the frequency of the generated nucleotides matches the frequency of the nucleotides from the inputed file
  cout<<"Amount of A that can be in generated DNA: "<<amountOfAThatCanBeUsed<<", this means the probability of A in the generated DNA strings is: "<<((float)amountOfAThatCanBeUsed / sumOfTheGeneratedLengths) * 100<<endl;
  cout<<"Amount of C that can be in generated DNA: "<<amountOfCThatCanBeUsed<<", this means the probability of C in the generated DNA strings is: "<<((float)amountOfCThatCanBeUsed / sumOfTheGeneratedLengths) * 100<<endl;
  cout<<"Amount of T that can be in generated DNA: "<<amountOfTThatCanBeUsed<<", this means the probability of T in the generated DNA strings is: "<<((float)amountOfTThatCanBeUsed / sumOfTheGeneratedLengths) * 100<<endl;
  cout<<"Amount of G that can be in generated DNA: "<<amountOfGThatCanBeUsed<<", this means the probability of T in the generated DNA strings is: "<<((float)amountOfGThatCanBeUsed / sumOfTheGeneratedLengths) * 100<<endl;

  //to allow the user to check on the console if the number of nucleotides generated is able to fill the 1000 lines
  cout<<"Number of nucleotides generated: "<<(amountOfAThatCanBeUsed + amountOfCThatCanBeUsed + amountOfTThatCanBeUsed + amountOfGThatCanBeUsed)<<"; there are "<<sumOfTheGeneratedLengths<<" spots that need to be filled."<<endl;

  for (int b = 0; b < sumOfTheGeneratedLengths; b++) { //loop through each char position in the strings length

    while(true) {

      //grab a nucleotide and put it into this dna string. Put in a while loop to make sure that if the random number leads to a nucleotide that is all used up, the program attempts to grab another random nucleotide and put into the string, provided that there is at least 1 nucleotide that is not all used up

      //generate a random int number between 0 and 4(excluding 4)
      int randomNumber = rand() % 4; //for info on how to generate a random int between 0 and a specified boundary, I used: http://www.math.uaa.alaska.edu/~afkjm/csce211/fall2018/handouts/RandomFunctions.pdf

      if ((randomNumber == 0) && (amountOfAThatCanBeUsed > 0)) {

        //use nucleotide A:
        amountOfAThatCanBeUsed -= 1;
        generatedDNAStrand += "A";
        break;

      }
      else if ((randomNumber == 1) && (amountOfCThatCanBeUsed > 0)) {

        //use nucleotide C:
        amountOfCThatCanBeUsed -= 1;
        generatedDNAStrand += "C";
        break;

      }
      else if ((randomNumber == 2) && (amountOfTThatCanBeUsed > 0)) {

        //use nucleotide T:
        amountOfTThatCanBeUsed -= 1;
        generatedDNAStrand += "T";
        break;

      }
      else if ((randomNumber == 3) && (amountOfGThatCanBeUsed > 0)) {

        //use nucleotide G:
        amountOfGThatCanBeUsed -= 1;
        generatedDNAStrand += "G";
        break;


      }

    }

  }

  return generatedDNAStrand;

}

//attempts to insure there is enough nucleotides to fill the 1000 strings in the case that the rounding of the number of nucleotides caused some to be knocked off
void DNAGenerator::checkWhichNucleotideCanBeAddedWithoutCausingASignificantChangeToTheRelativeFrequencyOfTheNucleotides(int numberOfNucleotidesThatNeedToBeGenerated) {

  while(true) {

    if ((amountOfAThatCanBeUsed + amountOfCThatCanBeUsed + amountOfTThatCanBeUsed + amountOfGThatCanBeUsed) < numberOfNucleotidesThatNeedToBeGenerated) {

      //the rounding to an int caused a nucleotide or more to be knocked off
      if ((((((float)amountOfAThatCanBeUsed + 1) / numberOfNucleotidesThatNeedToBeGenerated) * 100) - probOfA) < 0.04) {

        //can add a nucleotide to amountOfA without causing a drastic change in its relative frequency
        amountOfAThatCanBeUsed++;

      }
      else if ((((((float)amountOfCThatCanBeUsed + 1) / numberOfNucleotidesThatNeedToBeGenerated) * 100) - probOfC) < 0.04) {

        //can add a nucleotide to amountOfC without causing a drastic change in its relative frequency
        amountOfCThatCanBeUsed++;

      }
      else if ((((((float)amountOfTThatCanBeUsed + 1) / numberOfNucleotidesThatNeedToBeGenerated) * 100) - probOfT) < 0.04) {

        //can add a nucleotide to amountOfT without causing a drastic change in its relative frequency
        amountOfTThatCanBeUsed++;

      }
      else if ((((((float)amountOfGThatCanBeUsed + 1) / numberOfNucleotidesThatNeedToBeGenerated) * 100) - probOfG) < 0.04) {

        //can add a nucleotide to amountOfG without causing a drastic change in its relative frequency
        amountOfGThatCanBeUsed++;

      }
      else {

        //no nucleotides can be added without causing a major change to the relative frequency(from the things I have tested this line is never met, but I included it just in case, so that the program does not get stuck in this while loop)
        break;

      }

    }
    else {

      break;

    }

  }

}

//accessor method for retrieving the lengths of the 1000 DNA strings
string DNAGenerator::getTheLengthsOfTheGeneratedDNAStrands() {

  return lengthsOfGeneratedDNAStrands;

}
