#include "algo.h"

#include <future>
#include <optional>
#include <gtest/gtest.h>

namespace testing
{
namespace internal
{

/// @brief A specialization of the Google Test universal printer template for the boost::optional type
///
/// @tparam T A type with which boost::optional is parameterized
///
template<typename T>
class UniversalPrinter<::std::optional<T>>
{
public:
    /// @brief Shows Google Test how to print the specified object to the output stream
    ///
    /// @param[in] value An object to print
    ///
    /// @param[in,out] os An output stream
    ///
    static void Print(const ::std::optional<T>& value, ::std::ostream* os)
    {
        if (os)
        {
            *os << '(';
            if (!value)
            {
                *os << "nullopt";
            }
            else
            {
                UniversalPrint(*value, os);
            }
            *os << ')';
        }
    }
};

} // namespace internal
} // namespace testing

namespace Algo
{

TEST(Algo, countMatchedSymbols)
{
    ASSERT_EQ(countMatchedSymbols({ "aabbccd" }, "ab"), 4);
    ASSERT_EQ(countMatchedSymbols("ab", { "aabbccd" }), 2); // thinking about searching long pattern in short string
    ASSERT_EQ(countMatchedSymbols("aabbccd", { "aabbccd" }), 7);
    ASSERT_EQ(countMatchedSymbols({ "" }, { "" }), 0);
    ASSERT_EQ(countMatchedSymbols({ "a" }, { "" }), 0);
    ASSERT_EQ(countMatchedSymbols({ "" }, { "a" }), 0);
    ASSERT_EQ(countMatchedSymbols({ "aaaa" }, { "a" }), 4);
    ASSERT_EQ(countMatchedSymbols({ "AaaB" }, { "a" }), 2);
    ASSERT_EQ(countMatchedSymbols({ "A1aaB2" }, { "12" }), 2);
}

TEST(Algo, countDigitsOneByOne)
{
    ASSERT_EQ(countDigitsOneByOne({ 0, 0, 0, 0, 0, 0, 0 }), 0);
    ASSERT_EQ(countDigitsOneByOne({ 1, 0, 0, 0, 0, 0, 0 }), 1);
    ASSERT_EQ(countDigitsOneByOne({ 0, 0, 0, 0, 0, 0, 1 }), 1);
    ASSERT_EQ(countDigitsOneByOne({ 0, 0, 0, 0, 1, 1, 1 }), 3);
    ASSERT_EQ(countDigitsOneByOne({ 1, 1, 1, 0, 0, 0, 0 }), 3);
    ASSERT_EQ(countDigitsOneByOne({ 1, 1, 1, 0, 0, 0, 1 }), 3);
    ASSERT_EQ(countDigitsOneByOne({ 1, 1, 1, 0, 1, 0, 1 }), 3);
    ASSERT_EQ(countDigitsOneByOne({ 1, 1, 1, 0, 0, 1, 1 }), 3);
    ASSERT_EQ(countDigitsOneByOne({ 0, 1, 1, 0, 1, 1, 1 }), 3);
    ASSERT_EQ(countDigitsOneByOne({ 0, 1, 1, 0, 1, 1, 0 }), 2);
    ASSERT_EQ(countDigitsOneByOne({ 1, 0, 1, 0, 1, 0, 1 }), 1);
    ASSERT_EQ(countDigitsOneByOne({ 0, 1, 0, 1, 0, 1, 0 }), 1);
    ASSERT_EQ(countDigitsOneByOne({ 1, 1, 1, 1, 1, 1, 1 }), 7);
    ASSERT_EQ(countDigitsOneByOne({}), 0);
    ASSERT_EQ(countDigitsOneByOne({1}), 1);
    ASSERT_EQ(countDigitsOneByOne({ 1, 2, 3, 4, 5, 6, 7 }), 1);
    ASSERT_EQ(countDigitsOneByOne({ 5, 5, 5, 5, 5, 1 }), 1);
    ASSERT_EQ(countDigitsOneByOne({ 5, 5, 5, 5, 5, 1 }, 5), 5);
    ASSERT_EQ(countDigitsOneByOne({ 5, 5, 5, 5, 5, 1 }, 2), 0);
    ASSERT_EQ(countDigitsOneByOne({ 2, 5, 2, 2, 2, 1 }, 5), 1);
    ASSERT_EQ(countDigitsOneByOne({ 100, 5, 100, 100, 2, 100 }, 100), 2);
}

TEST(Algo, deleteValues)
{
    {
        std::vector<int> v;
        ASSERT_EQ(deleteValues(v), false);
    }
    {
        std::vector v{ 1 };
        ASSERT_EQ(deleteValues(v, 1), true);
        ASSERT_EQ(v.empty(), true);
    }
    {
        std::vector v{ 0, 1, 1, 0 };
        std::vector ref{ 1, 1 };
        ASSERT_EQ(deleteValues(v), true);
        ASSERT_EQ(v.size(), ref.size());
        ASSERT_EQ(v.size(), ref.size());
    }
    {
        std::vector v{ 0, 0, 0, 0 };
        ASSERT_EQ(deleteValues(v), true);
        ASSERT_EQ(v.empty(), true);
    }
    {
        std::vector v{ 0, 0, 0, 0 };
        std::vector ref{ 0, 0, 0, 0 };
        ASSERT_EQ(deleteValues(v, 10), false);
        ASSERT_EQ(v.empty(), false);
        ASSERT_EQ(v, ref);
    }
    {
        std::vector v{ 1, 5, 5, 5 };
        std::vector ref{ 1 };
        ASSERT_EQ(deleteValues(v, 5), true);
        ASSERT_EQ(v.size(), ref.size());
        ASSERT_EQ(v, ref);
    }
    {
		std::vector v{ 1, 2, 3, 4, 5 };
		for (int const value : { 1, 2, 3, 4, 5 })
		{
			ASSERT_EQ(deleteValues(v, value), true);
		}
        ASSERT_EQ(v.empty(), true) << "Unequal length";
    }
}

TEST(Algo, alignString)
{
    ASSERT_EQ("", alignString({}, 3));
    ASSERT_EQ("", alignString({ "1" }, 0));
    ASSERT_EQ("x", alignString({ "x" }, 1));
    ASSERT_EQ("xy", alignString({ "x", "y" }, 2));
    ASSERT_EQ("", alignString({ "x", "y" }, 1));
    ASSERT_EQ("x y", alignString({ "x", "y" }, 3));
    ASSERT_EQ("a b c", alignString({ "a", "b", "c" }, 5));
    ASSERT_EQ("a   b  c", alignString({ "a", "b", "c" }, 8));
    ASSERT_EQ("a  b  c  d", alignString({ "a", "b", "c", "d" }, 10));
    ASSERT_EQ("a   b  c  d", alignString({ "a", "b", "c", "d" }, 11));
}

class A
{
public:
    A() : ab(*this)
    {
    }

