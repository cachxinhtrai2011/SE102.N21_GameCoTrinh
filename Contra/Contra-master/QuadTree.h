#pragma once
#include "GameObject.h"
#include <map>
class TreeNode;
typedef TreeNode* LPTREENODE;

class TreeNode
{
private:
	int id;
	float x;
	float y;
	float width;
	float height;
	static int NodeCount;
	LPTREENODE parentNode;
	vector<LPTREENODE>* child;
	vector<LPGAMEOBJECT>* gameObjects;
public:
	TreeNode(float x, float y, float width, float height, LPTREENODE parent = NULL) {
		id = NodeCount;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		NodeCount++;
		child = NULL;
		gameObjects = NULL;
		parentNode = parent;
	}
	void Split();

	void AddObjectToNode(LPGAMEOBJECT object);
	void Update(LPGAMEOBJECT object);
	vector<LPTREENODE>* IsObjectInside(LPGAMEOBJECT object);
	void GetBoundingBox(float& left, float& top, float& right, float& down)
	{
		left = x;
		down = y;
		right = x + width;
		top = y + height;
	}
	vector<LPTREENODE>* NodeInCam();
	vector<LPGAMEOBJECT>* GetObject() {
		if (child != NULL)
		{
			vector<LPGAMEOBJECT>* result = new vector<LPGAMEOBJECT>();
			for (int i = 0; i < child->size(); i++)
			{
				LPTREENODE temp = child->at(i);
				vector<LPGAMEOBJECT>* gameObjectList = temp->GetObject();
				if (gameObjectList != NULL)
					result->insert(result->end(), gameObjectList->begin(), gameObjectList->end());

			}
			return result;
		}
		else
			return gameObjects;
	}
};