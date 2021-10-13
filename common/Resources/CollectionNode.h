#pragma once

class CollectionNode {
private:
	int length = 0;
public:
	CollectionNode** pChildren = nullptr;

	CollectionNode();
	CollectionNode(int _length);
	~CollectionNode();

	CollectionNode* add(int index, CollectionNode* pNewCollection);
	CollectionNode* get(int index);
};
