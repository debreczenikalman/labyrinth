#include "DDelegateAction.h"
#include "DLinkedList.cpp"
#include <stdlib.h>



/// <summary>
/// Delegate event handler
/// </summary>
/// <typeparam name="Return">Type of the function (void, int, char...)</typeparam>
/// <typeparam name="...Params">Flexible number of function parameter types</typeparam>
template <class Return, class... Params>
class DDelegate
{
public:

	DDelegate()
	{
		actionList = new DLinkedList<DDelegateAction<Return, Params...>*>();
	}
	~DDelegate()
	{
		delete actionList;
	}

	/// <summary>
	/// Fires all subscribed function
	/// </summary>
	/// <param name="...p">Arguments for every function to use</param>
	void FireAllWithoutReturn(Params... p)
	{

		for (int i = 0; i < actionList->Count(); i++)
		{
			actionList->SeekToIndex(i);
			Return r = actionList->currentElement->data->Fire(p...);
			if (is_pointer<r>())
			{
				delete r;
			}
		}
		actionList->SeekToIndex(0);
	}

	/// <summary>
	/// Fires all functions with specified ID
	/// </summary>
	/// <param name="...p">Arguments for every function to use</param>
	/// <param name="ID">ID filter</param>
	void FireAllWithoutReturns(Params... p, int ID)
	{
		for (int i = 0; i < actionList->Count(); i++)
		{
			actionList->SeekToIndex(i);
			if (actionList->currentElement->data->ID == ID)
			{
				Return r = actionList->currentElement->data->Fire(p...);
				if (is_pointer<r>())
				{
					delete r;
				}
			}
		}
		actionList->SeekToIndex(0);
	}


	/// <summary>
	/// Fires all function and returns their values in an array
	/// </summary>
	/// <param name="...p">Parameters for every function to use</param>
	/// <returns>The reurned value of each function</returns>
	Return* FireAll(Params... p)
	{
		Return* retArray = (Return*)calloc(actionList->Count(), sizeof(Return*));
		for (int i = 0; i < actionList->Count(); i++)
		{
			actionList->SeekToIndex(i);
			retArray[i] = actionList->currentElement->data->Fire(p...);

		}
		actionList->SeekToIndex(0);
		return retArray;
	}

	/// <summary>
	/// Fires all function with specified ID and returns their values in an array
	/// </summary>
	/// <param name="...p">Parameters for every function to use</param>
	/// <param name="ID">ID filter</param>
	/// <returns>The reurned value of each function</returns>
	Return* FireAll(Params... p, int ID)
	{
		Return* retArray = (Return*)calloc(actionList->Count(), sizeof(Return*));
		for (int i = 0; i < actionList->Count(); i++)
		{
			actionList->SeekToIndex(i);
			if (actionList->currentElement->data->ID == ID)
			{
				retArray[i] = actionList->currentElement->data->Fire(p...);
			}
		}
		actionList->SeekToIndex(0);
		return retArray;
	}


	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(Return(*function)(Params...))
	{
		DDelegateAction<Return, Params...>* tmp = new DDelegateAction<Return, Params...>(function);
		if (tmp != nullptr)
		{
			actionList->PushLast(tmp);
			return true;
		}
		else return false;
	}

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <param name="id">ID of function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(Return(*function)(Params...), int id)
	{
		DDelegateAction<Return, Params...>* tmp = new DDelegateAction<Return, Params...>(function, id);
		if (tmp != nullptr)
		{
			actionList->PushLast(tmp);
			return true;
		}
		else return false;
	}

	/// <summary>
	/// Unsubrscribes all occurences of the specified function
	/// </summary>
	/// <param name="functionPointer">Function to remove from the delegate</param>
	void Unsubrscribe(Return(*functionPointer)(Params...))
	{
		for (int i = actionList->Count() - 1; i >= 0; i--)
		{
			actionList->SeekToIndex(i);
			if (function == actionList->currentElement->data->functionPointer)
			{
				actionList->RemoveCurrent();
			}
		}
	}

	/// <summary>
	/// Unsubscribes all functions with the specified ID
	/// </summary>
	/// <param name="ID">ID filter</param>
	void Unsubrscribe(int ID)
	{
		for (int i = actionList->Count() - 1; i >= 0; i--)
		{
			actionList->SeekToIndex(i);
			if (ID == actionList->currentElement->data->ID)
			{
				actionList->RemoveCurrent();
			}
		}
	}


	DLinkedList<DDelegateAction<Return, Params...>*>* actionList;


#if false
	/// <summary>
	/// Calls every function in subscribe order but deletes their returned value
	/// </summary>
	/// <param name="...p">Parameters for the functions to use</param>
	void FireAllWithoutReturns(Params... p)
	{
		int length = actionList->Count();
		for (int i = 0; i < length; i++)
		{
			(*actionList)[i];
			Return r = actionList->currentElement->data->Fire(p...);
			if (is_pointer<r>())
			{
				delete r;
			}
		}
	}

