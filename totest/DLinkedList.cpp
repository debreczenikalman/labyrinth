/// <summary>
/// The elements of which the DLinkedList is made up
/// </summary>
/// <typeparam name="T">Any</typeparam>
template <class T>
class LinkedListNode
{
public:
	/// <summary>
	/// The stored data
	/// </summary>
	T data;

	/// <summary>
	/// The next element in the list
	/// </summary>
	LinkedListNode<T>* nextElement;

	/// <summary>
	/// The previous element in the list
	/// </summary>
	LinkedListNode<T>* previousElement;

	/// <summary>
	/// Default constructor
	/// </summary>
	LinkedListNode()
	{
		data = 0;
		nextElement = nullptr;
		previousElement = nullptr;
	}

	/// <summary>
	/// Constructor with definable data as parameter
	/// </summary>
	/// <param name="data">Data to be stored</param>	
	LinkedListNode(T data)
	{
		this->data = data;
		nextElement = nullptr;
		previousElement = nullptr;
	}

	~LinkedListNode()
	{

	}

private:

};

/// <summary>
/// Two way linked list
/// </summary>
/// <typeparam name="T">Any</typeparam>
template<class T>
class DLinkedList
{

public:

	/// <summary>
	/// The first element of the linked list
	/// </summary>
	LinkedListNode<T>* firstElement;

	/// <summary>
	/// The last element of the list
	/// </summary>
	LinkedListNode<T>* lastElement;

	/// <summary>
	/// The currently active element of the list
	/// </summary>
	LinkedListNode<T>* currentElement;

	/// <summary>
	/// Constructor
	/// </summary>
	DLinkedList()
	{

	}



	/// <summary>
	/// Count of the elements in the list
	/// </summary>
	/// <returns>Count of the elements in the list</returns>
	int Count()
	{
		return count;
	}

	/// <summary>
	/// The index of the currently active node
	/// </summary>
	/// <returns>The index of the currently active node</returns>
	int CurrentIndex()
	{
		return currentIndex;
	}

	/// <summary>
	/// Seeks to the specified index in the list, making the nth element active
	/// </summary>
	/// <param name="newIndex">The index to seek to</param>
	void SeekToIndex(unsigned int newIndex)
	{
		if (newIndex < 0 || newIndex >= count)
		{
			return;
		}
		if (currentIndex == newIndex)
		{
			return;
		}
		else
		{
			if (currentIndex > newIndex)
			{
				if (currentIndex - newIndex > newIndex)
				{
					currentElement = firstElement;
					currentIndex = 0;
					for (int i = 0; i < newIndex; i++)
					{
						StepForward();
					}
				}
				else
				{
					int steps = currentIndex - newIndex;
					for (int i = 0; i < steps; i++)
					{
						StepBackward();
					}
				}
			}
			else
			{
				if (newIndex - currentIndex > count - newIndex)
				{
					currentElement = lastElement;
					currentIndex = count - 1;
					for (int i = 0; i < count - 1 - newIndex; i++)
					{
						StepBackward();
					}
				}
				else
				{
					int steps = newIndex - currentIndex;
					for (int i = 0; i < steps; i++)
					{
						StepForward();
					}
				}
			}
		}
		currentIndex = newIndex;
	}

	/// <summary>
	/// Steps to the next element of the list
	/// </summary>
	/// <returns>Whether the step was possible</returns>
	bool StepForward()
	{
		if (currentIndex == count - 1)
		{
			return false;
		}
		else
		{
			currentIndex++;
			currentElement = currentElement->nextElement;
		}
		return true;
	}

	/// <summary>
	/// Steps to the previous element of the list
	/// </summary>
	/// <returns>Whether the step was possible</returns>
	bool StepBackward()
	{
		if (currentIndex == 0)
		{
			return false;
		}
		else
		{
			currentIndex--;
			currentElement = currentElement->previousElement;
		}
		return true;
	}


#if false

