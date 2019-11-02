#pragma once

#include <string>
#include <vector>

namespace Algo {
int searchSubStr(std::string const& j, std::string const& s);

int countOnes(std::vector<int> const& v);

void deleteDublicates(std::vector<int> const& v);

std::string generateBraces(int pairs, char openedBr = '(', char closedBr = ')');

bool checkAnnagrams(std::string const& s);

void removeValue(std::vector<int>& v);

std::vector<int> mergeArrays(std::vector<std::vector<int>> const& v);
}  // namespace Algo