#include "TStack.h"

TStack::TStack(const TStack & v)
{
	Size = v.Size;
	pMem = new int[Size];
	top = v.top;
	for (int i = 0; i < Size; i++)
	{
		pMem[i] = v.pMem[i];
	}
}

TStack::TStack()
{
	top = -1;
	Size = MemSize;
	pMem = new int[Size];
	for (int i = 0; i < Size; i++)
	{
		pMem[i] = 0;
	}
}

TStack::~TStack(void)
{
	delete[]pMem;
}

TStack::TStack(int Si)
{
	top = -1;
	Size = Si;
	pMem = new int[Size];
	for (int i = 0; i < Size; i++)
	{
		pMem[i] = 0;
	}
}

int TStack::IsEmpty(void) const
{
	return top == -1;
}

int TStack::IsFull(void) const
{
	return top == Size - 1;
}

void TStack::Put(int val)
{
	pMem[++top] = val;
}

int TStack::Get(void)
{
	return pMem[top--];
}

int TStack::Peek(void) 
{
	return pMem[top];
}

