#include "DNASequencer.h" //for access to the methods defined in this header file
#include <iostream>
#include <math.h> //for access to sqrt()

using namespace std;

//a default contstructor
DNASequencer::DNASequencer() {

}

//deconstructor
DNASequencer::~DNASequencer() {

}

//an accessor method for getting the boolean which indicates whether or not there was at least 1 valid line in the file
bool DNASequencer::CheckIfThereWasAtLeastOneValidLine() {

  return thereIsAtLeastOneValidLineInTheInputFile;

}

void DNASequencer::sequenceThisDNAString(string dnaString) {

  if (checkIfStringIsADNAString(dnaString) == true) {

    thereIsAtLeastOneValidLineInTheInputFile = true;
    string lowerCaseVersionOfDNAString = makeStringLowerCase(dnaString); //needs to be done since capitalization is not guaranteed
    int lengthOfThisLine = 0; //stores the length of the current DNA strand being read so that it can be saved for later use (when mean of lengths is calculated, etc)
    numberOfLines++; //keeps track of how many different dna strings have been read, so that the mean length and variance can be computed later

    //this is a dna string, we are safe to record data using it:
    /*

    This is a valid dna string, we are safe to record data using it.
    The loop below loops through each character in the DNA string so that
    the amounts of each nucleotide and nucleotidePair can be calculated.

    */
    for (int i = 0; i < lowerCaseVersionOfDNAString.length(); i++) {

      numberOfNucleotides++; //sums up the length of the DNA strings in the list
      incrementNumberForEachNucleotide(lowerCaseVersionOfDNAString[i]);
      incrementNumberForEachNucleotidePair(i, lowerCaseVersionOfDNAString);
      lengthOfThisLine++;

    }

    /*
    Keeps track of every dna strand length provided.
    I added a space in between each number as this will allow me
    to insure I can grab lengths from this string that have more than
    digit, otherwise I would only be able to grab single digit lengths which is a problem
    in the case that there are lengths >= 10
    */
    lengthsOfEachDNAString += " "+to_string(lengthOfThisLine); //info on how to use to_string method is from: https://stackoverflow.com/questions/16582640/how-to-convert-a-floating-point-into-a-string
    //cout<<lengthsOfEachDNAString<<endl;

  }

}

//makes sure the string is all lowercase since capitalization is not guaranteed in the input file dna strands
string DNASequencer::makeStringLowerCase(string lineToMakeLowerCase) {

  string theStringInLowerCase = ""; //the lower case version of the dna string given

  for (int i = 0; i < lineToMakeLowerCase.length(); i++) { //loop through each character in the string and make it lowercase

    theStringInLowerCase += tolower(lineToMakeLowerCase[i]);

  }

  return theStringInLowerCase;

}

//does all the calculations using a couple of helper methods and records those stats onto a file using the dataRecorder
void DNASequencer::doCalculationsForThisDNAFile() {

  calculateProbabilities();
  calculateMeanOfLengthOfDNAStrings();
  calculateVarianceOfLengthOfDNAStrings();
  calculateStandardDeviationOfLengthOfDNAStrings();

  dataRecorder.RecordStatisticsOntoFile(numberOfNucleotides, meanOfDNALengths, varianceOfDNALengths, standardDeviationOfDNALengths,
    probabilityOfA, probabilityOfC, probabilityOfT, probabilityOfG,
    probabilityOfAA,probabilityOfAC, probabilityOfAT, probabilityOfAG,
    probabilityOfCC, probabilityOfCA, probabilityOfCT, probabilityOfCG,
    probabilityOfTT, probabilityOfTA, probabilityOfTC, probabilityOfTG,
    probabilityOfGG, probabilityOfGA, probabilityOfGC, probabilityOfGT,
    numberOfA, numberOfC, numberOfT, numberOfG
  );

  //logOutDataToConsole(); //for debugging purposes
  resetAllValuesToDefault();

}

