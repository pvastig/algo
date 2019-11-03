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
 \brief Count ones in the set 0 and 1
 \details for example: for set {101010} the function returns 3
 \param v Input array of 0 and 1
 \return Count of ones in input array
*/
int countOnes(std::vector<int> const& v);

/*!
 \brief Deletes duplicates in array
 \param v Array of integer numbers
 \todo make template function based on the one
*/
void deleteDublicates(std::vector<int> const& v);

/*!
 \brief Generates different sequence of braces
 \param pairs Count of braces
 \param openedBr Opened brace
 \param closedBr Closed brace
 \return Generated sequence of string braces
 \todo take out the fun in class?
*/
std::string generateBraces(int pairs, char openedBr = '(', char closedBr = ')');

/*!
 \brief Checks that the string is anagrams
 \param str Checking string
 \return true if string is anagrams else false
*/
bool checkAnagrams(std::string const& str);

/*!
 \brief Removes value from from the given array
 \param v Given array
*/
void removeValue(std::vector<int>& v);

/*!
 \brief Merges sorted arrays into one
 \param v Array of sorted arrays
 \return Merged array
*/
std::vector<int> mergeArrays(std::vector<std::vector<int>> const& v);
}  // namespace Algo
