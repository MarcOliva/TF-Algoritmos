
template<typename T, T NADA>
class Lista
{
private:
	struct Nodo
	{
		T elemento;
		Nodo* next;
		Nodo* prev;
		Nodo(T elem, Nodo* p = nullptr, Nodo* n = nullptr) :
			elemento(elem), prev(p), next(n) {}
	};

	Nodo* head;
	Nodo* last;
	int length;
public:
	Lista() : head(nullptr), last(nullptr), length(0) {}

	~Lista()
	{
		//std::cout << this->length << '\n';
		while ( this->head != nullptr )
		{
			Nodo* aux = this->head;
			this->head = this->head->next;
			delete aux;
			//std::cout << "estoy en el bucle\n";
		}
		//std::cout << "sali del bucle\n";
		this->head = nullptr;
		this->last = nullptr;
		this->length = 0;
	}

	int size()
	{
		return this->length;
	}

	bool isEmpty()
	{
		return (this->length == 0);
	}

	void agregar_final(T elem)
	{

		if (this->length == 0)
		{
			Nodo* newest = new Nodo(elem, nullptr, nullptr);
			this->last = newest;
			this->head = newest;
		}
		else
		{
			Nodo* newest = new Nodo(elem, this->last, nullptr);
			this->last->next = newest;
			this->last = newest;
		}
		this->length++;
	}

	void eliminar_inicio()
	{
		if (this->length > 0)
		{
			Nodo* aux = this->head;
			this->head = this->head->next;
			if (this->length == 1)
			{
				this->head = nullptr;
				this->last = nullptr;
			}

			delete aux;

			this->length--;
		}
	}

	void eliminar_final()
	{
		if (this->length > 0)
		{
			Nodo* aux = this->last;
			this->last = this->last->prev;

			if (this->length == 1)
			{
				this->last = nullptr;
				this->head = nullptr;
			}

			delete aux;

			this->length--;
		}
	}

	void eliminar_pos(int pos)
	{
		if (pos < 0 || pos >= this->length) return;
		else if (pos == 0) this->eliminar_inicio();
		else if (pos == (this->length - 1)) this->eliminar_final();
		else if (pos >(this->length - pos)) //si esta mas cerca de LAST
		{
			Nodo* corredor = this->last;
			for (int i = this->length - 1; i > (pos + 1); --i)
			{
				corredor = corredor->prev;
			}

			Nodo* aeliminar = corredor->prev;
			corredor->prev = aeliminar->prev;

			aeliminar->prev->next = corredor;

			delete aeliminar;
			this->length--;
		}
		else //esta mas cerca de HEAD
		{
			Nodo* corredor = this->head;
			for (int i = 1; i < pos; ++i)
			{
				corredor = corredor->next;
			}

			Nodo* aeliminar = corredor->next;
			corredor->next = aeliminar->next;

			aeliminar->next->prev = corredor;

			delete aeliminar;
			this->length--;
		}
	}

	T get_inicio()
	{
		if (this->length > 0)
		{
			return this->head->elemento;
		}
		else return NADA;
	}

	T get_final()
	{
		if (this->length > 0)
		{
			return this->last->elemento;
		}
		else return NADA;
	}

	T get_pos(int pos)
	{
		if (pos < 0 || pos >= this->length) return NADA;
		else if (pos == 0) return this->get_inicio();
		else if (pos == (this->length - 1)) return this->get_final();
		else if (pos >(this->length - pos)) //si esta mas cerca de LAST
		{
			Nodo* corredor = this->last;
			for (int i = this->length - 1; i > pos; --i)
			{
				corredor = corredor->prev;
			}

			return corredor->elemento;
		}
		else //esta mas cerca de HEAD
		{
			Nodo* corredor = this->head;
			for (int i = 0; i < pos; ++i)
			{
				corredor = corredor->next;
			}

			return corredor->elemento;
		}
	}

	class iterator {
        Nodo* aux;
        int pos;
    public:
        iterator(Nodo* aux, int pos)
            : aux(aux), pos(pos) {}
        bool operator != (iterator other) {
            return pos != other.pos;
        }
        int operator ++() {
            aux = aux->next;
            ++pos;
            return 0;
        }
        T operator *() {
            return aux->elemento;
        }
		int getPosIterator()
		{
			return this->pos;
		}
    };
    
	iterator begin() {
        return iterator(this->head, 0);
    }
    
	iterator end() {
        return iterator(nullptr, this->length);
    }
};