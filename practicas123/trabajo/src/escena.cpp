

#include "ig-aux.h"
#include "escena.h"

#include "objeto3d.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "practicas.h"
#include "camara.h"
#include "materiales-luces.h"
#include "seleccion.h"

//includes necesario a partir de la práctica 3
//#include "modelo-jer.h"
#include "grafo-escena.h"

#include "modelo-jer1.h"
#include "modelo-jer2.h"



using namespace std; 


// -----------------------------------------------------------------------------------------------

Escena::Escena()
{
   // COMPLETAR: Práctica 4: inicializar 'col_fuentes' y 'material_ini'
   // ...


   // COMPLETAR: Práctica 5: hacer 'push_back' de varias camaras perspectiva u ortogonales,
   // (sustituir la cámara orbital simple ('CamaraOrbitalSimple') por varias cámaras de 3 modos ('Camara3Modos')
   camaras.push_back( new CamaraOrbitalSimple() );
   

}
// -----------------------------------------------------------------------------------------------
// visualiza la escena en la ventana actual, usando la configuración especificada en 'cv'

void Escena::visualizarGL( ContextoVis & cv )
{
   using namespace std ;

   // recuperar el cauce actual de 'cv' en 'cauce', activarlo
   Cauce * cauce = cv.cauce_act ; assert( cauce != nullptr );
   cauce->activar() ;

   // recuperar la cámara actual de esta escena y  fijar las matrices 'modelview'
   // y 'projection' en el cauce gráfico (es decir: activar la cámara actual)
   CamaraInteractiva * camara = camaras[ind_camara_actual] ; assert( camara != nullptr );
   const float ratio_vp = float(cv.ventana_tam_y)/float(cv.ventana_tam_x) ;
   camara->fijarRatioViewport( ratio_vp );
   camara->activar( *cauce ) ;


   // dibujar los ejes, si procede
   if ( cv.dibujar_ejes  )
      DibujarEjesSolido( *cauce ) ;

   // fijar el color por defecto en el cauce para dibujar los objetos
   // if ( cv.fondo_blanco && ! cv.iluminacion )
   //    glColor3f( 0.0, 0.0, 0.0 );
   // else
   //    glColor3f( 1.0, 1.0, 1.0 );
   glColor3f( 1.0, 1.0, 1.0 );

   // COMPLETAR: Práctica 1: Configurar el cauce en función de:
   //    cv.sombr_plano (true/false)              --> usar fijarModoSombrPlano (método del 'cauce')
      //    cv.modo_visu   (puntos,lineas o relleno) --> usar glPolygonMode

   // MI CÓDIGO 
   cauce->fijarModoSombrPlano(cv.sombr_plano);  //fijamos modo sombreado
   switch (cv.modo_visu)
   {
   case (ModosVisu::relleno):
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
     break;
      
   case (ModosVisu::lineas):
     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
     break;

   case (ModosVisu::puntos):
     glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
     break;
   default:
     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
     cout << "EN EL MÉTODO ESCENA::VISUALIZAR SE HA ENTRADO EN EL DEFAULT POSIBLEMENTE POR num_modos" << endl;  
     break;  
   }
   //FIN MI CÓDIGO 

   if ( cv.iluminacion )
   {
      // COMPLETAR: Práctica 4: activar evaluación del MIL (y desactivar texturas)
      // * habilitar evaluación del MIL en el cauce (fijarEvalMIL)
      // * activar la colección de fuentes de la escena
      // * activar el material inicial
      // ....

   }
   else // si la iluminación no está activada, deshabilitar MIL y texturas
   {  cauce->fijarEvalMIL( false );
      cauce->fijarEvalText( false );
   }

   // recuperar el objeto actual de esta escena
   Objeto3D * objeto = objetos[ind_objeto_actual] ; assert( objeto != nullptr );

   // COMPLETAR: Práctica 1: visualizar el objeto actual ('objeto')

   //MI CÓDIGO
   objeto->visualizarGL(cv);  // envío de secuencias de vértices
                                      // necesitamso crear el array de vértices 
   // FIN MI CÓDIGO 




   // si hay un FBO, dibujarlo (opcional...)


}





// -----------------------------------------------------------------------------------------------
// pasa la cámara actual a la siguiente

void Escena::siguienteCamara()
{
   assert( ind_camara_actual < camaras.size() );
   ind_camara_actual = (ind_camara_actual+1 ) % camaras.size();
   using namespace std ;
   cout << "Cámara actual cambiada a: " << (ind_camara_actual+1) << " (de " << camaras.size() << ")" << endl ;
}

