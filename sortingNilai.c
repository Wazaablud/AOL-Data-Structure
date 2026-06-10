#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX 100

typedef struct {
	char nim[20];
	char nama[50];
	float nilai;
} Mahasiswa;

Mahasiswa data[MAX];
int jumlahData = 0;


// POINTER

void swap(Mahasiswa *a, Mahasiswa *b) {
	Mahasiswa temp = *a;
	*a = *b;
	*b = temp;
}

// QUICK SORT

int partition(int low, int high) {
	float pivot = data[high].nilai;
	
	int i = low - 1;
	
	for(int j = low; j < high; j++) {
		if(data[j].nilai < pivot) {
			i++;
			swap(&data[i], &data[j]);
		}
	}
	
	swap(&data[i + 1], &data[high]);
	
	return i + 1;
}

void quickSort(int low, int high) {
	if(low < high) {
		int pi = partition(low, high);
		
		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}


// MERGE SORT

void merge(int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	
	Mahasiswa L[n1];
	Mahasiswa R[n2];
	
	for(int i = 0; i < n1; i++) {
		L[i] = data[left + 1];
	}
	
	for(int j = 0; j < n2; j++) {
		R[j] = data[mid + 1 + j];
	}
	
	int i = 0;
	int j = 0;
	int k = left;
	
	while(i < n1 && j < n2) {
		if(L[i].nilai <= R[j].nilai) {
			data[k++] = L[i++];
		}
		else {
			data[k++] = R[j++];
		}
	}
	
	while(i < n1) {
		data[k++] = L[i++];
	}
	
	while(j < n2) {
		data[k++] = R[j++];
	}
}

void mergeSort(int left, int right) {
	if(left < right) {
		int mid = left + (right - left) / 2;
		
		mergeSort(left, mid);
		mergeSort(mid + 1, right);
		
		merge(left, mid, right);
	}
}


// HEAP SORT

void heapify(int n, int i) {
	int terbesar = i;
	
	int kiri = 2 * i + 1;
	int kanan = 2 * i + 2;
	
	if(kiri < n && data[kiri].nilai > data[terbesar].nilai) {
		terbesar = kiri;
	}
	
	if(kanan < n && data[kanan].nilai > data[terbesar].nilai) {
		terbesar = kanan;
	}
	
	if(terbesar != i) {
		swap(&data[i], &data[terbesar]);
		
		heapify(n, terbesar);
	}
}

void heapSort() {
	for(int i = jumlahData / 2 - 1; i >= 0; i--) {
		heapify(jumlahData, i);
	}
	
	for(int i = jumlahData - 1; i > 0; i--) {
		swap(&data[0], &data[i]);
		
		heapify(i, 0);
	}
}


// LINKED LIST

typedef struct Node {
	Mahasiswa mhs;
	struct Node *next;
} Node;

Node *head = NULL;

void insertLinkedList(Mahasiswa mhs) {
	Node *baru = (Node*)malloc(sizeof(Node));
	
	baru->mhs = mhs;
	baru->next = NULL;
	
	if(head == NULL) {
		head = baru;
		return;
	}
	
	Node *temp = head;
	
	while(temp->next != NULL) {
		temp = temp->next;
	}
	
	temp->next = baru;
}

void tampilLinkedList() {
	Node *temp = head;
	
	printf("\n===== LINKED LIST =====\n");
	
	while(temp != NULL) {
		printf("%s | %s | %.2f\n",
			   temp->mhs.nim,
			   temp->mhs.nama,
			   temp->mhs.nilai);
			   
		temp = temp->next;
	}
}

void hapusLinkedList(char nim[]) {
	Node *temp = head;
	Node *prev = NULL;
	
	while(temp != NULL && strcmp(temp->mhs.nim, nim) != 0) {
		prev = temp;
		temp = temp->next;
	}
	
	if(temp == NULL) {
		return;
	}
	
	if(prev == NULL) {
		head = temp->next;
	}
	else {
		prev->next = temp->next;
	}
	
	free(temp);
}


// HASH TABLE

#define TABLE_SIZE 101

typedef struct HashNode {
	Mahasiswa mhs;
	struct HashNode *next;
} HashNode;

HashNode *hashTable[TABLE_SIZE];

int hashFunction(char nim[]) {
	int sum = 0;
	
	for(int i = 0; nim[i] != '\0'; i++) {
		sum += nim[i];
	}
	
	return sum % TABLE_SIZE;
}

void insertHash(Mahasiswa mhs) {
	int index = hashFunction(mhs.nim);
	
	HashNode *baru = (HashNode*)malloc(sizeof(HashNode));
	
	baru->mhs = mhs;
	baru->next = hashTable[index];
	
	hashTable[index] = baru;
}

void searchHash(char nim[]) {
	int index = hashFunction(nim);
	
	HashNode *temp = hashTable[index];
	
	while(temp != NULL) {
		if(strcmp(temp->mhs.nim, nim) == 0) {
			printf("\nData ditemukan!\n");
			printf("NIM   : %s\n", temp->mhs.nim);
			printf("Nama  : %s\n", temp->mhs.nama);
			printf("Nilai : %.2f\n", temp->mhs.nilai);
			
			return;
		}
		
		temp = temp->next;
	}
	
	printf("Data tidak ditemukan!\n");
}


// BST

typedef struct BSTNode {
	Mahasiswa mhs;
	
	struct BSTNode *left;
	struct BSTNode *right;
} BSTNode;

BSTNode *root = NULL;

BSTNode* createBSTNode(Mahasiswa mhs) {
	BSTNode *baru = (BSTNode*)malloc(sizeof(BSTNode));
	
	baru->mhs = mhs;
	
	baru->left = NULL;
	baru->right = NULL;
	
	return baru;
}

BSTNode* insertBST(BSTNode *root, Mahasiswa mhs) {
	if(root == NULL) {
		return createBSTNode(mhs);
	}
	
	if(mhs.nilai < root->mhs.nilai) {
		root->left = insertBST(root->left, mhs);
	}
	else {
		root->right = insertBST(root->right, mhs);
	}
	
	return root;
}

void inorderBST(BSTNode *root) {
	if(root != NULL) {
		inorderBST(root->left);
		
		printf("%s | %s | %.2f\n",
			   root->mhs.nim,
			   root->mhs.nama,
			   root->mhs.nilai);
		
		inorderBST(root->right);
	}
}

BSTNode* searchBST(BSTNode *root, float nilai) {
	if(root == NULL) {
		return NULL;
	}
	
	if(root->mhs.nilai == nilai) {
		return root;
	}
	
	if(nilai < root->mhs.nilai) {
		return searchBST(root->left, nilai);
	}
	
	return searchBST(root->right, nilai);
}

// AVL TREE

typedef struct AVLNode {
	Mahasiswa mhs;
	
	int height;
	
	struct AVLNode *left;
	struct AVLNode *right;
} AVLNode;

AVLNode *avlRoot = NULL;

int getHeight(AVLNode *node) {
	if(node == NULL) {
		return 0;
	}
	
	return node->height;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

AVLNode* createAVLNode(Mahasiswa mhs) {
	AVLNode *baru = (AVLNode*)malloc(sizeof(AVLNode));
	
	baru->mhs = mhs;
	
	baru->left = NULL;
	baru->right = NULL;
	
	baru->height = 1;
	
	return baru;
}

int getBalance(AVLNode *node) {
	if(node == NULL) {
		return 0;
	}
	
	return getHeight(node->left) - getHeight(node->right);
}

AVLNode* rightRotate(AVLNode *y) {
	AVLNode *x = y->left;
	AVLNode *T2 = x->right;
	
	x->right = y;
	y->left = T2;
	
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	
	return x;
}

AVLNode* leftRotate(AVLNode *x) {
	AVLNode *y = x->right;
	AVLNode *T2 = y->left;
	
	y->right = x;
	x->right = T2;
	
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	
	return y;
}

AVLNode* insertAVL(AVLNode* node, Mahasiswa mhs) {
	if(node == NULL) {
		return createAVLNode(mhs);
	}
	
	if(mhs.nilai < node->mhs.nilai) {
		node->left = insertAVL(node->left, mhs);
	}
	else {
		node->right = insertAVL(node->right, mhs);
	}
	
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	
	int balance = getBalance(node);
	
	/* LEFT LEFT */
	if(balance > 1 && mhs.nilai > node->left->mhs.nilai) {
		return rightRotate(node);
	}
	
	/* RIGHT RIGHT */
	if(balance < -1 && mhs.nilai > node->right->mhs.nilai) {
		return leftRotate(node);
	}
	
	/* LEFT RIGHT */
	if(balance > 1 && mhs.nilai > node->left->mhs.nilai) {
		node->left = leftRotate(node->left);
		
		return rightRotate(node);
	}
	
	/* RIGHT LEFT */
	if(balance < -1 && mhs.nilai < node->right->mhs.nilai) {
		node->right = rightRotate(node->right);
		
		return leftRotate(node);
	}
	
	return node;
}

void inorderAVL(AVLNode *root) {
	if(root != NULL) {
		inorderAVL(root->left);
		
		printf("%s | %s | %.2f\n",
			   root->mhs.nim,
			   root->mhs.nama,
			   root->mhs.nilai);
		
		inorderAVL(root->right);
	}
}

AVLNode* searchAVL(AVLNode *root, float nilai) {
	if(root == NULL) {
		return NULL;
	}
	
	if(root->mhs.nilai == nilai) {
		return root;
	}
	
	if(nilai < root->mhs.nilai) {
		return searchAVL(root->left, nilai);
	}
	
	return searchAVL(root->right, nilai);
}


// HEAP

#define MAX_HEAP 100

Mahasiswa heap[MAX_HEAP];
int heapSize = 0;

void heapifyUp(int index) {
	while(index > 0) {
		int parent = (index - 1) / 2;
		
		if(heap[parent].nilai >= heap[index].nilai) {
			break;
		}
		
		swap(&heap[parent], &heap[index]);
		
		index = parent;
	}
}

void insertHeap(Mahasiswa mhs) {
	if(heapSize >= MAX_HEAP) {
		return;
	}
	
	heap[heapSize] = mhs;
	
	heapifyUp(heapSize);
	
	heapSize++;
}

void heapifyDown(int index) {
	int terbesar = index;
	
	int kiri = 2 * index + 1;
	int kanan = 2 * index + 2;
	
	if(kiri < heapSize && heap[kiri].nilai > heap[terbesar].nilai) {
		terbesar = kiri;
	}
	
	if(kanan < heapSize && heap[kanan].nilai > heap[terbesar].nilai) {
		terbesar = kanan;
	}
	
	if(terbesar != index) {
		swap(&heap[index], &heap[terbesar]);
		
		heapifyDown(terbesar);
	}
}

void tampilTop1() {
	if(heapSize == 0) {
		printf("Belum ada data.\n");
		return;
	}
	
	printf("\n===== TOP 1 =====\n");
	printf("NIM   : %s\n", heap[0].nim);
	printf("Nama  : %s\n", heap[0].nama);
	printf("Nilai : %.2f\n", heap[0].nilai);
}

void tampilTopN(int n) {
	if(heapSize == 0) {
		printf("Belum ada data.\n");
		return;
	}
	
	Mahasiswa tempHeap[MAX_HEAP];
	int tempSize = heapSize;
	
	for(int i = 0; i < heapSize; i++) {
		tempHeap[i] = heap[i];
	}
	
	printf("\n===== TOP %d =====\n", n);
	
	for(int i = 0; i < n && tempSize > 0; i++) {
		printf("%d. %s | %s | %.2f\n",
			   i + 1,
			   tempHeap[0].nim,
			   tempHeap[0].nama,
			   tempHeap[0].nilai);
		   
		tempHeap[0] = tempHeap[tempSize - 1];
		
		tempSize--;
		
		int idx = 0;
		
		while(1) {
			int terbesar = idx;
			int kiri = 2 * idx + 1;
			int kanan = 2 * idx + 2;
			
			if(kiri < tempSize && tempHeap[kiri].nilai > tempHeap[terbesar].nilai) {
				terbesar = kiri;
			}
			
			if(kanan < tempSize && tempHeap[kanan].nilai > tempHeap[terbesar].nilai) {
				terbesar = kanan;
			}
			
			if(terbesar == idx) {
				break;
			}
			
			Mahasiswa temp = tempHeap[idx];
			tempHeap[idx] = tempHeap[terbesar];
			tempHeap[terbesar] = temp;
			idx = terbesar;
		}
	}
}


// TRIE

#define ALPHABET_SIZE 26

typedef struct TrieNode {
	struct TrieNode *children[ALPHABET_SIZE];
	int isEnd;
	char nama[50];
} TrieNode;

TrieNode *trieRoot = NULL;

TrieNode* createTrieNode() {
	TrieNode *node = (TrieNode*)malloc(sizeof(TrieNode));
	
	node->isEnd = 0;
	
	strcpy(node->nama, "");
	
	for(int i = 0; i < ALPHABET_SIZE; i++) {
		node->children[i] = NULL;
	}
	
	return node;
}

void insertTrie(char *nama) {
	TrieNode *current = trieRoot;
	
	for(int i = 0; nama[i] != '\0'; i++) {
		char c = tolower(nama[i]);
		
		if(c < 'a' || c > 'z') {
			continue;
		}
		
		int index = c - 'a';
		
		if(current->children[index] == NULL) {
			current->children[index] = createTrieNode();
		}
		
		current = current->children[index];
	}
	
	current->isEnd = 1;
	strcpy(current->nama, nama);
}

void tampilSemuaTrie(TrieNode *node) {
	if(node == NULL) {
		return;
	}
	
	if(node->isEnd) {
		printf("%s\n", node->nama);
	}
	
	for(int i = 0; i < 26; i++) {
		tampilSemuaTrie(node->children[i]);
	}
}

void searchPrefix(char *prefix) {
	TrieNode *current = trieRoot;
	
	for(int i = 0; prefix[i] != '\0'; i++) {
		char c = tolower(prefix[i]);
		
		if(c < 'a' || c > 'z') {
			continue;
		}
		
		int index = c - 'a';
		
		if(current->children[index] == NULL) {
			printf("Tidak ditemukan!\n");
			return;
		}
		
		current = current->children[index];
	}
	
	printf("\nHasil pencarian:\n");
	tampilSemuaTrie(current);
}


// DISJOINT SET

int parent[MAX];

void makeSet(int n) {
	for(int i = 0; i < n; i++) {
		parent[i] = i;
	}
}

int findSet(int x) {
	if(parent[x] == x) {
		return x;
	}
	
	return parent[x] = findSet(parent[x]);
}

void unionSet(int a, int b) {
	int rootA = findSet(a);
	int rootB = findSet(b);
	
	if(rootA != rootB) {
		parent[rootB] = rootA;
	}
}

char getGrade(float nilai) {
	if(nilai >= 85) {
		return 'A';
	}
	
	if(nilai >= 70) {
		return 'B';
	}
	
	if(nilai >= 55) {
		return 'C';
	}
	
	return 'D';
}

void buildDisjointSet() {
	makeSet(jumlahData);
	
	for(int i = 0; i < jumlahData; i++) {
		for(int j = i + 1; j < jumlahData; j++) {
			if(getGrade(data[i].nilai) == getGrade(data[j].nilai)) {
				unionSet(i, j);
			}
		}
	}
}


// ARRAY + POINTER

void tampilKelompok() {
	buildDisjointSet();
	
	printf("\n===== KELOMPOK NILAI ======\n");
	
	for(int i = 0; i < jumlahData; i++) {
		if(findSet(i) == i) {
			printf("\nKelompok %c\n", getGrade(data[i].nilai));
			
			for(int j = 0; j < jumlahData; j++) {
				if(findSet(j) == i) {
					printf("%s | %s | %.2f\n",
						   data[j].nim,
						   data[j].nama,
						   data[j].nilai);
				}
			}
		}
	}
}

void tambahData() {
	if(jumlahData >= MAX) {
		printf("Data penuh!\n");
		return;
	}
	
	Mahasiswa baru;
	
	printf("Masukkan NIM   : ");
	scanf("%s", baru.nim);
	
	printf("Masukkan Nama  : ");
	scanf(" %[^\n]", baru.nama);
	
	printf("Masukkan Nilai : ");
	while(scanf("%f", &baru.nilai) != 1) {
		printf("Input harus berupa angka!\n");
		printf("Masukkan Nilai : ");
		
		while(getchar() != '\n');
	}
	
	data[jumlahData] = baru;
	insertLinkedList(baru);
	insertHash(baru);
	root = insertBST(root, baru);
	avlRoot = insertAVL(avlRoot, baru);
	insertHeap(baru);
	insertTrie(baru.nama);
	
	jumlahData++;
	
	printf("\nData berhasil ditambahkan!\n");
}

void tampilData() {
	if(jumlahData == 0) {
		printf("\nBelum ada data.\n");
		return;
	}
	
	printf("\n================================================\n");
	printf("%-15s %-20s %-10s\n",
		   "NIM",
		   "Nama",
		   "Nilai");
	printf("================================================\n");
	
	for(int i = 0; i < jumlahData; i++) {
		printf("%-15s %-20s %-10.2f\n",
			   data[i].nim,
			   data[i].nama,
			   data[i].nilai);
	}
}

void hapusData() {
	char nim[20];
	int posisi = -1;
	
	printf("Masukkan NIM yang ingin dihapus: ");
	scanf("%s", nim);
	
	for(int i = 0; i < jumlahData; i++) {
		if(strcmp(data[i].nim, nim) == 0) {
			posisi = i;
			break;
		}
	}
	
	if(posisi == -1) {
		printf("Data tidak ditemukan!\n");
		return;
	}
	
	for(int i = posisi; i < jumlahData - 1; i++) {
		data[i] = data[i + 1];
	}
	
	jumlahData--;
	
	printf("data berhasil dihapus!\n");
	
	hapusLinkedList(nim);
}


void copyData(Mahasiswa source[], Mahasiswa destination[], int n) {
    for(int i = 0; i < n; i++) {
        destination[i] = source[i];
    }
}


// MENU

int main() {
	trieRoot = createTrieNode();
	int pilihan;	
	
	do {
		printf("\n");
		printf("===== SISTEM DATA MAHASISWA =====\n");
		printf("1. Tambah Data\n");
		printf("2. Tampilkan Data\n");
		printf("3. Hapus Data\n");
		printf("4. Quick Sort\n");
		printf("5. Merge Sort\n");
		printf("6. Heap Sort\n");
		printf("7. Tampilkan Linked List\n");
		printf("8. Cari NIM (Hash Table)\n");
		printf("9. Tampilkan BST (Indorder)\n");
		printf("10. Cari Nilai di BST\n");
		printf("11. Tampilkan AVL Tree\n");
		printf("12. Cari Nilai di AVL\n");
		printf("13. Tampilkan Top 1\n");
		printf("14. Tampilkan Top N\n");
		printf("15. Cari Nama (Trie)\n");
		printf("16. Tampilkan Kelompok Nilai\n");
		printf("17. Bandingkan Semua Sorting\n");
		printf("0. Keluar\n");
		printf("Pilihan : ");
		scanf("%d", &pilihan);
		
		switch(pilihan) {
			case 1:
				tambahData();
				break;
			
			case 2:
				tampilData();
				break;
			
			case 3:
				hapusData();
				break;
			
			case 4: {
				clock_t start = clock();
				quickSort(0, jumlahData - 1);
				clock_t end = clock();
				double waktu = ((double)(end - start)) / CLOCKS_PER_SEC;

    			printf("\nData berhasil diurutkan dengan Quick Sort.\n");
				printf("Waktu eksekusi : %.6f detik\n", waktu);
				break;
			}
				
			case 5: {
    			clock_t start = clock();
				mergeSort(0, jumlahData - 1);
				clock_t end = clock();
				double waktu = ((double)(end - start)) / CLOCKS_PER_SEC;
				
				printf("\nData berhasil diurutkan dengan Merge Sort.\n");
				printf("Waktu eksekusi : %.6f detik\n", waktu);
				break;
			}
			
			case 6: {
    			clock_t start = clock();
				heapSort();
				clock_t end = clock();
				double waktu = ((double)(end - start)) / CLOCKS_PER_SEC;

				printf("\nData berhasil diurutkan dengan Heap Sort.\n");
				printf("Waktu eksekusi : %.6f detik\n", waktu);
				break;
			}
			
			case 7:
				tampilLinkedList();
				break;
				
			case 8: {
				char nimCari[20];
				
				printf("Masukkan NIM : ");
				scanf("%s", nimCari);
				
				searchHash(nimCari);
				break;
			}
			
			case 9:
				printf("\n===== BST INORDER =====\n");
				inorderBST(root);
				break;
			
			case 10: {
				float nilaiCari;
				
				printf("Masukkan Nilai : ");
				scanf("%f", &nilaiCari);
				
				BSTNode *hasil = searchBST(root, nilaiCari);
				
				if(hasil != NULL) {
					printf("\nData ditemukan!\n");
					printf("%s | %s | %.2f\n",
						   hasil->mhs.nim,
						   hasil->mhs.nama,
						   hasil->mhs.nilai);
				}
				else {
					printf("Data tidak ditemukan!\n");
				}
				break;
			}
			
			case 11:
				printf("\n===== AVL TREE =====\n");
				inorderAVL(avlRoot);
				break;
			
			case 12: {
				float nilaiCari;
				
				printf("Masukkan Nilai : ");
				scanf("%f", &nilaiCari);
				
				AVLNode *hasil = searchAVL(avlRoot, nilaiCari);
				
				if(hasil != NULL) {
					printf("\nData ditemukan!\n");
					printf("%s | %s | %.2f\n",
						   hasil->mhs.nim,
						   hasil->mhs.nama,
						   hasil->mhs.nilai);
				}
				else {
					printf("Data tidak ditemukan!\n");
				}
				break;
			}
			
			case 13:
				tampilTop1();
				break;
			
			case 14: {
				int n;
				
				printf("Top berapa? ");
				scanf("%d", &n);
				
				tampilTopN(n);
				break;
				
				break;
			}
			
			case 15: {
				char prefix[50];
				
				printf("Masukkan awalan nama : ");
				scanf(" %[^\n]", prefix);
				
				searchPrefix(prefix);
				break;
			}
			
			case 16:
				tampilKelompok();
				break;
			
			case 17: {
    			Mahasiswa backup[MAX];
    			copyData(data, backup, jumlahData);

    			/* QUICK SORT */
    			copyData(backup, data, jumlahData);
    			clock_t start = clock();
    			quickSort(0, jumlahData - 1);
    			clock_t end = clock();
    			double quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    			/* MERGE SORT */
    			copyData(backup, data, jumlahData);
    			start = clock();
    			mergeSort(0, jumlahData - 1);
    			end = clock();
    			double mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    			/* HEAP SORT */
    			copyData(backup, data, jumlahData);
    			start = clock();
    			heapSort();
    			end = clock();
    			double heapTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    			printf("\n===== HASIL BENCHMARK =====\n");
    			printf("Quick Sort : %.6f detik\n", quickTime);
    			printf("Merge Sort : %.6f detik\n", mergeTime);
    			printf("Heap Sort  : %.6f detik\n", heapTime);
				break;
}
			
			case 0:
				printf("Sampai jumpa lagi!\n");
				break;
				
			default:
				printf("Pilihan tidak valid.\n");
		}
	} while(pilihan != 0);
	
	return 0;
}
