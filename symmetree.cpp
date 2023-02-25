 #include <vector>
 #include <algorithm>
 #include <math.h>
 #include <iostream>
 #include <string>

 const std::string SPACER[4] = {"|", "_", " ", "\\"};

 const std::string PC = "My PC";

 const std::string FILE_TYPES[3] = {"Documents","Photos","Games"};
 const std::string DOC_NAMES[2] = {"taxes.pdf","resume.docx"};
 const std::string PHOTO_NAMES[4] = {"vacation.png","puppy.jpg","meme.gif","beach.png"};
 const std::string GAME_NAMES[3] = {"pinball.exe", "shooter.exe","strategy.exe"};

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
    if (parent != nullptr) {
        parent->SetChild(this);
    }
    SetDepth(depthIn);
}

 //******
void DeleteChild(int input) {
    delete children.at(input);
    children.erase(children.begin() + input);
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
     std::vector<Node<T>*> children;
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
 Tree (const Tree& other) {
     other.StartTraversal();
     root = new Node<T>(other.GetCurr()->GetData());
     curr = root;
 	next = root;
     CopyNode(other);
 }

 //******
 void CopyNode(const Tree& other) {
     int iter = other.GetCurr()->GetChildCount();
     for (int space = 0; space < iter; space++) {
 		curr->NewChild(next, other.GetCurr()->GetChild(space)->GetData());
 		next = nullptr;
     }
     for (int space = 0; space < iter; space++) {
         MoveDown(space);
         other.MoveDown(space);
         CopyNode(other);
         MoveUp();
         other.MoveUp();
     }
 }

 //******
 void SymmetricNode(const Tree& other) {
     int iter = other.GetCurr()->GetChildCount();
     for (int space = 0; space < iter; space++) {
         curr->NewChild(next, other.GetCurr()->GetChild(iter - space - 1)->GetData());
 		next = nullptr;
     }
     for (int space = 0; space < iter; space++) {
         MoveDown(space);
         other.MoveDown(iter - space - 1);
         SymmetricNode(other);
         MoveUp();
         other.MoveUp();
     }
 }

 //******
 Node<T>* GetCurr() const {
     return curr;
 }

 Node<T>* GetRoot() const {
     return root;
 }

 void StartTraversal() const {
     curr = root;
 }

 //******
 void AddNode(T input) {
     curr->NewChild(next, input);
     next = nullptr;
 }

 //******
 void MoveDown(int childPos)const{
     curr = curr->GetChild(childPos);
 }

 //******
 void MoveUp() const {
     curr = curr->GetParent();
 }

 void PrintTree() {
     curr = root;
     PrintLevel(curr);
     std::cout << "\n\n";
 }

 void PrintLevel(Node<T>* nodeIn) const{
     std::vector<bool> checkBranch;
     Node<T>* tempPtr = nodeIn->GetParent();
     Node<T>* tempChild = nodeIn;
     while (tempPtr != nullptr) {
         int last = tempPtr->GetChildCount() - 1;
         if (tempPtr->GetChild(last) == tempChild) {
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
 bool CheckSymmetry(const Tree<T>& otherTree) {
     curr = root;
     otherTree.StartTraversal();
     Node<T>* temp = curr;
     Node<T>* otherTemp = otherTree.GetCurr();
     int len = temp->GetChildCount();
     int otherLen = otherTemp->GetChildCount();
     if (len != otherLen) {
         std::cout << "\n\nNot same length\n\n";
         return false;
     }
     for (int iter = 0; iter < len; iter++) {
         if (temp->GetChild(iter)->GetData() != otherTemp->GetChild(len - iter - 1)->GetData()) {
             std::cout << "\n\nNot same at location\n\n";
             return false;
             Node<T>* pass = temp->GetChild(iter);
             Node<T>* otherPass = otherTemp->GetChild(len-1-iter);
             if (!(CheckSymmetry(pass, otherPass))) {
                 return false;
             }
         }
     }
 	std::cout << "\n\nSuccess; in parent node\n\n";
     return true;
 }

 //******
 void MakeSymmetrical(Tree<T>& other) {
     DeleteTree();
     other.StartTraversal();
     root = new Node<T>(other.GetCurr()->GetData(), nullptr, 0);
     curr = root;
     SymmetricNode(other);
 }

 //******
 bool CheckSymmetry(Node<T>* pass,
     Node<T>* otherPass) const {

     Node<T>* temp = pass;
     Node<T>* otherTemp = otherPass;
     int len = temp->GetChildCount();
     int otherLen = otherTemp->GetChildCount();
     if (len != otherLen) {
             return false;
     }
     for (int iter = 0; iter < len; iter++) {
         if (temp->GetChild(iter)->GetData() != otherTemp->GetChild(len - 1 - iter)->GetData()) {
 			std::cout << "\n\nFailure\n\n";
             return false;
 			std::cout << "\n\nFailure\n\n";
         }
 		else {
 			std::cout << "\n\nSame pointer\n\n";
 		}
         Node<T>* nextPass= temp->GetChild(iter);
         Node<T>* otherNext = otherTemp->GetChild(len-1-iter);
         if (!(CheckSymmetry(nextPass,otherNext))) { 			std::cout << "\n\nFailure\n\n";
             return false;
         }
     }
 std::cout << "\n\nSuccess\n\n";
     return true;
 }
  /*
 //******
 bool CheckEquality(Tree<T> otherTree) {
     curr = root;
     otherTree.StartTraversal();
     Node<T>* temp = curr;
     Node<T>* otherTemp = otherTree.GetCurr();
     int len = temp->GetChildVector().size();
     int otherLen = otherTemp->GetChildVector(). size();
     if (len != otherLen) {
         std::cout << "\n\nNot same length\n\n";
         return false;
     }
     for (int iter = 0; iter < len; iter++) {
         if (temp->GetChild(iter)->GetData() != otherTemp->GetChild(iter)->GetData()) {
             std::cout << "\n\nNot same at location\n\n";
             return false;
             Node<T>* pass = temp->GetChildVector().at(iter);
             Node<T>* otherPass = otherTemp->GetChildVector().at(len-1-iter);
             if (!(CheckEquality(pass, otherPass))) {
                 return false;
             }
         }
     }
     return true;
 }

 //******
 bool CheckEquality(Node<T>* pass,
     Node<T>* otherPass) {

     Node<T>* temp = pass;
     Node<T>* otherTemp = otherPass;
     int len = temp->GetChildCount();
     int otherLen = otherTemp->GetChildCount();
     if (len != otherLen) {
             return false;
     }
     for (int iter = 0; iter < len; iter++) {
         if (temp->GetChild(iter) != otherTemp->GetChild(iter)) {
             return false;
         }
         Node<T>* nextPass= temp->GetChild(iter);
         Node<T>* otherNext = otherTemp->GetChild(iter);
         if (!(CheckSymmetry(nextPass,otherNext))) {
             return false;
         }
     }
     return true;
 }

 operator==(Tree& other) {
  	CheckEquality(other);
 }
 */

 //******
 void DeleteTree() {
     curr = root;
     Node<T>* temp = nullptr;
     int last = 0;
     while (root->GetChildCount() > 0) {
         while (GetCurr()->GetChildCount() > 0) {
             temp = GetCurr();
             last = temp->GetChildCount() - 1;
             MoveDown(last);
         }
     MoveUp();
     temp = GetCurr();
     temp->DeleteChild(last);
     }
     temp = root;
     root = nullptr;
     curr = root;
     delete temp;
     temp = nullptr;
 }

 //******
 ~Tree() {
    if (root != nullptr) {
        DeleteTree();
    }
 }

 //******
 private:
 mutable Node<T>* root;
 mutable Node<T>* curr;
 mutable Node<T>* next;

 };


 //******************************************


 int main(){
     Tree<std::string> myTree(PC);
     Tree<std::string> myOther(PC);
     for (int iter = 0; iter < 3; iter++) {
         myTree.AddNode(FILE_TYPES[iter]);
         myOther.AddNode(myTree.GetCurr()->GetChild(iter)->GetData());
         if (iter == 0) {
             myTree.MoveDown(iter);
             myOther.MoveDown(iter);
             for (int make = 0; make < 2; make++) {
                 myTree.AddNode(DOC_NAMES[make]);
                 myOther.AddNode(myTree.GetCurr()->GetChild(make)->GetData());
             }
             myTree.MoveUp();
             myOther.MoveUp();
         }
         else if (iter == 1) {
             myTree.MoveDown(iter);
             myOther.MoveDown(iter);
             for (int make = 0; make < 4; make++) {
                 myTree.AddNode(PHOTO_NAMES[make]);
                 myOther.AddNode(myTree.GetCurr()->GetChild(make)->GetData());
             }
             myTree.MoveUp();
             myOther.MoveUp();
         }
         else {
             myTree.MoveDown(iter);
             myOther.MoveDown(iter);
             for (int make = 0; make < 3; make++) {
                 myTree.AddNode(GAME_NAMES[make]);
                 myOther.AddNode(myTree.GetCurr()->GetChild(make)->GetData());
             }
         myTree.MoveUp();
         myOther.MoveUp();
         }
     }
 // std::cout << "Test";
    Tree final(myOther);
    myTree.MakeSymmetrical(myOther);
    myTree.PrintTree();
     myOther.PrintTree();
     final.MakeSymmetrical(myOther);
     final.PrintTree();

     if (myOther.CheckSymmetry(final)) {
         std::cout << "\n\nSymmetrical\n\n";
     }
     if (myOther.CheckSymmetry(myTree)) {
        std::cout << "\n\nSymmetrical\n\n";
     }
     if (myTree.CheckSymmetry(final)) {
         std::cout << "\n\nSymmetrical\n\n";
     }
 /*
 	if (myTree.CheckEquality(final)) {
 		std::cout << "\n\nEqual\n\n";
 	}
 	else {
 		std::cout << "\n\nNot equal\n\n";
 	}
 	*/
 	return 0;
 }
