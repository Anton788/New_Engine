#pragma once
#include "stdafx.h"
#include <assert.h>
#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdint.h>
#include <malloc.h>
#include <dos.h>
#include <random>
#include <time.h>
#include <ctime>
#include <ctype.h>
#include <locale>
#include <intrin.h>
#pragma intrinsinc(__rdtsc);

	// Структуры данных:
typedef char ForSTACK;
#define INIT_SIZE 10
#define MULTIPLIER 2
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102
	typedef struct Stack_Tag
	{
		ForSTACK *data;
		size_t size;
		size_t top;
	}
	Stack_t;
	Stack_t* Create_Stack()
	{
		Stack_t *out = NULL;
		out = (Stack_t*)malloc(sizeof(Stack_t));
		if (out == NULL)
		{
			exit(OUT_OF_MEMORY);
		}
		out->size = INIT_SIZE;
		out->data = (ForSTACK*)malloc(out->size * sizeof(ForSTACK));
		if (out->data == NULL)
		{
			free(out);
			exit(OUT_OF_MEMORY);
		}
		out->top = 0;
		return out;
	}
	void Delete_Stack(Stack_t **stack)
	{
		free((*stack)->data);
		free(*stack);
		*stack = NULL;
	}
	void Resize_Stack(Stack_t *stack)
	{
		stack->size *= MULTIPLIER;
		stack->data = (ForSTACK*)realloc(stack->data, stack->size * sizeof(ForSTACK));
		if (stack->data == NULL)
		{
			exit(STACK_OVERFLOW);
		}
	}
	void Push_Stack(Stack_t *stack, ForSTACK value)
	{
		if (stack->top >= stack->size)
		{
			Resize_Stack(stack);
		}
		stack->data[stack->top] = value;
		stack->top++;
	}
	ForSTACK Pop_Stack(Stack_t *stack)
	{
		if (stack->top == 0)
		{
			exit(STACK_UNDERFLOW);
		}
		stack->top--;
		return stack->data[stack->top];
	}
	ForSTACK Peek_Stack(const Stack_t *stack)
	{
		if (stack->top <= 0)
		{
			exit(STACK_UNDERFLOW);
		}
		return stack->data[stack->top - 1];
	}
	void Implode_Stack(Stack_t *stack) {
		stack->size = stack->top;
		stack->data = (ForSTACK*)realloc(stack->data, stack->size * sizeof(ForSTACK));
	}


	//авось пригодится:
void PRINT_INT_MASS(int *a, int n)  // функция вывода 
{
	static int num = 1; // номер комбинации

	printf("%d", num++);
	printf(":  ", "\n");
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");

}
void PRINT_DOB_MASS(double *a, int n)  // функция вывода 
{
	static int num = 1; // номер комбинации

	printf("%lf", num++);
	printf(":  ", "\n");
	for (int i = 0; i < n; i++)
		printf("%lf ", a[i]);
	printf("\n");

}
void obmen(double i, double k) // для упрощения кода
{
	double s = i;
	i = k;
	k = s;
}
void obmen_index(void* i, void* k) // для упрощения кода
{
	void* s = i;
	i = k;
	k = s;
}
unsigned long long int factorial(int a)
{
	if (a >1)
		return(a*factorial(a - 1));
	else return 1;

}
unsigned long long int power(int a, int b)
	{
		unsigned long long int s = 1;
		for (int i = 1; i < b + 1; i++) 
		{
			s = s*a;
		}
		return s;
	}
unsigned long int poisk(unsigned long int *s, unsigned long int k, unsigned long int p, unsigned long int i) // функция для поиска числа с заданным интервалом от предыдущего
	{
		unsigned long int m = 0, h;
		for (h = k + 1; h < (p + 1); h++)   //сравнение
		{
			if (s[k] + i - s[h] == 0)
				m = h;
		}
		return m;
	}
int SledComb(int *a, int n) // Функция нахождения следующей комбинации методом сортировки по возрастанию всех таких комбинаций
	{
		int m = n - 2;
		while (m != -1 && a[m] >= a[m + 1]) m--; //если доходит до -1 элемета, то, видимо, массив кончился
		if (m == -1)
			return 0; // закрываем функцию
		int k = n - 1;
		while (a[m] >= a[k]) k--;
		obmen(a[m], a[k]);
		int l = m + 1, r = n - 1; // сортировка оставшейся части
		while (l < r)
			obmen(a[l++], a[r--]);
		return 1;
	}
