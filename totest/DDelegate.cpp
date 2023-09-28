#pragma once

#include "DDelegate.hpp"
#include "DDelegateAction.hpp"

#include "DLinkedList.hpp"


template <class Return, class... Params>
DDelegate<Return, Params...>::DDelegate()
{
	actionList = new DLinkedList<DDelegateAction<Return, Params...>*>();
}

template <class Return, class... Params>
DDelegate<Return, Params...>::~DDelegate()
{
	actionList->Empty(true);
	delete actionList;
}

template <class Return, class... Params>
void DDelegate<Return, Params...>::FireAllWithoutReturn(Params... p)
{

	for (int i = 0; i < actionList->Count(); i++)
	{
		actionList->SeekToIndex(i);
		actionList->currentElement->data->Fire(p...);
	}
	actionList->SeekToIndex(0);
}

template <class Return, class... Params>
void DDelegate<Return, Params...>::FireAllWithoutReturn(Params... p, int ID)
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

template <class Return, class... Params>
Return* DDelegate<Return, Params...>::FireAll(Params... p)
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

template <class Return, class... Params>
Return* DDelegate<Return, Params...>::FireAll(Params... p, int ID)
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

template <class Return, class... Params>
bool DDelegate<Return, Params...>::Subscribe(Return(*function)(Params...))
{
	DDelegateAction<Return, Params...>* tmp = new DDelegateAction<Return, Params...>(function);
	if (tmp != nullptr)
	{
		actionList->PushLast(tmp);
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
		actionList->PushLast(tmp);
		return true;
	}
	else return false;
}

template <class Return, class... Params>
void DDelegate<Return, Params...>::Unsubscribe(Return(*functionPointer)(Params...))
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

template <class Return, class... Params>
void DDelegate<Return, Params...>::Unsubscribe(int ID)
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

template <class Return, class... Params>
void DDelegate<Return, Params...>::UnsubrscribeAll()
{
	for (int i = actionList->Count() - 1; i >= 0; i--)
	{
		actionList->SeekToIndex(i);
		delete actionList->currentElement->data;
		actionList->RemoveCurrent();

	}
}




template <class... Params>
DDelegate<void, Params...>::DDelegate()
{
	actionList = new DLinkedList<DDelegateAction<void, Params...>*>();
}

template <class... Params>
DDelegate<void, Params...>::~DDelegate()
{
	actionList->Empty(true);
	delete actionList;
}



template <class... Params>
void DDelegate<void, Params...>::FireAllWithoutReturn(Params... p)
{

	for (int i = 0; i < actionList->Count(); i++)
	{
		actionList->SeekToIndex(i);
		actionList->currentElement->data->Fire(p...);

	}
	actionList->SeekToIndex(0);
}

template <class... Params>
void DDelegate<void, Params...>::FireAllWithoutReturn(Params... p, int ID)
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


template <class... Params>
bool DDelegate<void, Params...>::Subscribe(void(*functionPointer)(Params...))
{
	DDelegateAction<void, Params...>* tmp = new DDelegateAction<void, Params...>(functionPointer);
	if (tmp != nullptr)
	{
		actionList->PushLast(tmp);
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
		actionList->PushLast(tmp);
		return true;
	}
	else return false;
}


template <class... Params>
void DDelegate<void, Params...>::Unsubscribe(void(*functionPointer)(Params...))
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


template <class... Params>
void DDelegate<void, Params...>::Unsubscribe(int ID)
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


template <class... Params>
void DDelegate<void, Params...>::UnsubrscribeAll()
{
	for (int i = actionList->Count() - 1; i >= 0; i--)
	{
		actionList->SeekToIndex(i);
		delete actionList->currentElement->data;
		actionList->RemoveCurrent();

	}
}

