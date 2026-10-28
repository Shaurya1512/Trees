
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct node {int data;struct node *left,*right;} Node;

Node *newNode(int x){Node *p=malloc(sizeof(Node));if(!p)exit(1);p->data=x;p->left=p->right=NULL;return p;}
Node *create(){int x;if(scanf("%d",&x)!=1||x==-1)return NULL;Node *p=newNode(x);p->left=create();p->right=create();return p;}

void inorder(Node *r){if(r){inorder(r->left);printf("%d ",r->data);inorder(r->right);}}
void preorder(Node *r){if(r){printf("%d ",r->data);preorder(r->left);preorder(r->right);}}
void postorder(Node *r){if(r){postorder(r->left);postorder(r->right);printf("%d ",r->data);}}

void inorderIter(Node *r){Node *s[MAX],*p=r;int top=-1;while(p||top>=0){while(p){s[++top]=p;p=p->left;}p=s[top--];printf("%d ",p->data);p=p->right;}}
void preorderIter(Node *r){if(!r)return;Node *s[MAX];int top=-1;s[++top]=r;while(top>=0){Node *p=s[top--];printf("%d ",p->data);if(p->right)s[++top]=p->right;if(p->left)s[++top]=p->left;}}
void postorderIter(Node *r){if(!r)return;Node *s1[MAX],*s2[MAX];int t1=-1,t2=-1;s1[++t1]=r;while(t1>=0){Node *p=s1[t1--];s2[++t2]=p;if(p->left)s1[++t1]=p->left;if(p->right)s1[++t1]=p->right;}while(t2>=0)printf("%d ",s2[t2--]->data);}
void levelorder(Node *r){if(!r)return;Node *q[MAX];int f=0,b=0;q[b++]=r;while(f<b){Node *p=q[f++];printf("%d ",p->data);if(p->left)q[b++]=p->left;if(p->right)q[b++]=p->right;}}

int count(Node *r){return r?1+count(r->left)+count(r->right):0;}
int leaves(Node *r){if(!r)return 0;if(!r->left&&!r->right)return 1;return leaves(r->left)+leaves(r->right);}
int nonLeaf(Node *r){if(!r||(!r->left&&!r->right))return 0;return 1+nonLeaf(r->left)+nonLeaf(r->right);}
int oneChild(Node *r){if(!r)return 0;return ((!r->left)!=(!r->right))+oneChild(r->left)+oneChild(r->right);}
int twoChildren(Node *r){if(!r)return 0;return (r->left!=NULL&&r->right!=NULL)+twoChildren(r->left)+twoChildren(r->right);}
int onlyLeft(Node *r){if(!r)return 0;return (r->left!=NULL&&r->right==NULL)+onlyLeft(r->left)+onlyLeft(r->right);}
int onlyRight(Node *r){if(!r)return 0;return (r->left==NULL&&r->right!=NULL)+onlyRight(r->left)+onlyRight(r->right);}
int sum(Node *r){return r?r->data+sum(r->left)+sum(r->right):0;}
int countLevel(Node *r,int k){if(!r||k<0)return 0;return k==0?1:countLevel(r->left,k-1)+countLevel(r->right,k-1);}
int height(Node *r){if(!r)return -1;int a=height(r->left),b=height(r->right);return 1+(a>b?a:b);}

void printLeaves(Node *r){if(!r)return;if(!r->left&&!r->right)printf("%d ",r->data);printLeaves(r->left);printLeaves(r->right);}
void printNonLeaf(Node *r){if(!r)return;if(r->left||r->right)printf("%d ",r->data);printNonLeaf(r->left);printNonLeaf(r->right);}
void printOneChild(Node *r){if(!r)return;if((r->left&&!r->right)||(!r->left&&r->right))printf("%d ",r->data);printOneChild(r->left);printOneChild(r->right);}
void printTwoChildren(Node *r){if(!r)return;if(r->left&&r->right)printf("%d ",r->data);printTwoChildren(r->left);printTwoChildren(r->right);}
void printOnlyLeft(Node *r){if(!r)return;if(r->left&&!r->right)printf("%d ",r->data);printOnlyLeft(r->left);printOnlyLeft(r->right);}
void printOnlyRight(Node *r){if(!r)return;if(!r->left&&r->right)printf("%d ",r->data);printOnlyRight(r->left);printOnlyRight(r->right);}