char *gets(char *s)
{
	/*очистка буфера ввода */
	fflush(stdin);

	int i, k = getchar();

	/* Возвращаем NULL если ничего не введено */
	if (k == EOF)
		return NULL;

	/* Считываем и копируем в буфер символы пока не достигнем конца строки или файла */
	for (i = 0; k != EOF && k != '\n'; ++i) {
		s[i] = k;
		k = getchar();

		/* При обнаружении ошибки результирующий буфер непригоден */
		if (k == EOF && !feof(stdin))
			return NULL;
	}

	/* Нуль-терминируем и возвращаем буфер в случае успеха.
	Символ перевода строки в буфере не хранится. */
	s[i] = '\0';

	return s;
}
void STOPE()
{
	getchar(); getchar();
}


	//Сортировки массивов:
		// Сортировка пузырьком:
			void Bub_Int_Sort_Up(int* arrayPtr, int length_array)
		{
				bool exit = false;

				while (!exit)
				{
					exit = true;
					for (int i = 0; i < (length_array - 1); i++)
						if (arrayPtr[i] > arrayPtr[i + 1])
						{
							obmen(arrayPtr[i], arrayPtr[i + 1]);
							exit = false;
						}
				}
		}
			void Bub_Int_Sort_Down(int* arrayPtr, int length_array)
		{
			bool exit = false;

			while (!exit)
			{
				exit = true;
				for (long int i = 0; i < (length_array - 1); i++)
					if (arrayPtr[i] < arrayPtr[i + 1])
					{
						obmen(arrayPtr[i], arrayPtr[i + 1]);
						exit = false;
					}
			}
		}
			void Bub_Dob_Sort_Up(double* arrayPtr, int length_array)
		{
			bool exit = false;

			while (!exit)
			{
				exit = true;
				for (long int i = 0; i < (length_array - 1); i++)
					if (arrayPtr[i] > arrayPtr[i + 1])
					{
						obmen(arrayPtr[i], arrayPtr[i + 1]);
						exit = false;
					}
			}
		}
			void Bub_Dob_Sort_Down(double* arrayPtr, int length_array)
		{
			bool exit = false;

			while (!exit)
			{
				exit = true;
				for (long int i = 0; i < (length_array - 1); i++)
					if (arrayPtr[i] < arrayPtr[i + 1])
					{
						obmen(arrayPtr[i], arrayPtr[i + 1]);
						exit = false;
					}
			}
		}
		// Сортировка слиянием:
			void Merge_Int_Up( int *a, long int n)
	{
		long int mid = n / 2;
		if (n % 2 == 1)
			mid++;
		long int h = 1; // шаг
		long int *c = (long int*)malloc(n * sizeof(long int));
		long int step;
		while (h < n)
		{
			step = h;
			long int i = 0;   // индекс первого пути
			long int j = mid; // индекс второго пути
			long int k = 0;   // индекс элемента в результирующей последовательности
			while (step <= mid)
			{
				while ((i < step) && (j < n) && (j < (mid + step))) // пока не дошли до конца пути
				{
					if (a[i] < a[j])
					{
						c[k] = a[i];
						i++; k++;
					}
					else {
						c[k] = a[j];
						j++; k++;
					}
				}
				while (i < step)
				{ // переписываем оставшиеся элементы первого пути (если второй кончился раньше)
					c[k] = a[i];
					i++; k++;
				}
				while ((j < (mid + step)) && (j < n))
				{  // переписываем оставшиеся элементы второго пути (если первый кончился раньше)
					c[k] = a[j];
					j++; k++;
				}
				step = step + h; // переходим к следующему этапу
			}
			h = h * 2;
			// Переносим упорядоченную последовательность (промежуточный вариант) в исходный массив
			for (i = 0; i < n; i++)
				a[i] = c[i];
		}
	}
			void Merge_Dob_Up(double *a,long int n)
	{
		long int mid = n / 2;
		if (n % 2 == 1)
			mid++;
		long int h = 1; // шаг
		double *c = (double*)malloc(n * sizeof(double));
		long int step;
		while (h < n)
		{
			step = h;
			long int i = 0;   // индекс первого пути
			long int j = mid; // индекс второго пути
			long int k = 0;   // индекс элемента в результирующей последовательности
			while (step <= mid)
			{
				while ((i < step) && (j < n) && (j < (mid + step))) // пока не дошли до конца пути
				{
					if (a[i] < a[j])
					{
						c[k] = a[i];
						i++; k++;
					}
					else {
						c[k] = a[j];
						j++; k++;
					}
				}
				while (i < step)
				{ // переписываем оставшиеся элементы первого пути (если второй кончился раньше)
					c[k] = a[i];
					i++; k++;
				}
				while ((j < (mid + step)) && (j < n))
				{  // переписываем оставшиеся элементы второго пути (если первый кончился раньше)
					c[k] = a[j];
					j++; k++;
				}
				step = step + h; // переходим к следующему этапу
			}
			h = h * 2;
			// Переносим упорядоченную последовательность (промежуточный вариант) в исходный массив
			for (i = 0; i < n; i++)
				a[i] = c[i];
		}
	}
		// нафиг вставками, qsort и qsort_s в stdlib
		// так и быть, вот онa
			void qs(int *s_arr, int first, int last)
			{
				if (first < last)
				{
					int left = first, right = last, middle = s_arr[(left + right) / 2];
					do
					{
						while (s_arr[left] < middle) left++;
						while (s_arr[right] > middle) right--;
						if (left <= right)
						{
							int tmp = s_arr[left];
							s_arr[left] = s_arr[right];
							s_arr[right] = tmp;
							left++;
							right--;
						}
					} while (left <= right);
					qs(s_arr, first, right);
					qs(s_arr, left, last);
				}
			}
			void Quick_Sort(int *s_arr, int length)
			{
				int first = 0;
				int last = length-1;

				if (first < last)
				{
					int left = first, right = last, middle = s_arr[(left + right) / 2];
					do
					{
						while (s_arr[left] < middle) left++;
						while (s_arr[right] > middle) right--;
						if (left <= right)
						{
							int tmp = s_arr[left];
							s_arr[left] = s_arr[right];
							s_arr[right] = tmp;
							left++;
							right--;
						}
					} while (left <= right);
					qs(s_arr, first, right);
					qs(s_arr, left, last);
				}
			}
		

