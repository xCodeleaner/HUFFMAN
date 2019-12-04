#include <stdio.h>
#include <stdlib.h>
#include "huffman.h" 

int main(void)
{
	//����������ַ��������շ����� 
	htTree *codeTree = buildTree("4444333221");
	
	//���ݴ����ĺշ����������б� 
	hlTable *codeTable = buildTable(codeTree);

	//ʹ�úշ����б������� 
	encode(codeTable,"4444333221");
	
	//ʹ�úշ��������룬��ע��ֻ�ܽ������������ַ� 
	decode(codeTree,"1001010");
	
	return 0;
}

//We build the tree depending on the string 
//We build the table depending on the Huffman tree
//We encode using the Huffman table
//We decode using the Huffman tree
//We can decode string that only use symbols from the initial string
