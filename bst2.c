
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 100

typedef struct node { int data; struct node *left,*right; } Node;

Node *newNode(int x){Node *p=malloc(sizeof(Node));if(!p)exit(1);p->data=x;p->left=p->right=NULL;return p;}
Node *insert(Node *r,int x){if(!r)return newNode(x);if(x<r->data)r->left=insert(r->left,x);else if(x>r->data)r->right=insert(r->right,x);return r;}
Node *searchBST(Node *r,int x){if(!r||r->data==x)return r;return x<r->data?searchBST(r->left,x):searchBST(r->right,x);}
Node *minimum(Node *r){if(!r)return NULL;while(r->left)r=r->left;return r;}
Node *maximum(Node *r){if(!r)return NULL;while(r->right)r=r->right;return r;}

void inorder(Node *r){if(r){inorder(r->left);printf("%d ",r->data);inorder(r->right);}}
void preorder(Node *r){if(r){printf("%d ",r->data);preorder(r->left);preorder(r->right);}}
void postorder(Node *r){if(r){postorder(r->left);postorder(r->right);printf("%d ",r->data);}}
void levelorder(Node *r){if(!r)return;Node *q[MAX];int f=0,b=0;q[b++]=r;while(f<b){Node *p=q[f++];printf("%d ",p->data);if(p->left)q[b++]=p->left;if(p->right)q[b++]=p->right;}}

int count(Node *r){return r?1+count(r->left)+count(r->right):0;}
int leaves(Node *r){if(!r)return 0;if(!r->left&&!r->right)return 1;return leaves(r->left)+leaves(r->right);}
int nonLeaf(Node *r){if(!r||(!r->left&&!r->right))return 0;return 1+nonLeaf(r->left)+nonLeaf(r->right);}
int oneChild(Node *r){if(!r)return 0;return ((!r->left)!=(!r->right))+oneChild(r->left)+oneChild(r->right);}
int twoChildren(Node *r){if(!r)return 0;return (r->left!=NULL&&r->right!=NULL)+twoChildren(r->left)+twoChildren(r->right);}
int onlyLeft(Node *r){if(!r)return 0;return (r->left!=NULL&&r->right==NULL)+onlyLeft(r->left)+onlyLeft(r->right);}
int onlyRight(Node *r){if(!r)return 0;return (r->left==NULL&&r->right!=NULL)+onlyRight(r->left)+onlyRight(r->right);}
int sum(Node *r){return r?r->data+sum(r->left)+sum(r->right):0;}
int height(Node *r){if(!r)return -1;int a=height(r->left),b=height(r->right);return 1+(a>b?a:b);}
int countLevel(Node *r,int k){if(!r||k<0)return 0;return k==0?1:countLevel(r->left,k-1)+countLevel(r->right,k-1);}

void printLeaves(Node *r){if(!r)return;if(!r->left&&!r->right)printf("%d ",r->data);printLeaves(r->left);printLeaves(r->right);}
void printNonLeaf(Node *r){if(!r)return;if(r->left||r->right)printf("%d ",r->data);printNonLeaf(r->left);printNonLeaf(r->right);}
void printOneChild(Node *r){if(!r)return;if((r->left&&!r->right)||(!r->left&&r->right))printf("%d ",r->data);printOneChild(r->left);printOneChild(r->right);}
void printTwoChildren(Node *r){if(!r)return;if(r->left&&r->right)printf("%d ",r->data);printTwoChildren(r->left);printTwoChildren(r->right);}
void printOnlyLeft(Node *r){if(!r)return;if(r->left&&!r->right)printf("%d ",r->data);printOnlyLeft(r->left);printOnlyLeft(r->right);}
void printOnlyRight(Node *r){if(!r)return;if(!r->left&&r->right)printf("%d ",r->data);printOnlyRight(r->left);printOnlyRight(r->right);}

Node *parentNode(Node *r,int x){Node *p=NULL;while(r&&r->data!=x){p=r;r=x<r->data?r->left:r->right;}return r?p:NULL;}
Node *siblingNode(Node *r,int x){Node *p=parentNode(r,x);if(!p)return NULL;return p->left&&p->left->data==x?p->right:p->left;}
int depth(Node *r,int x){int d=0;while(r){if(r->data==x)return d;r=x<r->data?r->left:r->right;d++;}return -1;}
int nodeHeight(Node *r,int x){return height(searchBST(r,x));}
void ancestors(Node *r,int x){if(!searchBST(r,x))return;while(r&&r->data!=x){printf("%d ",r->data);r=x<r->data?r->left:r->right;}}
void descendants(Node *r,int x){Node *p=searchBST(r,x);if(!p)return;preorder(p->left);preorder(p->right);}
int countDescendants(Node *r,int x){Node *p=searchBST(r,x);return p?count(p)-1:-1;}
void printLeftSubtree(Node *r,int x){Node *p=searchBST(r,x);if(p)preorder(p->left);}
void printRightSubtree(Node *r,int x){Node *p=searchBST(r,x);if(p)preorder(p->right);}

Node *predecessor(Node *r,int x){Node *p=searchBST(r,x),*ans=NULL;if(!p)return NULL;if(p->left)return maximum(p->left);while(r!=p){if(x>r->data){ans=r;r=r->right;}else r=r->left;}return ans;}
Node *successor(Node *r,int x){Node *p=searchBST(r,x),*ans=NULL;if(!p)return NULL;if(p->right)return minimum(p->right);while(r!=p){if(x<r->data){ans=r;r=r->left;}else r=r->right;}return ans;}

Node *deleteNode(Node *r,int x){if(!r)return NULL;if(x<r->data)r->left=deleteNode(r->left,x);else if(x>r->data)r->right=deleteNode(r->right,x);else{if(!r->left){Node *t=r->right;free(r);return t;}if(!r->right){Node *t=r->left;free(r);return t;}Node *t=minimum(r->right);r->data=t->data;r->right=deleteNode(r->right,t->data);}return r;}