// Список обыкновенный:
#define LINKS_PER_NODE 2
typedef void For_Linked_List;
	typedef struct Node_t
	{
		For_Linked_List *value;
		Node_t *LINKS[2];
	}
	Node_t;
	typedef struct Linked_List
	{
		size_t size;
		Node_t *head;
		Node_t *tail;
		//Node_t *head[]; 
	} 
	Linked_List;
	Linked_List* Сreate_Linked_List() 
	{
		Linked_List *tmp = (Linked_List*)malloc(sizeof(Linked_List));
		tmp->size = 0;
		tmp->head = tmp->tail = NULL;
		//tmp->head[] = NULL;
		return tmp;
	}
	void Delete_Linked_List(Linked_List **list)
	{
		Node_t *tmp = (*list)->head;
		Node_t *next = NULL;
		while (tmp) 
		{
			next = tmp->LINKS[0];
			free(tmp);
			tmp = next;
		}
		free(*list);
		(*list) = NULL;
	}
	// Операции со списком:
	void Push_Front_Linked_List(Linked_List *list, For_Linked_List *data)
	{
		Node_t *tmp = (Node_t*)malloc(sizeof(Node_t));
		if (tmp == NULL) 
		{
			exit(1);
		}
		tmp->value = data;
		tmp->LINKS[0] = list->head;
		tmp->LINKS[1] = NULL;
		if (list->head)
		{
			list->head->LINKS[1] = tmp;
		}
		list->head = tmp;

		if (list->tail == NULL)
		{
			list->tail = tmp;
		}
		list->size++;
	}
	void* Pop_Front_Linked_List(Linked_List *list)
	{
		Node_t *prev;
		void *tmp;
		if (list->head == NULL)
		{
			exit(2);
		}
		prev = list->head;
		list->head = list->head->LINKS[0];
		if (list->head)
		{
			list->head->LINKS[1] = NULL;
		}
		if (prev == list->tail) 
		{
			list->tail = NULL;
		}
		tmp = prev->value;
		free(prev);
		list->size--;
		return tmp;
	}
	void Push_Back_Linked_List(Linked_List *list, For_Linked_List *value)
	{
		Node_t *tmp = (Node_t*)malloc(sizeof(Node_t));
		if (tmp == NULL)
		{
			exit(3);
		}
		tmp->value = value;
		tmp->LINKS[0] = NULL;
		tmp->LINKS[1] = list->tail;
		if (list->tail)
		{
			list->tail->LINKS[0] = tmp;
		}
		list->tail = tmp;

		if (list->head == NULL) 
		{
			list->head = tmp;
		}
		list->size++;
	}
	void* Pop_Back_Linked_List(Linked_List *list)
	{
		Node_t *next;
		void *tmp;
		if (list->tail == NULL) 
		{
			exit(4);
		}

		next = list->tail;
		list->tail = list->tail->LINKS[1];
		if (list->tail) 
		{
			list->tail->LINKS[0] = NULL;
		}
		if (next == list->head)
		{
			list->head = NULL;
		}
		tmp = next->value;
		free(next);
		list->size--;
		return tmp;
	}
	Node_t* Get_Nth_Node(Linked_List *list, size_t index)
	{
		Node_t *tmp = NULL;
		size_t i;

		if (index < (list->size / 2))
		{
			i = 0;
			tmp = list->head;
			while (tmp && i < index)
			{
				tmp = tmp->LINKS[0];
				i++;
			}
		}
		else
		{
			i = list->size - 1;
			tmp = list->tail;
			while (tmp && i > index)
			{
				tmp = tmp->LINKS[1];
				i--;
			}
		}

		return tmp;
	}
	void* Delete_Nth_Node(Linked_List *list, size_t index) {
		Node_t *elm = NULL;
		void *tmp = NULL;
		elm = Get_Nth_Node(list, index);
		if (elm == NULL) {
			exit(5);
		}
		if (elm->LINKS[1]) {
			elm->LINKS[1]->LINKS[0] = elm->LINKS[0];
		}
		if (elm->LINKS[0]) {
			elm->LINKS[0]->LINKS[1] = elm->LINKS[1];
		}
		tmp = elm->value;

		if (!elm->LINKS[1]) {
			list->head = elm->LINKS[0];
		}
		if (!elm->LINKS[0]) {
			list->tail = elm->LINKS[1];
		}

		free(elm);

		list->size--;

		return tmp;
	}
	void Print_Linked_List(Linked_List *list, void(*fun)(void*)) {
		Node_t *tmp = list->head;
		while (tmp) {
			fun(tmp->value);
			tmp = tmp->LINKS[0];
		}
		printf("\n");
	}
	Linked_List* List_From_Array(For_Linked_List *arr, size_t n, size_t size) {
		Linked_List *tmp = NULL;
		size_t i = 0;
		if (arr == NULL)
		{
			exit(7);
		}
		tmp = Сreate_Linked_List();
		while (i < n)
		{
			Push_Back_Linked_List(tmp, ((char*)arr + i*size));
			i++;
		}

		return tmp;
	}
	void Insert_Node_Before_Element(Linked_List *list, Node_t* elm, For_Linked_List *data)
	{
		Node_t *ins = NULL;
		if (elm == NULL)
		{
			exit(6);
		}

		if (!elm->LINKS[1]) 
		{
			Push_Front_Linked_List(list, data);
			return;
		}
		ins = (Node_t*)malloc(sizeof(Node_t));
		ins->value = data;
		ins->LINKS[1] = elm->LINKS[1];
		elm->LINKS[1]->LINKS[0] = ins;
		ins->LINKS[0] = elm;
		elm->LINKS[1] = ins;

		list->size++;
	}
	void Print_Node_Int(void *value)
	{
		printf(" %d ", *((int*)value));
	}
	void Print_Node_Dob(void *value)
	{
		printf(" %lf ", *((double*)value));
	}
	void Print_Node_Char(void *value)
	{
		printf(" %c ", *((char*)value));
	}
	void Insert_In_Linked_List(Linked_List *list, size_t index, For_Linked_List *data)
	{
		Node_t *elm = (Node_t*)malloc(sizeof(Node_t));;
		Node_t *ins = NULL;
		elm = Get_Nth_Node(list, index--);
		Insert_Node_Before_Element(list, elm, data);
	}
	int Length_Of_List(Node_t* head)
	{
		int count = 0;
		Node_t *current = head;
		while (current != NULL)
		{
		count++;
			current = current->LINKS[0];
		}
		return(count);
	}
	void Front_Back_Split(Node_t* source, Node_t** frontRef, Node_t** backRef)
	{
		int len = Length_Of_List(source);
		int i;
		Node_t * current = source;
		if (len < 2)
		{
			*frontRef = source;
			*backRef = NULL;
		}
		else
		{
			int hopCount = (len - 1) / 2;
			for (i = 0; i<hopCount; i++)
			{
				current = current->LINKS[0];
			}
			// исходный список разбивается на два подсписка
			*frontRef = source;
			*backRef = current->LINKS[0];
			current->LINKS[0] = NULL;
		}
	}
	int Compare_Int_UP(For_Linked_List* a, For_Linked_List* b)
	{
		if ((char*)a >= (char*)b) return 1;
		else return 0;
	}