Node *find(Node *r,int x){if(!r||r->data==x)return r;Node *p=find(r->left,x);return p?p:find(r->right,x);}
int depth(Node *r,int x,int d){if(!r)return -1;if(r->data==x)return d;int a=depth(r->left,x,d+1);return a!=-1?a:depth(r->right,x,d+1);}
int nodeHeight(Node *r,int x){return height(find(r,x));}
Node *parentNode(Node *r,int x){if(!r)return NULL;if((r->left&&r->left->data==x)||(r->right&&r->right->data==x))return r;Node *p=parentNode(r->left,x);return p?p:parentNode(r->right,x);}
Node *siblingNode(Node *r,int x){Node *p=parentNode(r,x);if(!p)return NULL;return p->left&&p->left->data==x?p->right:p->left;}

int ancestors(Node *r,int x){if(!r)return 0;if(r->data==x)return 1;if(ancestors(r->left,x)||ancestors(r->right,x)){printf("%d ",r->data);return 1;}return 0;}
void printTree(Node *r){preorder(r);}
void descendants(Node *r,int x){Node *p=find(r,x);if(!p)return;printTree(p->left);printTree(p->right);}
int countDescendants(Node *r,int x){Node *p=find(r,x);return p?count(p)-1:-1;}
void printLeftSubtree(Node *r,int x){Node *p=find(r,x);if(p)preorder(p->left);else printf("Node not found");}
void printRightSubtree(Node *r,int x){Node *p=find(r,x);if(p)preorder(p->right);else printf("Node not found");}

int identical(Node *a,Node *b){if(!a&&!b)return 1;if(!a||!b)return 0;return a->data==b->data&&identical(a->left,b->left)&&identical(a->right,b->right);}
int isMirror(Node *a,Node *b){if(!a&&!b)return 1;if(!a||!b)return 0;return a->data==b->data&&isMirror(a->left,b->right)&&isMirror(a->right,b->left);}
void mirror(Node *r){if(!r)return;Node *t=r->left;r->left=r->right;r->right=t;mirror(r->left);mirror(r->right);}
Node *copyTree(Node *r){if(!r)return NULL;Node *p=newNode(r->data);p->left=copyTree(r->left);p->right=copyTree(r->right);return p;}
void freeTree(Node *r){if(r){freeTree(r->left);freeTree(r->right);free(r);}}

int main(){
    Node *root,*p,*par,*sib,*c;int x;
    printf("Enter tree in preorder (-1 for NULL):\n");
    root=create();

    printf("\nInorder: ");inorder(root);
    printf("\nPreorder: ");preorder(root);
    printf("\nPostorder: ");postorder(root);
    printf("\nIterative inorder: ");inorderIter(root);
    printf("\nIterative preorder: ");preorderIter(root);
    printf("\nIterative postorder: ");postorderIter(root);
    printf("\nLevel order: ");levelorder(root);

    printf("\nTotal=%d Leaves=%d NonLeaf=%d OneChild=%d TwoChildren=%d",count(root),leaves(root),nonLeaf(root),oneChild(root),twoChildren(root));
    printf("\nOnlyLeft=%d OnlyRight=%d Sum=%d Height=%d\n",onlyLeft(root),onlyRight(root),sum(root),height(root));

    printf("Leaf values: ");printLeaves(root);
    printf("\nNon-leaf values: ");printNonLeaf(root);
    printf("\nDegree-1 values: ");printOneChild(root);
    printf("\nDegree-2 values: ");printTwoChildren(root);
    printf("\nOnly-left values: ");printOnlyLeft(root);
    printf("\nOnly-right values: ");printOnlyRight(root);
    printf("\nNodes at depth 2: %d\n",countLevel(root,2));

    printf("\nEnter node value: ");
    if(scanf("%d",&x)==1){
        p=find(root,x);
        if(!p)printf("Node not found\n");
        else{
            par=parentNode(root,x);sib=siblingNode(root,x);
            printf("Parent: ");if(par)printf("%d\n",par->data);else printf("none\n");
            printf("Sibling: ");if(sib)printf("%d\n",sib->data);else printf("none\n");
            printf("Ancestors: ");ancestors(root,x);
            printf("\nDescendants: ");descendants(root,x);
            printf("\nLeft subtree: ");printLeftSubtree(root,x);
            printf("\nRight subtree: ");printRightSubtree(root,x);
            printf("\nDepth=%d Level=%d NodeHeight=%d DescendantCount=%d\n",depth(root,x,0),depth(root,x,0)+1,nodeHeight(root,x),countDescendants(root,x));
        }
    }

    c=copyTree(root);
    printf("Copy identical: %s\n",identical(root,c)?"yes":"no");
    mirror(c);
    printf("Copy is mirror: %s\n",isMirror(root,c)?"yes":"no");
    freeTree(c);freeTree(root);
    return 0;
}
