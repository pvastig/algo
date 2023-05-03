#include <map>

#include <gtest/gtest.h>

template<typename K, typename V>
class interval_map
{
public:
    std::map<K, V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map(V const& val)
    {
        m_map.insert(m_map.end(), std::make_pair(std::numeric_limits<K>::lowest(), val));
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign(K const& keyBegin, K const& keyEnd, V const& val)
    {
       // if (!(keyBegin < keyEnd))
          //  return;

        typename std::map<K, V>::iterator iterBegin; /*The new begin with val, can be begin()*/
        typename std::map<K, V>::iterator iterEnd;   /*the new end of val, can be end()*/

        auto lowerKeyBegin = m_map.lower_bound(keyBegin); //either end() or some iter whose key is not less than keyBegin. [1st O(logN)]
        auto upperKeyEnd = m_map.upper_bound(keyEnd); //some iter where keyEnd < key, or end()  [2nd O(logN)]
        auto prevKeyEnd = std::prev(upperKeyEnd);

        /*
        The next interval of the new interval starts at keyEnd if the previous value at keyEnd differed from val
        */
        if (!(prevKeyEnd->second == val))
        {
            // prevKeyEnd is either less than the new end we are inserting, or the same (no update to avoid copying from erased node)
            if (!(prevKeyEnd->first < keyEnd) && !(keyEnd < prevKeyEnd->first))
                iterEnd = prevKeyEnd;
            else
                iterEnd = m_map.insert_or_assign(upperKeyEnd, keyEnd, prevKeyEnd->second);
        }
        else
        {
            iterEnd = upperKeyEnd;
        }

        /*
        The new interval starts at keyBegin if the would-be previous interval has a different value.
        Previous interval is either a key in the map less than keyBegin, or non-existent when lower_bound is m_map.begin()
        The new interval's start is merged with previous interval, if the previous interval has the same value.
        */
        if (lowerKeyBegin != m_map.begin())
        {
            auto prevIter = std::prev(lowerKeyBegin); //safe when end(), because we always have at least one value
            if (!(prevIter->second == val))
            {
                iterBegin = m_map.insert_or_assign(lowerKeyBegin, keyBegin, val);
            }
            else iterBegin = prevIter;
        }
        else
        {
            iterBegin = m_map.insert_or_assign(lowerKeyBegin, keyBegin, val);
        }

		// Erase all keys between the new begin and end (excluding) so that there is only one value after iterBegin
		// This is fine when iterEnd is end()
		if (auto nextIterOfBegin = std::next(iterBegin);
			nextIterOfBegin != m_map.end())
		{
			//I would be very interested in a smarter way to get rid of this part without additional storage ...
			m_map.erase(nextIterOfBegin, iterEnd);
		}
	}

     //debug - check canonical
     //for (auto iter = m_map.begin(); iter != m_map.end(); ++iter)
     //{
     //  auto next = std::next(iter);
     //  if (next != m_map.end() && iter->second == next->second)
     //  {
     //      throw;
     //  }
     //}

    // look-up of the value associated with key
    V const& operator[](K const& key) const
    {
        return (--m_map.upper_bound(key))->second;
    }


    // a print function for debugging
    void show()
    {
        std::cout << "show" << std::endl;
        for (const auto [key, value] : m_map)
        {
            std::cout << key << " -> " << value << std::endl;
        }
    }
};

TEST(test_interval_map, test_interval_map)
{
    interval_map<unsigned int, char> imap{ 'A' };
    /*imap.assign(8, 12, 'k');
    imap.assign(2, 12, 'k');
    imap.assign(2, 12, 'b');
    imap.assign(5, 12, 'b');
    imap.assign(4, 10, 'b');
    imap.assign(4, 12, 'b');
    imap.assign(8, 13, 'a');
    imap.assign(6, 9, 'j');*/

    imap.assign(1, 2, 'B');
    imap.assign(3, 5, 'C');
    imap.assign(4, 7, 'E');
    imap.assign(4, 6, 'A');

    imap.show();

    std::cout << imap['j'] << std::endl;
    std::cout << imap['A'] << std::endl;
    std::cout << imap['b'] << std::endl;
    std::cout << imap['k'] << std::endl;
}

struct TestKeyType
{
    unsigned int val;
    constexpr TestKeyType(unsigned int val) : val(val)
    {
    }
    constexpr bool operator<(const TestKeyType& other) const
    {
        return val < other.val;
    }
};

namespace std
{
template<> class numeric_limits<TestKeyType>
{
public:
    static constexpr TestKeyType lowest()
    {
        return TestKeyType(numeric_limits<unsigned int>::lowest());
    }
    //static constexpr TestKeyType lowest() { return TestKeyType(-250); }
};
}

using TestValueType = char;

struct TestFloatKeyType
{
    float val;

