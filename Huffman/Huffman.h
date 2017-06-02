#ifndef HUFFMAN
#define HUFFMAN

struct TreeNode 
{
	int frequency;
	char ascii;
	TreeNode* left;
	TreeNode* right;
	std::string code;
	
	TreeNode (char ascii, int frequency)
	{
		this->ascii = ascii;
		this->frequency = frequency;
		left = right = nullptr;
		code = "";
	}
	
	TreeNode (char ascii, int frequency, TreeNode* left, TreeNode* right)
	{
		this->ascii = ascii;
		this->frequency = frequency;
		this->left = left;
		this->right = right;
		this->code = "";
	}
	
	/*
	 *
	 *		POR QUE NÃO FUNCIONA? CARALHO, PORRA, INFERNO, CACETE, VAI TOMAR NO CU, FILHA DA PUTA, CUZÃO DA PORRA, VAI SE FODER
	 *		
	bool operator<(const TreeNode* tree_node) const
    {
        return frequency > tree_node->frequency;
    }
	bool operator>(const TreeNode* tree_node) const
	{
		return frequency < tree_node->frequency;
	}
	*/
};

struct OrderByFrequence
{
	bool operator()(TreeNode* left, TreeNode* right) const
	{
		return (left->frequency > right->frequency);
	}
};

#endif