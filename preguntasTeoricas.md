### Preguntas teóricas que se pueden presentar en los distintos finales.
<br>

#### Estos finales se pueden encontrar en [el repo de El Dipa](https://github.com/Taller-de-Programacion/examenes).
<br>

### Explique como funciona la **herencia** **publica** en C++ y que diferencias tiene con la **herencia** **privada**.
##### [Pregunta del 06/07/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/1.pdf).

La Herencia es uno de los conceptos mas importantes y fundamentales de la programación orientada a objetos. A grandes rasgos nos permite definir una clase en función de otra.

En C++, la ***herencia publica*** mantiene la misma visibilidad de los miembros públicos y protegidos de la clase base en las clases derivadas. Por otro lado, los miembros privados no se comparten.

Por otro lado, en la ***herencia privada*** todos los miembros publicos y protegidos de la clase base se comparten con la visibilidad de **privados**. Y los miembros privados siguen sin ser compartidos.

<br>

### Indique 2 posibles usos del modificador const. Utilice en cada caso una breve sentencia de código que lo emplee junto con la explicación del significado/consecuencia de su uso.
##### [Pregunta del 06/07/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/1.pdf).

Dos posibles usos pueden ser : 

1. Para indicar que una variable va a ser inmutable.( o como se las llama en el curso "constantes")
    ```c
     const int edad = 5;
    ```
    Esto nos da la seguridad que durante toda la ejecución del código la variable `edad` va a tener el valor que le fue asignado cuando se instancia a la misma.
2. Otro posible uso es para indicar que un método es constante, lo que indica que no modifica ningún miembro de la clase a la que pertenece. 
    ```cpp
    class clase{
        std::string nombre;
        public:
        std::string getNombre() const {
            return nombre;
        }
    }
    ```
    <br>
### Explique el concepto de Mutex. Escriba un ejemplo simple de código donde su uso resulte fundamental para garantizar el correcto empleo de recursos en un contexto concurrente. Describa los métodos disponibles y su uso.
##### [Pregunta del 06/07/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/1.pdf).
<br>

En C++  *mutex* es un objeto con dos estados posibles, bloqueado y liberado. La gracia de este objeto reside en solucionar posibles problemas de concurrencia. 
Cuando un hilo intenta hacer uso del mismo lo obtiene instantáneamente si el estado del mismo es liberado o la ejecución del mismo se queda bloqueada en ese punto hasta que dicho **mutex** sea liberado.
Los dos métodos posible que tiene (y son los que se utilizan para cambiar de estado) son :

* .lock() Que es utilizado para bloquear el mismo, y en caso de que este ya se encuentre bloqueado espera a que el estado del mismo pase a liberado.
* .unlock() Que cambia el estado del mismo a liberado. 

```cpp
#include <thread>
#include <mutex>

std::mutex m;

void imprimir_bloqueante (int n, char caracter) {
    m.lock();
    for(int i=0;i<n;i++){
        std::cout<<c;
    }
    std::cout<<'\n';
    m.unlock()
}

int main () {
    std::thread th1 (imprimir_bloqueante(10,'-'));
    std::thread th2 (imprimir_bloqueante(10,'*'));
    th1.join(); th2.join();
    return 0;
}
```

<br>

### Explique el concepto de referencia en C++. que diferencias hay con respecto a los punteros?
##### [Pregunta del 13/07/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/2.pdf).
En C++ una referencia es un tipo de dato que sirve como alias de otra variable. Por otro lado, los punteros son simplemente una dirección de memoria. Ademas las referencias son inmutables, pueden apuntar a un solo objeto en toda su vida. Por otro lado, los punteros son variables, pueden apuntar a distintas direcciones de memoria.
Se podría decir que la referencia llega como una abstracción de mas alto nivel para solucionar mucho de los mismos problemas que antes eran solucionados por punteros.

<br>

### Explique el concepto de **object slicin** (objeto recortado). Escriba un breve ejemplo sobre como esto afecta una función que pretende aplicar polimorfismo sobre uno de sus parámetros.
##### [Pregunta del 13/07/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/2.pdf).
EL object slicin ocurre cuando se asigna un objeto perteneciente a una clase derivada a una instancia de su clase base. Lo que genera que se "pierda" parte de la información (de ahi sale el nombre de este termino). Ya que C++ al ser un lenguaje de tipado estático, cada instancia de una variable ocupa un espacio constante en memoria.

