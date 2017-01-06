# Construir el ejecutable

CPPFLAGS=-O3

all: csa

csa : csa.obj juego.obj parser.obj scrutil.obj
	$(CXX) $(CPPFLAGS) csa.obj juego.obj parser.obj scrutil.obj -ocsa

csa.obj : csa.cpp defs.h
	$(CXX) $(CPPFLAGS) -c csa.cpp -ocsa.obj

juego.obj : juego.cpp juego.h defs.h
	$(CXX) $(CPPFLAGS) -c juego.cpp -ojuego.obj

parser.obj : parser.cpp parser.h defs.h
	$(CXX) $(CPPFLAGS) -c parser.cpp -oparser.obj

scrutil.obj : scrutil.cpp scrutil.h
	$(CXX) $(CPPFLAGS) -c scrutil.cpp -oscrutil.obj

clean : 
	$(RM) *.exe
	$(RM) *.obj
	$(RM) *.o
	$(RM) csa
