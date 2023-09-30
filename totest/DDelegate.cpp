#ifndef DDELEGATE
#define DDELEGATE

#include "DDelegate.hpp"

#include "Platform.cpp"

#ifdef LINUX
#include "DDelegateAction.cpp"
#include "DLinkedList.cpp"
#endif
#ifdef WINDOWS
#include "DDelegateAction.cpp"
#include "DLinkedList.cpp"
#endif


template <class Return, class... Params>
DDelegate<Return, Params...>::DDelegate()
{
	DDelegate<Return, Params...>::actionList = new DLinkedList<DDelegateAction<Return, Params...>*>();
}

template <class Return, class... Params>
DDelegate<Return, Params...>::~DDelegate()
{
	DDelegate<Return, Params...>::actionList->Empty(true);
	delete DDelegate<Return, Params...>::actionList;
}

template <class Return, class... Params>
void DDelegate<Return, Params...>::FireAllWithoutReturn(Params... p)
{

	for (int i = 0; i < DDelegate<Return, Params...>::actionList->Count(); i++)
	{
		actionList->SeekToIndex(i);
		DDelegate<Return, Params...>::actionList->currentElement->data->Fire(p...);
	}
	DDelegate<Return, Params...>::actionList->SeekToIndex(0);
}

template <class Return, class... Params>
void DDelegate<Return, Params...>::FireAllWithoutReturn(Params... p, int ID)
{
	for (int i = 0; i < DDelegate<Return, Params...>::actionList->Count(); i++)
	{
		DDelegate<Return, Params...>::actionList->SeekToIndex(i);
		if (DDelegate<Return, Params...>::actionList->currentElement->data->ID == ID)
		{
			Return r = DDelegate<Return, Params...>::actionList->currentElement->data->Fire(p...);
		}
	}
	DDelegate<Return, Params...>::actionList->SeekToIndex(0);
}

template <class Return, class... Params>
Return* DDelegate<Return, Params...>::FireAll(Params... p)
{
	Return* retArray = (Return*)calloc(DDelegate<Return, Params...>::actionList->Count(), sizeof(Return));
	for (int i = 0; i < DDelegate<Return, Params...>::actionList->Count(); i++)
	{
		DDelegate<Return, Params...>::actionList->SeekToIndex(i);
		retArray[i] = DDelegate<Return, Params...>::actionList->currentElement->data->Fire(p...);

	}
	DDelegate<Return, Params...>::actionList->SeekToIndex(0);
	return retArray;
}

template <class Return, class... Params>
Return* DDelegate<Return, Params...>::FireAll(Params... p, int ID)
{
	Return* retArray = (Return*)calloc(DDelegate<Return, Params...>::actionList->Count(), sizeof(Return));
	for (int i = 0; i < DDelegate<Return, Params...>::actionList->Count(); i++)
	{
		DDelegate<Return, Params...>::actionList->SeekToIndex(i);
		if (DDelegate<Return, Params...>::actionList->currentElement->data->ID == ID)
		{
			retArray[i] = DDelegate<Return, Params...>::actionList->currentElement->data->Fire(p...);
		}
	}
	DDelegate<Return, Params...>::actionList->SeekToIndex(0);
	return retArray;
}

template <class Return, class... Params>
bool DDelegate<Return, Params...>::Subscribe(Return(*function)(Params...))
{
	DDelegateAction<Return, Params...>* tmp = new DDelegateAction<Return, Params...>(function);
	if (tmp != nullptr)
	{
		DDelegate<Return, Params...>::actionList->PushLast(tmp);
		return true;
	}
	else return false;
}

template <class Return, class... Params>
bool DDelegate<Return, Params...>::Subscribe(Return(*function)(Params...), int id)
{
	DDelegateAction<Return, Params...>* tmp = new DDelegateAction<Return, Params...>(function, id);
	if (tmp != nullptr)
	{
		DDelegate<Return, Params...>::actionList->PushLast(tmp);
		return true;
	}
	else return false;
}

template <class Return, class... Params>
void DDelegate<Return, Params...>::Unsubscribe(Return(*functionPointer)(Params...))
{
	for (int i = DDelegate<Return, Params...>::actionList->Count() - 1; i >= 0; i--)
	{
		DDelegate<Return, Params...>::actionList->SeekToIndex(i);
		if (functionPointer == DDelegate<Return, Params...>::actionList->currentElement->data->functionPointer)
		{
			DDelegate<Return, Params...>::actionList->RemoveCurrent();
		}
	}
}

