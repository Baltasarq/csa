// Parser.h
// Cabeceras del analizador sintct.
//////////////////////////////////////////////////////////////////////////

#ifndef PARSER__H__
#define PARSER__H__

#include <fstream>
#include <string>

#include "lista.h"
#include "defs.h"             // Definiciones generales

extern const std::string parsPROMPT;
extern const std::string parsMSGNOPANT;
extern const std::string parsNOLLEVASDEESOS;
extern const std::string parsNOSECOMO;
extern const std::string aventPRESYNOMBRE;
extern const std::string parsMSGNOHAY;
extern const std::string parsMSGSYSNOSE;
extern const std::string parsMSGSYSPUESTO;
extern const std::string parsMSGSYSNOLOLLEVAS;
extern const std::string parsMSGSYSOBJNOEXISTE;
extern const std::string parsMENSAJECOGER;
extern const std::string parsMENSAJEDEJAR;
extern const std::string parsMENSAJEPONER;
extern const std::string parsMENSAJEQUITAR;
extern const std::string parsNOLLEVASDEESOS;
extern const std::string parsNOLLEVASDEESOSP;
extern const std::string parsNOSEPUEDECOGER;
extern const std::string parsMSGFIN;
extern const std::string parsDEMASIADOPESO;
extern const std::string parsNOESPONIBLE;
extern const std::string parsYALOLLEVAS;

// Clases del parser -------------------------------------------  CLASES

//////////////////////// Clase Vocablos ////////////////////////////////

class Voc {
public:
	Voc(unsigned int n, unsigned int s, unsigned int t, const std::string &p)
		: numid( n ), syn( s ), tipo( t ), palabra( p )
		{}

	unsigned int getNumId() const
		{ return numid; }

	unsigned int getSyn() const
		{ return syn; }

	unsigned int getTipo() const
		{ return tipo; }

	const std::string &getPalabra() const
		{ return palabra; }

private:
	unsigned int numid;
	unsigned int syn;
	unsigned int tipo;

	std::string palabra;
};

class Vocablos: public Lista<Voc> {
public:
	/// Buscar por palabra en el diccionario
	unsigned int busca(const std::string &p);

	/// Buscar por id en el diccionario
	unsigned int busca(unsigned int x);

	/// Compara dos cadenas, a ver si es syn de la otra.
	/// @param constante La cadena constante que se quiere comparar
	/// @param vocablo El vocablo con el que se quiere comparar, ya buscado
	/// @return true si son iguales o si un syn del vocablo es igual. False en otro caso.
	bool compara(const std::string &constante, const std::string &vocablo);

	friend std::ostream &operator<<(std::ostream &o, Vocablos &x)
	{
		const char *avoc[] = {
				"Dir","Acc","Ctr","Nom",
				"Adj", "Art", "Adv", "Prep"
		};

		o << "Vocablos" << std::endl << std::endl;

		x.ve( x.inic() );
		while( !x.esFin() )
		{
			o << x.getActual()->getNumId()
			  << ' ' << x.getActual()->getPalabra() << ' '
			  << avoc[ x.getActual()->getTipo() - parsDIRECCION ] << ' '
			  << x.getActual()->getSyn() << std::endl;

			x.sig();
		}

		return o;
   }
};

//////////////////////// Clase Mensajes ////////////////////////////////
class Mensaje {
public:
	Mensaje(const std::string &nom, const std::string &msg)
		: nombre( nom ), mensaje( msg )
		{}

	const std::string &getNombre()   const
		{ return nombre;  }
	const std::string &getMensaje()  const
		{ return mensaje; }
private:
	std::string nombre;
	std::string mensaje;
};

class Mensajes: public Lista<Mensaje> {
public:
	Mensaje * busca(const std::string &x);

	const std::string operator[](const std::string &x)
		{ 	Mensaje * toret;
			if ( ( toret = busca( x ) ) != NULL )
					return toret->getMensaje();
			else 	return "";
		}

	friend std::ostream &operator << (std::ostream &o, Mensajes &x)
	{
		o << std::endl << "Mensajes ---------" << std::endl;
		x.ve( x.inic() );

		while ( !x.esFin() )
		{
			o << x.getActual()->getNombre() << ':' << std::endl;
			o << x.getActual()->getMensaje() << std::endl;
			x.sig();
		}
		o << std::endl << std::endl;

		return o;
	}

private:
	static Mensaje FAIL;
};

//////////////////////// Clase Tvbles ////////////////////////////////

