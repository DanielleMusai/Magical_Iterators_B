#include "MagicalContainer.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>
using namespace std;
namespace ariel
{

    void MagicalContainer::addElement(int element)
    {
        elements.push_back(element);
        std::sort(elements.begin(), elements.end());
    }


void MagicalContainer::removeElement(int element)
{
    auto iter = std::find(elements.begin(), elements.end(), element);
    if (iter == elements.end())
    {
        throw std::runtime_error("Element not found");
    }
    elements.erase(iter);
}

    int MagicalContainer::size() const
    {
        return elements.size();
    }

    bool MagicalContainer::getElement(int element) const
    {
        for (const auto &iter : elements)
        {
            if (iter == element)
            {
                return true;
            }
        }
        return false;
    }
    bool MagicalContainer::operator<(const MagicalContainer &other) const
    {
        return size() < other.size();
    }

    bool MagicalContainer::operator>(const MagicalContainer &other) const
    {
        return size() > other.size();
    }

    ////////////////////////// AscendingIterator /////////////////////
  MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer& container) : container(container) {
    iterator = container.elements.begin();
    
}


 MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
    if (&container != &other.container) {
        throw std::runtime_error("Iterators are pointing to different containers");
    }

    iterator = other.iterator;
    return *this;
}


    int MagicalContainer::AscendingIterator::operator*() const
    {
        return *iterator;
    }

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
    if (iterator == container.elements.end()) {
        throw std::runtime_error("Iterator is already at the end");
    }

    ++iterator;
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
    return iterator == other.iterator;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
    return iterator != other.iterator;
}

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
    {
        return iterator < other.iterator;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
    {
        return iterator > other.iterator;
    }

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const
{
    AscendingIterator it(container);
    if (!container.elements.empty())
    {
        it.iterator = container.elements.begin();
    }
    return it;
}


 MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const {
    AscendingIterator it(container);
    it.iterator = container.elements.end();
    return it;
}
    ////////////////////// SideCrossIterator ///////////////////////
    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &cont, bool rev)
        : container(cont), reverse(rev)
    {
       
            if (reverse) {
                iterator = container.elements.rbegin().base();
            } else {
                iterator = container.elements.begin();
            }
       
    }
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
    if (&container != &other.container) {
        throw std::runtime_error("Iterators are pointing to different containers");
    }

    iterator = other.iterator;
    return *this;
}
    int MagicalContainer::SideCrossIterator::operator*() const
    {
        return *iterator;
    }

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++()
{
    if (iterator == container.elements.end())
    {
        throw std::runtime_error("Iterator is already at the end");
    }

    if (reverse)
    {
        if (iterator != container.elements.begin())
        {
            --iterator;
        }
        reverse = false;
    }
    else
    {
        ++iterator;
        if (iterator != container.elements.end())
        {
            ++iterator;
        }
        reverse = true;
    }

    return *this;
}


    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {
        return iterator == other.iterator;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        return iterator < other.iterator;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        return iterator > other.iterator;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const
    {
        return SideCrossIterator(container, reverse);
    }

  MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const {
    SideCrossIterator it(container);
    it.iterator = container.elements.end(); // Set iterator to the end position
    return it;
}

 
    ///////////////////////// PrimeIterator ///////////////////////
    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &cont)
        : container(cont), iterator(container.elements.begin())
    {
        while (iterator != container.elements.end() && !isPrime(*iterator))
            ++iterator;
    }
  MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
    if (&container != &other.container) {
        throw std::runtime_error("Iterators are pointing to different containers");
    }

    iterator = other.iterator;
    return *this;
}
    int MagicalContainer::PrimeIterator::operator*() const
    {
        return *iterator;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
    if (iterator == container.elements.end()) {
        throw std::runtime_error("Iterator is already at the end");
    }

    ++iterator;
        while (iterator != container.elements.end() && !isPrime(*iterator))
            ++iterator;
        return *this;
}
    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
    {
        return iterator == other.iterator;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
    {
        return iterator < other.iterator;
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
    {
        return iterator > other.iterator;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const
    {
        return PrimeIterator(container);
    }

  // PrimeIterator end function
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
    PrimeIterator it(container);
    it.iterator = container.elements.end(); // Set iterator to the end position
    return it;
}

    bool MagicalContainer::PrimeIterator::isPrime(int num)
    {
        if (num < 2)
            return false;
        for (int i = 2; i <= std::sqrt(num); ++i)
        {
            if (num % i == 0)
                return false;
        }
        return true;
    }
}