	/// <summary>
	/// Calls every function in subscribe order
	/// </summary>
	/// <param name="...p">An array of parameters for the functions to use</param>
	void FireAllWithoutReturns(Params...* p, int count)
	{
		int length = actionList->Count();
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < count; j++)
			{
				Return r = ((*actionList)[i])->data->Fire(p[j]...);
				if (is_pointer<r>())
				{
					delete r;
				}
			}
		}
	}

	/// <summary>
	/// Calls every function in subscribe order with specific ID
	/// </summary>
	/// <param name="...p">Parameters for the functions to use</param>
	/// <param name="ID">ID of function to call</param>
	void FireAllWithoutReturns(Params... p, int ID)
	{
		int revert = actionList->CurrentIndex();
		{
			int length = actionList->Count();
			Return* retArray = new Return[length];
			for (int i = 0; i < length; i++)
			{
				actionList->SeekToIndex(i);
				if (actionList->currentElement->data->ID == ID)
				{
					retArray[i] = actionList->currentElement->data->Fire(p...);
				}
			}
			delete[] retArray;
		}
		actionList->SeekToIndex(revert);
	}

	/// <summary>
	/// Calls every function in subscribe order with specific ID
	/// </summary>
	/// <param name="...p">An array of parameters for the functions to use</param>
	/// <param name="ID">ID of function to call</param>
	void FireAllWithoutReturns(Params... p[], int ID)
	{
		int revert = actionList->CurrentIndex();
		{
			int length = actionList->Count();
			Return* retArray = new Return[length];
			for (int i = 0; i < length; i++)
			{
				actionList->SeekToIndex(i);
				if (actionList->currentElement->data->ID == ID)
				{
					retArray[i] = actionList->currentElement->data->Fire(p[i]...);
				}
			}
			delete[] retArray;
		}
		actionList->SeekToIndex(revert);
	}


	/// <summary>
	/// Calls every function in subscribe order
	/// </summary>
	/// <param name="...p">Parameters for the functions to use</param>
	/// <returns>An array of the returned value of the functions</returns>
	Return* FireAll(Params... p)
	{
		int revert = actionList->CurrentIndex();
		{
			int length = actionList->Count();
			Return* retArray = new Return[length];
			for (int i = 0; i < length; i++)
			{
				actionList->SeekToIndex(i);
				retArray[i] = actionList->currentElement->data->Fire(p...);
			}
			actionList->SeekToIndex(revert);
			return retArray;
		}

	}

	/// <summary>
	/// Calls every function in subscribe order
	/// </summary>
	/// <param name="...p">An array of parameters for the functions to use</param>
	/// <returns>An array of the returned value of the functions</returns>
	Return* FireAll(Params... p[])
	{
		int revert = actionList->CurrentIndex();
		{
			int length = actionList->Count();
			Return* retArray = new Return[length];
			for (int i = 0; i < length; i++)
			{
				actionList->SeekToIndex(i);
				retArray[i] = actionList->currentElement->data->Fire(p[i]...);
			}
			actionList->SeekToIndex(revert);
			return retArray;
		}
	}

	/// <summary>
	/// Calls every function in subscribe order  with specific ID
	/// </summary>
	/// <param name="...p">Parameters for the functions to use</param>
	/// <param name="ID">ID of function to call</param>
	/// <returns>An array of the returned value of the functions</returns>
	Return* FireAll(Params... p, int ID)
	{
		int revert = actionList->CurrentIndex();
		{
			int length = actionList->Count();
			Return* retArray = new Return[length];
			for (int i = 0; i < length; i++)
			{
				actionList->SeekToIndex(i);
				if (actionList->currentElement->data->ID == ID)
				{
					retArray[i] = actionList->currentElement->data->Fire(p...);
				}
			}
			return retArray;
		}
	}

	/// <summary>
	/// Calls every function in subscribe order  with specific ID
	/// </summary>
	/// <param name="...p">An array of parameters for the functions to use</param>
	/// <param name="ID">ID of function to call</param>
	/// <returns>An array of the returned value of the functions</returns>
	Return* FireAll(Params... p[], int ID)
	{
		int revert = actionList->CurrentIndex();
		if (typeid(Return) == typeid(void))
		{
			int length = actionList->Count();
			for (int i = 0; i < length; i++)
			{
				if (actionList->currentElement->data->ID == ID)
				{
					actionList->SeekToIndex(i);
					if (actionList->currentElement->data->ID == ID)
					{
						actionList->currentElement->data->Fire(p[i]...);
					}
				}
			}
			return NULL;
		}
		else
		{
			int length = actionList->Count();
			Return* retArray = new Return[length];
			for (int i = 0; i < length; i++)
			{
				actionList->SeekToIndex(i);
				if (actionList->currentElement->data->ID == ID)
				{
					retArray[i] = actionList->currentElement->data->Fire(p[i]...);
				}
			}
			return retArray;
		}
	}


	/// <summary>
	/// Unsubscribes every function that matches the parameter
	/// </summary>
	/// <param name="function">Function to unsubscribe</param>
	void UnSubscribe(Return(*function)(Params...)) // TODO
	{
		int revert = actionList->CurrentIndex();

		// actionList->SeekToIndex(0);

		for (int i = 0; i < actionList->Count(); i++)
		{
			actionList->SeekToIndex(i);
			if (actionList->currentElement->data->functionPointer == function)
			{
				actionList->RemoveCurrent();
				i--;
				revert--;
			}
		}
		if (revert != -1)
		{
			actionList->SeekToIndex(revert);
		}
	}

	/// <summary>
	/// Unsubscribes every function with the same ID as parameter
	/// </summary>
	/// <param name="id">ID to unsubscibe</param>
	void UnSubscribe(int id)
	{
		int revert = actionList->CurrentIndex();

		// actionList->SeekToIndex(0);

		for (int i = 0; i < actionList->Count(); i++)
		{
			actionList->SeekToIndex(i);
			if (actionList->currentElement->data->ID == id)
			{
				actionList->RemoveCurrent();
				i--;
				revert--;
			}
		}
		if (revert != -1)
		{
			actionList->SeekToIndex(revert);
		}
	}


	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(Return(*function)(Params...))
	{
		DDelegateAction<Return, Params...>* tmp = new DDelegateAction<Return, Params...>(function);
		if (tmp != nullptr)
		{
			actionList->PushAfter(tmp);
			return true;
		}
		else return false;
	}

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <param name="id">ID of function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(Return(*function)(Params...), int id)
	{
		DDelegateAction<Return, Params...>* tmp = new DDelegateAction<Return, Params...>(function, id);
		if (tmp != nullptr)
		{
			actionList->PushAfter(tmp);
			return true;
		}
		else return false;
	}


	/// <summary>
	/// Two way linked list that stores the function pointers
	/// </summary>
