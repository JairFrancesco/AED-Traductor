#include <stdio.h>
#include <nodo.h>

using namespace std;

template <class T>
class Lista
{
    public:
        Lista(){
            m_phead = m_plast = 0;
        }
        int countPairs();
        int countPairs_r();
        void push_front(T d);
        void find(T d, Nodo<T>* p);
        void Add(T d,Nodo<T>*& p);
        void pushBack(T d);
        void print();
        bool exists(T d);
        void intersection(Lista<T>* L2);
        Nodo<T>* getHead();
        void print_r(Nodo<T>* aux);
    private:
        Nodo<T>* m_phead;
        Nodo<T>* m_plast;
};


template<class T>
void Lista<T>::pushBack(T d){
    Nodo<T>* pNew = new Nodo<T>(d);
    if (m_phead==0){
        m_phead = m_plast = pNew;
    } else {
        m_plast->m_psig = pNew;
        m_plast=pNew;
    }
};

template <class T>
void Lista<T>::push_front(T d){
    Nodo<T>* pNew = new Nodo<T>(d);
    if (m_phead == 0){
        m_phead=m_plast=pNew;
    } else {
        pNew->m_psig=m_phead;
        m_phead = pNew;
    }
}

template <class T>
void Lista<T>::find(T d, Nodo<T>* p){
    if (p==0) return false;
    if (p->m_dato==d) return true;
    find(d, p->m_psig);
}

template <class T>
void Lista<T>::Add(T d,Nodo<T>*& p){
    if (!p){
        p = new Nodo<T>(d);
        m_plast = p;
    }
    Add(d, p->m_psig);
}

template <class T>
int Lista<T>::countPairs(){
    Nodo<T>* aux = m_phead;
    int pairs = 0;
    while(aux){
        if (aux->m_dato%2==0){
            pairs++;
        }
        aux=aux->m_psig;
    }
    return pairs;
}

template <class T>
int Lista<T>::countPairs_r(){
    Nodo<T>* aux = m_phead;
    int pairs = 0;
    while(aux){
        if (aux->m_dato%2==0){
            pairs++;
        }
        aux=aux->m_psig;
    }
    return pairs;
}
template <class T>
void Lista<T>::print(){
    Nodo<T>* aux = m_phead;
    while (aux){
        cout<<aux->m_dato<<endl;
        aux=aux->m_psig;
    }
}

template <class T>
void Lista<T>::print_r(Nodo<T>* aux){
    if (!aux){
        return;
    } else {
        cout<<aux->m_dato<<endl;
        print_r(aux->m_psig);
    }
}

template <class T>
Nodo<T>* Lista<T>::getHead(){
    return m_phead;
}

template <class T>
bool Lista<T>::exists(T data){
    Nodo<T>* aux = m_phead;
    while (aux){
        if (aux->m_dato == data){
            return true;
        }
    }
    return false;
}

template <class T>
void Lista<T>::intersection(Lista<T>* L2){
    Lista<T>* intersect = new Lista<T>();
    Nodo<T>* auxL1 = this->m_phead;
    Nodo<T>* auxL2 = L2->getHead();
    while (auxL1){
        while(auxL2){
            if (auxL1->m_dato == auxL2->m_dato){
                if (!intersect->exists(auxL1->m_dato)){
                    intersect->pushBack(auxL2->m_dato);
                }
            }
            auxL2=auxL2->m_psig;
        }
        auxL1=auxL1->m_psig;
    }
    //Print the Lista intersection
    intersect->print();
}

template <class T>
void Lista<T>::max_r(Nodo<T>* aux, T maximum){
    if (aux->m_dato > maximum){
        maximum = aux->m_dato;
    }
    max_r(aux->m_psig, maximum);
}