class Var {
public:
	Var(const std::string &nom, const unsigned int &v = 0)
		: nombre( nom ), val( v )
		{}

	bool esValido() const
		{ return !( nombre.empty() ); }

	Var &operator=(const unsigned int &x)
		{ set( x ); return *this; }

	bool operator==(const unsigned int &x)
		{ return ( get() == x ); }

	bool operator<(const unsigned int &x)
		{ return ( get() < x ); }

	bool operator>(const unsigned int &x)
		{ return ( get() > x ); }

	const std::string &getNombre() const
		{ return nombre; }

	const unsigned int &get() const
		{ return val; }

	unsigned int &set(const unsigned int &x)
		{ return ( val = x ); }

private:
	std::string nombre;
	unsigned int val;

};

class Variables: public Lista<Var> {
public:
	Var &busca(const std::string &x);

	Var &operator [](const std::string &x)
		{ return busca( x ); }

	friend std::ostream &operator << (std::ostream &o, Variables &x)
	{
		o << std::endl << "Variables ---------" << std::endl;
		x.ve( x.inic() );
		while ( !x.esFin() )
		{
			o << x.getActual()->getNombre() << ':' << std::endl;
			o << x.getActual() << std::endl;
			x.sig();
		}
		o << std::endl << std::endl;

		return o;
	}

private:
	static Var FAIL;
};

//////////////////////// Clase Tobjetos /////////////////////////////////

class Objeto {
public:
    enum TipoObjeto { Escenario, Llevable, Ponible };

    Objeto(unsigned int id, unsigned int codv,
         const std::string &desc,
         bool llevado, bool visible, bool puesto,
         unsigned int loc,
         unsigned int w, TipoObjeto to);

    bool fueExaminado() const
        { return examinado; }
    void setExaminado()
        { examinado = true; }

    bool esVisible() const
        { return visible; }
    void setVisible(bool x = true)
        { visible = x; }

    unsigned int getNumId() const
        { return numId; }

    unsigned int getPeso() const
        { return peso; }
    void setPeso(unsigned int x)
        { peso = x; }

    unsigned int getCodVoc() const
        { return codVoc; }
    void setCodVoc(unsigned int x)
        { codVoc = x; }

    unsigned  int getNumLoc() const
        { return numLoc; }
    bool setNumLoc(unsigned int nl);

    const std::string getDesc() const
        { return desc; }
    void setDesc(const std::string &d)
        { desc = d; }

    TipoObjeto getTipo() const
        { return tipoObjeto; }
    void setTipo(TipoObjeto x)
        { tipoObjeto = x; }

    // Estado
    bool esLlevado() const
        { return llevado; }
    bool estaPuesto(void) const
        { return puesto; }
    bool setLlevado(bool x = true);
    bool setPuesto(bool x = true);

protected:
    bool llevado:1;
    bool puesto:1;

    unsigned int numId;
    TipoObjeto tipoObjeto;

    unsigned int peso;              // Pesa?
    unsigned int codVoc;            // Nombre identificativo
    unsigned int numLoc;            // donde ?
    std::string desc;
    bool visible:1;
    bool examinado:1;
};

class Objetos: public Lista<Objeto> {
public:
    Objetos() : pesoLlevados(0)
        {}

    unsigned int sig()
        { Lista<Objeto>::sig();
          return ( getActual() != NULL ?
                      getActual()->getNumId()
                    : parsUNSIGFAIL );
        }

    void carga(const Objeto &);
    bool busca(unsigned int numObj);
    unsigned int buscaPerVoc(unsigned int);
    unsigned int buscaSigPerLoc(unsigned int);

    unsigned int getPesoLlevados() const
        {return pesoLlevados; }
    unsigned int sumaPeso(int x)
        { return (pesoLlevados += x); }

    friend std::ostream &operator<<(std::ostream &o, Objetos &x)
    {
        Objeto *aux;
        const char *strTipo[] = {"Normal", "Llevable", "Ponible"};

        o << "Objetos" << std::endl;

        x.ve( x.inic() );
        while(!x.esFin())
        {
            aux = x.getActual();

            o << '#'  << aux->getNumId() << std::endl;
            o << '\t' << "Examinado: " << (aux->fueExaminado()? "Si":"No") << std::endl;
            o << '\t' << "Visible: "   << (aux->esVisible()? "Si":"No") << std::endl;
            o << '\t' << "Llevado: "   << (aux->esLlevado()? "Si":"No") << std::endl;
            o << '\t' << "Puesto: "    << (aux->estaPuesto()? "Si":"No") << std::endl;
            o << '\t' << "desc: "      << aux->getDesc() << std::endl;
            o << '\t' << "Palabra: "   << aux->getCodVoc() << std::endl;
            o << '\t' << "Localidad: " << aux->getNumLoc() << std::endl
              << '\t' << "Tipo: "      << strTipo[aux->getTipo() - Objeto::Escenario]
              << std::endl << std::endl << std::endl;

            x.sig();
        }

        return o;
    }
private:
    unsigned int pesoLlevados;
};