#endif // Junk
private:
};


template <class... Params>
class DDelegate<void, Params...>
{
public:

	DDelegate()
	{
		actionList = new DLinkedList<DDelegateAction<void, Params...>*>();
	}
	~DDelegate()
	{
		delete actionList;
	}

	/// <summary>
	/// Fires all subscribed function
	/// </summary>
	/// <param name="...p">Arguments for every function to use</param>
	void FireAllWithoutReturn(Params... p)
	{

		for (int i = 0; i < actionList->Count(); i++)
		{
			actionList->SeekToIndex(i);
			actionList->currentElement->data->Fire(p...);
			
		}
		actionList->SeekToIndex(0);
	}

	/// <summary>
	/// Fires all functions with specified ID
	/// </summary>
	/// <param name="...p">Arguments for every function to use</param>
	/// <param name="ID">ID filter</param>
	void FireAllWithoutReturn(Params... p, int ID)
	{
		for (int i = 0; i < actionList->Count(); i++)
		{
			actionList->SeekToIndex(i);
			if (actionList->currentElement->data->ID == ID)
			{
				actionList->currentElement->data->Fire(p...);				
			}
		}
		actionList->SeekToIndex(0);
	}

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(Return(*function)(Params...))
	{
		DDelegateAction<Return, Params...>* tmp = new DDelegateAction<Return, Params...>(function);
		if (tmp != nullptr)
		{
			actionList->PushLast(tmp);
			return true;
		}
		else return false;
	}

	/// <summary>
	/// Subscribes a function to the delegate
	/// </summary>
	/// <param name="function">The pointer to the function</param>
	/// <param name="id">ID of function</param>
	/// <returns>Whether the subscription was sucessful</returns>
	bool Subscribe(Return(*function)(Params...), int id)
	{
		DDelegateAction<Return, Params...>* tmp = new DDelegateAction<Return, Params...>(function, id);
		if (tmp != nullptr)
		{
			actionList->PushLast(tmp);
			return true;
		}
		else return false;
	}

	/// <summary>
	/// Unsubrscribes all occurences of the specified function
	/// </summary>
	/// <param name="functionPointer">Function to remove from the delegate</param>
	void Unsubrscribe(Return(*functionPointer)(Params...))
	{
		for (int i = actionList->Count() - 1; i >= 0; i--)
		{
			actionList->SeekToIndex(i);
			if (function == actionList->currentElement->data->functionPointer)
			{
				actionList->RemoveCurrent();
			}
		}
	}

	/// <summary>
	/// Unsubscribes all functions with the specified ID
	/// </summary>
	/// <param name="ID">ID filter</param>
	void Unsubrscribe(int ID)
	{
		for (int i = actionList->Count() - 1; i >= 0; i--)
		{
			actionList->SeekToIndex(i);
			if (ID == actionList->currentElement->data->ID)
			{
				actionList->RemoveCurrent();
			}
		}
	}

	DLinkedList<DDelegateAction<void, Params...>*>* actionList;
private:
};