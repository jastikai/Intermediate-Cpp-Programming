class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    ListNode* position_;

  public:
    ListIterator() : position_(nullptr) { }
    ListIterator(ListNode* x) : position_(x) { }

    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // Move the iterator to the next node
        position_ = position_->next;
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // Create a copy of the current iterator
        ListIterator temp(position_);
        // Move the iterator to the next node
        position_ = position_->next;
        return temp;
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // Move the iterator to the previous node
        position_ = position_->prev;
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // Create a copy of the current iterator
        ListIterator temp(position_);
        // Move the iterator to the previous node
        position_ = position_->prev;
        return temp;
    }

    bool operator!=(const ListIterator& rhs) {
        // Check if the iterators are pointing to different nodes
        return position_ != rhs.position_;
    }

    bool operator==(const ListIterator& rhs) {
        // Check if the iterators are pointing to the same node
        return position_ == rhs.position_;
    }

    const T& operator*() {
        // Return a reference to the data in the current node
        return position_->data;
    }

    const T* operator->() {
        // Return a pointer to the data in the current node
        return &(position_->data);
    }
};
