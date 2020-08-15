#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum Color {RED, BLACK};
FILE *ifp;
char infile[48];
typedef struct Node
{
    char data[256];
    bool color;
    struct Node *left, *right, *parent;
} Node;

Node * tree = NULL;
bool isDuplicate=false;

void ask_the_user_for_the_dictionary_file()
{
    char value[256];
    ifp = fopen(infile,"r");
    if (ifp == NULL)
    {
        system("cls");
        printf("\nFile Doesn't exist !!\n\n\n");
    }
    else
    {
        printf("reading file please wait!!\n\n");
        while(!feof(ifp))
        {
            fgets(value,256,ifp);
            value[strlen(value)-1]='\0';
            insert(value);

        }
        fclose(ifp);
    }
}
void ask_file()
{
    printf("Please enter the name of the dictionary file you wish to access\n");
    scanf("%s", infile);
    ifp = fopen(infile, "r");

    if(ifp == NULL)

        printf("Sorry, could not find that file!\n");

    else

    {

        ask_the_user_for_the_dictionary_file();

    }



}


bool search(Node* root, char val[])
{
    if(root == NULL)
        return false;
    else if(strcmp(root->data,val)==0)
    {
        return true;
    }

    else if(strcmp(val,root->data)==-1)
    {
        return search(root->left, val);
    }

    else
    {

        return search(root->right, val);
    }
}


int maxHeight(int x,int y)
{
    if(x>y)
        return x;
    else
        return y;
}
int height(Node *root)
{
    return (root == NULL ? -1 : 1 + maxHeight(height(root->left), height(root->right)));
}

int size(Node *root)
{
    return (root == NULL ? 0 : 1 + size(root->left) + size(root->right));
}



void inorder(Node *root) //Inorder traversal
{

    if (root == NULL)
        return;

    inorder(root->left);
    printf("%s\t",root->data);
    inorder(root->right);
}




void RL(Node * root, Node **pt) //Rotate Left Function
{
    Node *temp = (*pt)->right;

    (*pt)->right = temp->left;

    if ((*pt)->right != NULL)
        (*pt)->right->parent = pt;

    temp->parent = (*pt)->parent;

    if ((*pt)->parent == NULL)
        tree = temp;

    else if ((*pt) == (*pt)->parent->left)
        (*pt)->parent->left = temp;

    else
        (*pt)->parent->right = temp;

    temp->left = (*pt);
    (*pt)->parent = temp;
}

void RR(Node * root, Node **pt)   //Rotate Right Function
{
    Node *temp = (*pt)->left;

    (*pt)->left = temp->right;

    if ((*pt)->left != NULL)
        (*pt)->left->parent = (*pt);

    temp->parent = (*pt)->parent;

    if ((*pt)->parent == NULL)
        tree = temp;

    else if ((*pt) == (*pt)->parent->left)
        (*pt)->parent->left = temp;

    else
        (*pt)->parent->right = temp;

    temp->right = (*pt);
    (*pt)->parent = temp;
}


void REDYBLACKY(Node *newNode)
{
  //  printf("%s ",newNode->data);
    Node*parent=newNode->parent;
    Node*grand=NULL;
    if (parent&&parent->parent)
    {
        grand=parent->parent;
    }
    else if (!parent&&newNode->color==RED) // only one element and it is red .. it should be black
    {
       // printf("red root\n");
        newNode->color=BLACK;
        return;
    }
    ///////////////////////////
     if (newNode->color==RED&&parent->color==RED)//conflict found
    {
        if (grand->left&&grand->right&&grand->left->color==RED&&grand->right->color==RED)//red uncle
        {
            grand->color=RED;
            grand->left->color=BLACK;
            grand->right->color=BLACK;
          //  printf("red unlce\n");
            REDYBLACKY(grand);
        }
        else {// we have 4 cases 2 triangle and 2 line .... all
            if (newNode==parent->left&&parent==grand->right){//triangle case 1
              //  printf("triangle case 1\n");
                RR(tree,&parent);
                REDYBLACKY(parent);
            }
            else if (newNode==parent->right&&parent==grand->left){//triangle case 2
              //  printf("triangle case 2\n");
                RL(tree,&parent);
                REDYBLACKY(parent);
            }
            else if (newNode==parent->right&&parent==grand->right){//line case 1
               // printf("line case 1\n");
                RL(tree,&grand);
                parent->left->color=RED;
                parent->color=BLACK;
            }
            else if (newNode==parent->left&&parent==grand->left){//line case 1
               // printf("line case 2\n");
                RR(tree,&grand);
                grand->color=RED;
                parent->color=BLACK;

            }


        }
    }
//printf("\n");

}


