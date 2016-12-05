// queue.h -- class template for the linked list implementation of a queue
// note:  use of the copy constructor, overloaded assignment operator, or enqueue function
// can cause an exception to be thrown when heap memory is exhausted

#pragma once

#include <iostream>


// changed the Node struct to handle doubly linked functions
template <class DataType>
struct Node {
	DataType info;

	Node<DataType> *next;
	// added previous pointer to point to previous nodes in list;
	Node<DataType> *previous;
};

template <class DataType>
class Queue
{
public:
	Queue( );
	Queue( const Queue<DataType> & apqueue ); 
	~Queue( );
	Queue<DataType> & operator =( const Queue<DataType> & rqueue );
	void enqueue( const DataType & element );	
	bool dequeue( DataType & deqElement );
	bool peek( DataType & frontElement );  	
	bool isEmpty( ) const;
	void makeEmpty( );
	// added this function to find a particular element with
	bool findElement(const DataType & element);
	DataType returnAtLocation(int elementLocation);
	// added replace function to replace specific elements in the queue
	bool replace(const DataType & toSubstitute);
	void print();
	void reversePrint();
	// created getTotal to get the number of elements in the queue
	int getTotal();
private:
	Node<DataType> *front;
	Node<DataType> *back;
	Node<DataType> header;

	Node<DataType> *current;

	inline void deepCopy( const Queue<DataType> & original );

	// added number to keep track of how many elements in the queue
	int numElements;
};

template<class DataType>
inline Queue<DataType>::Queue()
{
	// added initialization
	front = back = current = &header;
	header.next = NULL;
	header.previous = NULL;
	numElements = 0;
}

template<class DataType>
inline Queue<DataType>::Queue(const Queue<DataType> & apqueue)
{
	// added deepCopy function
	deepCopy(apqueue);
}

template<class DataType>
inline Queue<DataType>::~Queue()
{
	// added makeEmpty
	makeEmpty();
}

// overloaded operator to assign queues
template<class DataType>
inline Queue<DataType>& Queue<DataType>::operator = (const Queue<DataType> & rqueue)
{
	if ((*this) == &rqueue)
		return (*this);

	makeEmpty();
	deepCopy(rqueue);
	return (*this);
}





// 1. enqueue (inserts element to the end)
template<class DataType>
inline void Queue<DataType>::enqueue(const DataType & element)
{
	// added step to check if the queue is of length 4
	if (numElements > 3) {

		DataType toLeave;

		(*this).dequeue(toLeave);

		std::cout << std::endl << "Capacity reached. " << toLeave << " is leaving the SmartPark." << std::endl;

		std::cout << "Current queue: " << std::endl;
		(*this).print();
	}


	// create new node to put the enqueued element in
	Node<DataType> *ptr = new Node<DataType>;

	// place element's data in the new node
	ptr->info = element;

	// point the back-node's next towards the new node
	back->next = ptr;
	
	// set ptr->previous to the node before it
	ptr->previous = back;

	// move the back pointer so that it points to the end node
	back = ptr;

	// added numElements to track elements
	numElements++;
}




// 2. dequeue (removes the front element and provides content)
template<class DataType>
inline bool Queue<DataType>::dequeue(DataType & deqElement)
{
	// early exit if the queue is empty
	if (front == back)
		return false;
	else 
	{
		// create pointer to prepare for node deletion;
		Node<DataType> *ptr = front->next;

		// put ptr->info into location deqElement
		deqElement = ptr->info;

		// move the header node's next around the element to be deleted
		front->next = ptr->next;

		// check if there are more than 2 elements in list
		if (back->previous != &header)
			// if there are more than 2, move the third node's previous to header
			ptr->next->previous = &header;
		// if there was only 2, set back = front
		else back = front;

		// delete the element at front of queue
		delete ptr;

		// added numElements
		numElements--;

		// upon success
		return true;
	}
}


// 5. peek (provides the element sitting at the top/front, but does not remove)
template<class DataType>
inline bool Queue<DataType>::peek(DataType & frontElement)
{
	// early exit if list is empty
	if (front == back) return false;
	else 
	{
		// put data in front node in frontElement's location
		frontElement = front->next->info;

		// upon success
		return true;
	}
}

// 3. isEmpty (checks whether the Queue is empty or not)
template<class DataType>
inline bool Queue<DataType>::isEmpty() const
{
	if (front == back) return true;
	else return false;
}


// 4. makeEmpty dequeues the entire queue
template<class DataType>
inline void Queue<DataType>::makeEmpty()
{
	// early exit if the list is already empty
	if (front == back)
		std::cout << "The list is already empty." << std::endl;

	else
	{	
		// loop to delete nodes
		do 
		{
			// temp pointer to delete nodes with
			Node<DataType> *ptr = back;

			// set the last node to the next-to-last
			back = back->previous;

			// delete the last node
			delete ptr;
		} 
		while (back != &header); // while there are still nodes before back

		// added numElements
		numElements = 0;
	}
}

// findElement is used to facilitate finding a specific element in the queue
template<class DataType>
inline bool Queue<DataType>::findElement(const DataType & element)
{
	current = front;

	do 
	{
		if (current->info == element)
			return true;

		else current = current->next;
	
	} while (current != back);

	// if not found in loop
	return false;
}

// added function to return info at a particular location for use in the printTable function
template<class DataType>
inline DataType Queue<DataType>::returnAtLocation(int elementLocation)
{
	current = front;

	// iterate through loop to the requested element's location
	for (int i = 0; i > elementLocation; i++)
		current = current->next;

	return current->info;
}

// created replace function to replace info at a particular element, 
// TODO figure out if there's a better way than to just use find again
template<class DataType>
inline bool Queue<DataType>::replace(const DataType & toSubstitute)
{
    (*this).enqueue(toSubstitute);
	
	//current = front;

    //do
    //{
	//	if (current->info == element)
	//    	current->info = toSubstitute;
	//	return true;

	//	else current = current->next;

    //} while (current != back);

    //return false;
}

// 6. print (prints all the elements from front to the end)
template<class DataType>
inline void Queue<DataType>::print()
{
	// early exit if the list is already empty
	if (front == back)
		std::cout << "The list is empty." << std::endl;

	else 
	{
		// set current to the first node
		current = front->next;

		// loop to print nodes
		while (current != back) 
		{
			std::cout << current->info << " -> ";
			// once printed, move current to the next node
			current = current->next;
		}

		// when there isn't a "next" left, print the last node
		std::cout << current->info << std::endl;
	}
}

// 7. reversePrint(prints all the elements from end to the front with the help of back
// pointers inside your nodes)
template<class DataType>
inline void Queue<DataType>::reversePrint()
{
	// early exit if the list is already empty
	if (front == back)
		std::cout << "The list is empty." << std::endl;

	else 
	{
		// set current to the last node
		current = back;

		// loop to print nodes
		// while (current->previous != NULL)
		// this loop has the runtime error problem, switched with this
		while (current != front)
		{
			std::cout << current->info << std::endl;
			// once printed, move current to the previous node
			current = current->previous;
		}

		// the two lines below aren't necessary anymore
		// when there isn't a "previous" left, print the first node
		// std::cout << current->info << std::endl;
	}
}

template<class DataType>
inline int Queue<DataType>::getTotal()
{
	return numElements;
}

template<class DataType>
inline void Queue<DataType>::deepCopy(const Queue<DataType>& original)
{
	// TODO make deepCopy function
}
