
/*
Escriba un programa que imprima por salida estándar los números entre 1 y 100
, en orden ascendente. Se pide que los números sean contabilizados por una 
variable global única y que los pares sean escritos por un hilo mientras que los
 impares sean escritos por otro. Contemple la correcta sincronización entre hilos
  y la liberación de los recursos utilizados.
  */
 
#include <iostream>
#include <thread>
#include <mutex>

int i = 1;
std::mutex m;

void contar(bool par) {
  m.lock();
  if (i%2 == 0 && !par){
    i++;
    std::cout<<i<<::std::endl;
  }
  if(i%2 != 0 && par) {
    i++;
    std::cout<<i<<::std::endl;
  }
  m.unlock();
}

int main() {
  std::thread th1 (contar,true);
  std::thread th2 (contar,false);
  th1.join(); th2.join();
  return 0;
}