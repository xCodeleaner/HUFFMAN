#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "huffman.h"
#include "pQueue.h"

void traverseTree(htNode *treeNode, hlTable **table, int k, char code[256])
{
	//If we reach the end we introduce the code in the table
	if(treeNode->left == NULL && treeNode->right == NULL)
	{
		code[k] = '\0';//结束字符串 
		hlNode *aux = (hlNode *)malloc(sizeof(hlNode));
		aux->code = (char *)malloc(sizeof(char)*(strlen(code)+1));
		strcpy(aux->code,code);
		aux->symbol = treeNode->symbol;
		aux->next = NULL;
		
		if((*table)->first == NULL)
		{
			(*table)->first = aux;
			(*table)->last = aux;
		}
		else
		{
			(*table)->last->next = aux;
			(*table)->last = aux;
		}
		
	}
	/*
	//We concatenate a 1 for each step to the right
	if(treeNode->right != NULL)
	{
		code[k]='1';
		traverseTree(treeNode->right,table,k+1,code);//递归 	
	}
	*/
	//We concatenate a 0 for each step to the left
	if(treeNode->left != NULL)
	{
		code[k]='0';
		traverseTree(treeNode->left,table,k+1,code);//递归 
	}
	
	//We concatenate a 1 for each step to the right
	if(treeNode->right != NULL)
	{
		code[k]='1';
		traverseTree(treeNode->right,table,k+1,code);//递归 	
	}
	
}

hlTable * buildTable(htTree * huffmanTree)
{
	//We initialize the table
	hlTable *table = (hlTable *)malloc(sizeof(hlTable));
	table->first = NULL;
	table->last = NULL;
	
	//Auxiliary variables
	char code[256];
	//k will memories the level on which the traversal is
	int k = 0;

	//We traverse the tree and calculate the codes
	traverseTree(huffmanTree->root,&table,k,code);
	
	//std::cout << table->first->symbol << std::endl; 
	
	return table;
}

 htTree * buildTree(char *inputString)//之所以将传入的字符串转变成指针是为了方便用数组的形式搜索每个字符 
{
	//The array in which we calculate the frequency of the symbols
	//Knowing that there are only 256 posibilities of combining 8 bits
	//(256 ASCII characters)
	int *probability = (int *)malloc(sizeof(int)*256);//probability出现的可能次数 
	
	//We initialize the array（初始化） 
	for(int i=0; i<256; i++)
	{ 
		probability[i]=0;
	}
	
	//We consider the symbol as an array index and we calculate how many times each symbol appears
	//统计待编码的字符串各个字符出现的次数 
	for(int i=0; inputString[i]!='\0'; i++)
	{ 
		probability[(unsigned char)inputString[i]] ++;//对出现的对应字符计次 
	}
	 
	//The queue which will hold the tree nodes
	// pQueue队列的头指针 
	pQueue * huffmanQueue;
	
	//初始化队列 
	initPQueue(&huffmanQueue);//此处传入了存放地址的地址 

	//We create nodes for each symbol in the string
	//填充队列 
	for(int i=0; i<256; i++)
	{ 
		if(probability[i] != 0)
		{
			htNode *aux = (htNode *)malloc(sizeof(htNode));
			aux->left = NULL;
			aux->right = NULL;
			aux->symbol = (char) i;
			
			addPQueue(&huffmanQueue,aux,probability[i]);
		}
	}
	 
	//We free the array because we don't need it anymore
	//填充队列完成后，字母出现次数就没用了，释放空间 
	free(probability);

	//We apply the steps described in the article to build the tree
	//生成赫夫曼树 
	while(huffmanQueue->size != 1)
	{
		int priority = huffmanQueue->first->priority;
		priority += huffmanQueue->first->next->priority;

		htNode *left = getPQueue(&huffmanQueue);
		htNode *right = getPQueue(&huffmanQueue);

		htNode *newNode = (htNode *)malloc(sizeof(htNode));
		newNode->left = left;
		newNode->right = right;

		addPQueue(&huffmanQueue,newNode,priority);
	}

	//We create the tree
	htTree *tree = (htTree *) malloc(sizeof(htTree));

	tree->root = getPQueue(&huffmanQueue);
	
	return tree;
}

void encode(hlTable *table, char *stringToEncode)
{
	hlNode *traversal;
	
	printf("\nEncoding\nInput string : %s\nEncoded string : \n",stringToEncode);

	//For each element of the string traverse the table
	//and once we find the symbol we output the code for it
	for(int i=0; stringToEncode[i]!='\0'; i++)
	{
		traversal = table->first;
		while(traversal->symbol != stringToEncode[i])
			traversal = traversal->next;
		printf("%s",traversal->code);
	}

	printf("\n");
}

void decode(htTree *tree, char *stringToDecode)
{
	htNode *traversal = tree->root;

	printf("\nDecoding\nInput string : %s\nDecoded string : \n", stringToDecode);

	//For each "bit" of the string to decode
	//we take a step to the left for 0
	//or ont to the right for 1
	for(int i=0; stringToDecode[i]!='\0'; i++)
	{
		if(traversal->left == NULL && traversal->right == NULL)
		{
			printf("%c",traversal->symbol);
			traversal = tree->root;
		}
		
		if(stringToDecode[i] == '0')
			traversal = traversal->left;

		if(stringToDecode[i] == '1')
			traversal = traversal->right;

		if(stringToDecode[i] != '0'&&stringToDecode[i]!='1')
		{
			printf("The input string is not coded correctly!\n");
			return;
		}
	}

	if(traversal->left == NULL && traversal->right == NULL)
	{
		printf("%c",traversal->symbol);
		traversal = tree->root;
	}

	printf("\n");
}