Lo que se pierde son los atributos extra que agrega la clase derivada.

Esto se puede evitar utilizando punteros o referencias al momento de utilizar polimorfismo, en lugar de tener instancias de objetos.

```cpp
class A {
    protected:
        int foo;
    public:
        A(int x): foo(x){}
    void print() {
        std::cout << "A, foo="<<foo<<std::endl;
    }
};

class B : public A {
    private:
        int bar;
    public:
        B(int x ,int y): A(x), bar(y){}
        void print() {
        std::cout << "A, foo="<<foo<<"bar="<<bar<<std::endl;
    }
};

int main(){
    B foo = B(1,2);
    foo.print();
    A bar = B;
    bar.print();
}
```
La salida es :
* 1,2 
* 1

Se puede solucionar simplemente con punteros o referencias..
<br>
### Explique la diferencia entre las etapas de compilación y enlazado (linking). Escriba un breve ejemplo de código con errores para cada una de ellas indicándolos de forma clara.
##### [Pregunta del 13/07/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/2.pdf).
<br>
Se trata de dos etapas distintas en el proceso de generar un ejecutable.<br>
<br>
Primero ocurre la compilación, donde se valida que los distintos archivos de código fuente estén correctamente formados, correcta sintaxis etc, y como salida se obtienen distintos archivos objeto.

Luego ocurre el enlazado, donde se toman los distintos archivos objeto y se los intenta convertir en un único ejecutable. Resolviendo las distintas referencias que puedan tener estos entre si. (Definiciones externas, uso de bibliotecas, etc..)

* Error de enlazado : 
    ```cpp
    int sumar (int a, int b);
    int main(){
        return 0;
    }
    ```
    La función sumar esta declarada pero no definida.

* Error de compilación : 
    ```cpp
        int main () {
            int foo = 5
            int bar = 8;
        }
    ```
    Sintaxis invalida, falta un ";"

### Describa el concepto de templates en C++. De un breve ejemplo de una función template.
##### [Pregunta del 13/07/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/2.pdf).
<br>
Los templates en C++ permiten escribir partes de nuestro código en forma genérica, sin necesidad de aclarar con que tipos de datos estamos trabajando. Normalmente es utilizado en casos donde distintas implementaciones solo varian en el tipo de dato que utilizan. (Los ejemplos mas comunes se dan en listas, colas, ordenamientos, etc)...

Ejemplo : 
```cpp
    template <class T>
    T max(T x, T y){
       return (x>y)? x: y;
    }
    //y se instancia con :
    max<int>(2,3);
```

### ¿Describa brevemente el contenedor map de la librería estándar de C++? Ejemplifique su uso.
##### [Pregunta del 20/07/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/3.pdf).
<br>

Map implementa un diccionario ordenado, funciona con templates lo que permite que podamos usar cualquier tipo de dato como clave y cualquier tipo de dato como valor. Las clases 

```cpp
    std::map<char, int> m;
    m.insert({'a', 1}); //Inserta un par clave-valor ('a', 1);
    std::cout << m1['a'] << std::endl; //Imprime 1
```
### Que es un método estático (o de clase) en c++? Muestre su manera de empleo mediante un breve ejemplo.
##### [Pregunta del 20/07/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/3.pdf).

<br>

Un método estático es un método que es independiente de cualquier instancia de la clase. Este tipo de métodos pueden ser llamados hasta en el caso que no tengamos ninguna instancia de la clase, esto es gracias al operador `::`.

Pero obviamente  esto trae otras limitaciones, un método estático solo puede acceder a miembros estáticos de la clase que lo contiene.

Los usos de este son infinitos.

Ejemplo:

```cpp
class Foo {
    public :
        static void bar() {}
}

int main (){
    Foo:bar();
    Foo x: 
    x.bar(); // ambos modos son validos.
}
```


### En que consiste el proceso de enlazado o linking?
##### [Pregunta del 20/07/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/3.pdf).
<br>

Ocurre luego del proceso de compilación, se toman los distintos archivos objeto (ya generados) y se los intenta convertir en un único ejecutable. Resolviendo las distintas referencias que puedan tener estos entre si. (Definiciones externas, uso de bibliotecas, etc..)

### Explique cómo se comporta el modificador virtual en C++ y qué relación guarda con las VTables (tablas virtuales). De un breve ejemplo donde su uso sea imprescindible.
##### [Pregunta del 3/08/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/4.pdf).
<br>

