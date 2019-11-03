/*!
\file
\brief The file contains different algorithms from sources

Contains real task from interview, books, exclusively for self-study
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
 \brief

 \fn deleteDublicates
 \param v
*/
void deleteDublicates(std::vector<int> const& v);

/*!
 \brief

 \fn generateBraces
 \param pairs
 \param openedBr
 \param closedBr
 \return std::string
*/
std::string generateBraces(int pairs, char openedBr = '(', char closedBr = ')');

/*!
 \brief

 \fn checkAnnagrams
 \param s
 \return bool
*/
bool checkAnnagrams(std::string const& s);

/*!
 \brief

 \fn removeValue
 \param v
*/
void removeValue(std::vector<int>& v);

/*!
 \brief

 \fn mergeArrays
 \param v
 \return std::vector<int>
*/
std::vector<int> mergeArrays(std::vector<std::vector<int>> const& v);
}  // namespace Algo
