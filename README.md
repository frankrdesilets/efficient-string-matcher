![Static Badge](https://img.shields.io/badge/License-MIT-blue)

# string-matcher

This application parses .txt files containing “texts,” uses Horspool’s String Matching algorithm to find texts containing an occurrence of a given “pattern,” and prints a report listing texts containing the pattern to the console.

### Sample Input File “sample.txt”:

```
frank
whether
There
that
desilets
the
theory
othEr
tetherball
theme
coppersmith
```

### Report Outputted to Console:

```
--- Report for "inputfiles/sample.txt" ---
Pattern to match: "the"
Number of texts in file: 11
Number of texts with occurrence of pattern in file: 5

Texts containing the pattern "the":
-> whether
-> the
-> theory
-> tetherball
-> theme
--- End of Report ---
```

## Project Description

This application uses an implementation of Horspool’s String Matching algorithm to match a “pattern” (a string of m characters) against “texts” (longer strings of n characters).

The pattern to match against texts is inputted by the user in main.cpp, and the texts to match against are parsed from input .txt files as character sequences separated by a space or new line. Multiple files can be run simultaneously, and reports are printed to the console for each file including information such as the total number of texts in the file, the total number of texts containing an occurrence of the pattern, and a list of all matching texts. The alphabet of acceptable characters are lowercase and uppercase letters (a-z, A-Z). Numbers and special characters are not supported.

I built this project using C++ and Xcode 15.3. The application was thoroughly tested with 10 .txt file inputs. Tests include ensuring accurate file parsing, accurate pattern matching at the beginning, middle, and end of texts (including complete patterns {"the"} and incomplete patterns {"th"}), and correct letter case and unsupported character detection.

## Motivation

I built this application to practice concepts learned in my Algorithms course and to sharpen my C++ skills.

## Features

-	String matching with worst case efficiency in θ(*n*) for random texts
-	Parses input .txt files
    - Incorrect input file formatting is detected and processed appropriately
-	Runs on multiple input files simultaneously
-	Report generation for each input file
    - Reports print to the console and include information such as the total number of texts in the file, the total number of texts containing an occurrence of the pattern, and a list of all matching texts

## How to Install and Run

1. Clone and import the repository to your C++ IDE workspace.
2. Run the project (the main method is located in String-Matcher/main.cpp).

## How to Use

### Pattern Input

The input for the pattern is located in the main method of String-Matcher/main.cpp. Only one pattern can be specified at a time.

To change the pattern:

1.	Navigate to the main method of String-Matcher/main.cpp.
2.	Modify the string variable “pattern” to update the pattern.

### Text Input

The input for texts is .txt files.

To create a new input file:

1.	Create a new .txt file in String-Matcher/inputfiles
2.	  Populate the file with texts. Text are character sequences separated by spaces or new lines. For example, the following formatting would yield the texts: “frank”, “whether”, “There”, and “that”.

```
frank
whether There
that
```

3.	Navigate to the main method of String-Matcher/main.cpp.
4.	Modify the vector “inputFileNames” contents. Every file included in this vector will be run.

## Testing

The application was thoroughly tested with 10 .txt file inputs. Tests include ensuring accurate file parsing, accurate pattern matching at the beginning, middle, and end of texts (including complete patterns {"the"} and incomplete patterns {"th"}), and correct letter case and unsupported character detection. Input files used for testing are located in testfiles/ and are run in the main method.
