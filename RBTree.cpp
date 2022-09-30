#include <iostream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    string color;
    Node* parent;
};

void print_Tree(Node*, int);

class RBT {
public:
    Node* GetRoot() { return main_root; }
    Node* GetMin() { return min_el; }
    RBT(int a) : size(a) {
        int value;
        for (int i = 0; i < size; i++)
        {
            cin >> value;
            cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
            Insert(value);
            MinSearch(value);
            cout << "Minimal element: " << min_el->data << "\nColor: " << min_el->color << endl;
            print_Tree(main_root, 5);
            cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        }
    }
    void MinSearch(int value) {
        Node* temp = ElSearch(value);
        if (temp != nullptr and min_el->data > temp->data)
            min_el = temp;
    }
    Node* ElSearch(int value) {
        Node* temp = new Node();
        temp = main_root;
        if (main_root->data == value)
            return main_root;
        while (temp != nullptr) {
            temp = value >= temp->data ? temp = temp->right : temp = temp->left;
            if (temp != nullptr and temp->data == value)
                break;
        }
        return temp;
    }
    void ReColor(Node*& node) {
        node->color == "BLACK" ? node->color = "RED" : node->color = "BLACK";
    }
    void LeftRotate(Node*& root) {
        if (root->right == nullptr)
            return;
        else {
            Node* temp = root->right;
            if (temp->left != nullptr) {
                root->right = temp->left;
                temp->left->parent = root;
            }
            else
                root->right = nullptr;
            if (root->parent != nullptr)
                temp->parent = root->parent;
            if (root->parent == nullptr)
                main_root = temp;
            else {
                if (root == root->parent->left)
                    root->parent->left = temp;
                else
                    root->parent->right = temp;
            }
            temp->left = root;
            root->parent = temp;
        }
    }
    void RightRotate(Node*& root) {
        if (root->left == nullptr)
            return;
        else {
            Node* temp = root->left;
            if (temp->right != nullptr) {
                root->left = temp->right;
                temp->right->parent = root;
            }
            else
                root->left = nullptr;
            if (root->parent != nullptr)
                temp->parent = root->parent;
            if (root->parent == nullptr)
                main_root = temp;
            else {
                if (root == root->parent->left)
                    root->parent->left = temp;
                else
                    root->parent->right = temp;
            }
            temp->right = root;
            root->parent = temp;
        }

    }
    bool ViolationsCheck(Node*& child, Node*& uncle, Node*& parent, Node*& grandparent) {
        bool violations = false;
        Node* temp = child->parent;
        Node* prev = child->parent;
        while (temp->left != nullptr) { //check left
            prev = temp;
            temp = temp->left;
            if (temp->color == "RED" and prev->color == "RED") {
                violations = true;
                child = temp;
                parent = child->parent;
                grandparent = parent->parent;
                uncle = grandparent->left == parent ? grandparent->right : grandparent->left;
                return violations;
            }
            else if (temp->left != nullptr and temp->color == "RED" and temp->left->color == "RED") {
                violations = true;
                child = temp->left;
                parent = child->parent;
                grandparent = parent->parent;
                uncle = grandparent->left == parent ? grandparent->right : grandparent->left;
                return violations;
            }
            else if (temp->right != nullptr and temp->color == "RED" and temp->right->color == "RED") {
                violations = true;
                child = temp->right;
                parent = child->parent;
                grandparent = parent->parent;
                uncle = grandparent->left == parent ? grandparent->right : grandparent->left;
                return violations;
            }
        }
        temp = prev = child->parent;
        while (temp->right != nullptr) { //check right
            prev = temp;
            temp = temp->right;
            if (temp->color == "RED" and prev->color == "RED") {
                violations = true;
                child = temp;
                parent = child->parent;
                grandparent = parent->parent;
                uncle = grandparent->left == parent ? grandparent->right : grandparent->left;
                return violations;
            }
            else if (temp->left != nullptr and temp->color == "RED" and temp->left->color == "RED") {
                violations = true;
                child = temp->left;
                parent = child->parent;
                grandparent = parent->parent;
                uncle = grandparent->left == parent ? grandparent->right : grandparent->left;
                return violations;
            }
            else if (temp->right != nullptr and temp->color == "RED" and temp->right->color == "RED") {
                violations = true;
                child = temp->right;
                parent = child->parent;
                grandparent = parent->parent;
                uncle = grandparent->left == parent ? grandparent->right : grandparent->left;
                return violations;
            }
        }
        temp = prev = child->parent;
        while (temp != main_root) {
            temp = temp->parent; //check parent
            if (temp->color == "RED" and ((temp->left != nullptr and temp->left->color == "RED") or (temp->right != nullptr and temp->right->color == "RED"))) {
                violations = true;
                child = (temp->color == "RED" and (temp->left != nullptr and temp->left->color == "RED") ? temp->left : temp->right);
                parent = child->parent;
                grandparent = parent->parent;
                uncle = grandparent->left == parent ? grandparent->right : grandparent->left;
                return violations;
            }
        }
        return violations;
    }
    void FixViolations(Node*& child) {
        Node* uncle;
        Node* parent;
        Node* grandparent;
        while (ViolationsCheck(child, uncle, parent, grandparent)) {
            if (child->parent == nullptr)
                ReColor(child);
            else if (uncle != nullptr and uncle->color == "RED") {
                ReColor(parent); ReColor(grandparent); ReColor(uncle);
            }
            else if (uncle == nullptr or uncle->color == "BLACK") {
                bool FamilyForm = false;
                if (grandparent->right == parent and parent->left == child or grandparent->left == parent and parent->right == child)
                    FamilyForm = true;
                if (FamilyForm) {
                    if (parent->left == child)
                        RightRotate(parent);
                    else if (parent->right == child)
                        LeftRotate(parent);
                }
                else {
                    ReColor(parent); ReColor(grandparent);
                    if (parent->left == child)
                        RightRotate(grandparent);
                    else if (parent->right == child)
                        LeftRotate(grandparent);
                }
            }
        }
        main_root->color = "BLACK";
        main_root->parent = nullptr;
    }
    void Insert(int value) {
        ;
        if (main_root == nullptr) {
            main_root = new Node();
            main_root->data = value;
            main_root->color = "BLACK";
            main_root->left = main_root->right = main_root->parent = nullptr;
            min_el = new Node();
            min_el->data = value;
            min_el->color = "BLACK";
        }
        else {
            Node* temp = new Node();
            temp = main_root;
            Node* prev = temp;
            while (temp != nullptr) {
                value >= temp->data ? temp = temp->right : temp = temp->left;
                if (temp != nullptr)
                    prev = temp;
            }
            Node* child = new Node();
            child->data = value;
            child->color = "RED";
            child->left = child->right = nullptr;
            child->parent = prev;
            value >= prev->data ? prev->right = child : prev->left = child;
            FixViolations(child);
        }
    }
private:
    int size;
    Node* main_root = nullptr;
    Node* min_el;
};

void print_Tree(Node* p, int level)
{
    if (p)
    {
        print_Tree(p->right, level + 3);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << p->data << "(" << p->color << ")" << endl << endl;
        print_Tree(p->left, level + 3);
    }
}


int main() {
    int first_s, second_s, value, func;
    Node* temp;
    do {
        cout << "Input N and M(N - amount of first sequence; M - second sequence) \n";
        cin >> first_s >> second_s;
    } while (first_s <= 0 or first_s > 255 or second_s < 0 or second_s > 255);
    cout << "Enter " << first_s << " numbers from the first sequence: " << endl;
    RBT A(first_s);
    cout << "Enter " << second_s << " numbers from the second sequence: " << endl;
    for (int i = 0; i < second_s; i++)
    {
        cin >> value;
        temp = A.ElSearch(value);
        if (temp == nullptr)
            cout << "Element not found \n";
        else if (temp != nullptr)
            cout << "Element's color:(" << value << ") is " << temp->color << endl;
    }
    return 0;
}
