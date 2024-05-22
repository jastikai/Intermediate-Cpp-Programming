/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
 
template <class T>
List<T>::List() { 
  head_ = nullptr; // Fixed: Use nullptr instead of NULL
  tail_ = nullptr; // Fixed: Use nullptr instead of NULL
  length_ = 0; // Fixed: Initialize length_ to 0
}

template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  return ListIterator(head_); // Completed: Return ListIterator with position at the beginning of the list
}

template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  return ListIterator(nullptr); // Completed: Return ListIterator one past the end of the list
}

template <typename T>
void List<T>::_destroy() {
  ListNode* current = head_;
  while (current != nullptr) {
      ListNode* next = current->next;
      delete current;
      current = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
  length_ = 0;
} // Completed: Destroy all dynamically allocated memory associated with the current List class

template <typename T>
void List<T>::insertBack(const T & ndata) {
  ListNode* newNode = new ListNode(ndata);
  if (tail_ != nullptr) {
      tail_->next = newNode;
      newNode->prev = tail_;
  } else {
      head_ = newNode;
  }
  tail_ = newNode;
  length_++;
} // Completed: Insert a new node at the back of the List

template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  ListNode* current = start;
  for (int i = 0; i < splitPoint && current != nullptr; i++) {
      current = current->next;
  }
  if (current != nullptr) {
      current->prev->next = nullptr;
      current->prev = nullptr;
  }
  return current;
} // Completed: Helper function to split a sequence of linked memory at the node splitPoint steps after start

template <typename T>
void List<T>::tripleRotate() {
    if (length_ < 3) return;

    ListNode* current = head_;
    ListNode* temp = current->next->next;

    while (temp != nullptr) {
        current->next->prev = nullptr;
        current->next = temp->next;
        temp->next = current;
        temp->prev = current->prev;
        current->prev = temp;
        if (current->next != nullptr) {
            current->next->prev = current;
        }
        if (temp->prev != nullptr) {
            temp->prev->next = temp;
        } else {
            head_ = temp;
        }
        current = temp->prev;
        if (current != nullptr) {
            temp = current->next;
            if (temp != nullptr) {
                temp = temp->next;
            }
        } else {
            temp = nullptr;
        }
    }
}



template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
    ListNode* current = startPoint;
    ListNode* next = nullptr;

    while (current != nullptr && current != endPoint->next) {
        next = current->next;
        current->next = current->prev;
        current->prev = next;
        current = next;
    }

    ListNode* temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;
}



template <typename T>
void List<T>::reverseNth(int n) {
    if (head_ == nullptr || n <= 1) return;

    ListNode* start = head_;
    ListNode* end = head_;

    // Move 'end' pointer 'n' steps forward or until end of list
    for (int i = 0; i < n - 1 && end != nullptr; ++i) {
        end = end->next;
    }

    // Reverse the first 'n' elements
    reverse(start, end);

    // Update head_ if it's the first block
    head_ = end;

    // Connect the current end to the next block's start
    if (end != nullptr) {
        end->prev->next = end->next;
        if (end->next != nullptr) {
            end->next->prev = end->prev;
        }
    }
}




template <typename T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  ListNode* mergedHead = nullptr;
  ListNode* mergedTail = nullptr;
  ListNode* currentFirst = first;
  ListNode* currentSecond = second;

  while (currentFirst != nullptr && currentSecond != nullptr) {
      if (currentFirst->data < currentSecond->data) {
          if (mergedHead == nullptr) {
              mergedHead = currentFirst;
              mergedTail = currentFirst;
          } else {
              mergedTail->next = currentFirst;
              currentFirst->prev = mergedTail;
              mergedTail = currentFirst;
          }
          currentFirst = currentFirst->next;
      } else {
          if (mergedHead == nullptr) {
              mergedHead = currentSecond;
              mergedTail = currentSecond;
          } else {
              mergedTail->next = currentSecond;
              currentSecond->prev = mergedTail;
              mergedTail = currentSecond;
          }
          currentSecond = currentSecond->next;
      }
  }

  if (currentFirst != nullptr) {
      mergedTail->next = currentFirst;
      currentFirst->prev = mergedTail;
  }

  if (currentSecond != nullptr) {
      mergedTail->next = currentSecond;
      currentSecond->prev = mergedTail;
  }

  return mergedHead;
} // Completed: Helper function to merge two sorted and independent sequences of linked memory

template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
  if (chainLength <= 1 || start == nullptr) return start;

  ListNode* middle = start;
  for (int i = 0; i < chainLength / 2; i++) {
      middle = middle->next;
  }

  ListNode* secondHalf = middle->prev->next;
  middle->prev->next = nullptr;
  secondHalf->prev = nullptr;

  ListNode* sortedFirstHalf = mergesort(start, chainLength / 2);
  ListNode* sortedSecondHalf = mergesort(secondHalf, chainLength - chainLength / 2);

  return merge(sortedFirstHalf, sortedSecondHalf);
} // Completed: Sorts a chain of linked memory given a start node and a size

template <typename T>
void List<T>::insertFront(const T& ndata) {
  ListNode* newNode = new ListNode(ndata);
  newNode->next = head_;
  newNode->prev = nullptr;
  
  if (head_ != nullptr) {
    head_->prev = newNode;
  } else {
    tail_ = newNode;
  }
  head_ = newNode;

  length_++;
} // Completed: Inserts a new node at the front of the List

template <typename T>
void List<T>::mergeWith(List<T>& otherList) {
    if (otherList.empty()) return;

    if (empty()) {
        head_ = otherList.head_;
        tail_ = otherList.tail_;
        length_ = otherList.length_;
    } else {
        head_ = merge(head_, otherList.head_);
        tail_ = head_;
        while (tail_->next != nullptr)
            tail_ = tail_->next;
        length_ += otherList.length_;
    }

    otherList.head_ = nullptr;
    otherList.tail_ = nullptr;
    otherList.length_ = 0;
} // Completed: Merges the given sorted list into the current sorted list

template <typename T>
void List<T>::reverse() {
    if (head_ == nullptr || head_->next == nullptr) return;

    ListNode* prev = nullptr;
    ListNode* current = head_;
    ListNode* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        current->prev = next; // Corrected to current->prev = prev;
        prev = current;
        current = next;
    }

    head_ = prev;
}