//used to refresh all values after the full sequence is complete, just in case the user decides to process another file, they begin with default values
void DNASequencer::resetAllValuesToDefault() {

  numberOfNucleotides = 0;
  numberOfNucleotidePairs = 0;

  numberOfLines = 0;
  lengthsOfEachDNAString = "";

  //the amount individual nucleotides:
  numberOfA = 0;
  numberOfC = 0;
  numberOfT = 0;
  numberOfG = 0;

  //the amount of every possible nucleotide pair found in file:
  numberOfAA = 0;
  numberOfAC = 0;
  numberOfAT = 0;
  numberOfAG = 0;

  numberOfCC = 0;
  numberOfCA = 0;
  numberOfCT = 0;
  numberOfCG = 0;

  numberOfTT = 0;
  numberOfTA = 0;
  numberOfTC = 0;
  numberOfTG = 0;

  numberOfGG = 0;
  numberOfGA = 0;
  numberOfGC = 0;
  numberOfGT = 0;

  //probability values for each nucleotide:
  probabilityOfA = 0;
  probabilityOfG = 0;
  probabilityOfC = 0;
  probabilityOfT = 0;

  //probability values for nucleotide pairs:
  probabilityOfAA = 0;
  probabilityOfAC = 0;
  probabilityOfAT = 0;
  probabilityOfAG = 0;

  probabilityOfCC = 0;
  probabilityOfCA = 0;
  probabilityOfCT = 0;
  probabilityOfCG = 0;

  probabilityOfTT = 0;
  probabilityOfTA = 0;
  probabilityOfTC = 0;
  probabilityOfTG = 0;

  probabilityOfGG = 0;
  probabilityOfGA = 0;
  probabilityOfGC = 0;
  probabilityOfGT = 0;

  meanOfDNALengths = 0;
  varianceOfDNALengths = 0;
  standardDeviationOfDNALengths = 0;

}

//calculates how much there is of each nucleotide
void DNASequencer::incrementNumberForEachNucleotide(char nucleotide) {

  if (nucleotide == 'a') {

    numberOfA++;

  }
  else if (nucleotide == 'c') {

    numberOfC++;

  }
  else if (nucleotide == 't') {

    numberOfT++;

  }
  else if (nucleotide == 'g') {

    numberOfG++;

  }

}

//calculates how much there is for each nucleotide pair
void DNASequencer::incrementNumberForEachNucleotidePair(int currentIndex, string dnaStrand) {

  string nucleotidePair = ""; //used to store the nucleotide pair

  /*
  Using the assumption that the DNA strands entered will have even lengths, then at every even index + 1 (since indeces start at 0) in the string,
  we will have a pair of nucleotides to grab, which is why I use the mod operator below
  */
  if (((currentIndex + 1) % 2) == 0) {

    //create a substring that represents the nucleotide pair. I did current index - 1 because this gives the starting index of the pair I want to grab
    nucleotidePair = dnaStrand.substr(currentIndex - 1, 2); //how to use the substr method is reference from: http://www.cplusplus.com/reference/string/string/substr/

    numberOfNucleotidePairs++; //keeps track of how many pairs exist so that probability can be computed for each pair later on

    if (nucleotidePair == "aa") {

      numberOfAA++;

    }
    else if (nucleotidePair == "ac") {

      numberOfAC++;

    }
    else if (nucleotidePair == "at") {

      numberOfAT++;

    }
    else if (nucleotidePair == "ag") {

      numberOfAG++;

    }
    else if (nucleotidePair == "cc") {

      numberOfCC++;

    }
    else if (nucleotidePair == "ca") {

      numberOfCA++;

    }
    else if (nucleotidePair == "ct") {

      numberOfCT++;

    }
    else if (nucleotidePair == "cg") {

      numberOfCG++;

    }
    else if (nucleotidePair == "tt") {

      numberOfTT++;

    }
    else if (nucleotidePair == "ta") {

      numberOfTA++;

    }
    else if (nucleotidePair == "tc") {

      numberOfTC++;

    }
    else if (nucleotidePair == "tg") {

      numberOfTG++;

    }
    else if (nucleotidePair == "gg") {

      numberOfGG++;

    }
    else if (nucleotidePair == "ga") {

      numberOfGA++;

    }
    else if (nucleotidePair == "gc") {

      numberOfGC++;

    }
    else if (nucleotidePair == "gt") {

      numberOfGT++;

    }

  }

}