//////////////////////// Clase Mapa ////////////////////////////////////

struct Conexion {
     std::string palabra;
     unsigned int numLocDest;
};

struct Localidad {
     unsigned int numLoc;
     unsigned int numConexiones;
     std::string desc;       // Desc. de la localidad
     Conexion conexiones[parsMAXCONEXIONESLOC];
};

class Mapa: public Lista<Localidad> {
public:
    Mapa() : numLoc( 0 )
        {}

    unsigned int getNumLoc() const
        { return numLoc; }

    void setNumLoc(unsigned int nl)
        { numLoc = nl; }

    bool describe(unsigned int);
    void escribeFormato(const std::string &str);

protected:
    unsigned int numLoc;
};

//////////////////////// Clase Tsentencia ///////////////////////////////

struct Sentencia {
    unsigned int codVocablos[ parsMAXVOCABLOSSENTENCIA ];
    unsigned int verbo;
    unsigned int cd;
    unsigned int adv;
    unsigned int leidoHasta;
};

//////////////////////// Clase Tokenizer ////////////////////////////////

class StringTokenizer {
public:
    static const std::string Delimitadores;

    StringTokenizer(): index(0)
        {}

    StringTokenizer(const std::string &x): index(0)
        { buffer = x; }

    unsigned int getPos() const
        { return index; }

    bool eol() const
        { return index >= buffer.length(); }

    std::string getNextToken();

    static std::string &mays(std::string &);
    static std::string &mins(std::string &);
    static std::string normaliza(const std::string &);
    static std::string &trim(std::string &);
    static bool esPuntuacion(char c);

private:
    std::string buffer;
    std::string token;
    unsigned int index;
};

//////////////////////////////// Clase Parser ////////////////////////////
//////////////////////// Clase GenParser //////////////////////////////
class GenParser {
public:
    virtual void setEntrada(std::string &)       	    = 0;
    virtual void hazAccion(std::string &)    		    = 0;
    virtual int  analiza(std::string &)                 = 0;
    virtual bool esFinalJuego() const          			= 0;
};

class Parser: public GenParser {
public:
    Parser(const std::string &jugador, unsigned int x = 60000)
        : nomjugador(jugador), limpeso(x)
        { prepara(); }

    Sentencia       orden;
    Objetos         objetos;
    Vocablos        vocablos;
    Mapa            mapa;
    Mensajes        mensajes;
    Variables       vbles;

    bool estaPresente(const std::string & obj, unsigned int loc)
        {
            objetos.buscaPerVoc( vocablos.busca( obj ) );
            return ( objetos.getActual()->getNumLoc() == loc );
        }

    bool esLlevado(const std::string &obj)
        {
            objetos.buscaPerVoc( vocablos.busca( obj ) );
            return ( objetos.getActual()->esLlevado() );
        }

    unsigned int decrementaMovidas()
        { if ( movidas > 0 ) { --movidas; } return movidas; }

    unsigned int getMovidas() const
        { return movidas; }

    unsigned int getPuntuacion() const
        { return punt; }

    unsigned int getNumLoc() const
        { return mapa.getNumLoc(); }

    unsigned int sumaPuntuacion(int x)
        { return ( punt += x ); }

    bool esFinalJuego() const
        { return final; }

    virtual void hazAccion(std::string &);
    virtual void setEntrada(std::string &);
    virtual int  analiza(std::string &);

    /// Controla las respuestas a la entrada del usuario
    virtual void hazResp()      = 0;

    /// Controla los procesos antes de pedir otra entrada
    virtual void hazProc1()     = 0;

    /// Movimiento en direcciones, norte, sur...
    /// @return true si finalmente se mueve
    bool hazDir();
    void hazCtrl();

    void hazDesc(unsigned int loc = parsUNSIGFAIL);
    void muestraPuntuacion();
protected:
    unsigned int punt;
    std::string nomjugador;
    unsigned int  movidas;
    unsigned int  limpeso;
    bool final;

    void prepara();
    void describeObjeto(Objeto &);
};

#endif
