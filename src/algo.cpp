#include "algo.h"

#include <cassert>
#include <iostream>
#include <set>

namespace Algo
{

int countMatchedSymbols(std::string const& str, std::string const& pattern)
{
	char countChar[255] = { 0 };
	for (auto const ch : pattern)
	{
		if (countChar[ch] == 0)
		{
			++countChar[ch];
		}
	}

	int result = 0;
	for (auto const ch : str)
	{
		result += countChar[ch];
	}

	return result;
}

int countDigitsOneByOne(std::vector<int> const& v, int const value)
{
	int countMax = 0;
	int countOne = 0;
	for (auto const item : v)
	{
		if (item == value)
		{
			++countOne;
		}
		else
		{
			countMax = std::max(countMax, countOne);
			countOne = 0;
		}
	}

	return std::max(countMax, countOne);
}

bool deleteValues(std::vector<int>& v, int const value)
{
	size_t const beforeDeleting = v.size();
	auto n = v.begin();
	for (; n != v.end(); ++n)
	{
		if (*n == value)
		{
			break;
		}
	}

	if (n == v.end())
	{
		return false;
	}

	for (auto it = n; ++it != v.end();)
	{
		if (*it != value)
		{
			*n++ = *it;
		}
	}

	assert(n != v.end());
	v.erase(n, v.end());

	size_t const afterDeleting = v.size();

	return beforeDeleting != afterDeleting;
}

std::string generate(std::string s, int l, int r, int pairs)
{
	if (l == pairs && r == pairs)
	{
		return s += '\n';
	}

	if (l < pairs)
	{
		generate(s + '(', l + 1, r, pairs);
	}
	if (r < l)
	{
		generate(s + ')', l, r + 1, pairs);
	}

	return s;
}

std::string generateBraces(int pairs, char openedBr, char closedBr)
{
	return generate("", 0, 0, pairs);
}

// TODO: correct the function, write tests
bool checkAnagrams(const std::string& str)
{
	std::set<char> s;
	for (auto const ch : str)
		if (bool notInserted = !s.insert(ch).second)
			return false;
	return true;
}
// TODO: correct the function, write tests
std::vector<int> mergeArrays(const std::vector<std::vector<int> >& v)
{
	size_t elements = 0;
	for (auto const& item : v)
		elements += item.size();
	std::vector<int> result;
	std::vector<int> res;
	std::vector<size_t> index(v.size(), 0);
	for (size_t j = 0; j < elements; ++j)
	{
		bool minValueFound = false;
		int foundIndex = -1;
		auto& first = v[0];
		int minValue = first[index[0]];
		for (size_t i = 0; i < v.size(); ++i)
		{
			if (index[i] >= v[i].size())
				continue;
			auto& vec = v[i];
			std::cout << "first: " << vec[index[i]] << "\n";
			if (vec[index[i]] < minValue)
			{
				minValue = vec[index[i]];
				minValueFound = true;
				foundIndex = i;
			}
		}
		if (index[0] >= v[0].size())
			continue;

		if (foundIndex < 0)
		{
			auto& vec = *v.begin();
			minValue = vec[index[0]];
			++index[0];
		}
		else if (foundIndex >= 0)
		{
			auto& vec = v[foundIndex];
			minValue = vec[index[foundIndex]];
			++index[foundIndex];
		}
		std::cout << "minValue = " << minValue << "\n";
		result.push_back(minValue);
	}

	return {};
}

std::string alignString(std::vector<std::string> const& words, size_t length)
{
	if (words.empty())
		return std::string();

	size_t totalLen = 0;
	for (auto const& word : words)
		totalLen += word.size();

	if (length < totalLen)
		return std::string();

	auto addSpace = [](size_t count)
	{
		std::string space;
		for (size_t j = 0; j < count; ++j)
			space += ' ';
		return space;
	};
	size_t const totalSpace = length - totalLen;
	size_t const countWords = words.size() > 1 ? words.size() - 1 : 1u;
	size_t const countSpace = totalSpace / countWords;
	std::string s = words[0] + addSpace(countSpace + totalSpace % countWords);
	if (words.size() > 1)
	{
		for (size_t i = 1; i < countWords; ++i)
		{
			s += words[i] + addSpace(countSpace);
		}
		s += words.back();
	}
	return s;
}

bool isPalindrome(const std::string& str)
{
	if (str.empty())
	{
		return true;
	}

	if (str.size() == 1)
	{
		return std::isalpha(str.front());
	}

	auto begin = str.cbegin();
	auto rbegin = str.rbegin();
	bool foundLetter = false;
	while (begin != str.cend() && rbegin != str.crend())
	{
		const auto charFromBegin = std::tolower(*begin);
		const auto charFromEnd = std::tolower(*rbegin);
		if (!std::isalpha(charFromBegin))
		{
			++begin;
			continue;
		}

		if (!std::isalpha(charFromEnd))
		{
			++rbegin;
			continue;
		}

		if (charFromBegin != charFromEnd)
		{
			return false;
		}

		++begin;
		++rbegin;
		foundLetter = true;
	}

	return foundLetter;
}

int binarySearch(const std::vector<int>& v, const int value)
{
	if (v.empty())
	{
		return -1;
	}

	assert(v.size() <= std::numeric_limits<int>::max());

	int b = 0;
	int e = v.size() - 1;
	while (e >= b)
	{
		const int mid = b + (e - b) / 2;
		if (v[mid] == value)
		{
			return mid;
		}

		if (value > v[mid])
		{
			b = mid + 1;
		}

		if (value < v[mid])
		{
			e = mid - 1;
		}
	}

	return -1;
}

int myAtoi(const char* str)
{
	int res = 0;
	while (*str)
	{
		const int digit = *str - '0';
		res = res * 10 + digit;
		++str;
	}

	return res;
}

}  // namespace Algo