Node *lca(Node *r,int a,int b){if(!searchBST(r,a)||!searchBST(r,b))return NULL;while(r){if(a<r->data&&b<r->data)r=r->left;else if(a>r->data&&b>r->data)r=r->right;else return r;}return NULL;}
Node *floorBST(Node *r,int x){Node *ans=NULL;while(r){if(r->data==x)return r;if(r->data>x)r=r->left;else{ans=r;r=r->right;}}return ans;}
Node *ceilBST(Node *r,int x){Node *ans=NULL;while(r){if(r->data==x)return r;if(r->data<x)r=r->right;else{ans=r;r=r->left;}}return ans;}
int countSmaller(Node *r,int x){if(!r)return 0;if(r->data>=x)return countSmaller(r->left,x);return 1+count(r->left)+countSmaller(r->right,x);}
int countGreater(Node *r,int x){if(!r)return 0;if(r->data<=x)return countGreater(r->right,x);return 1+count(r->right)+countGreater(r->left,x);}
void printRange(Node *r,int a,int b){if(!r)return;if(r->data>a)printRange(r->left,a,b);if(r->data>=a&&r->data<=b)printf("%d ",r->data);if(r->data<b)printRange(r->right,a,b);}
int validRange(Node *r,long long low,long long high){if(!r)return 1;if(r->data<=low||r->data>=high)return 0;return validRange(r->left,low,r->data)&&validRange(r->right,r->data,high);}
void kthSmall(Node *r,int *k,int *ans){if(!r||*k<=0)return;kthSmall(r->left,k,ans);if(*k<=0)return;--*k;if(*k==0){*ans=r->data;return;}kthSmall(r->right,k,ans);}
void kthLarge(Node *r,int *k,int *ans){if(!r||*k<=0)return;kthLarge(r->right,k,ans);if(*k<=0)return;--*k;if(*k==0){*ans=r->data;return;}kthLarge(r->left,k,ans);}
void freeTree(Node *r){if(r){freeTree(r->left);freeTree(r->right);free(r);}}

int main(){
    Node *root=NULL,*p,*s;int n,x,k,ans=0;
    printf("Enter number of BST nodes: ");if(scanf("%d",&n)!=1||n<0)return 1;
    printf("Enter elements: ");for(int i=0;i<n;i++){if(scanf("%d",&x)!=1)return 1;root=insert(root,x);}

    printf("\nInorder: ");inorder(root);
    printf("\nPreorder: ");preorder(root);
    printf("\nPostorder: ");postorder(root);
    printf("\nLevelorder: ");levelorder(root);

    printf("\nTotal=%d Leaves=%d NonLeaf=%d OneChild=%d TwoChildren=%d",count(root),leaves(root),nonLeaf(root),oneChild(root),twoChildren(root));
    printf("\nOnlyLeft=%d OnlyRight=%d Height=%d Sum=%d\n",onlyLeft(root),onlyRight(root),height(root),sum(root));

    printf("Leaf values: ");printLeaves(root);
    printf("\nNon-leaf values: ");printNonLeaf(root);
    printf("\nDegree-1 values: ");printOneChild(root);
    printf("\nDegree-2 values: ");printTwoChildren(root);
    printf("\nOnly-left values: ");printOnlyLeft(root);
    printf("\nOnly-right values: ");printOnlyRight(root);

    if(root)printf("\nMinimum=%d Maximum=%d\n",minimum(root)->data,maximum(root)->data);

    printf("\nEnter key to search: ");if(scanf("%d",&x)!=1)return 1;
    printf("Search: %s\n",searchBST(root,x)?"found":"not found");

    p=predecessor(root,x);s=successor(root,x);
    printf("Predecessor: ");if(p)printf("%d\n",p->data);else printf("none\n");
    printf("Successor: ");if(s)printf("%d\n",s->data);else printf("none\n");

    if(searchBST(root,x)){
        p=parentNode(root,x);s=siblingNode(root,x);
        printf("Parent: ");if(p)printf("%d\n",p->data);else printf("none\n");
        printf("Sibling: ");if(s)printf("%d\n",s->data);else printf("none\n");
        printf("Depth=%d NodeHeight=%d Descendants=%d\n",depth(root,x),nodeHeight(root,x),countDescendants(root,x));
        printf("Ancestors: ");ancestors(root,x);
        printf("\nDescendants: ");descendants(root,x);
        printf("\nLeft subtree: ");printLeftSubtree(root,x);
        printf("\nRight subtree: ");printRightSubtree(root,x);
        printf("\n");
    }

    p=floorBST(root,x);printf("Floor: ");if(p)printf("%d\n",p->data);else printf("none\n");
    p=ceilBST(root,x);printf("Ceil: ");if(p)printf("%d\n",p->data);else printf("none\n");
    printf("Smaller=%d Greater=%d ValidBST=%s\n",countSmaller(root,x),countGreater(root,x),validRange(root,LLONG_MIN,LLONG_MAX)?"yes":"no");
    printf("Nodes from 30 to 70: ");printRange(root,30,70);
    printf("\nNodes at depth 2: %d\n",countLevel(root,2));

    k=3;kthSmall(root,&k,&ans);if(k==0)printf("3rd smallest=%d\n",ans);
    k=3;kthLarge(root,&k,&ans);if(k==0)printf("3rd largest=%d\n",ans);

    printf("Enter key to delete: ");
    if(scanf("%d",&x)==1){root=deleteNode(root,x);printf("Inorder after deletion: ");inorder(root);printf("\n");}
    freeTree(root);return 0;
}
