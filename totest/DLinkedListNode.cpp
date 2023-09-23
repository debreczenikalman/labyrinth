/// <summary>
/// The elements of which the DLinkedList is made up
/// </summary>
/// <typeparam name="T">Any</typeparam>
template <class T>
class DLinkedListNode
{
public:
	/// <summary>
	/// The stored data
	/// </summary>
	T data;

	/// <summary>
	/// The next element in the list
	/// </summary>
	DLinkedListNode<T>* nextElement;

	/// <summary>
	/// The previous element in the list
	/// </summary>
	DLinkedListNode<T>* previousElement;

	/// <summary>
	/// Deletes the data
	/// </summary>
	void Delete()
	{
		// data = NULL;
	}

	/// <summary>
	/// Default constructor
	/// </summary>
	DLinkedListNode(): data(0), nextElement(nullptr), previousElement(nullptr)
	{

	}

	/// <summary>
	/// Constructor with definable data as parameter
	/// </summary>
	/// <param name="data">Data to be stored</param>	
	explicit DLinkedListNode(T data)
	{
		this->data = data;
		nextElement = nullptr;
		previousElement = nullptr;
	}

	~DLinkedListNode()
	{

	}



private:

};


/// <summary>
/// The elements of which the DLinkedList is made up
/// </summary>
/// <typeparam name="T">Any</typeparam>
template <typename T>
class DLinkedListNode<T*>
{
public:
	/// <summary>
	/// The stored data
	/// </summary>
	T data;

	/// <summary>
	/// The next element in the list
	/// </summary>
	DLinkedListNode<T>* nextElement;

	/// <summary>
	/// The previous element in the list
	/// </summary>
	DLinkedListNode<T>* previousElement;

	/// <summary>
	/// Deletes the data
	/// </summary>
	void Delete()
	{
		delete data;
	}

	/// <summary>
	/// Default constructor
	/// </summary>
	DLinkedListNode() : data(0), nextElement(nullptr), previousElement(nullptr)
	{

	}

	/// <summary>
	/// Constructor with definable data as parameter
	/// </summary>
	/// <param name="data">Data to be stored</param>	
	explicit DLinkedListNode(T data)
	{
		this->data = data;
		nextElement = nullptr;
		previousElement = nullptr;
	}

	~DLinkedListNode()
	{

	}


private:

};

/// <summary>
/// The elements of which the DLinkedList is made up
/// </summary>
/// <typeparam name="T">Any</typeparam>
template <typename T, size_t N>
class DLinkedListNode<T[N]>
{
public:
	/// <summary>
	/// The stored data
	/// </summary>
	T data;

	/// <summary>
	/// The next element in the list
	/// </summary>
	DLinkedListNode<T>* nextElement;

	/// <summary>
	/// The previous element in the list
	/// </summary>
	DLinkedListNode<T>* previousElement;

	/// <summary>
	/// Deletes the data
	/// </summary>
	void Delete()
	{
		// delete[] data;
	}

	/// <summary>
	/// Default constructor
	/// </summary>
	DLinkedListNode() : data(0), nextElement(nullptr), previousElement(nullptr)
	{

	}

	/// <summary>
	/// Constructor with definable data as parameter
	/// </summary>
	/// <param name="data">Data to be stored</param>	
	explicit DLinkedListNode(T data): nextElement(nullptr), previousElement(nullptr)
	{
		for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
		{
			this->data[i] = data[i];

		}
	}

	~DLinkedListNode()
	{

	}


private:

};
