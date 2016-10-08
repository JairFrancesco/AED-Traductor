#ifndef AVL_H
#define AVL_H
#include "NodoArbol.h"

template<class T>
class AVL
{
    public:
        AVL()
        {
            this->mpraiz=0;
        }
        void mostrar(Nodo<T>*);
        void insertar(T d);
        void rdd(Nodo<T>**&,bool);
        void rii(Nodo<T>*);
        void ver(Nodo<T>*,int);
        void rdi(Nodo<T>**&,bool);
        void rid(Nodo<T>*);
        int altura(Nodo<T>*);
        void balancear(Nodo<T>*&);

        bool find(Nodo<T>**&,T);
        int FE(Nodo<T>*);
        virtual ~AVL(){}
    protected:
    public:
        Nodo<T>* mpraiz;
};

template <class T>
void AVL<T>::balancear(Nodo<T>*& h)
{
    if (!h) return;
    balancear(h->mpson[0]);
    balancear(h->mpson[1]);
    if(!h->mpson[0]&&!h->mpson[1]){
        return;
    }
    Nodo<T>**aux=&h;
    if(h->mpson[0]&&h->mpson[1]){
        if(FE(h)>1)
        {
            if(FE(h->mpson[0])>0){
                rdd(aux,false);
            }
            else
            {
                rdi(aux,false);
                rdd(aux,false);
            }
        }
        else if(FE(h)<-1)
        {
            if(FE(h->mpson[1])>0)
            {
                rdi(aux,true);
                rdd(aux,true);
            }
            else
            {
                rdd(aux,true);
            }
        }
        return;
    }
    else if(h->mpson[0])
    {
        if(FE(h)>1){
            if(FE(h->mpson[0])>0){
                rdd(aux,false);
            }
            else{
                rdi(aux,false);
                rdd(aux,false);
            }
        }
        else if (FE(h)==-2)
        {
            if (FE(h->mpson[0])>0)
            {
                rdi(aux,false);
            }
            else
            {
                rdd(aux,false);
            }

        }
    }
    else if(h->mpson[1])
    {
                //std::cout<<"easdas"<<std::endl;
        if(FE(h)==2)
        {
            if(FE(h->mpson[1])>0)
            {
                rdd(aux,true);
            }
            else
            {
                rdi(aux,true);
            }
        }
    }
    altura(mpraiz);
}



template <class T>
int AVL<T>::FE(Nodo<T>* h)
{
    if (!h) return 0;
    //int b=altura(this->mpraiz);

    if (h->mpson[0] && h->mpson[1]) return (h->mpson[1]->altura)-(h->mpson[0]->altura);

    else if (h->mpson[0] && !h->mpson[1]) return  -1-h->mpson[0]->altura;
    else if (h->mpson[1] && !h->mpson[0]) return 1+h->mpson[1]->altura;
    else return 0;


}


template <class T>
void AVL<T>::ver(Nodo<T>* h,int n)
{
    if (!h) return;
    ver(h->mpson[1],n+1);
    for (int i=0;i<n;i++)
        std::cout<<"    ";
    std::cout<<"|"<<h->valor<<","<<FE(h)<<","<<h->altura<<std::endl;
    ver(h->mpson[0],n+1);
}

template <class T>
void AVL<T>::mostrar(Nodo<T>* h)
{
    if (!h) return;
    std::cout<<h->valor<<" -> ";
    mostrar(h->mpson[0]);
    mostrar(h->mpson[1]);
}

template <class T>
bool AVL<T>::find(Nodo<T>**&p,T d)
{
    p=&mpraiz;
    while (*p)
    {
        if ((*p)->valor==d) return true;
        if ((*p)->valor<d) p=&((*p)->mpson[1]);
        else p=&((*p)->mpson[0]);
    }
    return false;
}

template <class T>
int AVL<T>::altura(Nodo<T>* h)
{
    /*if (!h->mpson[0]&&!h->mpson[1]) return 0;
    if (h->mpson[0]&& !h->mpson[1]) return altura(h->mpson[0]);
    else if (h->mpson[1] && !h->mpson[0]) return altura(h->mpson[1]);
    else return altura(h->mpson[0])+altura(h->mpson[1]);*/
    if (!h) return -1;
    return h->altura=1+std::max(altura(h->mpson[0]),altura(h->mpson[1]));
}


template <class T>
void AVL<T>::insertar(T d)
{
    Nodo<T>** p;
    if (find(p,d)) return;
    *p=new Nodo<T>(d);

    altura(mpraiz);
        ver(mpraiz,0);
    std::cout<<"-------------------------"<<std::endl;
    balancear(mpraiz);

}

template <class T>
void AVL<T>::rdd(Nodo<T>**& h,bool l)
{
    Nodo<T>* aux=(*h);
    (*h)=aux->mpson[l];
    if ((*h)->mpson[!l]) aux->mpson[l]=(*h)->mpson[!l];
    else aux->mpson[l]=0;
    //aux->mpson[!l]=(*h)->mpson[!l];
    (*h)->mpson[!l]=aux;
}

template <class T>
void AVL<T>::rdi(Nodo<T>**& h, bool l)
{
    Nodo<T>* aux=(*h)->mpson[l];
    Nodo<T>* sn=(*h);
    (*h)=aux->mpson[!l];
    if ((*h)->mpson[!l]) sn->mpson[l]=(*h)->mpson[!l];
    else sn->mpson[l]=0;
    if ((*h)->mpson[l]) aux->mpson[!l]=(*h)->mpson[l];
    else aux->mpson[!l]=0;
    (*h)->mpson[l]=aux;
    (*h)->mpson[!l]=sn;
}


#endif // AVL_H
