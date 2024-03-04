//Enzo Tres Mediano
//2211731
//Objectivo: Fazer varias funcoes que vao maniupular avores


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//struct--------------------------------------------------------------------------------
typedef struct node Node;
struct node {
	int num;
	Node* left;
	Node* right;
};

//prototypos----------------------------------------------------------------------------
int* createRandNumList();
Node* createNode(int num);
Node* insertionABB(Node* node, int value);
void printTreeTrans(Node* node);
int checkABB(Node* node);
int checkHeight(Node* node);
void tradeTrees(Node* node);
void freetree(Node* node);

//main----------------------------------------------------------------------------------
int main(void) {
	int i;
	int* listNum = createRandNumList();
	for (i = 0; i < 10; i++) {
		printf("%d ", listNum[i]);
	}

	//Insertion ABB
	Node* stump = createNode(listNum[0]);
	for (i = 1; i < 10; i++) {
		insertionABB(stump, listNum[i]);
	}

	//Imprimacao das avores
	printf("\n\n");
	printTreeTrans(stump);

	//Check de ABB
	if (checkABB(stump) == 0) {
		printf("\n\nNot ABB\n");
	}
	else {
		printf("\n\nABB\n");
	}

	//Check altura
	printf("\nHeight: %d\n", checkHeight(stump));


	//TradeNodes
	tradeTrees(stump);
	printTreeTrans(stump);

	free(listNum);
	freetree(stump);
	return 0;
}
//Functions-----------------------------------------------------------------------------

int* createRandNumList() {
	srand(time(NULL));
	int max = 20;
	int min = 1;
	int n = 10;
	int* listofNums = malloc(n * sizeof(int));
	if (listofNums == NULL) {
		printf("Error allocating space");
		exit(2);
	}
	for (int i = 0; i < n; i++) {
		listofNums[i] = (rand() % (max - min + 1));
	}
	return listofNums;
}

Node* createNode(int num) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("Error allocating space");
		exit(2);
	}
	newNode->num = num;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

Node* insertionABB(Node* node, int value) {
	if (node == NULL) {
		return createNode(value);
	}
	else if (value < node->num) {
		node->left = insertionABB(node->left, value);
	}
	else if (value > node->num) {
		node->right = insertionABB(node->right, value);
	}
	return node;
}

void printTreeTrans(Node* node) {
	if (node == NULL) {
		return;
	}

	printf("ptr_no=%p, chave=%d esq=%p dir=%p\n", node, node->num, node->left, node->right);

	if (node->left != NULL) {
		printTreeTrans(node->left);
	}
	
	if (node->right != NULL) {
		printTreeTrans(node->right);
	}
}

int checkABB(Node* node) {
	if (node == NULL) {
		return 1;
	}

	if ((node->left == NULL || node->left->num < node->num) && (node->right == NULL || node->right->num > node->num)) {
		return checkABB(node->left) && checkABB(node->right);
	}

	return 0;
}

int checkHeight(Node* node) {
	if (node == NULL) {
		return 0;
	}

	int leftHeight = checkHeight(node->left);
	int rightHeight = checkHeight(node->right);

	return ((leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1));
}

void tradeTrees(Node* node) {
	if (node == NULL) {
		return;
	}

	Node* temp = node->left;
	node->left = node->right;
	node->right = temp;

	tradeTrees(node->left);
	tradeTrees(node->right);
}

void freetree(Node* node) {
	if (node == NULL) {
		return;
	}
	
	freetree(node->left);
	freetree(node->right);

	free(node);
}

//Foi dificil conseguir achar como era pra inserir em nivel, eu ate nem consegui achar como fazer.