    TestFloatKeyType() = default;

    TestFloatKeyType(float val) : val(val)
    {
    }
    bool operator< (TestFloatKeyType other) const
    {
        return other.val - val > 1.e-4f;
    }
};

namespace std
{
template<> class numeric_limits<TestFloatKeyType>
{
public:
    static TestFloatKeyType lowest()
    {
        return TestFloatKeyType(numeric_limits<float>::lowest());
    }
};
}

TEST(test_interval_map, EmptyRange)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(3, 3, 'B');

    ASSERT_EQ(m.m_map.size(), 2);
    ASSERT_EQ(m.m_map.count(3), 1);

    m.assign(3, 2, 'B');
    ASSERT_EQ(m.m_map.size(), 3);
    ASSERT_EQ(m.m_map.count(2), 1);
    ASSERT_EQ(m.m_map.count(3), 1);
}


TEST(test_interval_map, TrivialRange)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 10, 'B');
    ASSERT_TRUE(m[0] == 'A');
    for (int i = 1; i < 10; i++)
    {
        ASSERT_TRUE(m[i] == 'B');
    }
    ASSERT_TRUE(m[10] == 'A');
}

TEST(test_interval_map, TrivialTwoRange)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 3, 'B');
    m.assign(6, 8, 'C');
    ASSERT_TRUE(m[0] == 'A');
    ASSERT_TRUE(m[1] == 'B');
    ASSERT_TRUE(m[2] == 'B');
    ASSERT_TRUE(m[3] == 'A');
    ASSERT_TRUE(m[4] == 'A');
    ASSERT_TRUE(m[5] == 'A');
    ASSERT_TRUE(m[6] == 'C');
    ASSERT_TRUE(m[7] == 'C');
    ASSERT_TRUE(m[8] == 'A');
}

TEST(test_interval_map, OverwriteLowest)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(std::numeric_limits<TestKeyType>::lowest(), 10000, 'B');
    ASSERT_TRUE(m[0] == 'B');
    ASSERT_TRUE(m[9999] == 'B');
    ASSERT_TRUE(m[10000] == 'A');
}

TEST(test_interval_map, Merge)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(std::numeric_limits<TestKeyType>::lowest(), 10, 'B');
    m.assign(10, 20, 'B');
    ASSERT_TRUE(m[0] == 'B');
    ASSERT_TRUE(m[10] == 'B');
    ASSERT_TRUE(m[19] == 'B');
    ASSERT_TRUE(m[20] == 'A');
}

TEST(test_interval_map, FloatKey)
{
    interval_map<TestFloatKeyType, TestValueType> m('A');
    m.assign(1.f, 5.f, 'B');
    ASSERT_TRUE(m[0.f] == 'A');
    ASSERT_TRUE(m[.999999999f] == 'B');
    ASSERT_TRUE(m[1.f] == 'B');
    ASSERT_TRUE(m[4.999f] == 'B');
    ASSERT_TRUE(m[5.f] == 'A');

}

TEST(test_interval_map, OverlappingRangeComplete)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(3, 5, 'B');
    m.assign(1, 6, 'C');
    ASSERT_TRUE(m[0] == 'A');
    ASSERT_TRUE(m[1] == 'C');
    ASSERT_TRUE(m[2] == 'C');
    ASSERT_TRUE(m[3] == 'C');
    ASSERT_TRUE(m[4] == 'C');
    ASSERT_TRUE(m[5] == 'C');
    ASSERT_TRUE(m[6] == 'A');
}

TEST(test_interval_map, OverlappingRangeInner)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 6, 'C');
    m.assign(3, 5, 'B');
    ASSERT_TRUE(m[0] == 'A');
    ASSERT_TRUE(m[1] == 'C');
    ASSERT_TRUE(m[2] == 'C');
    ASSERT_TRUE(m[3] == 'B');
    ASSERT_TRUE(m[4] == 'B');
    ASSERT_TRUE(m[5] == 'C');
    ASSERT_TRUE(m[6] == 'A');
}

TEST(test_interval_map, OverlappingRangeSmallToLarge)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(3, 6, 'C');
    ASSERT_TRUE(m[0] == 'A');
    ASSERT_TRUE(m[1] == 'B');
    ASSERT_TRUE(m[2] == 'B');
    ASSERT_TRUE(m[3] == 'C');
    ASSERT_TRUE(m[4] == 'C');
    ASSERT_TRUE(m[5] == 'C');
    ASSERT_TRUE(m[6] == 'A');
}