//for debugging purposes, logs out all of the calculated data into the console
void DNASequencer::logOutDataToConsole() {

  cout<<"Number of valid lines: "<<numberOfLines<<endl;
  cout<<"Number of nucleotidePairs: "<<numberOfNucleotidePairs<<endl;

  cout<<"Number of A: "<<numberOfA<<endl;
  cout<<"Number of C: "<<numberOfC<<endl;
  cout<<"Number of T: "<<numberOfT<<endl;
  cout<<"Number of G: "<<numberOfG<<endl;

  cout<<"Number of AA: "<<numberOfAA<<endl;
  cout<<"Number of AC: "<<numberOfAC<<endl;
  cout<<"Number of AT: "<<numberOfAT<<endl;
  cout<<"Number of AG: "<<numberOfAG<<endl;

  cout<<"Number of CC: "<<numberOfCC<<endl;
  cout<<"Number of CA: "<<numberOfCA<<endl;
  cout<<"Number of CT: "<<numberOfCT<<endl;
  cout<<"Number of CG: "<<numberOfCG<<endl;

  cout<<"Number of TT: "<<numberOfTT<<endl;
  cout<<"Number of TA: "<<numberOfTA<<endl;
  cout<<"Number of TC: "<<numberOfTC<<endl;
  cout<<"Number of TG: "<<numberOfTG<<endl;

  cout<<"Number of GG: "<<numberOfGG<<endl;
  cout<<"Number of GA: "<<numberOfGA<<endl;
  cout<<"Number of GC: "<<numberOfGC<<endl;
  cout<<"Number of GT: "<<numberOfGT<<endl;

  cout<<"Prob of A: "<<probabilityOfA<<endl;
  cout<<"Prob of C: "<<probabilityOfC<<endl;
  cout<<"Prob of T: "<<probabilityOfT<<endl;
  cout<<"Prob of G: "<<probabilityOfG<<endl;

  cout<<"Prob of AA: "<<probabilityOfAA<<endl;
  cout<<"Prob of AC: "<<probabilityOfAC<<endl;
  cout<<"Prob  of AT: "<<probabilityOfAT<<endl;
  cout<<"Prob of AG: "<<probabilityOfAG<<endl;

  cout<<"Prob of CC: "<<probabilityOfCC<<endl;
  cout<<"Prob of CA: "<<probabilityOfCA<<endl;
  cout<<"Prob of CT: "<<probabilityOfCT<<endl;
  cout<<"Prob of CG: "<<probabilityOfCG<<endl;

  cout<<"Prob of TT: "<<probabilityOfTT<<endl;
  cout<<"Prob of TA: "<<probabilityOfTA<<endl;
  cout<<"Prob of TC: "<<probabilityOfTC<<endl;
  cout<<"Prob of TG: "<<probabilityOfTG<<endl;

  cout<<"Prob of GG: "<<probabilityOfGG<<endl;
  cout<<"Prob of GA: "<<probabilityOfGA<<endl;
  cout<<"Prob of GC: "<<probabilityOfGC<<endl;
  cout<<"Prob of GT: "<<probabilityOfGT<<endl;

  cout<<"Mean of the lengths entered: "<<meanOfDNALengths<<endl;
  cout<<"Variance of the lengths entered: "<<varianceOfDNALengths<<endl;
  cout<<"Sum of the lengths entered: "<<numberOfNucleotides<<endl;
  cout<<"Standard deviation of lengths entered: "<<standardDeviationOfDNALengths<<endl;

}

//computes the probabilites for each nucleotide and each nucleotide pair as a percentage
void DNASequencer::calculateProbabilities() {

  //probability of nucleotides:
  probabilityOfA = (numberOfA / numberOfNucleotides) * 100;
  probabilityOfG = (numberOfG / numberOfNucleotides) * 100;
  probabilityOfT = (numberOfT / numberOfNucleotides) * 100;
  probabilityOfC = (numberOfC / numberOfNucleotides) * 100;

  //probabilityOfNucleotide pairs:
  probabilityOfAA = (numberOfAA / numberOfNucleotidePairs) * 100;
  probabilityOfAC = (numberOfAC / numberOfNucleotidePairs) * 100;
  probabilityOfAT = (numberOfAT / numberOfNucleotidePairs) * 100;
  probabilityOfAG = (numberOfAG / numberOfNucleotidePairs) * 100;

  probabilityOfCC = (numberOfCC / numberOfNucleotidePairs) * 100;
  probabilityOfCA = (numberOfCA / numberOfNucleotidePairs) * 100;
  probabilityOfCT = (numberOfCT / numberOfNucleotidePairs) * 100;
  probabilityOfCG = (numberOfCG / numberOfNucleotidePairs) * 100;

  probabilityOfTT = (numberOfTT / numberOfNucleotidePairs) * 100;
  probabilityOfTA = (numberOfTA / numberOfNucleotidePairs) * 100;
  probabilityOfTC = (numberOfTC / numberOfNucleotidePairs) * 100;
  probabilityOfTG = (numberOfTG / numberOfNucleotidePairs) * 100;

  probabilityOfGG = (numberOfGG / numberOfNucleotidePairs) * 100;
  probabilityOfGA = (numberOfGA / numberOfNucleotidePairs) * 100;
  probabilityOfGC = (numberOfGC / numberOfNucleotidePairs) * 100;
  probabilityOfGT = (numberOfGT / numberOfNucleotidePairs) * 100;

}

