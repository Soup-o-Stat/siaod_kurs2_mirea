#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct TreeNode {
	string name;
	TreeNode* left;
	TreeNode* right;

	TreeNode(const string& name)
		: name(name), left(nullptr), right(nullptr) {}
};

TreeNode* insertNode(TreeNode* root, const string& name) {
	if (root == nullptr) {
		return new TreeNode(name);
	}
	if (name < root->name) {
		root->left = insertNode(root->left, name);
	} else if (name > root->name) {
		root->right = insertNode(root->right, name);
	}
	return root;
}

void reverseOrder(TreeNode* root) {
	if (root != nullptr) {
		reverseOrder(root->right);
		cout << root->name << " ";
		reverseOrder(root->left);
	}
}

void inOrder(TreeNode* root) {
	if (root != nullptr) {
		inOrder(root->left);
		cout << root->name << " ";
		inOrder(root->right);
	}
}

int findPathLength(TreeNode* root, const string& target) {
	int length = 0;
	while (root != nullptr) {
		if (target < root->name) {
			root = root->left;
			length++;
		} else if (target > root->name) {
			root = root->right;
			length++;
		} else {
			return length;
		}
	}
	return -1;
}

int findHeight(TreeNode* root) {
	if (root == nullptr) {
		return -1;
	}
	int leftHeight = findHeight(root->left);
	int rightHeight = findHeight(root->right);
	return max(leftHeight, rightHeight) + 1;
}

void deleteTree(TreeNode* root) {
	if (root != nullptr) {
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
	}
}

void menu() {
	TreeNode* root = nullptr;
	int choice;
	string name;

	do {
		cout << "1. Input element"<<endl;;
		cout << "2. Reverse bypass"<<endl;
		cout << "3. Symmetric bypass"<<endl;
		cout << "4. Find the length of the path to the value"<<endl;
		cout << "5. Find tree height"<<endl;
		cout << "6. Exit"<<endl;
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Input name: ";
			cin >> name;
			root = insertNode(root, name);
			cout << "Element has been added"<<endl;;
			break;
		case 2:
			cout << "Reverse bypass: ";
			reverseOrder(root);
			cout << endl;
			break;
		case 3:
			cout << "Symmetric bypass: ";
			inOrder(root);
			cout << endl;
			break;
		case 4:
			cout << "Input name for search: ";
			cin >> name;
			int length;
			length = findPathLength(root, name);
			if (length != -1) {
				cout << "The length of the path to " << name << ": " << length << endl;
			} else {
				cout << "The value was not found in the tree"<<endl;
			}
			break;
		case 5:
			cout << "Tree height: " << findHeight(root) << endl;
			break;
		case 6:
			break;
		default:
			cout << "Error"<<endl;
		}
	} while (choice != 6);

	deleteTree(root);
}

int main() {
	menu();
	return 0;
}