Node* BSTInsert(Node * root, Node *newNode)
{
    if (root == NULL)
        return newNode;
    if(strcmp(root->data,newNode->data)==0)
    {
        isDuplicate=true;
        return NULL;
    }
    if (strcmp(newNode->data,root->data)==-1)
    {
        root->left  = BSTInsert(root->left, newNode);
        root->left->parent = root;
    }
    else if (strcmp(newNode->data, root->data)==1)
    {
        root->right = BSTInsert(root->right, newNode);
        root->right->parent = root;
    }
    return root;
}
Node * newNodeF(char data[])
{
    Node * node =   (Node*)malloc(sizeof(Node));
    strcpy(node->data,data);
    node->left = node->right = node->parent = NULL;
    node->color= RED;
    return node;
}
void insert(char data[])
{
    if(!search(tree,data))
    {
        Node * newNode = newNodeF(data); // Create a new node, with the value data.
        tree = BSTInsert(tree, newNode);//Insets like a normal Binary Search Tree.
        REDYBLACKY(newNode); //Converts into red black tree by fixing the violations.
        isDuplicate=false;
    }
    else
    {
        isDuplicate=true;
       // printf("The entry already exists\n");
    }
}
bool isEmpty()
{
    if (tree==NULL)
        return true;
    else
        return false;
}
bool isrbt(Node*tree){
if (!tree){
    return true;
}
else if (tree->color==RED&&tree->left&&tree->left->color==RED){
    return false;
}
else if (tree->color==RED&&tree->right&&tree->right->color==RED){
    return false;
}
else return ( isrbt(tree->left)&&isrbt(tree->right));
}
int main()
{
    char value[256];
        char ch[2];


start:
    system("cls");

    printf  ("1. For inserting a new word  \n");
    printf  ("2. For searching for an word  \n");
    printf  ("3. For traversing the tree  \n");
    printf  ("4. For viewing tree's height/size  \n");
    printf  ("5. For loading the dictionary  \n");

    printf  ("\n9. For exiting the selection/main-menu\n\n");
    printf("Please enter your selection\n");
    scanf("%s",&ch);


    if(strcmp(ch,"1")==0)
    {


        printf("Please enter the value you wish to insert\n");
        fflush(stdin);
        gets(value);
        insert(value);
        if(!isDuplicate)
        {
            printf("The value was inserted succesfuly\n");
            printf("The height of the tree is: %d \nThe size of the tree is: %d\n\n", height(tree),size(tree));
        }
        else
            printf("The entry already exists\n");;

    }
    else if(strcmp(ch,"2")==0)
    {
        if(isEmpty())
        {
            printf("You cannot search in an empty tree\n");
        }
        else
            printf("Please enter the value you wish to search for\n");
        fflush(stdin);
        gets(value);
        if(search(tree,value))
        {
            printf("Found\n");
        }
        else
            printf("Not found\n");
    }
    else if(strcmp(ch,"3")==0)
    {
        if(isEmpty())
            printf("You cannot traverse an empty tree\n");
        else inorder(tree);
    }

    else if (strcmp(ch,"4")==0)
    {
        if(isEmpty())
        {
            printf("The tree is empty\n");
        }
        else
            printf("The height of the tree is: %d \nThe size of the tree is: %d\n\n", height(tree),size(tree));

    }
    else if (strcmp(ch,"5")==0)
    {
        ask_file();
        printf("\n%d",isrbt(tree));
    }

    else if (strcmp(ch,"9")==0)
    {
        goto end;
    }
    else{printf("error\n");}
    printf("press any key to continue");
    getch();
    goto start;

end:return 0;
}