// Сортировка списков
	// Общая возвратная с выбором типа
	Linked_List* Sort_Of_Int_List(Linked_List *list, void Sort(int*, int))
	{
		int *arr = (int*)calloc(list->size + 1, sizeof(int));
		for (int i = 0; i <= list->size; i++)
		{
			arr[i] = *((int*)Get_Nth_Node(list, i)->value);
		}
		Sort(arr, list->size);
		int size = list->size;
		Delete_Linked_List(&list);
		return List_From_Array(arr, size, sizeof(int));
	}
	// Сортировка вставками
	void Insertion_Sort_Of_List(Linked_List **list)
	{

		Linked_List *out = Сreate_Linked_List();
		Node_t *sorted = NULL;
		Node_t *unsorted = NULL;

		Push_Front_Linked_List(out, Pop_Front_Linked_List(*list));
	
		unsorted = (*list)->head;
		while (unsorted) 
		{
			sorted = out->head;
			while (sorted && !((*(int*)(unsorted->value)) >(*(int*)(sorted->value))))
			{
				sorted = sorted->LINKS[0];
			}
			if (sorted) 
			{
				Insert_Node_Before_Element(out, sorted, unsorted->value);
			}
			else
			{
				Push_Back_Linked_List(out, unsorted->value);
			}
			unsorted = unsorted->LINKS[0];
		}

		free(*list);
		*list = out;
	}
	// Сортировка слиянем
	Node_t *Sorted_Merge(Node_t* a, Node_t* b)
	{
		Node_t* result = NULL;
		if (a == NULL) return(b);
		else if (b == NULL) return(a);
		if ((*(int*)a->value) <= (*(int*)(b->value)))
		{
			result = a;
			result->LINKS[0] = Sorted_Merge(a->LINKS[0], b);
		}
		else
		{
			result = b;
			result->LINKS[0] = Sorted_Merge(a, b->LINKS[0]);
		}
		return(result);
	}
	void Merge_Sort_Of_List(Node_t** headRef)
	{
		Node_t* head = *headRef;
		Node_t* a;
		Node_t* b;
		// вырожденный случай – длина списка равно 0 или 1
		if ((head == NULL) || (head->LINKS[0] == NULL))
		{
			return;
		}
		Front_Back_Split(head, &a, &b);
		Merge_Sort_Of_List(&a); // рекурсивная сортировка подсписков
		Merge_Sort_Of_List(&b);
		*headRef = Sorted_Merge(a, b);
	}

