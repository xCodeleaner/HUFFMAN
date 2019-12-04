#include "pQueue.h"
#include <stdlib.h>
#include <stdio.h>

void initPQueue(pQueue **queue)//** 地址的地址 
{
	//We allocate memory for the priority queue type
	//and we initialize the values of the fields
	(*queue) = (pQueue *) malloc(sizeof(pQueue));//分配空间 
	(*queue)->first = NULL;
	(*queue)->size = 0;
	return;//该句可以不写 
}

void addPQueue(pQueue **queue, TYPE val, unsigned int priority)
{
	//If the queue is full we don't have to add the specified value.
	//We output an error message to the console and return.
	if((*queue)->size == MAX_SZ)
	{
		printf("\nQueue is full.\n");
		return;
	}

	pQueueNode *aux = (pQueueNode *)malloc(sizeof(pQueueNode));
	aux->priority = priority;
	aux->val = val;

	//If the queue is empty we add the first value.
	//We validate twice in case the structure was modified abnormally at runtime (rarely happens).
	if((*queue)->size == 0 || (*queue)->first == NULL)
	{
		aux->next = NULL;
		(*queue)->first = aux;
		(*queue)->size = 1;
		return;
	}
	else
	{
		//If there are already elements in the queue and the priority of the element
		//that we want to add is greater than the priority of the first element,
		//we'll add it in front of the first element.

		//Be careful, here we need the priorities to be in descending order
		if(priority <= (*queue)->first->priority)
		{
			aux->next = (*queue)->first;
			(*queue)->first = aux;
			(*queue)->size ++;
			return;
		}
		else
		{
			//We're looking for a place to fit the element depending on it's priority
			pQueueNode * iterator = (*queue)->first;//与while搭配来实现for的功能 
			while(iterator->next != NULL)
			{
				//Same as before, descending, we place the element at the begining of the
				//sequence with the same priority for efficiency even if
				//it defeats the idea of a queue.
				if(priority <= iterator->next->priority)
				{
					aux->next = iterator->next;
					iterator->next = aux;
					(*queue)->size++;
					return;
				}
				iterator = iterator->next;
			}
			//If we reached the end and we haven't added the element,
			//we'll add it at the end of the queue.
			if(iterator->next == NULL)
			{
					aux->next = NULL;
					iterator->next = aux;
					(*queue)->size ++;
					return;
			}
		}
	}
}

//从队列里面获取数据 
TYPE getPQueue(pQueue **queue)
{
	TYPE returnValue;
	//We get elements from the queue as long as it isn't empty
	if((*queue)->size > 0)
	{
		returnValue = (*queue)->first->val;
		(*queue)->first = (*queue)->first->next;
		(*queue)->size--;
	}
	else
	{
		//If the queue is empty we show an error message.
		//The function will return whatever is in the memory at that time as returnValue.
		//Or you can define an error value depeding on what you choose to store in the queue.
		printf("\nQueue is empty.\n");
	}
	return returnValue;
}
