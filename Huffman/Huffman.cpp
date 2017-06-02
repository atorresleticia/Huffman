#include "stdafx.h"
#include <iostream>
#include <queue>
#include <string>
#include "Huffman.h"

using namespace std;

priority_queue<TreeNode*, vector<TreeNode*>, OrderByFrequence> huffman_queue;

void generate_codes(TreeNode* node, string bit)
{
	if (node != nullptr)
	{
		if(node->ascii != '0')
		{
			node->code = bit;
			cout << node->code << " " << node->ascii << endl;
		}
		generate_codes(node->left, bit + "0");
		generate_codes(node->right, bit + "1");
	}
}

void build_tree()
{
	while(huffman_queue.size() != 1)
	{
		TreeNode * left_child = huffman_queue.top();
		huffman_queue.pop();
		
		TreeNode* right_child = huffman_queue.top();
		huffman_queue.pop();
		
		huffman_queue.push(new TreeNode('0', (left_child->frequency + right_child->frequency), left_child, right_child));
	}

}

void build_queue(int frequencies[256])
{
	for(auto i = 0; i < 256; i++)
	{
		if (frequencies[i] > 0)
		{
			huffman_queue.push(new TreeNode(i, frequencies[i]));
		}
	}
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		auto err = "Número de argumentos inválido.\n [ ./<nome_programa> \"uma frase aleatoria\" ]\n";
		cerr << err << endl;
		return 0;
	}
	 
	int frequencies[256] = {0};
	auto message = argv[1];

	while (*message != '\0')
	{
		++frequencies[*message++];
	}
	
	build_queue(frequencies);
	
	build_tree();

	generate_codes(huffman_queue.top(), "");

	return 0;
}