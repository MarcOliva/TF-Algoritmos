#include <functional>

using namespace std;

template<typename T, typename R = T, T NONE = 0>
class ABB
{
    struct Nodo
    {
        T element;
        Nodo* left;
        Nodo* right;
        int levels;
    public:
        Nodo(T elem) : element(elem), levels(1), left(nullptr), right(nullptr) { }
    };

    Nodo* root;
    function<R(T)> key;
    int len;
public:
    ABB(function<R(T)> _key = [](T a) { return a; })
        : key(_key), root(nullptr), len(0) {}

    ~ABB()
    {
        this->clear(this->root);
    }

    int height()
    {
        return this->height(this->root);
    }

    int size()
    {
        return this->len;
    }

    void addElemento(T elem)
    {
        this->addElemento(this->root, elem);
    }

    void inOrder(function<void(T)> proc)
    {
        this->inOrder(this->root, proc);
    }

    void eliminarElemento(T elem)
    {
        this->eliminarElemento(this->root, elem);
    }
    //------------------------------METODOS PRIVADOS----------------------------------//
private:
    void clear(Nodo*& nodo)
    {
        if (nodo != nullptr)
        {
            this->clear(nodo->right);
            this->clear(nodo->left);

            delete nodo; //para eliminar el objeto de la memoria

            nodo = nullptr; //para que ya no apunte a memoria liberada
        }
    }

    int height(Nodo* nodo)
    {
        return (nodo == nullptr ? 0 : nodo->levels);
    }

    void addElemento(Nodo*& nodo, T elem)
    {
        if (nodo == nullptr)
        {
            nodo = new Nodo(elem);
        }
        else
        {
            if (key(elem) < key(nodo->element))
            {
                this->addElemento(nodo->left, elem);
            }
            else
            {
                this->addElemento(nodo->right, elem);
            }
            //balanceamos el arbol, despues de insertar el elemento. Podemos hacer esto, ya que es recursivo la funcion de agregar.
            this->balancear(nodo);
        }
    }

    void inOrder(Nodo* nodo, function<void(T)> proc)
    {
        if (nodo != nullptr)
        {
            this->inOrder(nodo->left, proc);
            proc(nodo->element);
            this->inOrder(nodo->right, proc);
        }
    }

    //implementacion recursiva
    void eliminarElemento(Nodo*& nodo, T elem)
    {
        if (nodo == nullptr) return;

        else if (elem < nodo->element)
            this->eliminarElemento(nodo->left, elem);
        else if (elem > nodo->element)
            this->eliminarElemento(nodo->right, elem);
        //caso que tenga dos hijos
        else if (nodo->left != nullptr && nodo->right != nullptr)
        {
            nodo->left = this->removeMax(nodo->left, nodo);
        }
        else
        {
            Nodo* aux = nodo;
            nodo = (nodo->left != nullptr) ? nodo->left : nodo->right;
            delete aux;
        }

        this->balancear(nodo);
    }


    Nodo* removeMax(Nodo*& nodo, Nodo* elementoCambiar)
    {
        if (nodo->right != nullptr)
        {
            nodo->right = this->removeMax(nodo->right, elementoCambiar);
        }
        else
        {
            elementoCambiar->element = nodo->element;
            Nodo* hl = nodo->left;
            delete nodo;
            return hl;
        }
        this->balancear(nodo);
        return nodo;
    }

    //------EMPIEZA----------Operaciones de balanceo-------------------------------//
    void updatelevel(Nodo* nodo)
    {
        if (nodo != nullptr)
        {
            int hl = this->height(nodo->left);
            int hr = this->height(nodo->right);
            //actualizamos a (la altura del hijo mas alto) mas 1.
            nodo->levels = (hl > hr ? hl : hr) + 1;
        }
    }

    void rotarLeft(Nodo*& nodo)
    {
        //auxiliar que apunte al hijo derecho para no perderlo
        Nodo* aux = nodo->right;

        //el nuevo hijo derecho del nodo principal va a ser el hijo izquierdo del anterior hijo derecho del nodo principal
        nodo->right = aux->left;
        //al hacer el cambio de arriba(al hacer el cambio de hijo), debems actualizar la altura del nodo principal(el que llega como parametro).    
        this->updatelevel(nodo);

        //convertimos al anterior hijo derecho del nodo principal, que se guardo en el aux, como el padre del nodo principal(que viene como parametro).
        aux->left = nodo;
        //al hacer el cambio de arriba(al hacer el cambio de hijo), debemos actualizar la altura del nodo aux
        this->updatelevel(aux);

        //actualizamos el puntero nodo principal, ya que el nuevo padre es el nodo que apunta aux, para esto se debe mandar el parametro como referencia, para cmbiar el valor de memoria.
        nodo = aux;
    }

    //la misma logica que rotar a la izquierda, pero todo los cambios reflejados.
    void rotarRight(Nodo*& nodo)
    {
        //auxiliar que apunte al hijo izquierdo para no perderlo
        Nodo* aux = nodo->left;

        //el nuevo hijo izquierdo del nodo principal va a ser el hijo derecho del anterior hijo izquierdo del nodo principal.
        nodo->left = aux->right;
        //al hacer el cambio de arriba (al hacer el cambio de hijo), debems actualizar la altura del nodo principal(el que llega como parametro). 
        this->updatelevel(nodo);

        //convertimos al anterior hijo izquierdo del nodo principal, que se guardo en el aux, como el padre del nodo principal(que viene como parametro).
        aux->right = nodo;
        //al hacer el cambio de arriba(al hacer el cambio de hijo), debemos actualizar la altura del nodo aux
        this->updatelevel(aux);

        //actualizamos el puntero nodo principal, ya que el nuevo padre es el nodo que apunta aux, para esto se debe mandar el parametro como referencia, para cmbiar el valor de memoria.
        nodo = aux;

    }

    void balancear(Nodo*& nodo)
    {
        int hl = this->height(nodo->left);
        int hr = this->height(nodo->right);

        //si se cumple siginifica que el nodo es pesado a la izquierda.
        if (hl - hr > 1)
        {
            hl = this->height(nodo->left->left);
            hr = this->height(nodo->left->right);

            //si el hijo derecho del hijo izquierdo del nodo es MAYOR en altura(levels) al hijo izquierdo del hijo izquierdo del nodo.
            if (hl < hr)
            {
                this->rotarLeft(nodo->left);
            }
            this->rotarRight(nodo);
        }
        //si se cumple significa que esta pesado a la derecha.
        else if (hl - hr < -1)
        {
            hl = this->height(nodo->right->left);
            hr = this->height(nodo->right->right);

            //si el hijo izquierdo del hijo derecho del nodo es MAYOR en altura(levels) al hijo derecho del hijo derecho del nodo.
            if (hl > hr)
            {
                this->rotarRight(nodo->right);
            }
            this->rotarLeft(nodo);
        }
        //si entra aca significa que esta balanceado, solo se debe actualizar su altura. 
        else
        {
            this->updatelevel(nodo);
        }

    }
    //------TERMINA-----------Operaciones de balanceo-------------------------------//
};
