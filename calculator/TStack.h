#pragma once
#define MemSize 50	

class TStack
{
	int top;
	int *pMem;
	int Size;
public:	
	TStack(const TStack &s);
	
	TStack();
    
	~TStack(void);
	
	TStack(int n);
	
	int IsEmpty(void);
	
	int IsFull(void);
	
	void Put(const int val);
	
	int Get(void);
	
	int Peek(void);

};