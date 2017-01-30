// lista.h
// Operaciones sobre la lista de nodos

#ifndef __lista_h__cpp_
#define __lista_h__cpp_

#include <list>

//*************************************************************************
// Lista, contenedor general
//*************************************************************************

template <typename T>
class Lista {
public:
    typedef typename std::list<T>::iterator Posicion;

    void reset()
		{ l.clear(); }
    std::size_t size() const
		{ return l.size(); }

    Lista()
		{ actual = l.begin(); }
    ~Lista()
        { reset(); }

    Posicion pos() const
		{ return actual; }
    Posicion sig()
		{ advance( actual, 1 ); return actual; }
    Posicion pre()
		{ advance( actual, -1 ); return actual; }
    Posicion ve(Posicion x)
		{ actual = x; return x; }
	T * getActual()
		{ return ( esFin()? NULL : &( *actual ) ); }
	const T * getActual() const
		{ return ( esFin()? NULL : &( *actual ) ); }

    virtual void mas(const T &x)
		{
			// Insertar
			l.push_back( x );
		}

    Posicion borra(Posicion i)
		{
			if ( !esVacia() ) {
				l.erase( i );
			}

			return i;
		}

    Posicion inic() const
		{ return l.begin(); }
    Posicion fin() const
		{ return l.end(); }

    Posicion inic()
		{ return l.begin(); }
    Posicion fin()
		{ return l.end(); }

    bool esFin() const
		{ return ( pos() == l.end() ); }
    bool esInic() const
		{ return ( pos() == l.begin() ); }
    bool esVacia() const
		{ return ( l.size() == 0 ); }


protected:
    std::list<T> l;
    Posicion actual;
};

#endif
