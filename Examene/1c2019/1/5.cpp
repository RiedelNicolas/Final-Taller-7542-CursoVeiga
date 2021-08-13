class Complex {
private:
    double x;
    double y;
public:
    Complex(double = 0,double y = 0);
    Complex(const Complex &in); //copia
    Complex(Complex &&in); //movimiento
    Complex& operator=(const Complex& otro); //asignacion por copia
    Complex& operator=(const Complex&& otro); //asignacion por movimiento
    Complex& operator++();
    Complex operator
}