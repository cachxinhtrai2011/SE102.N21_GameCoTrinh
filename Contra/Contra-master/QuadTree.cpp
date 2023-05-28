#include "QuadTree.h"
#include "Utils.h"
#include "Game.h"

int TreeNode::NodeCount = 0;

void TreeNode::AddObjectToNode(LPGAMEOBJECT object)
{
	if (!IsIntersac(object, this))
		return;
	if (child == NULL)
	{
		if (gameObjects == NULL)
			gameObjects = new vector<LPGAMEOBJECT>();
		for (int i = 0; i < gameObjects->size(); i++)
			if (gameObjects->at(i) == object)
				return;
		gameObjects->push_back(object);
		return;
	}
	else
	{
		for (int i = 0; i < child->size(); i++)
			child->at(i)->AddObjectToNode(object);
	}
}
void TreeNode::Update(LPGAMEOBJECT object)
{
	vector<LPTREENODE>* treeNodeList = this->IsObjectInside(object);
	for (int i = 0; i < treeNodeList->size(); i++)
	{
		if (!IsIntersac(object, treeNodeList->at(i)))
		{
			vector<LPGAMEOBJECT>* objectList = treeNodeList->at(i)->gameObjects;
			objectList->erase(std::remove(objectList->begin(), objectList->end(), object));
			if (objectList->size() == 0)
				treeNodeList->at(i)->gameObjects = NULL;
		}
	}
	this->AddObjectToNode(object);
}
vector<LPTREENODE>* TreeNode::NodeInCam()
{
	if (gameObjects != NULL)
	{
		vector<LPTREENODE>* a = new vector<LPTREENODE>();
		a->push_back(this);
		return a;
	}
	float left, top;
	CGame::GetInstance()->GetCamPos(left, top);
	float right = left + CGame::GetInstance()->GetScreenWidth();
	float bottom = top;
	top = top + CGame::GetInstance()->GetScreenHeight();
	if (!IsIntersac(left, top, right, bottom, this))
		return new vector<LPTREENODE>();
	if(child != NULL)
	{
		vector<LPTREENODE>* a = new vector<LPTREENODE>();
		for (int i = 0; i < child->size(); i++)
		{
			vector<LPTREENODE>* temp = child->at(i)->NodeInCam();
			if (temp != NULL)
			{
				a->insert(a->end(), temp->begin(), temp->end());
			}
		}
		return a;
	}
	return new vector<LPTREENODE>();
}
void TreeNode::Split()
{
	if (child != NULL)
	{
		for (int i = 0; i < child->size(); i++)
			child->at(i)->Split();
	}
	else
	{

		LPTREENODE node1 = new TreeNode(x, y, width / 2, height / 2, this);
		LPTREENODE node2 = new TreeNode(x + width / 2, y, width / 2, height / 2, this);
		LPTREENODE node3 = new TreeNode(x, y - height / 2, width / 2, height / 2, this);
		LPTREENODE node4 = new TreeNode(x + width / 2, y - height / 2, width / 2, height / 2, this);
		child = new vector<LPTREENODE>();
		child->push_back(node1);
		child->push_back(node2);
		child->push_back(node3);
		child->push_back(node4);
		if (gameObjects == NULL)
			return;
		for (int i = 0; i < gameObjects->size(); i++)
		{
			float left, top, right, down;
			LPGAMEOBJECT temp = gameObjects->at(i);
			temp->GetBoundingBox(left, top, right, down);
			if (IsIntersac(gameObjects->at(i), node1))
				node1->AddObjectToNode(temp);
			if (IsIntersac(gameObjects->at(i), node2))
				node2->AddObjectToNode(temp);
			if (IsIntersac(gameObjects->at(i), node3))
				node3->AddObjectToNode(temp);
			if (IsIntersac(gameObjects->at(i), node4))
				node4->AddObjectToNode(temp);
		}
		gameObjects = NULL;
	}

}

vector<LPTREENODE>* TreeNode::IsObjectInside(LPGAMEOBJECT object)
{
	if (gameObjects != NULL)
	{
		for (int i = 0; i < gameObjects->size(); i++)
			if (gameObjects->at(i) == object)
			{
				vector<LPTREENODE>* a = new vector<LPTREENODE>();
				a->push_back(this);
				return a;
			}
		return NULL;
	}
	if (child == NULL)
		return NULL;
	vector<LPTREENODE>* a = new vector<LPTREENODE>();
	for (int i = 0; i < child->size(); i++)
	{
		vector<LPTREENODE>* node = child->at(i)->IsObjectInside(object);
		if (node != NULL)
			a->insert(a->end(), node->begin(), node->end());
	}
	if (a->size() > 0)
		return a;
	return NULL;
}