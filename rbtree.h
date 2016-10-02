#ifndef RBTREE_H
#define RBTREE_H

#include <RBNode.h>
#include <iomanip>
#include <iostream>

using namespace std;

template <class T>
class RBTree
{
    public:
        RBTree()
        {
            m_pnil_node = new RBNode<T>();
            m_pnil_node->color = BLACK;
            m_pnil_node->m_pPadre = m_pnil_node;
            m_pRoot = m_pnil_node;
        };

        RBNode<T>* getTreeMinimum(RBNode<T>* m_pRoot);
        RBNode<T>* getTreeMaximum(RBNode<T>* m_pRoot);
        RBNode<T>* getNodo(T data); //Buscar
        void insertar(T data);
        void eliminar(T data);
        //RBNode<T>* getPadre(Nodo<T>* p);
        //RBNode<T>* getTio(Nodo<T>* p);
        //RBNode<T>* getHermano(Nodo<T>* p);
        bool soyIzquierdo();
        bool soyDerecho();
        void printInOrder(RBNode<T>* p);
        void postorder(RBNode<T>* p, int indent =0);
        RBNode<T>* getRaiz()
        {
            return m_pRoot;
        }

    private:
        RBNode<T>* m_pRoot;
        RBNode<T>* m_pnil_node;

        void rotacionIzquierda(RBNode<T>* p);
        void rotacionDerecha(RBNode<T>* p);
        void transplantar(RBNode<T>* nodoDestino,RBNode<T>* nodoOrigen);
        void insertFixup(RBNode<T>* p);
        void deleteFixup(RBNode<T>* p);
};

template <class T>
RBNode<T>* RBTree<T>::getNodo(T data)
{
    RBNode<T>* nodo = m_pRoot;
    while(nodo!=m_pnil_node && data!=nodo->m_Dato)
    {
        if (data < nodo->m_Dato)
        {
            nodo = nodo->m_pIzquierda;
        }
        else
        {
            nodo = nodo->m_pDerecha;
        }
    }
    return nodo;
}

template <class T>
void RBTree<T>::rotacionIzquierda(RBNode<T>* p)
{
    RBNode<T> * tmp = p->m_pDerecha;
    p->m_pDerecha = tmp->m_pIzquierda; // Pasar el subarbol izquierdo de tmp a subarbol derecha de p

    if (tmp->m_pIzquierda!=m_pnil_node)
        tmp->m_pIzquierda->m_pPadre = p;
    tmp->m_pPadre = p->m_pPadre; //Enlazar el padre de p a tmp

    if (p->m_pPadre == m_pnil_node)
        m_pRoot = tmp;
    else if (p == p->m_pPadre->m_pIzquierda)
        p->m_pPadre->m_pIzquierda = tmp;
    else
        p->m_pPadre->m_pDerecha = tmp;
    tmp->m_pIzquierda = p; //poner p a la izquierda de tmp
    p->m_pPadre = tmp;
}
//La rotacion a la derecha es simetrica a la rotacion a la izquierda
//Rotacion Izquierda y rotacion derecha se ejecutan en un tiempo O(1)
//Solo los punteros cambian por rotación, todos los demas atributos permanecen igual

template <class T>
void RBTree<T>::rotacionDerecha(RBNode<T>* p)
{
    RBNode<T>* tmp = p->m_pIzquierda;
    p->m_pIzquierda = tmp->m_pDerecha;

    if (tmp->m_pDerecha != m_pnil_node)
        tmp->m_pDerecha->m_pPadre = p;
    tmp->m_pPadre = p->m_pPadre;

    if (p->m_pPadre == m_pnil_node)
        m_pRoot = tmp;
    else if (p == p->m_pPadre->m_pDerecha)
        p->m_pPadre->m_pDerecha = tmp;
    else
        p->m_pPadre->m_pIzquierda = tmp;
    tmp->m_pDerecha = p;
    p->m_pPadre = tmp;
}

