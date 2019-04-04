#include <vector>
#include "math.h"
#include "stdlib.h"

using namespace std;

//Se define un arreglo de reales como un vector
typedef vector<float> Vector;
//Se define un arreglo de vectores como una matriz
typedef vector<Vector> Matrix;

//La función recibe:
//- Una matriz (se asume que será cuadrada)
//- La dimensión de la matriz
//La función crea una matriz cuadrada nxn llena de ceros
void zeroes(Matrix &M,int n){
    //Se crean n filas
    for(int i=0;i<n;i++){
        //Se crea una fila de n ceros
        vector<float> row(n,0.0);
        //Se ingresa la fila en la matriz
        M.push_back(row);
    }
}

//La función recibe:
//- Un vector (se asume columna)
//- La dimensión del vector
//La función crea un vector nx1 lleno de ceros
void zeroes(Vector &v,int n){
    //Se itera n veces
    for(int i=0;i<n;i++){
        //En cada iteración se agrega un cero al vector
        v.push_back(0.0);
    }
}

//La función recibe:
//- Una matriz
//- Una matriz que será la copia de la primera
//La función copiará todo el contenido de la primera matriz en
//la segunda, respetando las posiciones
void copyMatrix(Matrix A, Matrix &copy){
    //Se inicializa la copia con ceroes
    //asegurándose de sus dimensiones
    zeroes(copy,A.size());
    //Se recorre la matriz original
    for(int i=0;i<A.size();i++)
        for(int j=0;j<A.at(0).size();j++)
            //Se coloca la celda actual de la matriz original
            //en la misma posición dentro de la copia
            copy.at(i).at(j) = A.at(i).at(j);
}

//La función recibe:
//- Una matriz
//- Un vector
//- Un vector para la respuesta
//La función asume que las dimensiones de la matriz y los vectores son las
//adecuadas para que la multiplicación sea posible
void productMatrixVector(Matrix A, Vector v, Vector &R){
    //Se aplica básicamente la formulación que puede
    //consultarse en el siguiente enlace (entrar con cuenta UCA):
    //          https://goo.gl/PEzWWe

    //Se itera una cantidad de veces igual al número de filas de la matriz
    for(int f=0;f<A.size();f++){
        //Se inicia un acumulador
        float cell = 0.0;
        //Se calcula el valor de la celda de acuerdo a la formulación
        for(int c=0;c<v.size();c++){
            cell += A.at(f).at(c)*v.at(c);
        }
        //Se coloca el valor calculado en su celda correspondiente en la respuesta
        R.at(f) += cell;
    }
}

//La función recibe:
//- Un escalar (valor real)
//- Una matriz
//- Una matriz para la respuesta
//La función multiplica cada uno de los elementos de la matriz por el escalar,
//ubicando los resultados en la matriz de respuesta
void productRealMatrix(float real,Matrix M,Matrix &R){
    //Se prepara la matriz de respuesta con las mismas dimensiones de la
    //matriz
    zeroes(R,M.size());
    //Se recorre la matriz original
    for(int i=0;i<M.size();i++)
        for(int j=0;j<M.at(0).size();j++)
            //La celda actual se multiplica por el real, y se almacena
            //el resultado en la matriz de respuesta
            R.at(i).at(j) = real*M.at(i).at(j);
}

//La función recibe:
//- Una matriz
//- Un índice de fila i
//- Un índice de columna j
//La función elimina en la matriz la fila i, y la columna j
void getMinor(Matrix &M,int i, int j){
    //Se elimina la fila i
    M.erase(M.begin()+i); //Uso de begin para obtener un iterator a la posición de interés
    //Se recorren las filas restantes
    for(int i=0;i<M.size();i++)
        //En cada fila se elimina la columna j
        M.at(i).erase(M.at(i).begin()+j);
}

//La función recibe:
//- Una matriz
//La función calcula el determinante de la matriz de forma recursiva
float determinant(Matrix M){
    //Caso trivial: si la matriz solo tiene una celda, ese valor es el determinante
    if(M.size() == 1) return M.at(0).at(0);
    else{
        //Se implementa la siguiente formulación del siguiente enlace:
        //(Entrar con cuenta UCA)
        //              https://goo.gl/kbWdmu

        //Se inicia un acumulador
        float det=0.0;
        //Se recorre la primera fila
        for(int i=0;i<M.at(0).size();i++){
            //Se obtiene el menor de la posición actual
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,0,i);

            //Se calculala contribución de la celda actual al determinante
            //(valor alternante * celda actual * determinante de menor actual)
            det += pow(-1,i)*M.at(0).at(i)*determinant(minor);
        }
        return det;
    }
}

//La función recibe:
//- Una matriz
//- Una matriz que contendrá los cofactores de la primera
void cofactors(Matrix M, Matrix &Cof){
    //La matriz de cofactores se define así:
    //(Entrar con cuenta UCA)
    //          https://goo.gl/QK7BZo

    //Se prepara la matriz de cofactores para que sea de las mismas
    //dimensiones de la matriz original
    zeroes(Cof,M.size());
    //Se recorre la matriz original
    for(int i=0;i<M.size();i++){
        for(int j=0;j<M.at(0).size();j++){
            //Se obtiene el menor de la posición actual
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,i,j);
            //Se calcula el cofactor de la posición actual
            //      alternante * determinante del menor de la posición actual
            Cof.at(i).at(j) = pow(-1,i+j)*determinant(minor);
        }
    }
}

//La función recibe:
//- Una matriz
//- Una matriz que contendrá a la primera pero transpuesta
//La función transpone la primera matriz y almacena el resultado en la segunda
void transpose(Matrix M, Matrix &T){
    //Se prepara la matriz resultante con las mismas dimensiones
    //de la matriz original
    zeroes(T,M.size());
    //Se recorre la matriz original
    for(int i=0;i<M.size();i++)
        for(int j=0;j<M.at(0).size();j++)
            //La posición actual se almacena en la posición con índices
            //invertidos de la matriz resultante
            T.at(j).at(i) = M.at(i).at(j);
}

//La función recibe:
//- Una matriz
//- Una matriz que contendrá la inversa de la primera matriz
//La matriz calcula la inversa de la primera matriz, y almacena el resultado
//en la segunda
void inverseMatrix(Matrix M, Matrix &Minv){
    //Se utiliza la siguiente fórmula:
    //      (M^-1) = (1/determinant(M))*Adjunta(M)
    //             Adjunta(M) = transpose(Cofactors(M))

    //Se preparan las matrices para la de cofactores y la adjunta
    Matrix Cof, Adj;
    //Se calcula el determinante de la matriz
    float det = determinant(M);
    //Si el determinante es 0, se aborta el programa
    //No puede dividirse entre 0 (matriz no invertible)
    if(det == 0) exit(EXIT_FAILURE);
    //Se calcula la matriz de cofactores
    cofactors(M,Cof);
    //Se calcula la matriz adjunta
    transpose(Cof,Adj);
    //Se aplica la fórmula para la matriz inversa
    productRealMatrix(1/det,Adj,Minv);
}
