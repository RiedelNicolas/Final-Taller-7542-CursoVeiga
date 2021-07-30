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

En C++ *mutex* es un objeto con dos estados posible, bloqueado y liberado. La gracia de este objeto reside en solucionar posibles problemas de concurrencia.