template <class Return, class... Params>
void DDelegate<Return, Params...>::Unsubscribe(int ID)
{
	for (int i = DDelegate<Return, Params...>::actionList->Count() - 1; i >= 0; i--)
	{
		DDelegate<Return, Params...>::actionList->SeekToIndex(i);
		if (ID == DDelegate<Return, Params...>::actionList->currentElement->data.ID)
		{
			DDelegate<Return, Params...>::actionList->RemoveCurrent();
		}
	}
}

template <class Return, class... Params>
void DDelegate<Return, Params...>::UnsubrscribeAll()
{
	for (int i = DDelegate<Return, Params...>::actionList->Count() - 1; i >= 0; i--)
	{
		DDelegate<Return, Params...>::actionList->SeekToIndex(i);
		delete DDelegate<Return, Params...>::actionList->currentElement->data;
		DDelegate<Return, Params...>::actionList->RemoveCurrent();

	}
}




template <class... Params>
DDelegate<void, Params...>::DDelegate()
{
	DDelegate<void, Params...>::actionList = new DLinkedList<DDelegateAction<void, Params...>*>();
}

template <class... Params>
DDelegate<void, Params...>::~DDelegate()
{
	DDelegate<void, Params...>::actionList->Empty(true);
	delete DDelegate<void, Params...>::actionList;
}



template <class... Params>
void DDelegate<void, Params...>::FireAllWithoutReturn(Params... p)
{

	for (int i = 0; i < DDelegate<void, Params...>::actionList->Count(); i++)
	{
		DDelegate<void, Params...>::actionList->SeekToIndex(i);
		DDelegate<void, Params...>::actionList->currentElement->data->Fire(p...);

	}
	DDelegate<void, Params...>::actionList->SeekToIndex(0);
}

template <class... Params>
void DDelegate<void, Params...>::FireAllWithoutReturn(Params... p, int ID)
{
	for (int i = 0; i < DDelegate<void, Params...>::actionList->Count(); i++)
	{
		DDelegate<void, Params...>::actionList->SeekToIndex(i);
		if (DDelegate<void, Params...>::actionList->currentElement->data->ID == ID)
		{
			DDelegate<void, Params...>::actionList->currentElement->data->Fire(p...);
		}
	}
	DDelegate<void, Params...>::actionList->SeekToIndex(0);
}


template <class... Params>
bool DDelegate<void, Params...>::Subscribe(void(*functionPointer)(Params...))
{
	DDelegateAction<void, Params...>* tmp = new DDelegateAction<void, Params...>(functionPointer);
	if (tmp != nullptr)
	{
		DDelegate<void, Params...>::actionList->PushLast(tmp);
		return true;
	}
	else return false;
}


template <class... Params>
bool DDelegate<void, Params...>::Subscribe(void(*functionPointer)(Params...), int id)
{
	DDelegateAction<void, Params...>* tmp = new DDelegateAction<void, Params...>(functionPointer, id);
	if (tmp != nullptr)
	{
		DDelegate<void, Params...>::actionList->PushLast(tmp);
		return true;
	}
	else return false;
}


template <class... Params>
void DDelegate<void, Params...>::Unsubscribe(void(*functionPointer)(Params...))
{
	for (int i = DDelegate<void, Params...>::actionList->Count() - 1; i >= 0; i--)
	{
		DDelegate<void, Params...>::actionList->SeekToIndex(i);
		if (functionPointer == DDelegate<void, Params...>::actionList->currentElement->data->functionPointer)
		{
			delete DDelegate<void, Params...>::actionList->currentElement->data;
			DDelegate<void, Params...>::actionList->RemoveCurrent();
		}
	}
}


template <class... Params>
void DDelegate<void, Params...>::Unsubscribe(int ID)
{
	for (int i = DDelegate<void, Params...>::actionList->Count() - 1; i >= 0; i--)
	{
		DDelegate<void, Params...>::actionList->SeekToIndex(i);
		if (ID == DDelegate<void, Params...>::actionList->currentElement->data->ID)
		{
			delete DDelegate<void, Params...>::actionList->currentElement->data;
			DDelegate<void, Params...>::actionList->RemoveCurrent();
		}
	}
}


template <class... Params>
void DDelegate<void, Params...>::UnsubrscribeAll()
{
	for (int i = DDelegate<void, Params...>::actionList->Count() - 1; i >= 0; i--)
	{
		DDelegate<void, Params...>::actionList->SeekToIndex(i);
		delete DDelegate<void, Params...>::actionList->currentElement->data;
		DDelegate<void, Params...>::actionList->RemoveCurrent();

	}
}


#endif