//Insertar
template <class T>
void RBTree<T>::insertar(T data)
{
    RBNode<T>* p = new RBNode<T>(data);
    RBNode<T>* y = m_pnil_node;
    RBNode<T>* x = m_pRoot;
    while (x != m_pnil_node)
    {
        y = x;
        if (p->m_Dato < x->m_Dato)
            x = x->m_pIzquierda;
        else
            x = x->m_pDerecha;
    }

    p->m_pPadre = y;
    if (y == m_pnil_node)
        m_pRoot = p;
    else if (p->m_Dato < y->m_Dato)
        y->m_pIzquierda = p;
    else
        y->m_pDerecha = p;

    p->m_pIzquierda = m_pnil_node;
    p->m_pDerecha = m_pnil_node;
    p->color = RED;
    insertFixup(p);
}


template <class T>
void RBTree<T>::transplantar(RBNode<T>* nodoDestino, RBNode<T>* nodoOrigen)
{
    if (nodoDestino->m_pPadre == m_pnil_node)
        m_pRoot = nodoDestino;
    else if (nodoDestino == nodoDestino->m_pPadre->m_pIzquierda)
        nodoDestino->m_pPadre->m_pIzquierda = nodoOrigen;
    else
        nodoDestino->m_pPadre->m_pDerecha = nodoOrigen;
    nodoOrigen->m_pPadre = nodoDestino->m_pPadre;
}

template <class T>
void RBTree<T>::insertFixup(RBNode<T>* p)
{
    RBNode<T> * tmp;
    while (p->m_pPadre->color == RED) {
        if (p->m_pPadre == p->m_pPadre->m_pPadre->m_pIzquierda) {
            tmp = p->m_pPadre->m_pPadre->m_pDerecha;
            if (tmp->color == RED) {
                p->m_pPadre->color = BLACK;         //Caso 1
                tmp->color = BLACK;                 //Caso 1
                p->m_pPadre->m_pPadre->color = RED; //Caso 1
                p = p->m_pPadre->m_pPadre;          //Caso 1
            }
            else {
                if (p == p->m_pPadre->m_pDerecha) {
                    p = p->m_pPadre;                //Caso 2
                    rotacionIzquierda(p);           //Caso 2
                }
                p->m_pPadre->color = BLACK;         //Caso 3
                p->m_pPadre->m_pPadre->color = RED; //Caso 3
                rotacionDerecha(p->m_pPadre->m_pPadre);//Caso 3
            }
        }
        else { //lo mismo, con m_pIzquierda y m_pDerecha intercambiados
            tmp = p->m_pPadre->m_pPadre->m_pIzquierda;
            if (tmp->color == RED) {
                p->m_pPadre->color = BLACK;
                tmp->color = BLACK;
                p->m_pPadre->m_pPadre->color = RED;
                p = p->m_pPadre->m_pPadre;
            }
            else {
                if (p == p->m_pPadre->m_pIzquierda) {
                    p = p->m_pPadre;
                    rotacionDerecha(p);
                }
                p->m_pPadre->color = BLACK;
                p->m_pPadre->m_pPadre->color = RED;
                rotacionIzquierda(p->m_pPadre->m_pPadre);
            }
        }
    }
    this->m_pRoot->color = BLACK;
}


template <class T>
void RBTree<T>::eliminar(T data)
{
    RBNode<T> * p = getNodo(data);
    RBNode<T> * tmp = p;
    RBNode<T> * tmp2;
    Color colorOriginal = tmp->color;
    if (p->m_pIzquierda == m_pnil_node) {
        tmp2 = p->m_pDerecha;
        transplantar(p, p->m_pDerecha);
    }
    else if (p->m_pDerecha == m_pnil_node)
    {
        tmp2 = p->m_pIzquierda;
        transplantar(p, p->m_pIzquierda);
    } else {
        tmp = getTreeMinimum(p->m_pDerecha);
        colorOriginal = tmp->color;
        tmp2 = tmp->m_pDerecha;
        if (tmp->m_pPadre == p) {
            tmp2->m_pPadre = tmp;
        } else {
            transplantar(tmp, tmp->m_pDerecha);
            tmp->m_pDerecha = p->m_pDerecha;
            tmp->m_pDerecha->m_pPadre = tmp;
        }
        transplantar(p, tmp);
        tmp->m_pIzquierda = p->m_pIzquierda;
        tmp->m_pIzquierda->m_pPadre = tmp;
        tmp->color = p->color;
    }
    if (colorOriginal == BLACK)
        deleteFixup(tmp2);
}

