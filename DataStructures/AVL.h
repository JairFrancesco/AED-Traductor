#ifndef AVL_H
#define AVL_H
#include <NodoArbol.h>

template<class T>
class AVL :public SearchStructure
{
    public:
        AVL()
        {
            this->mpraiz=0;
        }
        void mostrar(NodoA<T>*);
        void insertar(T d);
        void rdd(NodoA<T>**&,bool);
        void rii(NodoA<T>*);
        void ver(NodoA<T>*,int);
        void rdi(NodoA<T>**&,bool);
        void rid(NodoA<T>*);
        int altura(NodoA<T>*);
        void balancear(NodoA<T>*&);
        bool find(NodoA<T>**&,T);
        int FE(NodoA<T>*);

        NodoA<T>* padre(NodoA<T>* h)
        {
            NodoA<T>* p,*q;
            p=this->mpraiz;
            T d=h->valor;
            while (p)
            {
                if (d==p->valor) break;
                q=p;
                if (d>p->valor) p=p->mpson[1];
                else p=p->mpson[0];
            }
            return q;
        }

        void begin()
        {
            NodoA<T>*aux=mpraiz;
            while (aux->mpson[0])
                aux=aux->mpson[0];
            current=aux;
        }
        void end()
        {
            NodoA<T>*aux=mpraiz;
            while (aux->mpson[1])
                aux=aux->mpson[1];
            mplast=aux;
            //return aux;
        }
        bool terminate()
        {
            if (!current->mpson[1] && current==mplast) return true;
            return false;
        }
        void next()
        {
            if (!current) return ;
            NodoA<T>*aux=current;
            //std::cout<<"actual: "<<aux->valor<<std::endl;
            if (aux->mpson[1]) current=current->mpson[1];
            else
            {
                NodoA<T>* p=padre(aux);
                while(aux->valor > p->valor)
                {
                    aux=p;
                    p=padre(aux);
                }
                current=p;

            }
        }

        

        Palabra getData()
        {
            return current->valor;
        }

        virtual ~AVL(){}
    protected:
    public:
        NodoA<T>* mpraiz;
        NodoA<T>* current;
        NodoA<T>* mplast;
};

template <class T>
void AVL<T>::balancear(NodoA<T>*& h)
{
    if (!h) return;
    balancear(h->mpson[0]);
    balancear(h->mpson[1]);
    if(!h->mpson[0]&&!h->mpson[1]){
        return;
    }
    NodoA<T>**aux=&h;
    if(h->mpson[0]&&h->mpson[1]){
        if(FE(h)>1)
        {
            if(FE(h->mpson[0])>0){
                rdd(aux,false);
            }
            else
            {
                //rdi(aux,false);
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
int AVL<T>::FE(NodoA<T>* h)
{
    if (!h) return 0;
    //int b=altura(this->mpraiz);

    if (h->mpson[0] && h->mpson[1]) return (h->mpson[1]->altura)-(h->mpson[0]->altura);

    else if (h->mpson[0] && !h->mpson[1]) return  -1-h->mpson[0]->altura;
    else if (h->mpson[1] && !h->mpson[0]) return 1+h->mpson[1]->altura;
    else return 0;


}


template <class T>
void AVL<T>::ver(NodoA<T>* h,int n)
{
    if (!h) return;
    ver(h->mpson[1],n+1);
    for (int i=0;i<n;i++)
        std::cout<<"    ";
    std::cout<<"|"<<h->valor.idioma1<<","<<FE(h)<<","<<h->altura<<std::endl;
    ver(h->mpson[0],n+1);
}

template <class T>
void AVL<T>::mostrar(NodoA<T>* h)
{
    if (!h) return;
    std::cout<<h->valor<<" -> ";
    mostrar(h->mpson[0]);
    mostrar(h->mpson[1]);
}

template <class T>
bool AVL<T>::find(NodoA<T>**&p,T d)
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
int AVL<T>::altura(NodoA<T>* h)
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
    NodoA<T>** p;
    if (find(p,d)) return;
    *p=new NodoA<T>(d);
    altura(mpraiz);
    balancear(mpraiz);

}

template <class T>
void AVL<T>::rdd(NodoA<T>**& h,bool l)
{
    NodoA<T>* aux=(*h);
    (*h)=aux->mpson[l];
    if ((*h)->mpson[!l]) aux->mpson[l]=(*h)->mpson[!l];
    else aux->mpson[l]=0;
    //aux->mpson[!l]=(*h)->mpson[!l];
    (*h)->mpson[!l]=aux;
}

template <class T>
void AVL<T>::rdi(NodoA<T>**& h, bool l)
{
    NodoA<T>* aux=(*h)->mpson[l];
    NodoA<T>* sn=(*h);
    (*h)=aux->mpson[!l];
    if ((*h)->mpson[!l]) sn->mpson[l]=(*h)->mpson[!l];
    else sn->mpson[l]=0;
    if ((*h)->mpson[l]) aux->mpson[!l]=(*h)->mpson[l];
    else aux->mpson[!l]=0;
    (*h)->mpson[l]=aux;
    (*h)->mpson[!l]=sn;
}


#endif // AVL_H
