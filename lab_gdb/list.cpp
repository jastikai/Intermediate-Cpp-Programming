/**
 * @file list.cpp
 * Singly Linked List (lab_gdb).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 *
 * @author Veer Dedhia
 * @date (modified) Spring 2014
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template<typename T>
void List<T>::clear() {
    while (head != nullptr) {
        ListNode* temp = head;     // Store the current head
        head = head->next;         // Move the head to the next node
        delete temp;               // Delete the stored node
    }
    length = 0;                    // Reset the size of the list
}


/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template<typename T>
void List<T>::insertFront(const T& elem) {
    ListNode* newNode = new ListNode(elem);  // Create a new node with the given element
    newNode->next = head;                    // Set the next pointer of the new node to the current head
    head = newNode;                          // Update the head to point to the new node
    length++;                                // Increment the size of the list
}


template <class T>
void List<T>::insertBack(const T &ndata)
{
    // Create a new node with the given data
    ListNode *newNode = new ListNode(ndata);

    // If the list is empty, set the new node as the head
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        // Traverse to the end of the list
        ListNode *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        // Set the next pointer of the last node to the new node
        temp->next = newNode;
    }

    // Increment the length of the list
    length++;
}



template <class T>
void List<T>::reverse()
{
    if (head != nullptr) {
        head = reverse(head, nullptr, length);
    }
}

template <class T>
typename List<T>::ListNode* List<T>::reverse(ListNode* curr, ListNode* prev, int len)
{
    if (curr == nullptr)
    {
        // Base case: we have reached the end of the list
        // Return the previous node, which is now the new head of the reversed list
        return prev;
    }

    // Recursive case: continue reversing the rest of the list
    // Store the next node in the list
    ListNode* nextNode = curr->next;
    // Set the next pointer of the current node to the previous node
    curr->next = prev;
    // Recursively call reverse on the next node with the current node as the previous node
    // and decrement the length of the remaining list
    return reverse(nextNode, curr, len - 1);
}



/**
 * Shuffles the current list by applying a perfect shuffle once. This entails
 * splitting the list in half, then interleaving the two halves.
 * For example:
 * start : < 1, 2, 3, 4, 5 >
 * split : < 1, 2, 3 >    < 4, 5 >
 * final : < 1, 4, 2, 5, 3 >
 */
template <class T>
void List<T>::shuffle()
{
    // Check if the list has at least two nodes
    if (length < 2)
        return;

    // Find the midpoint of the list
    ListNode* slow = head;
    ListNode* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // slow points to the midpoint or the first node of the second half
    ListNode* secondHalf = slow->next;
    slow->next = nullptr; // Split the list into two halves

    // Interleave the two halves
    ListNode* current = head;
    while (secondHalf != nullptr) {
        ListNode* nextFirstHalf = current->next;
        ListNode* nextSecondHalf = secondHalf->next;

        current->next = secondHalf;
        secondHalf->next = nextFirstHalf;

        current = nextFirstHalf;
        secondHalf = nextSecondHalf;
    }
}



