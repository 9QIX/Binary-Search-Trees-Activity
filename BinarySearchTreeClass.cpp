#include<iostream>
#include<cstdlib>

using namespace std;

struct nod{
    int info;
    struct nod *l;
    struct nod *r;
}*r;

class BSTree{
public:
    static void search(nod *, int);
    static void find(int, nod **, nod **);
    void insert(nod *, nod *);
    static void del(int);
    static void a(nod *,nod *);
    static void b(nod *,nod *);
    static void c(nod *,nod *);
    void show(nod *, int);

    BSTree(){
        r = nullptr;
    }
};

void BSTree::find(int i, nod **par, nod **loc){
    nod *ptr, *ptrsave;
    if(r == nullptr){
        *loc = nullptr;
        *par = nullptr;

        return;
    }
    if(i == r->info){
        *loc = r;
        *par = nullptr;

        return;
    }
    if(i < r->info)
        ptr = r->l;
    else
        ptr = r->r;
    ptrsave = r;

    while(ptr != nullptr){
        if (i == ptr->info){
            *loc = ptr;
            *par = ptrsave;

            return;
        }

        ptrsave = ptr;

        if (i < ptr->info)
            ptr = ptr->l;

        else
            ptr = ptr->r;
    }
    *loc = nullptr;
    *par = ptrsave;
}

void BSTree::search(nod *root, int data){
    int depth = 0;
    nod *temp = new nod;
    temp = root;

    while(temp != nullptr){
        depth++;
        if(temp->info == data){
            cout<<"\nData found at depth: "<<depth<<endl;

            return;
        }
        else if(temp->info > data)
            temp = temp->l;
        else
            temp = temp->r;
    }
    cout << "\nData not found"<<endl;
}

void BSTree::insert(nod *tree, nod *newnode){
    if (r == nullptr){
        r = new nod;
        r->info = newnode->info;
        r->l = nullptr;
        r->r = nullptr;

        cout << "Root Node is Added" << endl;

        return;
    }

    if(tree->info == newnode->info){
        cout << "Element already in the tree" <<endl;

        return;
    }

    if(tree->info > newnode->info){
        if (tree->l != nullptr){
            insert(tree->l, newnode);
        }
        else{
            tree->l = newnode;
            (tree->l)->l = nullptr;
            (tree->l)->r = nullptr;
            cout << "Node Added To Left" << endl;

            return;
        }
    }
    else{
        if(tree->r != nullptr){
            insert(tree->r, newnode);
        }
        else{
            tree->r = newnode;
            (tree->r)->l = nullptr;
            (tree->r)->r = nullptr;
            cout << "Node Added To Right" <<endl;

            return;
        }

    }
}

void BSTree::del(int i){
    nod *par, *loc;
    if(r == nullptr){
        cout << "Tree empty" <<endl;

        return;
    }

    find(i, &par, &loc);
    if(loc == nullptr){
        cout << "Item not present in tree" << endl;

        return;
    }
    if(loc->l == nullptr && loc->r == nullptr){
        a(par, loc);
        cout << "item deleted" << endl;
    }
    if(loc->l!= nullptr && loc->r == nullptr){
        b(par, loc);
        cout << "item deleted" << endl;
    }
    if(loc->l== nullptr && loc->r != nullptr){
        b(par, loc);
        cout << "item deleted" << endl;
    }
    if(loc->l != nullptr && loc->r != nullptr){
        c(par, loc);
        cout << "item deleted" << endl;
    }
    free(loc);
}

void BSTree::a(nod *par, nod *loc ){
    if(par == nullptr){
        r = nullptr;
    }
    else{
        if (loc == par->l)
            par->l = nullptr;
        else
            par->r = nullptr;
    }
}

void BSTree::b(nod *par, nod *loc){
    nod *child;
    if(loc->l!= nullptr)
        child = loc->l;
    else
        child = loc->r;
    if(par == nullptr){
        r = child;
    }
    else{
        if(loc == par->l)
            par->l = child;
        else
            par->r = child;
    }
}

void BSTree::c(nod *par, nod *loc){

    nod *ptr, *ptrsave, *suc, *parsuc;
    ptrsave = loc;
    ptr = loc->r;

    while(ptr->l!= nullptr){
        ptrsave = ptr;
        ptr = ptr->l;
    }

    suc = ptr;
    parsuc = ptrsave;

    if(suc->l == nullptr && suc->r == nullptr)
        a(parsuc, suc);
    else
        b(parsuc, suc);
    if(par == nullptr){
        r = suc;
    }
    else{
        if (loc == par->l)
            par->l = suc;
        else
            par->r = suc;
    }
    suc->l = loc->l;
    suc->r = loc->r;
}

void BSTree::show(nod *ptr, int level){
    int i;
    if(ptr != nullptr){
        show(ptr->r, level+1);
        cout << endl;
        if(ptr == r)
            cout << "\nRoot -> : ";
        else{
            for(i = 0;i < level;i++)
                cout<<" ";
        }
        cout << ptr->info;
        show(ptr->l, level+1);
    }
}

int main(){
    int c, n,item;
    BSTree bst;
    nod *t;
    while (true){
        cout << "\nOperations:" << endl;
        cout << "1.Insert Element (int n)" << endl;
        cout << "2.Delete Element (int n)" << endl;
        cout << "3.Search Element (int n)" << endl;
        cout << "4.Display the tree" << endl;
        cout << "5.Quit" << endl;
        cout << "\nEnter your choice: ";
        cin >> c;

        switch(c){
            case 1:
                t = new nod;
                cout << "Enter the number to be inserted : ";
                cin >> t->info;
                bst.insert(r, t);
                break;
            case 2:
                if (r == nullptr){
                    cout << "Tree is empty, nothing to delete" <<endl;
                    continue;
                }
                cout << "Enter the number to be deleted : ";
                cin >> n;
                bst.del(n);
                break;
            case 3:
                cout << "Search:";
                cin >> item;
                bst.search(r,item);
                break;
            case 4:
                cout << "Display:"<<endl;
                bst.show(r,1);
                cout << endl;
                break;
            case 5:
                exit(1);
            default:
                cout <<"Wrong choice" <<endl;
        }
    }
}