TEST(test_interval_map, OverlappingRangeLargeToSmall)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(3, 6, 'C');
    m.assign(1, 5, 'B');
    ASSERT_TRUE(m[0] == 'A');
    ASSERT_TRUE(m[1] == 'B');
    ASSERT_TRUE(m[2] == 'B');
    ASSERT_TRUE(m[3] == 'B');
    ASSERT_TRUE(m[4] == 'B');
    ASSERT_TRUE(m[5] == 'C');
    ASSERT_TRUE(m[6] == 'A');
}

TEST(test_interval_map, ExtendingRangeBegin)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(3, 5, 'B');
    ASSERT_TRUE(m[0] == 'A');
    ASSERT_TRUE(m[1] == 'A');
    ASSERT_TRUE(m[2] == 'A');
    ASSERT_TRUE(m[3] == 'B');
    ASSERT_TRUE(m[4] == 'B');
    ASSERT_TRUE(m[5] == 'A');

    m.assign(1, 4, 'B');
    ASSERT_TRUE(m[0] == 'A');
    ASSERT_TRUE(m[1] == 'B');
    ASSERT_TRUE(m[2] == 'B');
    ASSERT_TRUE(m[3] == 'B');
    ASSERT_TRUE(m[4] == 'B');
    ASSERT_TRUE(m[5] == 'A');
}

TEST(test_interval_map, ExtendingRangeEnd)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(3, 6, 'B');
    ASSERT_TRUE(m[0] == 'A');
    ASSERT_TRUE(m[1] == 'B');
    ASSERT_TRUE(m[2] == 'B');
    ASSERT_TRUE(m[3] == 'B');
    ASSERT_TRUE(m[4] == 'B');
    ASSERT_TRUE(m[5] == 'B');
    ASSERT_TRUE(m[6] == 'A');
}

TEST(test_interval_map, ExtendingRangeBothBeginEnd)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(2, 3, 'B');
    m.assign(1, 5, 'B');
    ASSERT_TRUE(m[0] == 'A');
    ASSERT_TRUE(m[1] == 'B');
    ASSERT_TRUE(m[2] == 'B');
    ASSERT_TRUE(m[3] == 'B');
    ASSERT_TRUE(m[4] == 'B');
    ASSERT_TRUE(m[5] == 'A');
}

TEST(test_interval_map, OverwriteEndValueSafety)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(2, 5, 'B');
    m.assign(5, 8, 'C');
    m.assign(4, 5, 'A');
}

TEST(test_interval_map, ReusingExistingRangeBothBeginEnd)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(2, 3, 'B');
    ASSERT_TRUE(m[0] == 'A');
    ASSERT_TRUE(m[1] == 'B');
    ASSERT_TRUE(m[2] == 'B');
    ASSERT_TRUE(m[3] == 'B');
    ASSERT_TRUE(m[4] == 'B');
    ASSERT_TRUE(m[5] == 'A');
}

TEST(test_interval_map, ReusingEnd)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(4, 6, 'A');
    ASSERT_TRUE(m[0] == 'A');
    ASSERT_TRUE(m[1] == 'B');
    ASSERT_TRUE(m[2] == 'B');
    ASSERT_TRUE(m[3] == 'B');
    ASSERT_TRUE(m[4] == 'A');
    ASSERT_TRUE(m[5] == 'A');
}

TEST(test_interval_map, RestoringInitial)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(1, 5, 'A');
    ASSERT_TRUE(m[0] == 'A');
    ASSERT_TRUE(m[1] == 'A');
    ASSERT_TRUE(m[2] == 'A');
    ASSERT_TRUE(m[3] == 'A');
    ASSERT_TRUE(m[4] == 'A');
    ASSERT_TRUE(m[5] == 'A');
}

TEST(test_interval_map, RestoringInitial2)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(0, 7, 'A');
    ASSERT_TRUE(m[0] == 'A');
    ASSERT_TRUE(m[1] == 'A');
    ASSERT_TRUE(m[2] == 'A');
    ASSERT_TRUE(m[3] == 'A');
    ASSERT_TRUE(m[4] == 'A');
    ASSERT_TRUE(m[5] == 'A');
}

TEST(test_interval_map, VeryComplex)
{
    interval_map<TestKeyType, TestValueType> m('A');
    m.assign(3, 6, 'B');
    m.assign(2, 5, 'C');
    m.assign(4, 7, 'A');

    ASSERT_TRUE(m[1] == 'A');
    ASSERT_TRUE(m[2] == 'C');
    ASSERT_TRUE(m[3] == 'C');
    ASSERT_TRUE(m[4] == 'A');
    ASSERT_TRUE(m[5] == 'A');
    ASSERT_TRUE(m[6] == 'A');
    ASSERT_TRUE(m[7] == 'A');
}

