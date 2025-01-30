#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

//****************************************************************************//

// CLASSES AND STRUCT HERE:

//****************************************************************************//
    /**
     * @brief Represents a sorted list of elements of type T.
     * 
     * Note - The type T must support the '>' operator.
     */
    template <typename T>
    class SortedList {
        /**
         * @brief Declaring the Node struct for access from the SortedList class.
         */
        struct Node;

        /**
         * @brief Represents the head of the list.
         */
        Node* m_head;
        
        /**
         * @brief Represents the number of elements in the list.
         */
        size_t m_length;

        /**
         * @brief Clears the list and releases the memory allocated for the nodes.
         */
        void clear();

    public:
        
        /**
         * @brief Empty constructor, Copy constructor, Assignment operator and Destructor.
         */ 
        SortedList();
        SortedList(const SortedList&);
        SortedList& operator=(const SortedList&);
        ~SortedList();

        /**
         * @brief Represents a const iterator for a SortedList object.
         */
        class ConstIterator;
        ConstIterator begin() const;
        ConstIterator end() const;

        /**
         * @brief Inserts a new element to the list.
         * @param element The element to insert.
         */
        void insert(const T&);

        /**
         * @brief Removes an element from the list.
         * @param it An iterator pointing to the element to remove.
         */
        void remove(const ConstIterator&);

        /**
         * @brief Returns the number of elements in the list.
         */
        int length() const;

        /**
         * @brief Returns a new list with elements that satisfy a given condition.
         * @param predicate typename for a Boolean functor that receives 
         *      an element and returns a Boolean value.
         * @return A new list with elements that satisfy the given condition.
         */
        template<typename Predicate>
        SortedList filter(Predicate) const;

        /**
         * @brief Returns a new list with elements that were modified by an operation.
         * @param operation A function that receives an element and returns a new element.
         * @return A new list with elements that were modified by the given operation.
         */
        template<typename Operation>
        SortedList apply(Operation) const;
    };

//****************************************************************************//
    
    template <typename T>
    class SortedList<T>::ConstIterator {
        Node* m_listHead;
        Node* m_node;
        explicit ConstIterator(Node*, Node*);
        friend class SortedList;

    public:
        ConstIterator(const ConstIterator&) = default;
        ConstIterator& operator=(const ConstIterator&) = default;
        ~ConstIterator() = default;
        const T& operator*() const;
        ConstIterator& operator++();
        bool operator!=(const ConstIterator&) const;
    };

//****************************************************************************//

    template <typename T>
    struct SortedList<T>::Node {
        T m_data;
        Node* m_next;
        Node* m_previous;
        explicit Node(const T& data) :
            m_data(data), m_next(nullptr), m_previous(nullptr) {}
    };

//****************************************************************************//

// IMPLEMENTATIONS FROM HERE:

//****************************************************************************//

    template<typename T>
    void SortedList<T>::clear() {
        while (m_head) {
            const Node* toDelete = m_head;
            m_head = m_head->m_next;
            delete toDelete;
        }
        m_length = 0;
    }

//****************************************************************************//

    template<typename T>
    SortedList<T>::SortedList() : m_head(nullptr), m_length(0) {}

//****************************************************************************//

    template<typename T>
    SortedList<T>::SortedList(const SortedList& sortedList) :
        m_head(nullptr), m_length(0) {
        try {
            if (sortedList.m_head) {
                m_head = new Node(sortedList.m_head->m_data);
                Node* thisCurrent = m_head;
                Node* current = sortedList.m_head;
                while(current->m_next) {
                    thisCurrent->m_next = new Node(current->m_next->m_data);
                    thisCurrent->m_next->m_previous = thisCurrent;
                    thisCurrent = thisCurrent->m_next;
                    current = current->m_next;
                }
            }
            m_length = sortedList.m_length;
        }
        catch (...) {
            clear();
            throw;
        }
    }

