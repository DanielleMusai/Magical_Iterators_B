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
        elements.sort();
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

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container)
        : container(container)
    {
        iterator = container.elements.begin();
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Iterators are pointing to different containers");
        }

        iterator = other.iterator;
        return *this;
    }

    int MagicalContainer::AscendingIterator::operator*() const
    {
        return *iterator;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        if (iterator == container.elements.end())
        {
            throw std::runtime_error("Iterator is already at the end");
        }

        ++iterator;
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
    {
        return iterator == other.iterator;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
    {
        return iterator != other.iterator;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
    {
        return *iterator < *other.iterator;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
    {
        return *iterator > *other.iterator;
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

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const
    {
        AscendingIterator it(container);
        it.iterator = container.elements.end();
        return it;
    }

    ////////////////////// SideCrossIterator ///////////////////////

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
        : container(container)
    {
        if (container.elements.empty())
        {
            lowIterator = container.elements.end();
            highIterator = container.elements.end();
            reverse = false;
        }
        else
        {
            lowIterator = container.elements.begin();
            highIterator = std::prev(container.elements.end());
            reverse = true;
        }
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, std::list<int>::iterator iteratorStart, std::list<int>::iterator iteratorEnd, bool rev) : container(container), lowIterator(iteratorStart), highIterator(iteratorEnd), reverse(rev)
    {
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {

        return (this->lowIterator == other.lowIterator) && (this->highIterator == other.highIterator) && (this->reverse == other.reverse);
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
    {
        return !(*this == other);
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {

        if (lowIterator == container.elements.end())
        {
            throw std::runtime_error("Iterator is already at the end");
        }
        if (this->lowIterator == this->highIterator)
        {
            this->lowIterator = this->container.elements.end();
            this->highIterator = this->container.elements.end();
            this->reverse = false;
            return *this;
        }

        if (reverse)
            ++this->lowIterator;
        else
            --this->highIterator;

        this->reverse = !this->reverse;
        return *this;
    }

    int MagicalContainer::SideCrossIterator::operator*()
    {
        if (reverse)
            return *this->lowIterator;
        else
            return *this->highIterator;
    }

    bool MagicalContainer::MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        return *lowIterator < *other.lowIterator;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        return *lowIterator > *other.lowIterator;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Iterators are pointing to different containers");
        }

        if (this != &other)
        {
            container = other.container;
            lowIterator = other.lowIterator;
            highIterator = other.highIterator;
            reverse = other.reverse;
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    {

        if (container.elements.empty())
        {
            return end();
        }

        return SideCrossIterator(container, container.elements.begin(), std::prev(container.elements.end()), true);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
    {
        return SideCrossIterator(container, container.elements.end(), container.elements.end(), false);
    }

    ///////////////////////// PrimeIterator ///////////////////////

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &cont)
        : container(cont), iterator(container.elements.begin())
    {
        while (iterator != container.elements.end() && !isPrime(*iterator))
            ++iterator;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
    {
        if (&container != &other.container)
        {
            throw std::runtime_error("Iterators are pointing to different containers");
        }

        iterator = other.iterator;
        return *this;
    }

    int MagicalContainer::PrimeIterator::operator*() const
    {
        return *iterator;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        if (iterator == container.elements.end())
        {
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
        return *iterator < *other.iterator;
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
    {
        auto iter1 = iterator;
        auto iter2 = other.iterator;
        while (iter1 != container.elements.end() && iter2 != other.container.elements.end())
        {
            if (*iter1 > *iter2)
            {
                return true;
            }
            else if (*iter1 < *iter2)
            {
                return false;
            }
            ++iter1;
            ++iter2;
        }

        return (iter1 == container.elements.end() && iter2 != other.container.elements.end());
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const
    {
        return PrimeIterator(container);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const
    {
        PrimeIterator it(container);
        it.iterator = container.elements.end();
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
