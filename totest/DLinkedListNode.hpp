#pragma once

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

	DLinkedListNode();
	explicit DLinkedListNode(T data);
	~DLinkedListNode();

	/// <summary>
	/// Deletes the data
	/// </summary>
	void Delete();

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

	DLinkedListNode();
	DLinkedListNode(T* data);
	~DLinkedListNode();

	/// <summary>
	/// Deletes the data
	/// </summary>
	void Delete();


private:

};

template<class T, int N>
class DLinkedListNode<T[N]>
{
public:
	T data[N];
	DLinkedListNode<T[N]>* nextElement;
	DLinkedListNode<T[N]>* previousElement;

	DLinkedListNode();
	explicit DLinkedListNode(T data[N]);
	~DLinkedListNode();

	/// <summary>
	/// Deletes the data
	/// </summary>
	void Delete();


private:

};

#include "DLinkedListNode.cpp"