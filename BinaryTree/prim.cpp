#include <iostream>
using namespace std;
// nullptr > NULL

struct Tree {
	int info;
	Tree* left;
	Tree* right;
};

void View(Tree* t, int level) {
	if (t != NULL) {
		View(t->right, level + 1);
		for (int i = 0; i < level; i++) {
			cout << '\t';
		}
		cout << t->info << endl;
		View(t->left, level + 1);
	}
}

void ShowElem(Tree* t) {
	if (t != NULL) {
		cout << "Element: " << t << " with info: " << t->info << ", left: " << t->left << ", right: " << t->right << endl;
	}
}

Tree* Leaf(int inf) {
	Tree* t = new Tree;
	if (!t) {
		cout << "No memory to create leaf of the tree.\n";
		return NULL;
	}
	t->info = inf;
	t->left = t->right = NULL;
	return t;
}

Tree* Make(Tree* Root) {
	Tree* prev = NULL, *t;
	int b, find;
	if (Root == NULL) {
		cout << "Enter Root: ";
		cin >> b;
		Root = Leaf(b);
	}
	while (true) {
		cout << "Enter Root: ";
		cin >> b;
		if (b < 0) {
			break;
		}
		t = Root;
		find = 0;

		while (t != NULL & !find) {
			prev = t;
			if (b == t->info) {
				find = 1;
			}
			else {
				if (b < t->info) {
					t = t->left;
				}
				else {
					t = t->right;
				}
			}
		}

		if (!find) {
			t = Leaf(b);
			if (b < prev->info) {
				prev->left = t;
			}
			else {
				prev->right = t;
			}
		}
	}
	return Root;
}

Tree* AddOne(Tree* Root, int b) {
	Tree* prev = NULL, *t;
	int find;
	if (Root == NULL) {
		Root = Leaf(b);
		return Root;
	}
	t = Root;
	find = 0;

	while (t != NULL & !find) {
		prev = t;
		if (b == t->info) {
			find = 1;
		}
		else {
			if (b < t->info) {
				t = t->left;
			}
			else {
				t = t->right;
			}
		}
	}

	if (!find) {
		t = Leaf(b);
		if (b < prev->info) {
			prev->left = t;
		}
		else {
			prev->right = t;
		}
	}
	return Root;
}

Tree* Del(Tree* Root, int key) {
	Tree* Del, *PrevDel, *R, *PrevR;
	Del = Root;
	PrevDel = NULL;

	while (Del != NULL && Del->info != key) {
		PrevDel = Del;
		if (Del->info > key) {
			Del = Del->left;
		}
		else {
			Del = Del->right;
		}
	}

	if (Del == NULL) {
		cout << "No find key to delete.\n";
		return Root;
	}
	if (Del->right == NULL) {
		R = Del->left;
	}
	else {
		if (Del->left == NULL) {
			R = Del->right;
		}
		else {
			PrevR = Del;
			R = Del->left;
			while (R->right != NULL) {
				PrevR = R;
				R = R->right;
			}

			if (PrevR == Del) {
				R->right = Del->right;
			}
			else {
				R->right = Del->right;
				PrevR->right = R->left;
				R->left = PrevR;
			}
		}

		if (Del == Root) {
			Root = R;
		}
		else {
			if (Del->info < PrevDel->info) {
				PrevDel->left = R;
			}
			else {
				PrevDel->right = R;
			}
		}
	}
	cout << "Delete element: " << Del << " with info: " << Del->info << endl;
	delete Del;
	return Root;
}

Tree* DelAll(Tree* t) {
	if (t != NULL) {
		ShowElem(t);
		DelAll(t->left);
		DelAll(t->right);
		delete t;
		t = NULL;
	}
	return t;
}

int main() {
	system("chcp 65001");
	Tree* Root = NULL;

	Root = Make(Root);
	View(Root, 0);
	
	int r = 1, k;
	do {
		cout << "0-Завершить программу\n1-Создать дерево и заполнить его узлами и листьями\n"
			<< "2-Добавить дереву лист\n3-Распечатать дерево\n4-Удалить узел(лист), имеющий искомое значение\n"
			<< "5-Удалить все дерево из памяти\nВведите пункт меню: ";
		cin >> r;

		switch (r) {
			case 0: break;
			case 1: {
				if (Root != NULL) {
					cout << "Tree already exists. Delete tree first.\n";
					break;
				}
				Root = Make(Root);
				break;
			}
			case 2: {
				cout << "Enter value to add in the Tree: ";
				cin >> k;
				Root = AddOne(Root, k);
				break;
			}
			case 3: {
				View(Root, 0);
				break;
			}
			case 4: {
				cout << "Enter value to delete in Tree: ";
				cin >> k;
				Root = Del(Root, k);
				break;
			}
			case 5: {
				Root = DelAll(Root);
				if (Root == NULL) {
					cout << "Tree deleted.\n";
				}
				else {
					cout << "The Tree wasn't successfully deleted.\n";
				}
				break;
			}
		}
	} while (r != 0);
	system("pause");
	return 0;
}