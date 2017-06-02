/*O menor elemento se encontra na esquerda da árvore.
 * Caso dois nodos tenham a mesma frequencia, o elemento que será inserido tem prioridade em relação ao seu igual na fila.
 * Esquerda 0
 * Direita 1
 */

#include "stdafx.h"
#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>
#include "Huffman.h"
#include <fstream>

using namespace std;

priority_queue<TreeNode*, vector<TreeNode*>, OrderByFrequence> huffman_queue;
string code = "";
string code_vector[256] = {""};
char* message;
int huffman_size;

void compare_to_ascii()
{
	int ascii_size = 8 * strlen(message);
	cout << "Number of bits (ASCII) = " << ascii_size << endl;
	cout << "Number of bits saved = " << ascii_size - huffman_size << endl << endl;

}

void generate_string()
{
	huffman_size = 0;
	char* tmp = message;
	while(*tmp != '\0')
	{
		cout << code_vector[*tmp];
		huffman_size += code_vector[*tmp].size();
		*tmp++;
	}
	cout << endl;
	cout << "Number of bits (Huffman) = " << huffman_size << endl;
}

void generate_codes(TreeNode* node, string bit)
{
	if (node != nullptr)
	{
		if(node->ascii != '0') //nodo com ascii 0 é concatenação de duas ou mais letras
		{
			node->code = bit;
			cout << "\t" << node->ascii << "\t" << node->code << endl;
			code_vector[node->ascii] = node->code;
		}
		generate_codes(node->left, bit + "0");
		generate_codes(node->right, bit + "1");
	}
}

/*o que está antes na fila vai pra esquerda, pois o maior sempre fica por último
Depois de pegar os dois primeiros elementos, cria um novo com ascii = 0 e frequencias somadas*/
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

/*Todos os elementos que aparecem na frase serão adicionados à fila de prioridade*/
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
		auto err = "Invalid args number...\n [ Linux: ./<nome_programa> \"uma frase aleatoria\" ]\n [ Windows: <nome_programa> \"uma frase aleatoria\" ]";
		cerr << err << endl;
		return 0;
	}
	
	system("Title HUFFMAN COMPRESSED CODE GENERATOR FOR DUMMIES");
	system("cls");

	int frequencies[256] = {0};
	message = argv[1];
	char *tmp = message;

	cout << "Mensagem = " << message << endl;

	while (*tmp != '\0')
	{
		++frequencies[*tmp++];
	}

	build_queue(frequencies);
	
	build_tree();

	cout << "Codes: " << endl;
	generate_codes(huffman_queue.top(), "");

	cout << "\nHuffmann string = ";
	generate_string();

	compare_to_ascii();

	return 0;
}