El modificador `virtual` en c++ es utilizado exclusivamente en el ámbito de la herencia.
Puede ser utilizado para : 
1. Para declarar un método de una clase como virtual, lo que indica que dicho método va a tener que ser implementado por una clase que herede de esta. Es elemental para el polimorfismo.
2. Para evitar problemas en herencia múltiple, donde debido a descuidos en un árbol de herencias una clase podría llegar a tener bases "repetidas". Para esto se indica al momento de indicar la herencia como "virtual".

La relación con las VTables es que :

En el momento que una clase tiene un método virtual se genera una [vTable](https://pabloariasal.github.io/2017/06/10/understanding-virtual-tables/) para los mismos, que no es mas que una ayuda para saber a que función se tiene que llamar en tiempo de ejecución. Esto puede ser un poco menos eficiente en términos de código, ya que hay un par de direccionamientos extras, pero nos permite utilizar polimorfismo que tiene un gran poder de abstracción.


### Explique el uso de valores por defecto en templates de C++. Escriba un ejemplo.
##### [Pregunta del 3/08/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/4.pdf).
<br>

Los templates pueden tener un valor por defecto. Donde se les especifica que tipo de dato deben tomar en caso de que no se aclare ninguno, 
ejemplo : 
```cpp
template <class T = Int>
    T max(T x, T y){
       return (x>y)? x: y;
    }
```

<br>

### Explique qué es y para qué sirve un constructor de copia en C++, Indique cómo se comporta el sistema si éste no es definido por el desarrollador.
##### [Pregunta del 10/08/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/5.pdf).
<br>

Los constructores por copia son utilizados cuando un argumento se pasa por valor. Sirven para inicializar un nuevo objeto en base a otro.

Si este no es definido por el desarrollador, el sistema le asigna uno por default. A menos que el desarrollador decida borrarlo.

El constructor por copia por defecto simplemente *copia* todos los miembros de la clase enviada a la que recibe.

Una solución para que no sea copiable puede ser : 

```cpp
Point(const Point &p) = delete;
```
y si queremos sacar el operador de asignación (que no es ningún constructor)

```cpp
Point& operator=(const Point &p) = delete;
```
<br>

### ¿Qué elementos debo exigir a un equipo de desarrollo externo para poder utilizar una función de la librería que ellos están desarrollando? ¿En qué parte del proceso de compilación se resuelven las llamadas a dichas función?
##### [Pregunta del 10/08/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/5.pdf).
<br>

Debe exigir : 
1. Un header con la declaración de la función.
2. La implementación de la misma, puede ser compilada (en código objeto) o en código fuente.
2. Una correcta documentación para saber como trabajar con la misma.

Los llamados a dicha función se resuelven en el procesos de enlazado(linking) ya que allí se resuelven las distintas referencias entre los distintos código objetos creados.
<br>


### Describa el concepto de loop de eventos (event loop) utilizado en programación orientada a eventos, y en particular, en entornos de interfaz gráfica (GUIs)
##### [Pregunta del 10/08/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.1/5.pdf).

<br>

Una de las principales características de la programación orientada a eventos es que el programa tiene que estar constantemente *escuchando* los nuevos eventos que se puedan llegar a generar.

Como solución a esto nace algo llamado "loop de eventos", que normalmente se implementa en su hilo particular.
Se puede describir en 3 pasos principales : 
1. Espera a que se genere un nuevo evento (Normalmente mediante alguna función bloqueante)
2. Al llegar un nuevo evento lo despacha al modulo del programa que se encargue de ese comportamiento.
3. Vuelve al punto uno.

Particularmente el comportamiento de una interaz grafica se suele solucionar mediante un loop de eventos. Donde podemos tener múltiples entradas (Clicks en pantalla, input de teclado, algun sensor etc) y en base a estas entradas (eventos) es como debemos manejar el comportamiento de nuestra interfaz.

<br>

### Explique que es y para que sirve una variable de clase (atributo estático) en c++. Mediante un ejemplo, indique como se define dicha variable, su incializacion, y el accesos a su valor para realizar una impresión simple en el main.
##### [Pregunta del 7/12/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.2/1.pdf).

Es una variable que es común a todas las instancias de dicha clase. Se declarar como un atributo normal pero con la palabra reservada `static` previa. Su valor de inicializacion puede ser especificada o no, comportándose como una variable regular.

Ejemplo :

```cpp
class A {
    public :
    static int x;
}
```
y para acceder desde el main 

```cpp
int main() {
    std::cout<<A::x;
    //o
    A foo;
    std::cout<<foo.x;
}
```
<br>

### ¿Qué significa que una función es bloqueante? ¿Cómo subsanaría esa limitación en términos de mantener el programa ‘vivo’?
##### [Pregunta del 14/12/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.2/2.pdf).

Significa que el hilo que la invoca puede llegar a tener parada su ejecución por tiempo indefinido, en la mayoría de los casos esperando un input externo.(sea de disco, red, humano, etc.). Una solución para mantener el programa vivo es la concurrencia, uso de threads para que mientras ese hilo espera la función poder ir ejecutando otras instrucciones.


### Explique qué son los métodos virtuales y para qué sirven. De un breve ejemplo donde su uso sea imprescindible.
##### [Pregunta del 14/12/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.2/2.pdf).

<br>

Los métodos virtuales son utilizados principalmente en la herencia. Sirven para obligar a una clase hija a implementar dicho método de su clase base.
Son imprescindibles en clases abstractas e interfaces.
El ejemplo mas básico puede ser el de las distintas figuras que heredan de dibujable pero se dibujan diferente.

<br>

### ¿Qué función utiliza para esperar la terminación de un thread? Ejemplifique mediante código.
##### [Pregunta del 14/12/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.2/2.pdf).

<br>

Para esperar la terminación de un thread se utiliza el método `join`.
Que se encarga de esperar a que dicho hilo termine la ejecución para unirse con el que lo llama.

Ejemplo :
```cpp
void saludar (){
    std::cout<<"Hola!"<<std::endl
}
int main(){
    std::thread t(saludar);
    t.join();
    return 0;
}
```

### ¿Qué es el polimorfismo? Ejemplifique mediante código
##### [Pregunta del 14/12/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.2/2.pdf).
<br>

En POO, polimorfismo es la capacidad de que un mismo método sea interpretado de distintas manera según la clase que lo implemente. Es algo sumamente util! 

```cpp
#include <iostream> 
using namespace std;
 
class Shape {
   protected:
      int width, height;
      
   public:
      Shape( int a = 0, int b = 0){
         width = a;
         height = b;
      }
      int area() {
         cout << "Parent class area :" <<endl;
         return 0;
      }
};
class Rectangle: public Shape {
   public:
      Rectangle( int a = 0, int b = 0):Shape(a, b) { }
      
      int area () override { 
         cout << "Rectangle class area :" <<endl;
         return (width * height); 
      }
};

class Triangle: public Shape {
   public:
      Triangle( int a = 0, int b = 0):Shape(a, b) { }
      
      int area () override { 
         cout << "Triangle class area :" <<endl;
         return (width * height / 2); 
      }
};

// Main function for the program
int main() {
   Shape *shape;
   Rectangle rec(10,7);
   Triangle  tri(10,5);

   // store the address of Rectangle
   shape = &rec;
   
   // call rectangle area.
   shape->area();

   // store the address of Triangle
   shape = &tri;
   
   // call triangle area.
   shape->area();
   
   return 0;
}
```


### Describa el proceso de transformación de código fuente a un ejecutable. Precise las etapas, las tareas desarrolladas y los tipos de error generados en cada una de ellas.
##### [Pregunta del 14/12/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.2/3.pdf).
<br>

El proceso de transformación de código fuente a ejecutable se puede separar en 3 etapas.

1. Precompilación : Se remplazan los macros y otras directivas de precompilador. Los tipos de errores que pueden llegar a ocurrir están ligados a estas directivas. También se eliminan los comentarios
2. Compilación : Se parsea el texto, verifica la sintaxis y se ensambla el codigo objeto. Los tipo de erorres posibles son errores en sintaxis, de tipado (si el lenguaje lo requiere), etc.
3. Enlazado (linking) : Se intenta formar el ejecutable en base a los distintos archivos objeto que nos quedaron del paso previo. Los distintos tipos de errores pueden ser tener referencias a funciones que no estén implementadas, problemas con los nombres (repetidos), etc.

<br>

### ¿Que función se utiliza para lanzar un thread? Ejemplifique mediante código
##### [Pregunta del 14/12/2017](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.2/3.pdf).
<br>

Un thread es literalmente un hilo de ejecución. Tiene su propio stack, registros(esencial para la programación concurrente) y que comparte con los demás threads del programa : El heap, el code segment, el data segment, y los fd.

En c++ el thread se lanza llamando al constructor std::thread(fun,args).

Ejemplo :
```cpp
void saludar (){
    std::cout<<"Hola!"<<std::endl
}
int main(){
    std::thread t(saludar);
    t.join();
    return 0;
}
```

### Explique qué usos tiene la palabra reservada static en C++. De un breve ejemplo de uno de ellos.
##### [Pregunta del 15/02/2018](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.2/4.pdf).
<br>

1. Como modificador de funciones :
    Hace que dicha función solo sea accesible desde ese mismo archivo.
2. Variable statics : 
    * Global -> Reside en el dataSegment, solo puede ser accedida desde el archivo donde fue definida. Se inicializa cuando comienza el programa y se libera cuando termina.
    Hace que sean inicializadas una única vez y su ámbito se vuelve el data segment del archivo.
    * En una función -> También reside en el data segment pero solo puede ser accedida por la función que la define. Su valor se preservar en los distintos llamados a dicha función.
3. Atributo de clase static :
    Reside en el dataSegment y es único por cada clase, independientemente de la cantidad de instancias que tenga.
4. Método de clase static :
    Es independiente de las distintas instancias, solo puede acceder a los miembros static de la clase.

<br>

### Explique los distintos tipos de herencia que admite C++. De un breve ejemplo de al menos una de ellas.
##### [Pregunta del 15/02/2018](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.2/4.pdf).
<br>

1. publica.
2. privada.
3. protegida.

### Describir y ejemplificar el uso de #ifndef
##### [Pregunta del 15/02/2018](https://github.com/Taller-de-Programacion/examenes/blob/master/2017.2/4.pdf).
<br>

Esta directiva checkea si el identificador asociado esta definido, en caso de no estar definido la condición es verdadera.
El ejemplo clásico esta en las "guardas" de los headers.


### Que es la compilación condicional? En que etapa del proceso de transformación de código se resuelve? Ejemplifique mediante un código C dando un caso de uso util.
##### [Pregunta del 1c 2018](https://github.com/Taller-de-Programacion/examenes/blob/master/2018.1/1.md).
<br>

Es una herramienta para indicar al preproseador si debe o no excluir/incluir distintas partes de nuestro código. El ejemplo mas comun es el de los guards de los headers

**VER DE IMPLEMENTAR CODIGO DE ESTO**



### Cual es el motivo por el cual las clases que utilizan templates se declaran y definen en los .h?
##### [Pregunta del 1c 2018](https://github.com/Taller-de-Programacion/examenes/blob/master/2018.1/1.md).
<br>

Por como funcionan los templates requerimos saber con que tipo de datos van a ser reemplazados al momento de compilar. Esto generaria que no podramos tener un archivo .c que implemente las distintas clases, ya que no dispondriamos de la informacion suficiente para que los mismos sean compilados.

<br>

### Cual es el uso de la funcion listen? Que parametros tiene y para que sirven?
##### [Pregunta del 1c 2018](https://github.com/Taller-de-Programacion/examenes/blob/master/2018.1/1.md).
<br>

La funcion listen es utilizada para indicar que un socket debe esperar conexiones entrantes. 
Para utilizarla primero debemos tener un socket correctamente creado, luego ....
 **Esto medio que sale con practica.**

 <br>

 ### Que es un deadlock? Ejemplifique.
##### [Pregunta del 1c 2018](https://github.com/Taller-de-Programacion/examenes/blob/master/2018.1/1.md).
<br>

Un deadlock ocurre cuando un conjunto de procesos ejecutandose en hilos diferentes se bloquean permanentemente.
Una de las principales razones de esto es cuando distintos hilos comparten recursos.
 
 Por ejemplo : 

 Tenemos proceso 1 que toma el recurso A y espera a que se libere el recurso B para liberar el A y tomar el B. Y por otro lado tenemos a el proceso 2 tomando el recurso B y esperando a que se libere para tomar A para liberar el recurso B y tomar el A. Esto genera un deadlock.

 
 ### Que es un thread? Que funciones se utilizan para manipularlos (lanzarlos, etc)?.
##### [Pregunta del 1c 2018](https://github.com/Taller-de-Programacion/examenes/blob/master/2018.1/1.md).
<br>

Un thread es literalmente un hilo de ejecución. Tiene su propio stack, registros(esencial para la programación concurrente) y que comparte con los demás threads del programa : El heap, el code segment, el data segment, y los fd.

Para manipularlos tenemos : 
El constructor para lanzarlos y join para esperar a que finalice su ejecucion.



### Como se logra que 2 threads accedan (lectura/escritura) a un mismo recurso compartido sin que se genere problemas de consistencia? Ejemplifique
##### [Pregunta del 1c 2018](https://github.com/Taller-de-Programacion/examenes/blob/master/2018.1/1.md).
<br>

Esto se logra mediante algun mecanismo de exclusion mutua (por ejemplo Mutex en c++).
Donde mediante distintos metodos (lock y unlock). Podemos tomar control/liberar los distintos recursos.
***El ejemplo de este es bastante tedioso***


### Que es una macro en C?
##### [Pregunta del 1c 2018](https://github.com/Taller-de-Programacion/examenes/blob/master/2018.1/4.md).
<br>

Una macro en C es un fragmento de codigo que recibe un alias, luego al utilizar este alias se reemplaza con el codigo que lo definimos. Esto ocurre en el proceso de precompilacion.

Uno de los usos mas comunes es para definir constantes :

Ejemplo : 
```c
#define TAM 10

int main(){
    int arreglo[TAM];
}
```


### Explique que es y para que sirve un constructor MOVE en C++. Indique como se comporta el sistema si este no es definido por el desarrollador.
##### [Pregunta del 1c 2018](https://github.com/Taller-de-Programacion/examenes/blob/master/2018.1/4.md).
<br>
C++ nos permite definir constructores por movimiento, que como bien explica su nombre nos indica nos permite "mover" una instancia de un objeto a otra.

Este constructor normalmente se implementa en clases donde no tiene sentido crear "copias". Como por ejemplo sockets, etc.
En el constructor por movimiento se mueven los atributos al objeto nuevo y se invalidan en el anterior. De esta forma el objeto viejo sigue existiendo y siendo valido, pero el valor de sus atributos ya no genera inconcistencias(si se llama a su destructor).
Si el constructor por movimiento no es definido por el desarrollador, se incluye uno por defecto que realiza std::move para todos los atributos, pero no los invalida en el objeto viejo.


### Que es un functor? Ejemplifique.
##### [Pregunta del 1c 2018](https://github.com/Taller-de-Programacion/examenes/blob/master/2018.1/4.md).
<br>

Un functor es un objeto en c++ qe tiene sobrecargado el operador `()`.  Se puede pensar como una clase que funciona como una funcion.
A lo largo de materia tambien solemos usarlo en el uso de threads.

La ventaja que trae frente a una funcion convencional es son objetos, por lo tanto ademas de tener un comportamiento (como una funcion) tambien tienen un estado que puede ir variando en funcion de la ejecucion. Permite un codigo mucho mas flexible.

Ejemplo :

```cpp
class Impresora{
    public:
        Impresora(std::string in):texto(in){}
        void operator() () {
            std::cout<<texto<<std::endl;
        }
    private:
        std::string texto;
}

int main() {
    Impresora impresora("Hola mundo");
    impresora();
    return 0;
}
```

### ¿Qué ventaja ofrece un lock RAII frente al tradicional lock/unlock?
##### [Pregunta del 1c 2018](https://github.com/Taller-de-Programacion/examenes/blob/master/2018.2/3.pdf).
<br>

La principal ventaja que trae es el poder de abstraccion, como usuario de la clase "protegida" nos olvidamos de tener que bloquear/liberar el mutex. 
Ademas hace al codigo mas robusto, ya que se minimizan los errores debido a que el constructor bloquea el mutex y el destructor lo libera. 



### ¿Qué valor arroja sizeof(int)? Justifique.
##### [Pregunta del 1c 2018](https://github.com/Taller-de-Programacion/examenes/blob/master/2018.2/4.pdf).
<br>

Esta expresion devuelve el valor de un entero expresado en size_t.

Este valor depende 100% la arquitectura y el compilador.
Normalmente en arquitecturas de 16 bits devolvera 2 bytes, en 32 bits 4 bytes y en 64 puede valer tanto 8 o 4. (Si compilamos el programa con gcc el mismo vale 4.)

La razon por la que en muchos sistemas de 64 bits sigue valiendo 4 bytes es exclusivamente por razones de retrocompatibilidad con recursos compartidos que tambien trabajan con estructuras de 32 bits.


### ¿Qué características debe tener un compilador C para se considerado “portable”?
##### [Pregunta del 1c 2019](https://github.com/Taller-de-Programacion/examenes/blob/master/2019.1/3.pdf).
<br>
(Este ejercicio me lo respondio a El Dipa)

Un compilador C portable es aquel que soporta la sintaxis (y semantica) del lenguage C dado un estandar (ANSI, C11, C17) y que no agrega
ninguna sintaxis adicional por fuera del estandar (de tal manera que el mismo codigo podria ser compilado por otro compilador). Esto incluye
tambien el proceso de compilacion estandar (precompilacion, compilacion,
linkeo)

Ademas el compilador debe ofrecer una implementacion a la libreria estandar
de C (lease, string.h, stdio.h, stdlib.h) respetando el estandar de C mencionado anteriormente tal que un programa compilado en un entorno pueda ser ejecutado en otro que tenga una libreria C compatible.


### Explique qué es cada uno de los siguientes, haciendo referencia a su inicialización, su comportamiento y el area de memoria donde residen:
1. Una variable global static.
2. Una variable local static
3. Un atributo de clase static.
##### [Pregunta del 1c 2019](https://github.com/Taller-de-Programacion/examenes/blob/master/2019.1/4.pdf).
<br>

1. Una variable global static reside en el data segment del programa, solo puede ser accedido en el archivo donde fue definida. Se inicializa cuando comienza el programa y se libera cuando termina. En caso de no recibir inicializacion la porcion de memoria que le corresponde se carga en cero.
2. Una variable local static tambien reside en el data segment del programa, pero solo puede ser accedida en la funcion donde fue definida. Al residir en el data segment su valor se preserva en los distintos llamados que se pueden realizar a la funcion. En caso de no especificar un valor de inicializacion, la misma comienza en 0 o null.
3. Atributo de clase static, tambien reside en el data segment. Es un atributo comun a todas las instancias de la clase, en caso de no inicializarce tambien se inicia en 0.

### Explique metodos virtuales puros y para que sirven : 
##### [Pregunta del 1c 2019](https://github.com/Taller-de-Programacion/examenes/blob/master/2019.1/4.pdf).
<br>
Los metodos virtuales puros son aquellos que estan obligados a implementar las clases hijas. Son imprecindibles en interfaces y clases abstractas.

```cpp
class animal{
    ...
    public:
        virtual void repirar() = 0; //Obligamos a que la derivada lo implemente, no se puede instanciar la clase animal.
}
```

### Considere la estructurastruct ejemplo int a; char b;.¿Es verdad que sizeof(ejemplo)=sizeof(a)+sizeof(b)? Justifique. 
##### [Pregunta del 2c 2019](https://github.com/Taller-de-Programacion/examenes/blob/master/2019.1/4.pdf).

No, no se puede realizar esta informacion.
El tamano de un struct no siempre es la suma de sus miembros. Esto es porque normalmente el compilador agrega un "padding" para evitar problemas de alineacion en memoria. 
Diferentes compiladores pueden tener distintas soluciones a esto, y esto excede cualquier estandar de C.


### ¿En qué consiste el patrón de diseño RAII? Ejemplifique. 
##### [Pregunta del 2c 2019](https://github.com/Taller-de-Programacion/examenes/blob/master/2019.1/4.pdf).
**Resource Acquisition Is Initialization**
<br>

El patron RAII se puede resumir en basicamente dos principios : 
1. Inicializar una clase en su constructor y obtener alli todos los recursos(acceso a red, disco, memoria, generacion de hilos..) que requiera la misma. En caso de no poder obtener un recurso, tira una exception.
2. Liberar los recursos adquiridos en el constructor en el destructor de la clase. Nunca arroja una excep.

Esto trae una gran cantidad de beneficios, como mayor poder de abstraccion, garantizamos que si la clase logra ser instanciada la misma tiene acceso a los recursos que requiere, garantizamos que los recursos se liberen(gracias al destructor).

C++ nos brinda una gran herramienta para esto como member initialization list, etc.

**Por ejemplo se puede usar un clase que escriba en un archivo**