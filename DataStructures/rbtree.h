#ifndef RBTREE_H
#define RBTREE_H

#include <rbnode.h>
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
            m_pnil_node->m_pDerecha = m_pnil_node;
            m_pnil_node->m_pIzquierda = m_pnil_node;
            m_pRoot = m_pnil_node;
        };

        RBNode<T>* getTreeMinimum(RBNode<T>* m_pRoot);
        RBNode<T>* getTreeMaximum(RBNode<T>* m_pRoot);
        RBNode<T>* getNodo(T data); //Buscar
        void insertar(T data);
        void eliminar(T data);
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
    RBNode<T>* p = new RBNode<T>(data); //Nuevo nodo
    RBNode<T>* y = m_pnil_node;
    RBNode<T>* x = m_pRoot;

    //Inserción comun en un BST
    while (x != m_pnil_node)
    {
        y = x; //Actualizamos y
        if (p->m_Dato < x->m_Dato)
            x = x->m_pIzquierda;
        else
            x = x->m_pDerecha;
    }    
    p->m_pPadre = y;

    if (y == m_pnil_node)
        m_pRoot = p;
    else if (p->m_Dato < y->m_Dato) //Dependiendo del dato ingresado lo colocamos como hijo derecho o izquierdo
        y->m_pIzquierda = p;
    else
        y->m_pDerecha = p;

    p->m_pIzquierda = m_pnil_node; //Cumplimos con las propiedades de un RB-Tree
    p->m_pDerecha = m_pnil_node;
    p->color = RED;
    insertFixup(p); //Para restaurar las propiedades de RB-Tree
}


template <class T>
void RBTree<T>::transplantar(RBNode<T>* nodoDestino, RBNode<T>* nodoOrigen)
{
    if (nodoDestino->m_pPadre == m_pnil_node)
        m_pRoot = nodoDestino;
    else if (nodoDestino->soyIzquierdo())
        nodoDestino->m_pPadre->m_pIzquierda = nodoOrigen;
    else
        nodoDestino->m_pPadre->m_pDerecha = nodoOrigen;
    nodoOrigen->m_pPadre = nodoDestino->m_pPadre;
}

template <class T>
void RBTree<T>::insertFixup(RBNode<T>* p)
{
    bool esIzquierdo = false;
    RBNode<T> * tmp;
    while (p->getPadre()->color == RED) {
        tmp = p->getTio();
        if (tmp->color == RED) //Caso 1
        {
            p->getPadre()->color = BLACK; //Caso 1
            tmp->color = BLACK; //Caso 1
            p->getAbuelo()->color = RED;//Caso 1
            p = p->getAbuelo(); //Caso 1
        }
        else
        {
            if (p->soyDerecho()) //Caso 2
            {
                p = p->getPadre();   //Caso 2
                rotacionIzquierda(p); //Caso 2
                esIzquierdo = false;
            }
            else
            {
                p = p->getPadre();
                rotacionDerecha(p);
                esIzquierdo = true;
            }
            p->getPadre()->color = BLACK; //Caso 3
            p->getAbuelo()->color = RED; //Caso 3
            if (esIzquierdo)
                rotacionIzquierda(p->getAbuelo()); //Caso 3
            else
                rotacionDerecha(p->getAbuelo()); //Caso 3
        }
    }
    this->m_pRoot->color = BLACK;
}


template <class T>
void RBTree<T>::eliminar(T data)
{
    RBNode<T> * p = getNodo(data); //Nodo a eliminar
    RBNode<T> * tmp = p; //Mas adelante sera el sucesor(Siguiente) del nodo a eliminar
    RBNode<T> * tmp2;
    Color colorOriginal = tmp->color;
    //Realiza practicamente el mismo procedimiento que un BST-Delete
    //Si solo tiene un hijo
    if (p->m_pIzquierda == m_pnil_node) {
        tmp2 = p->m_pDerecha;
        transplantar(p, p->m_pDerecha);
    }
    else if (p->m_pDerecha == m_pnil_node)
    {
        tmp2 = p->m_pIzquierda;
        transplantar(p, p->m_pIzquierda);
    }
    else //Si tiene dos hijos
    {
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
        deleteFixup(tmp2); //Cambia los colores y realiza rotaciones para restaurar las propiedades RED-BLACK
}

template <class T>
void RBTree<T>::deleteFixup(RBNode<T>* p)
{
    RBNode<T> * tmp;
    while (p != m_pRoot && p->color == BLACK) {
        tmp = p->getHermano();
        if (tmp->color == RED) //Caso1: el hermano de p es rojo
        {
            tmp->color = BLACK;                         //Caso 1
            p->getPadre()->color = RED;                 //Caso 1
            if (p->soyIzquierdo())
            {
                rotacionIzquierda(p->getPadre());             //Caso 1
                tmp = p->m_pPadre->m_pDerecha;              //Caso 1
            }
            else
            {
                rotacionDerecha(p->getPadre());             //Caso 1
                tmp = p->m_pPadre->m_pIzquierda;              //Caso 1
            }

        }
        //Caso2: el hermano de p: (tmp) es negro y ambos hijos de tmp son negros
        if (tmp->m_pIzquierda->color == BLACK && tmp->m_pDerecha->color == BLACK) {
            tmp->color = RED;                           //Caso 2
            p = p->getPadre();                            //Caso 2
        }
        else
        {
            if (p->soyIzquierdo())
            {
                //Caso3: el hermano de p: (tmp) es negro, el hijo izquierdo de tmp es rojo
                    //y el hijo derecho de tmp es negro.
                if (tmp->m_pDerecha->color == BLACK)
                {
                    tmp->m_pIzquierda->color = BLACK;       //Caso 3
                    tmp->color = RED;                       //Caso 3
                    rotacionDerecha(tmp);                   //Caso 3
                    tmp = p->m_pPadre->m_pDerecha;          //Caso 3
                }
                //Caso 4: el hermano de p: (tmp) es negro y el hijo derecho de tmp es rojo
                tmp->color = p->m_pPadre->color;            //Caso 4
                p->m_pPadre->color = BLACK;                 //Caso 4
                tmp->m_pDerecha->color = BLACK;             //Caso 4
                rotacionIzquierda(p->m_pPadre);             //Caso 4
                p = m_pRoot;                                //Caso 4
            }
            else
            {
                //Caso3: el hermano de p: (tmp) es negro, el hijo derecho de tmp es rojo
                    //y el hijo derecho de tmp es negro.
                if (tmp->m_pIzquierda->color == BLACK)
                {
                    tmp->m_pDerecha->color = BLACK;       //Caso 3
                    tmp->color = RED;                       //Caso 3
                    rotacionIzquierda(tmp);                   //Caso 3
                    tmp = p->m_pPadre->m_pIzquierda;          //Caso 3
                }
                //Caso 4: el hermano de p: (tmp) es negro y el hijo derecho de tmp es rojo
                tmp->color = p->m_pPadre->color;            //Caso 4
                p->m_pPadre->color = BLACK;                 //Caso 4
                tmp->m_pIzquierda->color = BLACK;             //Caso 4
                rotacionDerecha(p->m_pPadre);             //Caso 4
                p = m_pRoot;                                //Caso 4
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
    catch (exception &e)
    {
        cout<< "Algo sucedio...."<<endl;
    }
}

#endif // RBTREE_H
