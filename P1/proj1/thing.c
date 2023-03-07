#include <stdio.h>
#include <stdlib.h>
#define _DEFAULT_SOURCE
#include <stdlib.h>
typedef struct node* node;
struct node
{
int v; /* The value to store */
node leftChild; /* Left child */
node rightChild; /* Right child */
node *hook; /* Pointer to field in the father node */
};

node A;

/*agciliary functions*/





static int randBit(void){
    static unsigned int M = 0;
    static unsigned int P;
    int r;
    if(0 == M){
        M = ~0;
        P = random();
    }
    r = P & 1;
    M = M>>1;
    P = P>>1;
    printf("Flipped a %d\n", r);
    return r;
}

int ptr2loc(node v, node A)
{
    int r;
    r = -1;
    if(NULL != v)
        r = ((size_t) v - (size_t) A) / sizeof(struct node);
    return (int)r;
}
node root(node h){
    /*TODO remove comment*/
    node fake= h;
    printf("root A[%d] is ", ptr2loc(h,A));
    while(fake->hook!=NULL){
        /*printf("c %d\n",ptr2loc(h, A));*/
        fake=&A[ptr2loc((node)fake->hook, A)];
        /*printf("f %d\n",ptr2loc(fake,A));*/
    }
    printf("A[%d]\n", ptr2loc(fake,A));
    return fake;

}
/*0 == false everything else == true*/
static void link(node f, node c, int d){
    printf("link A[%d] as %s of A[%d]\n",
    ptr2loc(c, A),
    d ? "rightChild" : "leftChild",
    ptr2loc(f, A));
    if(d){
        /*make c rightChild of f*/
        f->rightChild=c;
        c->hook=&f->rightChild;
    }
    else{
        f->leftChild=c;
        c->hook=&f->leftChild;
    }
}
void showNode(node v)
{
    int f;
    if(NULL == v)
        printf("NULL\n");
    else {
        printf("node: %d ", ptr2loc(v, A));
        printf("v: %d ", v->v);
        printf("leftChild: %d ", ptr2loc(v->leftChild, A));
        printf("rightChild: %d ", ptr2loc(v->rightChild, A));
        f = ptr2loc((node)v->hook, A);
        printf("father: %c %d",
            &(A[f].leftChild) == v->hook ? 'l' : 'r',
            f);
        printf("\n");
        }
}
void showHeaps(node v){
    showNode(v);
    if(v->leftChild!=NULL)
        showHeaps(v->leftChild);
    if(v->rightChild!=NULL)
        showHeaps(v->rightChild);
}
void setV(node v, int val){
    /* TODO check if root*/
    
    /*v->hook=NULL;*/
    v->v=val;
}
int meld(node h1, node h2){
    node sHelper;
    int i;
    printf("Meld A[%d] A[%d]\n", ptr2loc(h1,A), ptr2loc(h2,A));
    if(h1==NULL) return ptr2loc(h2,A);

    /* should it only be if != istead of < ?*/
    if (h2->v < h1->v){
        printf("Swap to A[%d] A[%d]\n", ptr2loc(h2,A), ptr2loc(h1,A));
        sHelper = h2;
        h2 = h1;
        h1 = sHelper;
    }
    if(randBit()==1){
        i=meld(h1->rightChild,h2);
        link(h1,&A[i],1);
        return ptr2loc(h1,A);
    }
    else{
        i=meld(h1->leftChild,h2);
        link(h1,&A[i],0);
        return ptr2loc(h1,A);
    }
    /*TODO remove?*/
}
int decreaseKey(node h, int val){
    node r;
    if(h->hook==NULL){
        h->v=val;
        return ptr2loc(h,A);
    }
    else{
        r=root(h);
        *h->hook=NULL;
        h->hook=NULL;
        h->v=val;
        return meld(r,h);
    }
}

int vMin(node n){
    int i;
    node r;
    r = root(n);
    i= r->v;
    return i;
}
int idOfMin(node n){
    int i;
    node r;
    r = root(n);
    i= ptr2loc(r,A);
    return i;
}
int extractMin(node n){
    node r;
    int i;
    printf("extractMin A[%d]\n", ptr2loc(n,A));
    r = root(n);
    r->v=0;
    if(r->leftChild==NULL && r->rightChild==NULL){
        return ptr2loc(n,A);
    }
    /*if rightchild exists alone*/
    if(r->leftChild==NULL){
        r->rightChild->hook=NULL;
        i = ptr2loc(r->rightChild,A);
        r->rightChild=NULL;
        return i;
    }
    /*if leftchild exists alone*/
    if(r->rightChild==NULL){
        r->leftChild->hook=NULL;
        i = ptr2loc(r->leftChild,A);
        r->leftChild=NULL;
        return i;
    }
    /*if both exist*/
    r->leftChild->hook=NULL;
    r->rightChild->hook=NULL;
    /*TODO set r->leftChild rightChild to null?*/
    i = meld(r->leftChild,r->rightChild);
    r->leftChild=NULL;
    r->rightChild=NULL;
    return i;   
}

int deleteNode(node n){
    node r;
    int i;
    if(n->hook==NULL){
        return extractMin(n);
    }
    /*else*/
    r=root(n);
    /*TODO check if cut is right*/
    *n->hook=NULL;
    n->hook=NULL;
    if(n->leftChild==NULL && n->rightChild==NULL){
        return ptr2loc(r,A);
    }
    i=extractMin(n);
    /*else*/
    /*TODO check if A + i is right*/
    return meld(r,A + i);
}

int main(){
    int n;
    int seed;
    int i1;
    int i2;
    int opt;
    /*scanf("%d",&n);
    printf("%d\n",n);*/
    scanf("%d", &n);
    A = (node)calloc(n, sizeof(struct node));

    scanf("%d",&seed);
    srandom(seed);
    opt=' ';
    while(opt != EOF && opt != 'X'){
        switch (opt)
        {
        case 'S': 
            /* code */
            scanf("%d", &i1);
            showNode(A + i1);
            /*printf("%d\n",i1);*/
            break;
        case 'P': 
            /* code */
            scanf("%d", &i1);
            showHeaps(A + i1);
            break;
        case 'V': 
            /* code */
            scanf("%d", &i1);
            scanf("%d", &i2);
            printf("set A[%d] to %d\n", i1, i2);
            setV(A + i1,i2);
            break;
        case 'U': 
            /* code */
            scanf("%d", &i1);
            scanf("%d", &i2);
            printf("%d\n",meld(A + i1, A + i2));
            break;
        case 'R': 
            /* code */
            scanf("%d", &i1);
            scanf("%d", &i2);
            printf("decKey A[%d] to %d\n", i1, i2);
            printf("%d\n",decreaseKey(A + i1, i2));
            break;
        case 'M': 
            /* code */
            scanf("%d", &i1);
            printf("min A[%d]\n", i1);
            printf("%d\n",vMin(A + i1));
            break;
        case 'A': 
            /* code */
            scanf("%d", &i1);
            printf("%d\n",idOfMin(A + i1));
            break;
        case 'E': 
            /* code */
            scanf("%d", &i1);
            printf("%d\n",extractMin(A + i1));
            break;
        case 'D': 
            /* code */
            scanf("%d", &i1);
            printf("delete A[%d]\n", i1);
            printf("%d\n",deleteNode(A + i1));
            break;
                                                                        
        default:
            break;
        }
        opt=getchar();
    }
    printf("Final configuration:\n");
    for(i1=0;i1<n;i1++){
        showNode(A + i1);
    }
    free(A);
    return 0;
}