	/*LinkedListNode<T>* operator[](int index)
		{
			SeekToIndex(index);
			return currentElement;
		}*/

		/// <summary>
		/// Pushes data to the specified index, moving the rest of the list forward
		/// </summary>
		/// <param name="index">The index of the new element</param>
		/// <param name="data">Data to be stored</param>
		/// <returns>Whether the push was sucessful</returns>
	bool PushAt(int index, T data)
	{
		int revert = currentIndex;
		SeekToIndex(index);
		bool tmp = PushAfter(data);
		SeekToIndex(revert);
		return tmp;

	}
	/// <summary>
	/// Pushes data to the list, before the active element
	/// </summary>
	/// <param name="data">Data to be stored</param>
	/// <returns>Whether the push was sucessful</returns>
	bool Push(T data)
	{
		if (count == 0)
		{
			LinkedListNode<T>* n = new LinkedListNode<T>(data);
			if (n != nullptr)
			{
				firstElement = n;
				currentElement = n;
				lastElement = n;
				currentIndex = 0;
				count = 1;
				return true;
			}
			else return false;
		}
		else
		{
			if (currentIndex == 0)
			{
				LinkedListNode<T>* n = new LinkedListNode<T>(data);
				if (n != nullptr)
				{
					currentElement->previousElement = n;
					n->nextElement = currentElement;

					firstElement = n;

					count++;
					currentIndex++;

					return true;
				}
				else return false;
			}
			else
			{
				LinkedListNode<T>* n = new LinkedListNode<T>(data);
				if (n != nullptr)
				{
					n->nextElement = currentElement;
					n->previousElement = currentElement->previousElement;

					n->previousElement->nextElement = n;
					n->nextElement->previousElement = n;

					count++;
					currentIndex++;

					return true;
				}
				else return false;
			}
		}
	}
	/// <summary>
	/// Reads the data of the given index
	/// </summary>
	/// <param name="index">The index of the requested element</param>
	/// <returns>The data of teh element</returns>
	T GetDataAt(int index)
	{
		int revert = currentIndex;
		SeekToIndex(index);
		T tmp = currentElement->data;
		SeekToIndex(revert);
		return tmp;
	}


	/// <summary>
	/// Pushes data before the current element and remains positioned on the old one
	/// </summary>
	/// <param name="data">Data to be stored</param>
	/// <returns>Whether the push was sucessful</returns>
	bool PushBefore(T data)
	{
		if (count == 0)
		{
			LinkedListNode<T>* n = new LinkedListNode<T>(data);
			if (n != nullptr)
			{
				firstElement = n;
				currentElement = n;
				lastElement = n;
				currentIndex = 0;
				count = 1;
				return true;
			}
			else return false;
		}

		if (currentIndex == 0)
		{
			currentIndex -= 1;
			return PushFirst(data);
		}
		else
		{
			LinkedListNode<T>* n = new LinkedListNode<T>(data);
			if (n != nullptr)
			{
				n->nextElement = currentElement;
				n->previousElement = currentElement->previousElement;

				currentElement->previousElement->nextElement = n;
				currentElement->previousElement = n;

				count++;

				return true;
			}


			else return false;
		}
	}
	/// <summary>
	/// Pushes data after the current element and positions on the new element
	/// </summary>
	/// <param name="data">Data to be stored</param>
	/// <returns>Whether the push was sucessful</returns>
	bool PushAfter(T data)
	{
		if (currentIndex == count - 1 || count == 0)
		{
			currentIndex++;
			return PushLast(data);
		}
		else
		{
			LinkedListNode<T>* n = new LinkedListNode<T>(data);
			if (n != nullptr)
			{
				n->previousElement = currentElement;
				n->nextElement = currentElement->nextElement;

				currentElement->nextElement->previousElement = n;
				currentElement->nextElement = n;

				currentIndex++;
				count++;

				return true;
			}


			else return false;
		}
	}
	/// <summary>
/// Pushes data to the head of the list
/// </summary>
/// <param name="data">Data to be stored</param>
/// <returns>Whether the push was sucessful</returns>
	bool PushFirst(T data)
	{
		if (count == 0)
		{
			LinkedListNode<T>* n = new LinkedListNode<T>(data);
			if (n != nullptr)
			{
				firstElement = n;
				currentElement = n;
				lastElement = n;
				currentIndex = 0;
				count = 1;
				return true;
			}
			else return false;
		}
		else
		{
			LinkedListNode<T>* n = new LinkedListNode<T>(data);
			if (n != nullptr)
			{
				n->nextElement = firstElement;
				firstElement->previousElement = n;

				firstElement = n;

				count++;
				currentIndex++;
			}
			else return false;
		}
	}

