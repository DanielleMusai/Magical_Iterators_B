#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP

#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <list>
#include <set>

namespace ariel
{
    class MagicalContainer
    {
    private:
        std::list<int> elements;

    public:
        void addElement(int element);
        void removeElement(int element);
        int size() const;
        bool getElement(int element) const;
        bool operator<(const MagicalContainer &other) const;
        bool operator>(const MagicalContainer &other) const;

        class AscendingIterator
        {
        private:
            MagicalContainer &container;
            std::list<int>::const_iterator iterator;

        public:
            AscendingIterator(MagicalContainer &container);
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

        class SideCrossIterator
        {
        private:
            MagicalContainer &container;
            std::list<int>::iterator lowIterator;
            std::list<int>::iterator highIterator;
            bool reverse;

        public:
            SideCrossIterator(MagicalContainer &container);
            SideCrossIterator(MagicalContainer &, std::list<int>::iterator, std::list<int>::iterator, bool);
            SideCrossIterator &operator++();
            int operator*();
            bool operator==(const SideCrossIterator &) const;
            bool operator!=(const SideCrossIterator &) const;
            bool operator<(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;
            SideCrossIterator &operator=(const SideCrossIterator &other);
            SideCrossIterator begin();
            SideCrossIterator end();
        };

        class PrimeIterator
        {
        private:
            MagicalContainer &container;
            std::list<int>::const_iterator iterator;
            bool isPrime(int num);

        public:
            PrimeIterator(MagicalContainer &container);
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
    };
}

#endif /* MAGICAL_CONTAINER_HPP */