// -----------------------------------------------------------------------------------------------
// pasa el objeto actual al siguiente

void Escena::siguienteObjeto()
{
   if ( objetos.size() == 0 )
      return ;
   assert( ind_objeto_actual < objetos.size() );
   ind_objeto_actual = (ind_objeto_actual+1 ) % objetos.size();
   using namespace std ;
   cout << "Objeto actual cambiado a: " << objetoActual()->leerNombre()
        << " (" << (ind_objeto_actual+1) << "/" << objetos.size() << ")." << endl  ;
}

// -----------------------------------------------------------------------------------------------
// devuelve puntero al objeto actual

Objeto3D * Escena::objetoActual()
{
   assert( ind_objeto_actual < objetos.size() );
   assert( objetos[ind_objeto_actual] != nullptr );
   return objetos[ind_objeto_actual] ;
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la cámara actual

CamaraInteractiva * Escena::camaraActual()
{
   assert( ind_camara_actual < camaras.size() );
   assert( camaras[ind_camara_actual] != nullptr );
   return camaras[ind_camara_actual] ;
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la colección de fuentes actual

ColFuentesLuz * Escena::colFuentes()
{
   assert( col_fuentes != nullptr );
   return col_fuentes ;
}
// -----------------------------------------------------------------------------------------------

Escena1::Escena1()
{
   using namespace std ;
   cout << "Creando objetos de escena 1 .... " << flush ;

   // añadir el objeto 'Cubo' a la lista de objetos de esta escena:
   objetos.push_back( new Cubo() );

   // COMPLETAR: Práctica 1: creación del resto objetos de la práctica 1
   // Añadir objetos al vector 'objetos', con:
   //     objetos.push_back( new .... )
   // .........

   objetos.push_back( new Tetraedro());
   objetos.push_back( new CuboColor() );


   cout << "hecho." << endl << flush ;
}

// -------------------------------------------------------------------------
// COMPLETAR: Práctica 2
// Añadir la implementación del constructor de la clase Escena2 para construir

Escena2::Escena2()
{
   using namespace std ;
   cout << "Creando objetos de escena 2 .... " << flush ;

   // añadir el objeto 'Cubo' a la lista de objetos de esta escena:
  
   objetos.push_back( new Cilindro(4, 27) ); // con dos tapas
   objetos.push_back( new Cilindro(2, 13) ); // sin tapa
   //objetos.push_back( new Cilindro(3, 13) ); // con una tapa

   objetos.push_back( new Cono(2, 15 ));  // sin tapa
   objetos.push_back( new Cono(7, 15 ));  // con tapa

   objetos.push_back( new Esfera(20, 20 ));  

   // veamos si está bien costruida las mallas 
   objetos.push_back( new MallaPLY("../recursos/plys/ant.ply") );
   objetos.push_back( new MallaRevolPLY("../recursos/plys/peon.ply", 200) );

   


   cout << "hecho." << endl << flush ;
}
// los objetos que se indican en los guiones de las práctica 2
// .......


// -------------------------------------------------------------------------
// COMPLETAR: Práctica 3
// Añadir la implementación del constructor de la clase Escena3 para construir
// los objetos que se indican en los guiones de las práctica 3
// .......


Escena3::Escena3() {

  using namespace std ;
   cout << "Creando objetos de escena 3 .... " << flush ;

  
   objetos.push_back( new Pulpo() );



   cout << "hecho." << endl << flush ;
}


Escena4::Escena4() {

  using namespace std ;
   cout << "Creando objetos de escena 4 .... " << flush ;

  
   objetos.push_back( new Brazo() );



   cout << "hecho." << endl << flush ;
}


// ----------------------------------------------------------------------
// COMPLETAR: Práctica 4
// Añadir la implementación del constructor de la clase Escena4 para construir
// los objetos que se indican en los guiones de las práctica 4
// .......



// ----------------------------------------------------------------------
// COMPLETAR: Práctica 5
// Añadir la implementación del constructor de la clase Escena5 para construir
// los objetos que se indican en los guiones de las práctica 5
// .......



Escena5::Escena5() {

  using namespace std ;
   cout << "Creando objetos de escena 5 .... " << flush ;


   objetos.push_back( new GrafoEstrellaX(8)); 
   objetos.push_back(new PiramideExtrellaZ(8)); 
   objetos.push_back( new ExtrellaZ(8) );



   cout << "hecho." << endl << flush ;
}


Escena6::Escena6() {

  using namespace std ;
   cout << "Creando objetos de escena 5 .... " << flush ;


   objetos.push_back( new Toro(20,20)); 
   


   cout << "hecho." << endl << flush ;
}