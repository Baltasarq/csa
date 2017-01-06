#ifndef SCR_H_INCLUDED
#define SCR_H_INCLUDED

// Funciones necesarias para hacer ---------------------------- INTERFAZ
extern const bool NoPrompt;
extern void putLine(const std::string &, bool = true);
extern void getLine(std::string &, bool = true);

class Scr {
public:
    static void print(const std::string &txt)
        { putLine( txt, false ); }

    static void println(const std::string &txt = "")
        { putLine( txt ); }

    static void input(std::string &x)
        { getLine( x ); }
};

#endif // SCR_H_INCLUDED
