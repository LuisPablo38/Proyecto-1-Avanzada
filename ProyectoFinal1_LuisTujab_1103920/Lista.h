#pragma once
#include"Comparator.h"

template <typename T>
class Lista
{
	struct Nodo
	{
		T* item;
		Nodo* next;
		Nodo(T* item)
		{
			this->item = item;
			this->next = nullptr;
		}
	};
	Nodo* head;
	Nodo* tail;
	int size = 0;

public:
	int getSize()
	{
		return this->size;
	}

	bool isEmpty()
	{
		return this->size == 0;
	}

	void add(T* item)
	{
		Nodo* nodo = new Nodo(item);
		if (this->isEmpty())
		{
			this->head = this->tail = nodo;
		}
		else
		{
			this->tail->next = nodo;
			this->tail = this->tail->next;
		}
		this->size++;
	}
	T* get(int index)
	{
		if (index >= this->size || index < 0)
		{
			return nullptr;
		}
		Nodo* iterator = this->head;
		int i = 0;
		while (i < index)
		{
			iterator = iterator->next;
			i++;
		}
		return iterator->item;
	}
	T* remove(int index)
	{
		if (index >= this->size || index < 0)
		{
			return nullptr;
		}
		Nodo** iterator = &this->head;
		Nodo* previous = nullptr;
		int i = 0;
		while (i < index)
		{
			iterator = &(*iterator)->next;
			i++;
		}
		T* item = (*iterator)->item;
		*iterator = (*iterator)->next
			; this->size--;
		if (this->size == index)
		{
			this->tail = previous;
		}
		return item;
	}

	//T* elim(int item)
	//{
	//	Nodo* Lista; 
	//	Nodo* tmp; 
	//	tmp = Lista; 
	//	if (tmp->id == this->id)
	//	{
	//		Lista = Lista->next; 
	//		free(tmp); 
	//	}
	//	else
	//	{
	//		while ((tmp->next)->id != id)
	//		{
	//			tmp = tmp->next;
	//		}
	//		Nodo* tmp2 = tmp->next; 
	//		tmp->next = (tmp->next)->next;
	//		free(tmp2);
	//	}
	//	return Lista;
	//}

	Lista<T>* bubbleSort(Comparator<T>* comparator)
	{
		Nodo** i = &(this->head);

		while (*i != nullptr)
		{
			Nodo** j = &(*i)->next;

			while (*j != nullptr)
			{
				T** itemA = &(*i)->item;
				T** itemB = &(*j)->item; 

				if (comparator->compare(**itemA, **itemB)>0)
				{
					T* aux = *itemA;
					*itemA = *itemB;
					*itemB = aux; 

				}
				j = &(*j)->next; 
			}
			i = &(*i)->next;
		}
		return this; 
	}
};

