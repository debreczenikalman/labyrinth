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
/// <typeparam name="T*">Pointer type</typeparam>
template <typename T>
class DLinkedListNode<T*>
{
public:
	/// <summary>
	/// The stored data
	/// </summary>
	T* data;

	/// <summary>
	/// The next element in the list
	/// </summary>
	DLinkedListNode<T*>* nextElement;

	/// <summary>
	/// The previous element in the list
	/// </summary>
	DLinkedListNode<T*>* previousElement;

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
	explicit DLinkedListNode(T* data)
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
/// <typeparam name="T">Array</typeparam>
/// <typeparam name="N">Array length</typeparam>
template<class T, size_t N>
class DLinkedListNode<T[N]>
{
public:
	/// <summary>
	/// The stored data
	/// </summary>
	T data[N];

	/// <summary>
	/// The next element in the list
	/// </summary>
	DLinkedListNode<T[N]>* nextElement;

	/// <summary>
	/// The previous element in the list
	/// </summary>
	DLinkedListNode<T[N]>* previousElement;

	/// <summary>
	/// Deletes the data
	/// </summary>
	void Delete()
	{
		for (int i = 0; i < N; i++)
		{
			data[i] = 0;
		}
	}

	/// <summary>
	/// Default constructor
	/// </summary>
	DLinkedListNode() : nextElement(nullptr), previousElement(nullptr)
	{
		for (int i = 0; i < N; i++)
		{
			data[i] = 0;
		}
	}

	/// <summary>
	/// Constructor with definable data as parameter
	/// </summary>
	/// <param name="data">Data to be stored</param>	
	explicit DLinkedListNode(T data[N]) : nextElement(nullptr), previousElement(nullptr)
	{
		for (int i = 0; i < N; i++)
		{
			this->data[i] = data[i];

		}
	}

	~DLinkedListNode()
	{

	}


private:

};
