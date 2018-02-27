#ifndef STACK_H
#define STACK_H
#include<cstring>
using namespace std;


template <typename T>  //�侀�U�w�q�@��T
class stack{

public:
	stack();
	~stack(){
		delete [] stackPtr; //�Ѻc�l����O����
	}
	bool push(const T&);
	T top();
	bool pop();
	bool isEmpty() const{
		return (topSite == -1);  //topSite����-1�ɥN��stack�ŤF
	}
	bool isFull() const{
		return (topSite == (size-1));  //topSite����size-1�ɥN��stack���F(�ŧi1000���ܬ�0~999)
	}

private:
	int size,topSite;
	T *stackPtr;  //�s��T���A�@���}�C����


};


template <typename T> 
stack<T>::stack(){

	topSite = -1;
	size = 1000;  //����stack�j�p1000
	stackPtr = new T[1000];
}


template <typename T> 
bool stack<T>::push (const T &pushValue){

	if(!isFull()){  //�p�G�S����
		topSite = topSite + 1;  //���W�h���Ŧ첾��
		stackPtr[topSite] = pushValue; //��J���
		return true;
	}

	return false;
}


template <typename T> 
T stack<T>::top(){

	if(!isEmpty())
		return stackPtr[topSite];  //�^��stack���̤W�誺��
	return false;
}


template <typename T>
bool stack<T>::pop(){

	if(!isEmpty()){  //�p�G�S����
		topSite = topSite -1; //������topSite���U���Y�i�A���ᦳ�s���ȶi�Ӫ����л\
		return true;
	}
	return false;

}


#endif







