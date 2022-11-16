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

int countItems(string);
int intValue(string);
void createArray(string[], string);
Node* createTree(string);
Node* insertLevelOrder(string *, Node*, int, int);
void showTree(Node*);
int bstLength(Node*);
int largestBstLength(Node*, int);

int main()
{
  string input;
  getline(cin, input);
  Node *rootNode = createTree(input);
  // showTree(rootNode);
  cout << largestBstLength(rootNode, 0);
  return 0;
}

int intValue(string text)
{
  int value = 0;
  for(int i = 0; text[i]; i++)
    value = value * 10 + (text[i] - '0');
  return value;
}

int countItems(string data)
{
    int count = 0;
    for(int i = 0; data[i] ;i++)
      if(data[i] == ' ' || data[i] == '\t') count++;
    return count + 1;
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

// to insert nodes in level order, appending to a specific parent node
Node* insertLevelOrder(string arrNodes[], Node* parent, int i, int n)
{
    if (i < n && arrNodes[i] != "N" && arrNodes[i] != "null")
    {
        Node* temp = new Node;

        temp->value = intValue(arrNodes[i]);

        parent = temp;
        parent->left = insertLevelOrder(arrNodes, parent->left, 2 * i + 1, n);
        parent->right = insertLevelOrder(arrNodes, parent->right, 2 * i + 2, n);
    }
    return parent;
}

Node* createTree(string data)
{
  int nodesCount = countItems(data);
  string *arrNodes = new string[nodesCount];
  createArray(arrNodes, data);
  Node *rootNode;
  return insertLevelOrder(arrNodes, rootNode, 0, nodesCount);
}

// show items in tree order starting a specific parent node; for checking and observing tree values
void showTree(Node* parent)
{
    if (parent != NULL)
    {
        showTree(parent->left);
        cout << parent->value <<" ";
        showTree(parent->right);
    }
}

// left_subtree (keys) ≤ node (key) ≤ right_subtree (keys)
int bstLength(Node *parent)
{
  int length = 1;
  if(parent->left != NULL && parent->left->value <= parent->value && parent->right != NULL && parent->right->value >= parent->value)
  {
    length += bstLength(parent->left);
    length += bstLength(parent->right);
  }

  return length;
}

int largestBstLength(Node *root, int maxLength)
{
  int length = 0;
  if(root != NULL)
  {
    length = bstLength(root);
//    if(length > maxLength) maxLength = length;

    maxLength = largestBstLength(root->left, maxLength);
    maxLength = largestBstLength(root->right, maxLength);
  }
  return length > maxLength ? length : maxLength;
}
