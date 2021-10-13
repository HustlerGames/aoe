#include "CollectionNode.h"


CollectionNode::CollectionNode()
{
	length = 0;
}

CollectionNode::CollectionNode(int _length)
{
	length = _length;
	pChildren = new CollectionNode * [length];
	for (int i = 0; i < length; i++)
	{
		pChildren[i] = nullptr;
	}
}

CollectionNode::~CollectionNode()
{
	for (int i = 0; i < length; i++)
	{
		if (pChildren[i]) delete pChildren[i];
	}

	delete[] pChildren;

}


CollectionNode* CollectionNode::add(int index, CollectionNode* pNewCollection)
{
	if (pChildren[index])
		delete pChildren[index];

	pChildren[index] = pNewCollection;

	return pChildren[index];
}

CollectionNode* CollectionNode::get(int index)
{
	return pChildren[index];
}

