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

//agciliary functions

node root(node h){
    //TODO debug
    printf("root A[%d] is ", h);
    node fake= h;
    while(fake->hook!=NULL){
        fake=ptr2loc(h->hook, A);
    }
    printf("A[%d]\n", fake);
    return fake;

}

static void link(node f, node c, int d){
    printf("link A[%d] as %s of A[%d]\n",
    ptr2loc(c, A),
    d ? "rightChild" : "leftChild",
    ptr2loc(f, A));
    //TODO
}

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
    showHeaps(v->leftChild);
    showHeaps(v->rightChild);
}
void setV(node v, int val){
    // TODO check if root
    printf("set A[%d] to %d\n", v, val);

    v->v=val;
}
void meld(node h1, node h2){
    printf("Meld A[%d] A[%d]\n", h1, h2);
    node sHelper;
    // should it only be if != istead of < ?
    if (h2->v < h1->v){
        printf("Swap to A[%d] A[%d]\n", h2, h1);
        sHelper = h2;
        h2 = h1;
        h1 = sHelper;
    }
    if(randBit()==1){
        meld(h1->rightChild,h2);
    }
    else{
        meld(h1->leftChild,h2);
    }


    //TODO the rest and then print

}
void decreaseKey(node h, int val){
    // TODO what about parent? what is he pointing to
    node r;
    if(h->hook==NULL){
        h->v=h->v - val;
        printf("decKey A[%d] to %d\n", h, h->v);
    }
    else{
        r=root(h);
        h->hook=NULL;
        h->v=h->v - val;
        printf("decKey A[%d] to %d\n", h, h->v);
        meld(h,r);
    }
    return ;
}
int
main(){
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
            showNode(i1);
            //printf("%d\n",i1);
            break;
        case 'P': 
            /* code */
            scanf("%d", &i1);
            showHeaps(i1);
            break;
        case 'V': 
            /* code */
            scanf("%d", &i1);
            scanf("%d", &i2);
            setV(i1,i2);
            break;
        case 'U': 
            /* code */
            break;
        case 'R': 
            /* code */
            scanf("%d", &i1);
            scanf("%d", &i2);
            decreaseKey(i1, i2);
            break;
        case 'M': 
            /* code */
            break;
        case 'A': 
            /* code */
            break;
        case 'E': 
            /* code */
            break;
        case 'D': 
            /* code */
            break;
                                                                        
        default:
            break;
        }
        opt=getchar();
    }
    free(A);
    return 0;
}
