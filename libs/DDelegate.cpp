#include "DDelegateAction.cpp"
#include "DLinkedList.cpp"


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
		actionList->Empty(true);
		delete actionList;
	}

	DDelegate<Return, Params...>(DDelegate<Return, Params...>& original); // TODO
	DDelegate operator=(DDelegate<Return, Params...>& original); // TODO

	/// <summary>
	/// Fires all subscribed function. Does not handle the returned value, may cause memory leak. If that happens, use Fire() instead
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
	/// Fires all functions with specified ID. Does not handle the returned value, may cause memory leak. If that happens, use Fire() instead
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
				Return r = actionList->currentElement->data->Fire(p...);				
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
		Return* retArray = (Return*)calloc(actionList->Count(), sizeof(Return));
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
		Return* retArray = (Return*)calloc(actionList->Count(), sizeof(Return));
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
			if (functionPointer == actionList->currentElement->data->functionPointer)
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
			if (ID == actionList->currentElement->data.ID)
			{
				actionList->RemoveCurrent();
			}
		}
	}

	/// <summary>
	/// Unsubscribes every delegated function
	/// </summary>
	void UnsubscribeAll()
	{
		actionList->Empty(true);
	}


	DLinkedList<DDelegateAction<Return, Params...>*>* actionList;



private:
};


template <class ...Params>
class DDelegate<void, Params...>
{
public:

	DDelegate()
	{
		actionList = new DLinkedList<DDelegateAction<void, Params...>*>();
	}
	~DDelegate()
	{
		actionList->Empty(true);
		delete actionList;
	}
	
