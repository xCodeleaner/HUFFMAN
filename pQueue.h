#pragma once 
#ifndef _PQUEUE_H//头文件的规范定义方式 _filename_H 
#define _PQUEUE_H

#include "huffman.h"

//We modify the data type to hold pointers to Huffman tree nodes
#define TYPE htNode * //宏定义 

#define MAX_SZ 256

typedef struct _pQueueNode
{
	TYPE val;//TYPE就是宏定义类型 
	unsigned int priority;
	struct _pQueueNode *next;
}pQueueNode;

typedef struct _pQueue
{
	unsigned int size;
	pQueueNode *first;
}pQueue;

void initPQueue(pQueue **queue);
void addPQueue(pQueue **queue, TYPE val, unsigned int priority);
TYPE getPQueue(pQueue **queue);

#endif
