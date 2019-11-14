/*!
 \file
 \authors Astigeevich Pavel
 \warning Uses only for studying
 \brief The file contains different algorithms. Algorithms are taken from real
task, from interview, books, exclusively for self-study
*/

#pragma once

#include <string>
#include <vector>

namespace Algo {
/*!
 \brief Count matching symbols in a string
 \details for example: pattern "ab" in the string "aabbacd" returns 4
 \param str String where substring will be count
 \param pattern Substring
 \return Count of matching symbols in the string
*/
int countMatchedSymbols(std::string const& str, std::string const& pattern);

/*!
 \brief Counts one by one digit in the given array
 \details for example: for set {101010} and value 1 the function returns 1
 \details {111551} and value 5 returns 2
 \param v Array of 0 and 1
 \param value Value that are going to be counted, by default 1
 \return Count of valued digit
*/
int countOnes(std::vector<int> const& v, int value = 1);

/*!
 \brief Deletes wanted value in array
 \param v Input array
 \param value Deleting value from the array
 \todo make template function based on the one
*/
bool deleteValues(std::vector<int>& v, int value = 0);

/*!
 \brief Generates different sequence of braces
 \param pairs Count of pair braces
 \param openedBr Opened brace
 \param closedBr Closed brace
 \return Generated sequence of string braces
 \todo take out the fun in class?
*/
std::string generateBraces(int pairs, char openedBr = '(', char closedBr = ')');

/*!
 \brief Checks the given string is anagrams
 \param str Checking string
 \return True if string is anagrams, else false
*/
bool checkAnagrams(std::string const& str);

/*!
 \brief Merges sorted arrays into one
 \param v Array of sorted arrays
 \return Merged array
*/
std::vector<int> mergeArrays(std::vector<std::vector<int>> const& v);

std::string alignString(std::vector<std::string> const& words, size_t length);
}  // namespace Algo