	/// <summary>
/// Pushes data to the tail of the list
/// </summary>
/// <param name="data">Data to be stored</param>
/// <returns>Whether the push was sucessful</returns>
	bool PushLast(T data)
	{
		if (count == 0)
		{
			LinkedListNode<T>* n = new LinkedListNode<T>(data);
			if (n != nullptr)
			{
				firstElement = n;
				currentElement = n;
				lastElement = n;
				currentIndex = 0;
				count = 1;
				return true;
			}
			else return false;
		}
		else
		{
			LinkedListNode<T>* n = new LinkedListNode<T>(data);
			if (n != nullptr)
			{
				lastElement->nextElement = n;
				n->previousElement = lastElement;

				lastElement = n;

				count++;
				return true;
			}
			else return false;
		}
	}
#endif // obsolete 

	/// <summary>
	/// Pushes data before the current element
	/// </summary>
	/// <param name="data">Data to be pushed</param>
	/// <returns>If the push was successful or not</returns>
	bool PushBefore(T data)
	{
		if (count <= 0)
		{
			return FirstPush(data);
		}
		else
		{
			if (CurrentIndex() == 0)
			{
				return PushFirst(data);
			}
			else
			{
				LinkedListNode<T>* d = new LinkedListNode<T>(data);
				if (d != nullptr)
				{
					currentElement->previousElement->nextElement = d;
					d->previousElement = currentElement->previousElement;

					d->nextElement = currentElement;
					currentElement->previousElement = d;
					currentIndex++;
					count++;
				}
				else return false;
			}


		}
	}

	/// <summary>
	/// Pushes data after the current element
	/// </summary>
	/// <param name="data">Data to be pushed</param>
	/// <returns>If the push was successful or not</returns>
	bool PushAfter(T data)
	{
		if (count <= 0)
		{
			return FirstPush(data);
		}
		else
		{
			if (currentIndex == count - 1)
			{
				return PushLast(data);
			}
			else
			{
				LinkedListNode<T>* d = new LinkedListNode<T>(data);
				if (d != nullptr)
				{
					currentElement->nextElement->previousElement = d;
					d->nextElement = currentElement->nextElement;

					d->previousElement = currentElement;
					currentElement->nextElement = d;

					count++;
				}
				else return false;
			}
		}
	}

	/// <summary>
	/// Pushes data to the beginning of the list
	/// </summary>
	/// <param name="data">Data to be pushed</param>
	/// <returns>If the push was successful or not</returns>
	bool PushFirst(T data)
	{
		if (count <= 0)
		{
			return FirstPush(data);
		}
		else
		{
			LinkedListNode<T>* d = new LinkedListNode<T>(data);
			if (d != nullptr)
			{
				firstElement->previousElement = d;
				d->nextElement = firstElement;

				firstElement = d;
				count++;
				currentIndex++;
				return true;
			}
			else return false;
		}
	}