//****************************************************************************//

    template<typename T>
    SortedList<T>& SortedList<T>::operator=(const SortedList& sortedList) {
        if (this != &sortedList) {
            SortedList temp(sortedList);
            Node* tempHead = m_head;
            m_head = temp.m_head;
            temp.m_head = tempHead;
            m_length = sortedList.m_length;
        }
        return *this;
    }

//****************************************************************************//

    template<typename T>
    SortedList<T>::~SortedList() {
        clear();
    }

//****************************************************************************//

    template<typename T>
    void SortedList<T>::insert(const T& element) {
        Node* newNode = new Node(element);
        if (m_head == nullptr) {
            m_head = newNode;
        }
        else if(!(m_head->m_data > element)) {
            newNode->m_next = m_head;
            m_head->m_previous = newNode;
            m_head = newNode;
        }
        else {
            Node* current = m_head;
            while (current->m_next != nullptr &&
                current->m_next->m_data > element) {
                current = current->m_next;
            }
            newNode->m_next = current->m_next;
            newNode->m_previous = current;
            if (current->m_next != nullptr) {
                current->m_next->m_previous = newNode;
            }
            current->m_next = newNode;
        }
        m_length++;
    }

//****************************************************************************//

    template<typename T>
    void SortedList<T>::remove(const ConstIterator& it) {
        if (it.m_listHead != m_head) {
            throw std::range_error("Not of list Iterator");
        }
        if (it.m_node) {
            if (it.m_node->m_previous) {
                it.m_node->m_previous->m_next = it.m_node->m_next;
            }
            if (it.m_node->m_next) {
                it.m_node->m_next->m_previous = it.m_node->m_previous;
            }
            if (it.m_node == m_head) {
                m_head = it.m_node->m_next;
            }
            delete it.m_node;
            m_length--;
        }
    }

//****************************************************************************//

    template<typename T>
    int SortedList<T>::length() const {
        return m_length;
    }

//****************************************************************************//

    template<typename T>
    template<typename Predicate>
    SortedList<T> SortedList<T>::filter(Predicate predicate) const {
        SortedList result;
        for (ConstIterator it = begin(); it != end(); ++it) {
            if (predicate(*it)) {
                result.insert(*it);
            }
        }
        return result;
    }

//****************************************************************************//

    template<typename T>
    template<typename Operation>
    SortedList<T> SortedList<T>::apply(Operation operation) const {
        SortedList result;
        for (ConstIterator it = begin(); it != end(); ++it) {
            result.insert(operation(*it));
        }
        return result;
    }

//****************************************************************************//

    template<typename T>
    SortedList<T>::ConstIterator::ConstIterator(Node* listHead, Node* node) :
        m_listHead(listHead), m_node(node) {}

//****************************************************************************//

    template<typename T>
    typename SortedList<T>::ConstIterator SortedList<T>::begin() const {
        return ConstIterator(m_head, m_head);
    }

//****************************************************************************//

    template<typename T>
    typename SortedList<T>::ConstIterator SortedList<T>::end() const {
        return ConstIterator(m_head, nullptr);
    }

//****************************************************************************//

    template<typename T>
    bool SortedList<T>::ConstIterator::operator!=(const ConstIterator& it) const {
        if (m_listHead && it.m_listHead && m_listHead != it.m_listHead) {
            throw std::range_error("Comparing Iterators of two differante lists");
        }
        return m_node != it.m_node;
    }

//****************************************************************************//

    template<typename T>
    const T& SortedList<T>::ConstIterator::operator*() const {
        if (!m_node) {
            throw std::out_of_range("Bad Index");
        }
        return m_node->m_data;
    }

//****************************************************************************//

    template<typename T>
    typename SortedList<T>::ConstIterator& SortedList<T>::ConstIterator::operator++() {
        if (!m_node) {
            throw std::out_of_range("Bad Index");
        }
        m_node = m_node->m_next;
        return *this;
    }

}

//****************************************************************************//