	DDelegate<Return, Params...>(DDelegate<void, Params...>& original); // TODO
	DDelegate operator=(DDelegate<void, Params...>& original); // TODO


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
	bool Subscribe(void(*functionPointer)(Params...))
	{
		DDelegateAction<void, Params...>* tmp = new DDelegateAction<void, Params...>(functionPointer);
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
	bool Subscribe(void(*functionPointer)(Params...), int id)
	{
		DDelegateAction<void, Params...>* tmp = new DDelegateAction<void, Params...>(functionPointer, id);
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
	void Unsubrscribe(void(*functionPointer)(Params...))
	{
		for (int i = actionList->Count() - 1; i >= 0; i--)
		{
			actionList->SeekToIndex(i);
			if (functionPointer == actionList->currentElement->data->functionPointer)
			{
				delete actionList->currentElement->data;
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
				delete actionList->currentElement->data;
				actionList->RemoveCurrent();
			}
		}
	}

	DLinkedList<DDelegateAction<void, Params...>*>* actionList;
private:
};

///// <summary>
///// Delegate event handler
///// </summary>
///// <typeparam name="Return">Type of the function (void, int, char...)</typeparam>
///// <typeparam name="...Params">Flexible number of function parameter types</typeparam>
//template <class Return, class ...Params>
//class DDelegate <Return*, Params...>
//{
//public:
//
//	DDelegate()
//	{
//		actionList = new DLinkedList<DDelegateAction<Return, Params...>*>();
//	}
//	~DDelegate()
//	{
//		delete actionList;
//	}
//	DDelegate(DDelegate& original)
//	{
//
//	} // TODO
//
//	/// <summary>
//	/// Fires all subscribed function
//	/// </summary>
//	/// <param name="...p">Arguments for every function to use</param>
//	void FireAllWithoutReturn(Params... p)
//	{
//
//		for (int i = 0; i < actionList->Count(); i++)
//		{
//			actionList->SeekToIndex(i);
//			Return r = actionList->currentElement->data.Fire(p...);
//			delete r;
//		}
//		actionList->SeekToIndex(0);
//	}
//
//	/// <summary>
//	/// Fires all functions with specified ID
//	/// </summary>
//	/// <param name="...p">Arguments for every function to use</param>
//	/// <param name="ID">ID filter</param>
//	void FireAllWithoutReturn(Params... p, int ID)
//	{
//		for (int i = 0; i < actionList->Count(); i++)
//		{
//			actionList->SeekToIndex(i);
//			if (actionList->currentElement->data->ID == ID)
//			{
//				Return r = actionList->currentElement->data->Fire(p...);
//				delete r;
//				
//			}
//		}
//		actionList->SeekToIndex(0);
//	}
//
//
//	/// <summary>
//	/// Fires all function and returns their values in an array
//	/// </summary>
//	/// <param name="...p">Parameters for every function to use</param>
//	/// <returns>The reurned value of each function</returns>
//	Return* FireAll(Params... p)
//	{
//		Return* retArray = (Return*)calloc(actionList->Count(), sizeof(Return*));
//		for (int i = 0; i < actionList->Count(); i++)
//		{
//			actionList->SeekToIndex(i);
//			retArray[i] = actionList->currentElement->data->Fire(p...);
//
//		}
//		actionList->SeekToIndex(0);
//		return retArray;
//	}
//
//	/// <summary>
//	/// Fires all function with specified ID and returns their values in an array
//	/// </summary>
//	/// <param name="...p">Parameters for every function to use</param>
//	/// <param name="ID">ID filter</param>
//	/// <returns>The reurned value of each function</returns>
//	Return* FireAll(Params... p, int ID)
//	{
//		Return* retArray = (Return*)calloc(actionList->Count(), sizeof(Return*));
//		for (int i = 0; i < actionList->Count(); i++)
//		{
//			actionList->SeekToIndex(i);
//			if (actionList->currentElement->data->ID == ID)
//			{
//				retArray[i] = actionList->currentElement->data->Fire(p...);
//			}
//		}
//		actionList->SeekToIndex(0);
//		return retArray;
//	}
//
//
//	/// <summary>
//	/// Subscribes a function to the delegate
//	/// </summary>
//	/// <param name="function">The pointer to the function</param>
//	/// <returns>Whether the subscription was sucessful</returns>
//	bool Subscribe(Return(*function)(Params...))
//	{
//		DDelegateAction<Return, Params...>* tmp = new DDelegateAction<Return, Params...>(function);
//		if (tmp != nullptr)
//		{
//			actionList->PushLast(tmp);
//			return true;
//		}
//		else return false;
//	}
//
//	/// <summary>
//	/// Subscribes a function to the delegate
//	/// </summary>
//	/// <param name="function">The pointer to the function</param>
//	/// <param name="id">ID of function</param>
//	/// <returns>Whether the subscription was sucessful</returns>
//	bool Subscribe(Return(*function)(Params...), int id)
//	{
//		DDelegateAction<Return, Params...>* tmp = new DDelegateAction<Return, Params...>(function, id);
//		if (tmp != nullptr)
//		{
//			actionList->PushLast(tmp);
//			return true;
//		}
//		else return false;
//	}
//
//	/// <summary>
//	/// Unsubrscribes all occurences of the specified function
//	/// </summary>
//	/// <param name="functionPointer">Function to remove from the delegate</param>
//	void Unsubrscribe(Return(*functionPointer)(Params...))
//	{
//		for (int i = actionList->Count() - 1; i >= 0; i--)
//		{
//			actionList->SeekToIndex(i);
//			if (functionPointer == actionList->currentElement->data->functionPointer)
//			{
//				actionList->RemoveCurrent();
//			}
//		}
//	}
//
//	/// <summary>
//	/// Unsubscribes all functions with the specified ID
//	/// </summary>
//	/// <param name="ID">ID filter</param>
//	void Unsubrscribe(int ID)
//	{
//		for (int i = actionList->Count() - 1; i >= 0; i--)
//		{
//			actionList->SeekToIndex(i);
//			if (ID == actionList->currentElement->data.ID)
//			{
//				actionList->RemoveCurrent();
//			}
//		}
//	}
//
//
//	DLinkedList<DDelegateAction<Return, Params...>*>* actionList;
//
//
//private:
//};