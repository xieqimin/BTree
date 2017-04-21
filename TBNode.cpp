#include<iostream>
typedef char ElemType;
#define MaxSize 30
using namespace std;
typedef struct node {
	ElemType data;
	struct node *lchild;
	struct node *rchild;
}BTNode;

void CreatBTNode(BTNode *&b, char *str) {
	int top=-1;
	int j = 0,k;
	BTNode *ST[MaxSize];
	BTNode *p=NULL;
	char ch=str[j];
	b = NULL;
	while (ch!='\0')
	{
		switch (ch)
		{
		case '(':top++; ST[top] = p; k = 1; break;
		case ')':top--; break;
		case ',':k = 2; break;
		default:p = new BTNode;
			p->data = ch; p->lchild = NULL; p->rchild = NULL;
			if (b == NULL)
				b = p;
			else {
				if (k == 1) {
					ST[top]->lchild = p; break;
				}
				else {
					ST[top]->rchild = p; break;
				}
			}
		}
		j++;
		ch = str[j];
	}
}
BTNode* FindNode(BTNode *b,ElemType x) {
	BTNode *p;
	BTNode *St[MaxSize];
	if (b == NULL)
		return NULL;
	int n=0, q=0;
	St[q] = b;
	n = 1;
	while (n != 0) {
		if (St[q%MaxSize] == NULL) {
			q++;
			n--;
		}
		else if (St[q%MaxSize]->data == x)
			return St[q%MaxSize];
		else {
			St[(n + q) % MaxSize] = St[q%MaxSize]->lchild;
			n++;
			St[(n + q) % MaxSize] = St[q%MaxSize]->rchild;
			n++;
			q++;
			n--;
		}
	}
}
int BTNodeDepth(BTNode *b) {
	int r, l;
	BTNode *St[MaxSize];
	int p=0, n1, n2, d;
	if (b == NULL)
		return 0;
	St[p] = b;
	n1 = 1;
	d = 0;
	while (n1!=0) {
		n2 = 0;
		d++;
		while (n1!=0) {
			if (St[p%MaxSize] == NULL) {
				p++;
				n1--;
			}
			else
			{
				St[(p + n1 + n2) % MaxSize] = St[p%MaxSize]->rchild;
				n2++;
				St[(p + n1 + n2) % MaxSize] = St[p%MaxSize]->lchild;
				n2++;
				p++;
				n1--;
			}
		}
		n1 = n2;
	}
	return d;
}
void DispBTNode(BTNode *b ) {
	if (b != NULL) {
		cout << b->data;
		if (b->lchild != NULL || b->rchild != NULL) {
			cout << "(";
			DispBTNode(b->lchild);
			cout << ",";
			DispBTNode(b->rchild);
			cout << ")";
		}
	}
}
void DestoryBTNode(BTNode *b) {
	if (b != NULL) {
		DestoryBTNode(b->lchild);
		DestoryBTNode(b->rchild);
		cout << " 销毁" << b->data;
		delete[] b;
	}
}
int main() {
	BTNode *b, *p;
	CreatBTNode(b, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	DispBTNode(b);
	cout << endl<<"H节点:";
	p = FindNode(b, 'H');
	cout << p->data;
	cout << endl << "树的高度:";
	cout << BTNodeDepth(b)<<endl;
	DestoryBTNode(b);
	return 0;
}
