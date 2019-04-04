#include <vector>
#include "math.h"
#include "stdlib.h"

using namespace std;

//Se define un arreglo de reales como un vector
typedef vector<float> Vector;
//Se define un arreglo de vectores como una matriz
typedef vector<Vector> Matrix;

//La funci�n recibe:
//- Una matriz (se asume que ser� cuadrada)
//- La dimensi�n de la matriz
//La funci�n crea una matriz cuadrada nxn llena de ceros
void zeroes(Matrix &M,int n){
    //Se crean n filas
    for(int i=0;i<n;i++){
        //Se crea una fila de n ceros
        vector<float> row(n,0.0);
        //Se ingresa la fila en la matriz
        M.push_back(row);
    }
}

//La funci�n recibe:
//- Un vector (se asume columna)
//- La dimensi�n del vector
//La funci�n crea un vector nx1 lleno de ceros
void zeroes(Vector &v,int n){
    //Se itera n veces
    for(int i=0;i<n;i++){
        //En cada iteraci�n se agrega un cero al vector
        v.push_back(0.0);
    }
}

//La funci�n recibe:
//- Una matriz
//- Una matriz que ser� la copia de la primera
//La funci�n copiar� todo el contenido de la primera matriz en
//la segunda, respetando las posiciones
void copyMatrix(Matrix A, Matrix &copy){
    //Se inicializa la copia con ceroes
    //asegur�ndose de sus dimensiones
    zeroes(copy,A.size());
    //Se recorre la matriz original
    for(int i=0;i<A.size();i++)
        for(int j=0;j<A.at(0).size();j++)
            //Se coloca la celda actual de la matriz original
            //en la misma posici�n dentro de la copia
            copy.at(i).at(j) = A.at(i).at(j);
}

//La funci�n recibe:
//- Una matriz
//- Un vector
//- Un vector para la respuesta
//La funci�n asume que las dimensiones de la matriz y los vectores son las
//adecuadas para que la multiplicaci�n sea posible
void productMatrixVector(Matrix A, Vector v, Vector &R){
    //Se aplica b�sicamente la formulaci�n que puede
    //consultarse en el siguiente enlace (entrar con cuenta UCA):
    //          https://goo.gl/PEzWWe

    //Se itera una cantidad de veces igual al n�mero de filas de la matriz
    for(int f=0;f<A.size();f++){
        //Se inicia un acumulador
        float cell = 0.0;
        //Se calcula el valor de la celda de acuerdo a la formulaci�n
        for(int c=0;c<v.size();c++){
            cell += A.at(f).at(c)*v.at(c);
        }
        //Se coloca el valor calculado en su celda correspondiente en la respuesta
        R.at(f) += cell;
    }
}

//La funci�n recibe:
//- Un escalar (valor real)
//- Una matriz
//- Una matriz para la respuesta
//La funci�n multiplica cada uno de los elementos de la matriz por el escalar,
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

//La funci�n recibe:
//- Una matriz
//- Un �ndice de fila i
//- Un �ndice de columna j
//La funci�n elimina en la matriz la fila i, y la columna j
void getMinor(Matrix &M,int i, int j){
    //Se elimina la fila i
    M.erase(M.begin()+i); //Uso de begin para obtener un iterator a la posici�n de inter�s
    //Se recorren las filas restantes
    for(int i=0;i<M.size();i++)
        //En cada fila se elimina la columna j
        M.at(i).erase(M.at(i).begin()+j);
}

//La funci�n recibe:
//- Una matriz
//La funci�n calcula el determinante de la matriz de forma recursiva
float determinant(Matrix M){
    //Caso trivial: si la matriz solo tiene una celda, ese valor es el determinante
    if(M.size() == 1) return M.at(0).at(0);
    else{
        //Se implementa la siguiente formulaci�n del siguiente enlace:
        //(Entrar con cuenta UCA)
        //              https://goo.gl/kbWdmu

        //Se inicia un acumulador
        float det=0.0;
        //Se recorre la primera fila
        for(int i=0;i<M.at(0).size();i++){
            //Se obtiene el menor de la posici�n actual
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,0,i);

            //Se calculala contribuci�n de la celda actual al determinante
            //(valor alternante * celda actual * determinante de menor actual)
            det += pow(-1,i)*M.at(0).at(i)*determinant(minor);
        }
        return det;
    }
}

//La funci�n recibe:
//- Una matriz
//- Una matriz que contendr� los cofactores de la primera
void cofactors(Matrix M, Matrix &Cof){
    //La matriz de cofactores se define as�:
    //(Entrar con cuenta UCA)
    //          https://goo.gl/QK7BZo

    //Se prepara la matriz de cofactores para que sea de las mismas
    //dimensiones de la matriz original
    zeroes(Cof,M.size());
    //Se recorre la matriz original
    for(int i=0;i<M.size();i++){
        for(int j=0;j<M.at(0).size();j++){
            //Se obtiene el menor de la posici�n actual
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,i,j);
            //Se calcula el cofactor de la posici�n actual
            //      alternante * determinante del menor de la posici�n actual
            Cof.at(i).at(j) = pow(-1,i+j)*determinant(minor);
        }
    }
}

//La funci�n recibe:
//- Una matriz
//- Una matriz que contendr� a la primera pero transpuesta
//La funci�n transpone la primera matriz y almacena el resultado en la segunda
void transpose(Matrix M, Matrix &T){
    //Se prepara la matriz resultante con las mismas dimensiones
    //de la matriz original
    zeroes(T,M.size());
    //Se recorre la matriz original
    for(int i=0;i<M.size();i++)
        for(int j=0;j<M.at(0).size();j++)
            //La posici�n actual se almacena en la posici�n con �ndices
            //invertidos de la matriz resultante
            T.at(j).at(i) = M.at(i).at(j);
}

//La funci�n recibe:
//- Una matriz
//- Una matriz que contendr� la inversa de la primera matriz
//La matriz calcula la inversa de la primera matriz, y almacena el resultado
//en la segunda
void inverseMatrix(Matrix M, Matrix &Minv){
    //Se utiliza la siguiente f�rmula:
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
    //Se aplica la f�rmula para la matriz inversa
    productRealMatrix(1/det,Adj,Minv);
}