	/// <summary>
	/// Pushes data to the end of the list
	/// </summary>
	/// <param name="data">Data to be pushed</param>
	/// <returns>If the push was successful or not</returns>
	bool PushLast(T data)
	{
		if (count <= 0)
		{
			return FirstPush(data);
		}
		else
		{
			LinkedListNode<T>* d = new LinkedListNode<T>(data);
			if (d != nullptr)
			{
				lastElement->nextElement = d;
				d->previousElement = lastElement;
				lastElement = d;
				count++;
				return true;
			}
			else return false;
		}
	}

	/// <summary>
	/// Removes the element at the specified index
	/// </summary>
	/// <param name="index">The index of the element</param>
	void RemoveAt(int index)
	{
		int revert = currentIndex;
		if (index < revert)
		{
			revert--;
		}
		SeekToIndex(index);
		if (index == 0) // first element
		{
			currentElement = currentElement->nextElement;
			delete (firstElement);
			firstElement = currentElement;
			currentElement->previousElement = nullptr;
		}
		else if (index == count - 1) // last element
		{
			currentElement = currentElement->previousElement;
			delete lastElement;
			lastElement = currentElement;
			currentElement->nextElement = nullptr;
			currentIndex--;
		}
		else // Any in between
		{
			currentElement = currentElement->previousElement;
			currentElement->nextElement = currentElement->nextElement->nextElement;
			delete (currentElement->nextElement->previousElement);
			currentElement->nextElement->previousElement = currentElement;
		}
		count--;
		SeekToIndex(revert);
	} //TODO: break

	/// <summary>
	/// Removes current element and moves items forward
	/// </summary>
	void RemoveCurrent()
	{
		if (count == 1)
		{
			delete(currentElement);
			firstElement = nullptr;
			lastElement = nullptr;
			currentElement = nullptr;
			currentIndex = 0;
			count = 0;
		}
		else if (currentIndex == 0)
		{
			currentElement = currentElement->nextElement;
			delete firstElement;
			firstElement = currentElement;
			currentElement->previousElement = nullptr;
			count--;
		}
		else if (currentIndex == count - 1)
		{
			currentElement = currentElement->previousElement;
			delete lastElement;
			lastElement = currentElement;
			currentElement->nextElement = nullptr;
			count--;
			currentIndex--;
		}
		else
		{
			LinkedListNode<T>* tmp = currentElement;
			currentElement->previousElement->nextElement = currentElement->nextElement;
			currentElement->nextElement->previousElement = currentElement->previousElement;
			currentElement = currentElement->nextElement;
			delete tmp;
			count--;
		}
	}

	/// <summary>
	/// Swaps two elements' stored data
	/// </summary>
	/// <param name="leftIndex">The first element of swap</param>
	/// <param name="rightIndex">The second element of swap</param>
	void Swap(int leftIndex, int rightIndex)
	{
		int revert = currentIndex;
		SeekToIndex(leftIndex);
		T left = currentElement->data;
		SeekToIndex(rightIndex);
		T right = currentElement->data;
		currentElement->data = left;
		SeekToIndex(leftIndex);
		currentElement->data = right;
		SeekToIndex(revert);
	}


	/// <summary>
	/// Empties the list and sets it up to be reused
	/// </summary>
	void Empty(bool deleteItem = false)
	{
		LinkedListNode<T>* tmp;
		while (firstElement != nullptr)
		{
			tmp = firstElement->nextElement;
			if (deleteItem)
			{
				delete(firstElement->data);
			}
			delete(firstElement);
			firstElement = tmp;
		}
		firstElement = nullptr;
		lastElement = nullptr;
		currentElement = nullptr;
		currentIndex = 0;
		count = 0;
	}

	~DLinkedList()
	{
		Empty();
	}

private:
	unsigned int currentIndex;
	unsigned int count;

	bool FirstPush(T data)
	{
		LinkedListNode<T>* d = new LinkedListNode<T>(data);
		if (d != nullptr)
		{
			firstElement = d;
			lastElement = d;
			currentElement = d;
			currentIndex = 0;
			count = 1;

			return true;
		}
		else return false;
	}

};