#ifndef STACK_H
#define STACK_H
#include<cstring>
using namespace std;


template <typename T>  //對底下定義一個T
class stack{

public:
	stack();
	~stack(){
		delete [] stackPtr; //解構子釋放記憶體
	}
	bool push(const T&);
	T top();
	bool pop();
	bool isEmpty() const{
		return (topSite == -1);  //topSite等於-1時代表stack空了
	}
	bool isFull() const{
		return (topSite == (size-1));  //topSite等於size-1時代表stack滿了(宣告1000的話為0~999)
	}

private:
	int size,topSite;
	T *stackPtr;  //存放T型態一維陣列指標


};


template <typename T> 
stack<T>::stack(){

	topSite = -1;
	size = 1000;  //給予stack大小1000
	stackPtr = new T[1000];
}


template <typename T> 
bool stack<T>::push (const T &pushValue){

	if(!isFull()){  //如果沒有滿
		topSite = topSite + 1;  //往上層的空位移動
		stackPtr[topSite] = pushValue; //填入其值
		return true;
	}

	return false;
}


template <typename T> 
T stack<T>::top(){

	if(!isEmpty())
		return stackPtr[topSite];  //回傳stack中最上方的值
	return false;
}


template <typename T>
bool stack<T>::pop(){

	if(!isEmpty()){  //如果沒有空
		topSite = topSite -1; //直接把topSite往下移即可，往後有新的值進來直接覆蓋
		return true;
	}
	return false;

}


#endif







