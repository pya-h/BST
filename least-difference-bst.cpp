#include <iostream>
#include <string>
using namespace std;
typedef
  struct Node
  {
    int value;
    struct Node *right = NULL, *left = NULL;
  }
Node;

int intValue(string);
int countItems(string);
void createArray(string[], string);
Node* createTree(string);
Node* insertLevelOrder(string *, Node*, int, int);
void showTree(Node*);
int absoluteValue(int);
int leastNodeDifferenceWithChilds(Node*,Node*, int);
int nodesLeastDifference(Node *root, int);

int main()
{
  int n = 0;
  cin >> n;
  string input;
  cin.ignore(); // for skipping unwanted '\n' and ' ' remained from previous input stream
  getline(cin, input);
  Node *rootNode = createTree(input);
  showTree(rootNode);cout<<endl;
  int diffrenceInitiateValue = rootNode->right != NULL ? absoluteValue(rootNode->value - rootNode->right->value) : absoluteValue(rootNode->value - rootNode->left->value);
  cout << nodesLeastDifference(rootNode, diffrenceInitiateValue);
  return 0;
}

int intValue(string text)
{
  int value = 0;
  for(int i = 0; text[i]; i++)
    value = value * 10 + (text[i] - '0');
  return value;
}

void createArray(string result[], string data)
{
  int index = 0, length = 0;
  for(; data[length] ; length++);

  for(int i = 0; i < length; i++)
  {
    int len = 0;
    for( ; i + len < length && data[i + len] != '\n' && data[i + len] != ' ' && data[i + len] != '\t'; len++) ;
    string item = data.substr(i, len);
    result[index] = item;

    i += len; // go to next item in the list
    index++;
  }
}
int countItems(string data)
{
    int count = 0;
    for(int i = 0; data[i] ;i++)
      if(data[i] == ' ' || data[i] == '\t') count++;
    return count + 1;
}
Node* createTree(string data)
{
  int nodesCount = countItems(data);
  string *arrNodes = new string[nodesCount];
  createArray(arrNodes, data);
  Node *rootNode;
  return insertLevelOrder(arrNodes, rootNode, 0, nodesCount);
}

// Function to insert nodes in level order
Node* insertLevelOrder(string arrNodes[], Node* parent, int i, int n)
{
    if (i < n)
    {
        if(arrNodes[i] == "N" || arrNodes[i] == "null")
          return NULL;
        Node* temp = new Node;

        temp->value = intValue(arrNodes[i]);

        parent = temp;
        parent->left = insertLevelOrder(arrNodes, parent->left, 2 * i + 1, n);
        parent->right = insertLevelOrder(arrNodes, parent->right, 2 * i + 2, n);
    }
    return parent;
}

// show items in tree order; for checking and observing tree values
void showTree(Node* parent)
{
    if (parent != NULL)
    {
        showTree(parent->left);
        cout << parent->value <<" ";
        showTree(parent->right);
    }
}
int absoluteValue(int value)
{
  return value < 0 ? -1 * value : value;
}
// calculate the node value differences with its childs -> for comparing with other minimums obtained by nodesLeastDifference function
int leastNodeDifferenceWithChilds(Node *parent, Node *child, int minDiff)
{
  int diff = minDiff;
  if(parent != NULL && child != NULL)
  {
      if( parent != child)
        diff = absoluteValue(parent->value - child->value);
      minDiff = leastNodeDifferenceWithChilds(parent, child->left, minDiff);
      minDiff = leastNodeDifferenceWithChilds(parent, child->right, minDiff);
  }

  return diff < minDiff ? diff : minDiff;

}

// compare all node deffierence values the finally find the minimum one
int nodesLeastDifference(Node *root, int leastDifferenceThroughoutTheTree)
{
  int nodesMinDiffWithItsChilds = leastDifferenceThroughoutTheTree;
  if(root != NULL)
  {
    nodesMinDiffWithItsChilds = leastNodeDifferenceWithChilds(root, root, leastDifferenceThroughoutTheTree);

    leastDifferenceThroughoutTheTree = nodesLeastDifference(root->left, leastDifferenceThroughoutTheTree);
    leastDifferenceThroughoutTheTree = nodesLeastDifference(root->right, leastDifferenceThroughoutTheTree);
  }
  return nodesMinDiffWithItsChilds < leastDifferenceThroughoutTheTree ? nodesMinDiffWithItsChilds : leastDifferenceThroughoutTheTree;
}
