#include <stdio.h>
#include <stdlib.h>
#include "huffman.h" 

int main(void)
{
	//根据输入的字符串创建赫夫曼树 
	htTree *codeTree = buildTree("4444333221");
	
	//根据创建的赫夫曼树生成列表 
	hlTable *codeTable = buildTable(codeTree);

	//使用赫夫曼列表来编码 
	encode(codeTable,"4444333221");
	
	//使用赫夫曼树解码，但注意只能解码出被编码的字符 
	decode(codeTree,"1001010");
	
	return 0;
}

//We build the tree depending on the string 
//We build the table depending on the Huffman tree
//We encode using the Huffman table
//We decode using the Huffman tree
//We can decode string that only use symbols from the initial string