//calculates the mean of the dna strand lengths
void DNASequencer::calculateMeanOfLengthOfDNAStrings() {

  meanOfDNALengths = numberOfNucleotides / numberOfLines; //the numberOfNucleotides is actually just the sum of all the DNA strand lengths, while the number of lines reflects how many different lengths there are; thus, both can be used to find the mean of the length

}

void DNASequencer::calculateVarianceOfLengthOfDNAStrings() {

  float numerator = 0; //the numerator of the variance equation

  int lineNumber = 0; //keeps track of what DNA strand we are on
  int currentLocationInDNALengthsString = 0; //keeps track of where we are currently at in the DNA length string so that the correct length can be applied to its correct DNA strand

  while (lineNumber < numberOfLines) { //insures that every length stored in the string of dna lengths is added into the numerator that will be used to calculate the variance

    string textVersionOfOurLength = ""; //a string representing the length of the DNA strand
    int lengthOfLine = 0; //a value that will store the text version of the DNA strand's length as an int so that math can be done on it
    float number; //a value that will store the difference between the length of each dna strand, and the mean, as the variance equation requires this

    for (int i = currentLocationInDNALengthsString; i < lengthsOfEachDNAString.length(); i++) {

      if ((lengthsOfEachDNAString.substr(i, 1) == " ") && (lengthOfLine != 0)) {

        //we are at the " " that comes after each number in the length string, need to break out of the loop since at this point we have the number that represents the length of the dna string
        currentLocationInDNALengthsString = i; //next time this loop runs, we need to start at the location we left off at in order to insure we grab the correct length
        lengthOfLine = stoi(textVersionOfOurLength);
        //cout<<"Length of inputed dna strand: "<<lengthOfLine<<endl;
        break;

      }
      else if (lengthsOfEachDNAString.substr(i, 1) != " ") {

        //we are at an index that has a digit in it, grab it:
        textVersionOfOurLength += lengthsOfEachDNAString[i];
        lengthOfLine = stoi(textVersionOfOurLength);

      }

    }

    number = lengthOfLine - meanOfDNALengths; //info on how to use the stof method is from: http://www.cplusplus.com/reference/string/stof/, used to convert the string representation of the number into a float so that math can be done correctly
    numerator += (number * number); //calculates the value of the numerator for the variance equation below
    lineNumber++;

  }

  //variance equation is from: https://www.mathsisfun.com/data/standard-deviation.html
  varianceOfDNALengths = numerator / numberOfLines;

}

//calculates the standard deviation of the lengths of the dna strands
void DNASequencer::calculateStandardDeviationOfLengthOfDNAStrings() {

  standardDeviationOfDNALengths = sqrt(varianceOfDNALengths); //standard deviation equation from: https://www.mathsisfun.com/data/standard-deviation.html

}

//a mutator method for setting this boolean from other classes
void DNASequencer::SetThereIsAtLeastOneValidLine(bool yesOrNo) {

  thereIsAtLeastOneValidLineInTheInputFile = yesOrNo;

}

//checks if the line being read is a valid dna line, if not then the line is ignored.
bool DNASequencer::checkIfStringIsADNAString(string dnaStringToCheck) {

  bool thisStringIsGoodToGo = true;

  for (int i = 0; i < dnaStringToCheck.length(); i++) {

    if ((tolower(dnaStringToCheck[i]) != 'a') && (tolower(dnaStringToCheck[i]) != 't') && (tolower(dnaStringToCheck[i]) != 'c') && (tolower(dnaStringToCheck[i]) != 'g')) {

      //found an invalid character that is not a nucleotide in a dna strand, making this an invalid line.
      thisStringIsGoodToGo = false;
      break;

    }

  }

  if (thisStringIsGoodToGo && (thereIsAtLeastOneValidLineInTheInputFile == false)) {

    thereIsAtLeastOneValidLineInTheInputFile = true;

  }

  return thisStringIsGoodToGo;

}
