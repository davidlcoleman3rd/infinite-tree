#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <string>

const std::string SPACER[4] = {"|", "_", " ", "\\"};

const std::string PC = "My PC";

const std::string FILE_TYPES[3] = {"Documents",
															"Photos",
															"Games"};
const std::string DOC_NAMES[2] = {"taxes.pdf",
															"resume.docx"};
const std::string PHOTO_NAMES[4] =
								{"vacation.png", "puppy.jpg",
								"meme.gif", "beach.png"};
const std::string GAME_NAMES[3] =
								{"pinball.exe", "shooter.exe",
								"strategy.exe"};

template <class T>
class Node{
public:

//******
	Node(T input) {
		data = input;
		parent = nullptr;
		depth = 0;
	}

//******
	Node(T dataIn, Node* parentIn, int depthIn) {
		data = dataIn;
		SetParent(parentIn);
		parent->SetChild(this);
		SetDepth(depthIn);
	}

//******
	void SetData(T input) {
		data = input;
	}

//******
	void NewChild(Node* nodeIn, T input) {
		nodeIn = new Node(input, this, (depth + 1));
	}

//******
	void SetChild(Node* inNode) {
		children.push_back(inNode);
	}

//******
	T GetData(){
		return data;
	}

//******
	Node* GetParent() {
		return parent;
	}

//******
	void SetParent(Node* inNode) {
		parent = inNode;
	}

//******
	Node* GetChild(int inPos) {
		return children.at(inPos);
	}

//******
	int GetChildCount() {
		return children.size();
	}

//******
	std::vector<Node*> GetChildVector() {
		return children;
	}
//******
	int GetDepth(){
		return depth;
	}

//******
	void SetDepth(int input) {
		depth = input;
	}

//******
private:
	Node* parent;
	std::vector<Node*> children;
	T data;
	int depth;
};

//******************************************

template <class T>
class Tree {
public:

	//******
	Tree(T input) {
		root = new Node(input);
		curr = root;
		next = root;
	}

	//******
	void AddNode(T input) {
		curr->NewChild(next, input);
		next = nullptr;
	}

	//******
	void MoveDown(int childPos) {
		curr = curr->GetChild(childPos);

	}

	//******
	void MoveUp() {
		curr = curr->GetParent();
	}

	void PrintTree() {
		curr = root;
		PrintLevel(curr);
		std::cout << "\n\n";
	}

	void PrintLevel(Node<T>* nodeIn) {
		std::vector<bool> checkBranch;
		Node<T>* tempPtr = nodeIn->GetParent();
		Node<T>* tempChild = nodeIn;
		while (tempPtr != nullptr) {
			int last = tempPtr->GetChildVector().size()
								- 1;
			if (tempPtr->GetChildVector().at(last)
									== tempChild)  {
				checkBranch.push_back(false);
			}
			else {
				checkBranch.push_back(true);
			}
			tempChild = tempPtr;
			tempPtr = tempPtr->GetParent();
		}
		std::reverse(checkBranch.begin(),
								checkBranch.end());
		int temp = nodeIn->GetDepth();
		for (int space = 0; space < temp; space++) {

					if (space < temp - 1) {
						if (checkBranch.at(space)) {
							std::cout << SPACER[0];
						}
						else {
							std::cout << SPACER[2];
						}
						std::cout << SPACER[2];
					}
					else if (space == temp - 1) {
						std::cout << SPACER[3];
					}
		}
		if (temp > 0) {
			std::cout << SPACER[1];
		}
		std::cout << nodeIn->GetData() << "\n";
		if (nodeIn->GetChildCount() > 0) {
			for (auto iter : nodeIn->GetChildVector()) {
				PrintLevel(iter);
			}
		}
}

	//******
private:
	Node<T>* root;
	Node<T>* curr;
	Node<T>* next;

};


//******************************************


int main(){
	Tree<std::string> myTree(PC);
	for (int iter = 0; iter < 3; iter++) {
		myTree.AddNode(FILE_TYPES[iter]);
		if (iter == 0) {
			myTree.MoveDown(iter);
			for (int make = 0; make < 2; make++) {
				myTree.AddNode(DOC_NAMES[make]);
			}
			myTree.MoveUp();
		}
		else if (iter == 1) {
			myTree.MoveDown(iter);
			for (int make = 0; make < 4; make++) {
				myTree.AddNode
				(PHOTO_NAMES[make]);
			}
			myTree.MoveUp();
		}
		else {
			myTree.MoveDown(iter);
			for (int make = 0; make < 3; make++) {
				myTree.AddNode
				(GAME_NAMES[make]);
			}
			myTree.MoveUp();
		}
	}
	myTree.PrintTree();
	return 0;
}