// Генераторы случайных чисел
	void RANDOM_INT_IN_MASS(int *&array, long int number, int MAX)
	{
		srand(time(NULL));
		*&array = (int*)malloc(number * sizeof(int));
		STOPE();
		for (long int i = 0; i < number; i++)
		{
			*&array[i] = (rand() % ((MAX)/2)+ rand() % ((MAX) / 2)+ rand() % (2));
		}
	}
	void RANDOM_CHAR_IN_MASS(char *&array, long int number)
	{
		srand(time(NULL));
		*&array = (char*)malloc(number * sizeof(char));
		for (long int i = 0; i < number; i++)
		{
			*&array[i] = rand() % 256;
		}
	}
	int  *GEN_RANDOM_INT_MASS(long int number, int MAX)
	{
		srand(time(NULL));
		int *arroy = (int*)malloc(number * sizeof(int));
		for (long int i = 0; i < number; i++)
		{
			arroy[i] = rand() % MAX;
		}
		return arroy;
	}

// Деревья
	typedef void For_Tree;

#define CMP_EQ(a, b) ((a) == (b))
#define CMP_LT(a, b) ((a) < (b))
#define CMP_GT(a, b) ((a) > (b))

	typedef struct Node_d
	{
		For_Tree *data;
		Node_d **Chado;
		Node_d *Batya;
		int Chado_Number;
		void *Tree, *level;
	}
	Node_d;
	typedef struct Tree
	{
		Node_d *root;
		int height, size;
	}
	Tree;
	Node_d* New_Leaf(For_Tree* value, Node_d *batya)
	{
		Node_d* tmp = (Node_d*)malloc(sizeof(Node_d));
		if (batya->Chado_Number != 0)
		{
			tmp->level = (((Node_d*)(batya->Chado[0]))->level);

		}
		else
		{
			int lvl = (int)batya->level + 1;
			tmp->level = (void*)lvl;
		}
		batya->Chado_Number++;
		batya->Chado = (Node_d**)realloc((void*)batya->Chado, batya->Chado_Number * sizeof(Node_d));
		tmp->data = value;
		tmp->Batya = batya;
		tmp->Chado_Number = 0;
		tmp->Tree = batya->Tree;
		Tree *derevo = (Tree*)batya->Tree;
		derevo->size++;
		if (batya->Chado_Number == 1)
			derevo->height++;
		batya->Chado[batya->Chado_Number - 1] = tmp;
		tmp->Chado = NULL;
		return tmp;
	}
	Tree* Create_Tree()
	{
		Node_d* tmp = (Node_d*)malloc(sizeof(Node_d));
		tmp->Batya = NULL;
		tmp->Chado_Number = 0;
		tmp->data = NULL;
		tmp->Chado = NULL;
		Tree* tree = (Tree*)malloc(sizeof(Tree));
		tree->root = tmp;
		tree->height = 1;
		tree->size = 1;
		tree->root->Tree = tree;
		tree->root->level = 0;
		return tree;
	}

	void Level_Remaking(Node_d *root, int lvl)
	{
		root->level = (void*)lvl;
		lvl++;
		for (int i = 0; i < root->Chado_Number; i++)
		{
			if (root->Chado[i] != NULL)
				Level_Remaking(root->Chado[i], lvl);
		}
	}
	void smth(Linked_List *list, void(*fun)(void*), int lvl, Tree* der)
	{
		
		if ((list->head->value) != NULL)
		{
			fun(((Node_d*)(list->head->value))->data);
			for (int i = 0; i < ((Node_d*)(list->head->value))->Chado_Number; i++)
			{
				Push_Back_Linked_List(list, ((Node_d*)(list->head->value))->Chado[i]);
			}
			if ((der->height) != (lvl + 1))
			{
				Push_Back_Linked_List(list, NULL);
			}
			
		}
		else
			{
			if ((Node_t*)(list->head->LINKS[0]) != NULL)
				if (((Node_d*)(list->head->LINKS[0]->value)) != NULL)
					if ((lvl + 1) != (int)(((Node_d*)(list->head->LINKS[0]->value))->level))
						printf("  _  ");
					else;
				else printf("  _  ");

			}
		if ((Node_t*)(list->head->LINKS[0]) != NULL)
			if (((Node_d*)(list->head->LINKS[0]->value)) != NULL)
			{
				if ((lvl + 1)== (int)(((Node_d*)(list->head->LINKS[0]->value))->level))
				{
					printf("   \n");
				}
			}
		Pop_Front_Linked_List(list);

	}
	void Print_Tree(Node_d *root, void(*fun)(void*))
	{
		Linked_List *list = Сreate_Linked_List();
		Push_Front_Linked_List(list, root);
		Push_Back_Linked_List(list, NULL);
		printf("  ");
		int lvl = 0;
		Tree *der = (Tree*)root->Tree;
		while (list->size)
		{
			
			if ((list->head->value) != NULL)
			{
				lvl = (int)((Node_d*)(list->head->value))->level;
			}
			smth(list, fun, lvl, der);
		}
		printf("\n");
	}
	void Rotate_Tree_Left(Node_d *a)
	{

		Node_d *b = a->Chado[1];
		a->Chado[1] = b->Chado[0];
		b->Chado[0] = a;
		((Tree*)(a->Tree))->root = b;
	}
	void Rotate_Tree_Right(Node_d *a)
	{
		Node_d *b = a->Chado[0];
		a->Chado[0] = b->Chado[1];
		b->Chado[1] = a;
		((Tree*)(a->Tree))->root = b;
	}
	void Big_Rotate_Tree_Left(Node_d *a)
	{
		Rotate_Tree_Right(a->Chado[1]);
		Rotate_Tree_Left(a);
	}
	void Big_Rotate_Tree_Right(Node_d *a)
	{
		Rotate_Tree_Left(a->Chado[0]);
		Rotate_Tree_Right(a);
	}


















	// Длинная арифметика
	typedef int* SuperLong;

