// *********************************************************************
// **
// ** Informática Gráfica, curso 2016-17
// ** Declaraciones de la clase Objeto3D.hpp
// **
// *********************************************************************

#ifndef IG_MALLAIND_HPP
#define IG_MALLAIND_HPP

#include <vector>          // usar std::vector

#include "objeto3d.h"   // declaración de 'Objeto3D'
#include "array-verts.h" // clase 'ArrayVert'

// ---------------------------------------------------------------------
// clase para objetos gráficos genéricos

class MallaInd : public Objeto3D
{
   

   protected:
      // COMPLETAR: incluir aquí las variables y métodos privados que sean
      // necesarios para una malla indexada
      // ......

      std::vector<Tupla3f> vertices ;
      std::vector<Tupla3i> triangulos ;

      std::vector<Tupla3f> col_ver ;  // colores de los vértices
      std::vector<Tupla3f> nor_ver ;  // normales de vértices
      std::vector<Tupla3f> nor_tri ;  // normales de triangulos
      std::vector<Tupla2f> cc_tt_ver ; // coordenadas de textura de los vértices

     
      // array de vértices con información de tablas para visualizar
      // (se crea bajo demanda: la primera vez que se llama a 'visualizarGL')
      ArrayVertices * array_verts = nullptr ; 



      // normales de triángulos y vértices
      void calcularNormales();

      // calculo de las normales de triángulos (solo si no están creadas ya)
      void calcularNormalesTriangulos() ;

  //_______ RETO 2 _________
  std:: vector<Tupla3f> esferaXZ;
  std:: vector<Tupla3f> esferaYZ;
  std:: vector<Tupla3f> esferaXY;

  Tupla3f centro_geometrico = {0,0,0};
  float radio_envolvente = 0;

  //____  parte 2

  ArrayVertices * array_envolventeXY = nullptr;
  ArrayVertices * array_envolventeXZ = nullptr;
  ArrayVertices * array_envolventeYZ = nullptr;
   

  
  
   public:
      // crea una malla vacía (nombre: "malla indexada nueva vacía")
   

  
  
   public:
      // crea una malla vacía (nombre: "malla indexada nueva vacía")
   

  
  
   public:
      // crea una malla vacía (nombre: "malla indexada nueva vacía")
      MallaInd() ;

      // crea una malla vacía con un nombre concreto:
      MallaInd( const std::string & nombreIni );

      // visualizar el objeto con OpenGL
      virtual void visualizarGL( ContextoVis & cv ) ;

  // _____ RETO 2 _________

  Tupla3f centroGeometrico();
  float calculaDistanciaMaxima();
  void calculaPuntosRepresentativos();


  void calculaTodo() {
    centroGeometrico();
    calculaDistanciaMaxima();
    calculaPuntosRepresentativos();
  }





} ;
// ---------------------------------------------------------------------
// Clase para mallas obtenidas de un archivo 'ply'
// es un tipo de malla indexada que defie un nuevo constructor
// que recibe el nombre del archivo ply como parámetro

class MallaPLY : public MallaInd
{
   public:
      MallaPLY( const std::string & nombre_arch ) ;
} ;


// ---------------------------------------------------------------------

class Cubo : public MallaInd
{
   public:
      Cubo();
};

// --------------------------------------------------------------------

class Cubo24 : public MallaInd
{
  public:
      Cubo24();
} ;


// -- MIS DECLARACIAONES

class Tetraedro: public MallaInd
{
public:
  Tetraedro();
};

class CuboColor: public MallaInd
{
public:
  CuboColor();
};

// ____________________  Para práctica 3 submarino ______

class PrismaTrapecio: public MallaInd
{
public:
  PrismaTrapecio();
};




//_______  RETO 4 _______-

class  ExtrellaZ: public MallaInd
{
public:
  ExtrellaZ( unsigned n); 
};

class  PiramideExtrellaZ: public MallaInd
{
public:
  PiramideExtrellaZ( unsigned n); 
}; 
#endif
