#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <vector>

namespace ariel
{

    class MagicalContainer
    {
    private:
        std::vector<int> elements;       // Original elements in insertion order
      // std::vector<int> sortedElements; // Sorted copy of elements

    public:
        void addElement(int element);
        void removeElement(int element);
        int size() const;
        bool getElement(int element) const;
        bool operator<(const MagicalContainer &other) const;
        bool operator>(const MagicalContainer &other) const;
        class AscendingIterator;
        class SideCrossIterator;
        class PrimeIterator;
    };

    class MagicalContainer::AscendingIterator
    {
    private:
        const MagicalContainer &container;
        std::vector<int>::const_iterator iterator;

    public:
        AscendingIterator(const MagicalContainer &cont);
        AscendingIterator &operator=(const AscendingIterator &other);
        int operator*() const;
        AscendingIterator &operator++();
        bool operator==(const AscendingIterator &other) const;
        bool operator!=(const AscendingIterator &other) const;
        bool operator<(const AscendingIterator &other) const;
        bool operator>(const AscendingIterator &other) const;
        AscendingIterator begin() const;
        AscendingIterator end() const;
    };

    class MagicalContainer::SideCrossIterator
    {
    private:
        const MagicalContainer &container;
        std::vector<int>::const_iterator iterator;
        bool reverse;

    public:
        SideCrossIterator(const MagicalContainer &cont, bool rev = false);
        SideCrossIterator &operator=(const SideCrossIterator &other);
        int operator*() const;
        SideCrossIterator &operator++();
        bool operator==(const SideCrossIterator &other) const;
        bool operator!=(const SideCrossIterator &other) const;
        bool operator<(const SideCrossIterator &other) const;
        bool operator>(const SideCrossIterator &other) const;
        SideCrossIterator begin() const;
        SideCrossIterator end() const;
    };

    class MagicalContainer::PrimeIterator
    {
    private:
        const MagicalContainer &container;
        std::vector<int>::const_iterator iterator;
        bool isPrime(int num);

    public:
        PrimeIterator(const MagicalContainer &cont);
        PrimeIterator &operator=(const PrimeIterator &other);
        int operator*() const;
        PrimeIterator &operator++();
        bool operator==(const PrimeIterator &other) const;
        bool operator!=(const PrimeIterator &other) const;
        bool operator<(const PrimeIterator &other) const;
        bool operator>(const PrimeIterator &other) const;
        PrimeIterator begin() const;
        PrimeIterator end() const;
    };

}

#endif /* MAGICALCONTAINER_HPP */