template <class T>
void RBTree<T>::deleteFixup(RBNode<T>* p)
{
    RBNode<T> * tmp;

    while (p != m_pRoot && p->color == BLACK) {
        if (p == p->m_pPadre->m_pIzquierda) {
            tmp = p->m_pPadre->m_pDerecha;
            if (tmp->color == RED) {
                tmp->color = BLACK;                         //Caso 1
                p->m_pPadre->color = RED;                   //Caso 1
                rotacionIzquierda(p->m_pPadre);             //Caso 1
                tmp = p->m_pPadre->m_pDerecha;              //Caso 1
            }
            if (tmp->m_pIzquierda->color == BLACK && tmp->m_pDerecha->color == BLACK) {
                tmp->color = RED;                           //Caso 2
                p = p->m_pPadre;                            //Caso 2
            }
            else
            {
                if (tmp->m_pDerecha->color == BLACK)
                {
                    tmp->m_pIzquierda->color = BLACK;       //Caso 3
                    tmp->color = RED;                       //Caso 3
                    rotacionDerecha(tmp);                   //Caso 3
                    tmp = p->m_pPadre->m_pDerecha;          //Caso 3
                }
                tmp->color = p->m_pPadre->color;            //Caso 4
                p->m_pPadre->color = BLACK;                 //Caso 4
                tmp->m_pDerecha->color = BLACK;             //Caso 4
                rotacionIzquierda(p->m_pPadre);             //Caso 4
                p = m_pRoot;                                //Caso 4
            }
        } else { //Lo mismo pero con m_pIzquierda y m_pDerecha intercambiados
            tmp = p->m_pPadre->m_pIzquierda;
            if (tmp->color == RED) {
                tmp->color = BLACK;
                p->m_pPadre->color = RED;
                rotacionDerecha(p->m_pPadre);
                tmp = p->m_pPadre->m_pIzquierda;
            }
            if (tmp->m_pDerecha->color == BLACK && tmp->m_pIzquierda->color == BLACK) {
                tmp->color = RED;
                p = p->m_pPadre;
            } else {
                if (tmp->m_pIzquierda->color == BLACK) {
                    tmp->m_pDerecha->color = BLACK;
                    tmp->color = RED;
                    rotacionIzquierda(tmp);
                    tmp = p->m_pPadre->m_pIzquierda;
                }
                tmp->color = p->m_pPadre->color;
                p->m_pPadre->color = BLACK;
                tmp->m_pIzquierda->color = BLACK;
                rotacionDerecha(p->m_pPadre);
                p = m_pRoot;
            }
        }
    }
    p->color = BLACK;
}

template <class T>
void RBTree<T>::postorder(RBNode<T>* p, int indent)
{
    if(p != NULL) {
        if(p->m_pIzquierda) postorder(p->m_pIzquierda, indent+4);
        if(p->m_pDerecha) postorder(p->m_pDerecha, indent+4);
        if (indent) {
            cout << std::setw(indent) << ' ';
        }
        cout<< p->m_Dato << "\n ";
    }
}

template <class T>
void RBTree<T>::printInOrder(RBNode<T>* p)
{
    try
    {
        if (!p) return;
        if (p->m_pIzquierda) printInOrder(p->m_pIzquierda);
        if (p->m_pIzquierda && p->m_pDerecha) cout <<p->color<<" : "<<p->m_Dato<<endl;
        if (p->m_pDerecha) printInOrder(p->m_pDerecha);

    }
    catch (exception_ptr &e)
    {
        cout<< "Algo sucedio...."<<endl;
    }
}

#endif // RBTREE_H