    A(double d) : ab(*this, d)
    {
    }

    double get() const
    {
        return a + b;
    }

    void set(double v)
    {
        a = v / 2; b = v / 2;
    }

    double a = 0.;
    double b = 0.;

    class GetSet
    {
    public:
        GetSet(A& a) : m_a(a)
        {
        }

        GetSet(A& a, double d) : m_a(a)
        {
            m_a.set(d);
        }

        operator double() const
        {
            m_a.set(m_a.get());
            return m_a.get();
        }

        GetSet& operator=(const A& other)
        {
            m_a.a = other.a;
            m_a.b = other.b;
            return *this;
        }

    private:
        A& m_a;
    };

    GetSet ab;
};

TEST(Algo, get_set)
{
	A a;
	a.a = 2;
	a.b = 3;
    // 2 + 3 = 5
	ASSERT_EQ(a.ab, 5);

	a.ab = 10.0;
	ASSERT_EQ(a.a, 5);
	ASSERT_EQ(a.b, 5);
}

TEST(Algo, isPalindrome)
{
    ASSERT_TRUE(isPalindrome(""));
    ASSERT_FALSE(isPalindrome("1"));
    ASSERT_TRUE(isPalindrome("a"));
    ASSERT_FALSE(isPalindrome(","));
    ASSERT_FALSE(isPalindrome(",,!,,"));
    ASSERT_FALSE(isPalindrome(",,!,"));
    ASSERT_TRUE(isPalindrome(",,!,a"));
    ASSERT_FALSE(isPalindrome(",,!,ab"));
    ASSERT_TRUE(isPalindrome("a,,!,"));
    ASSERT_TRUE(isPalindrome(",,!,aa"));
    ASSERT_TRUE(isPalindrome(",,!,aa!!!!"));
    ASSERT_FALSE(isPalindrome(",,!,ab!!!!)"));

    ASSERT_TRUE(isPalindrome("aa"));
    ASSERT_FALSE(isPalindrome("ab"));
    ASSERT_TRUE(isPalindrome("aba"));
    ASSERT_FALSE(isPalindrome("hello world!"));
    ASSERT_FALSE(isPalindrome("hedleh"));
    ASSERT_TRUE(isPalindrome("Was it a car or a cat I saw"));
    ASSERT_TRUE(isPalindrome("!!!!Was (it) a car. or ,a cat, I! saw!!!!???!!"));
    ASSERT_TRUE(isPalindrome("ABBA"));
}

TEST(Algo, binarySerach)
{
	{
		std::vector v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		ASSERT_EQ(binarySearch(v, 3), 2);
		ASSERT_EQ(binarySearch(v, 5), 4);
		ASSERT_EQ(binarySearch(v, 1), 0);
		ASSERT_EQ(binarySearch(v, 2), 1);
		ASSERT_EQ(binarySearch(v, 20), -1);
		ASSERT_EQ(binarySearch(v, 0), -1);
	}
	{
		std::vector v{ 1, 2, 3, 4, 5, 6 };
		ASSERT_EQ(binarySearch(v, 1), 0);
		ASSERT_EQ(binarySearch(v, 2), 1);
		ASSERT_EQ(binarySearch(v, 3), 2);
		ASSERT_EQ(binarySearch(v, 5), 4);
		ASSERT_EQ(binarySearch(v, 6), 5);
		ASSERT_EQ(binarySearch(v, 10), -1);
		ASSERT_EQ(binarySearch(v, 0), -1);
	}
	{
		std::vector<int> v;
		ASSERT_EQ(binarySearch(v, 1), -1);
	}

	/*{
		int value = 0;
		auto lambda = [&value]()
		{
			++value;
		};

		std::async(std::launch::async, lambda).get();
        std::cout << value << std::endl;

		std::async(std::launch::async, lambda).get();
		std::cout << value << std::endl;
	}*/
}

TEST(Algo, myAtoi)
{
    ASSERT_EQ(myAtoi("123"), 123);
    ASSERT_EQ(myAtoi(""), 0);
}

std::vector<int> sortSquareNumbers(const std::vector<int>& v)
{
    auto squareNumber = [](auto x)
    {
        return x * x;
    };

	std::vector<int> result;
    auto b = v.begin();
    auto e = v.rbegin();

    result.reserve(v.size());
	while(b != e.base() && b != v.end() && e != v.rend())
	{
		const int leftNum = squareNumber(*b);
		const int rightNum = squareNumber(*e);

        if (leftNum >= rightNum)
        {
            result.push_back(leftNum);
            ++b;
        }
        else
        {
            result.push_back(rightNum);
            ++e;
        }
	}

    return { result.crbegin(), result.crend() };
}

TEST(Algo, sortSquareNumbers)
{
    {
        std::vector v{ -2, -1, 0, 1, 2, 3 };
        std::vector ref{ 0, 1, 1, 4, 4, 9 };
        ASSERT_EQ(sortSquareNumbers(v), ref);
    }
    {
        std::vector v{ -2, -1 };
        std::vector ref{ 1, 4 };
        ASSERT_EQ(sortSquareNumbers(v), ref);
    }
    {
        std::vector v{ -1 };
        std::vector ref{ 1 };
        ASSERT_EQ(sortSquareNumbers(v), ref);
    }
    {
        std::vector v{ -1, -1, 0, 0, 1, 1 };
        std::vector ref{ 0, 0, 1, 1, 1, 1 };
        ASSERT_EQ(sortSquareNumbers(v), ref);
    }
    {
        std::vector v{ -5, -4, -3, -2, -1, 0 };
        std::vector ref{ 0, 1, 4, 9, 16, 25 };
        ASSERT_EQ(sortSquareNumbers(v), ref);
    }
    {
        std::vector v{ -4, -2, 1, 0, 2, 3, 5, 7 };
        std::vector ref{ 0, 1, 4, 4, 9, 16, 25, 49 };
        ASSERT_EQ(sortSquareNumbers(v), ref);
    }
}

}
