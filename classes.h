//Se crean cuatro enumeraciones que servirán para dar mayor legibilidad al código
enum lines {NOLINE,SINGLELINE,DOUBLELINE};
enum modes {NOMODE,INT_FLOAT,INT_INT_INT};
enum parameters {ELEMENT_LENGTH,THERMAL_CONDUCTIVITY,HEAT_SOURCE};
enum sizes {NODES,ELEMENTS,DIRICHLET,NEUMANN};

//Clase abstracta que representa un objeto en la malla
class item{
    protected:
        int id; //identificador
        float x; //coordenada en X (basta con este dato por estar en 1 dimensión)
        int node1; //identificador de nodo
        int node2; //segundo identificador de nodo
        float value; //valor asociado al objeto
    public:
        //Getters para los atributos
        int getId() {
            return id;
        }

        float getX() {
            return x;
        }

        int getNode1() {
            return node1;
        }

        int getNode2() {
            return node2;
        }

        float getValue() {
            return value;
        }

        //Métodos abstractos para instanciar los atributos de acuerdo a las necesidades

        //Caso en que se utiliza un entero y un real
        virtual void setIntFloat(int n,float r)=0;

        //Caso en que se utilizan tres enteros
        virtual void setIntIntInt(int n1,int n2,int n3)=0;

};

//Clase que representa cada nodo de la malla
class node: public item{

    public:
        //Un nodo usa un entero y un real: su identificador, y su coordenada en X
        void setIntFloat(int identifier, float x_coordinate){
            id = identifier;
            x = x_coordinate;
        }

        void setIntIntInt(int n1,int n2,int n3){
        }

};

//Clase que representa un elemento en la malla
class element: public item{

    public:
        void setIntFloat(int n1,float r){
        }

        //Un elemento usa tres enteros: su identificador, y los identificadores de sus nodos
        void setIntIntInt(int identifier, int firstnode,int secondnode){
            id = identifier;
            node1 = firstnode;
            node2 = secondnode;
        }

};

//Clase que representa una condición impuesta en un nodo de la malla
class condition: public item{

    public:
        //Una condición usa un entero y un real: un identificador de nodo, y un valor a aplicar
        void setIntFloat(int node_to_apply, float prescribed_value){
            node1 = node_to_apply;
            value = prescribed_value;
        }

         void setIntIntInt(int n1,int n2,int n3){
        }

};

//Clase que representa la malla del problema
class mesh{
        float parameters[3]; //Para este caso, los valores de l, k y Q
        int sizes[4]; //La cantidad de nodos, elementos, condiciones de dirichlet y neumann
        node *node_list; //Arreglo de nodos
        element *element_list; //Arreglo de elementos
        condition *dirichlet_list; //Arreglo de condiciones de Dirichlet
        condition *neumann_list; //Arreglo de condiciones de Neumann
    public:
        //Método para instanciar el arreglo de parámetros, almacenando los
        //valores de l, k y Q, en ese orden
        void setParameters(float l,float k,float Q){
            parameters[ELEMENT_LENGTH]=l;
            parameters[THERMAL_CONDUCTIVITY]=k;
            parameters[HEAT_SOURCE]=Q;
        }

        //Método para instanciar el arreglo de cantidades, almacenando la cantidad
        //de nodos, de elementos, y de condiciones (de Dirichlet y de Neumann)
        void setSizes(int nnodes,int neltos,int ndirich,int nneu){
            sizes[NODES] = nnodes;
            sizes[ELEMENTS] = neltos;
            sizes[DIRICHLET] = ndirich;
            sizes[NEUMANN] = nneu;
        }

        //Método para obtener una cantidad en particular
        int getSize(int s){
            return sizes[s];
        }

        //Método para obtener un parámetro en particular
        float getParameter(int p){
            return parameters[p];
        }

        //Método para instanciar los cuatro atributos arreglo, usando
        //las cantidades definidas
        void createData(){
            node_list = new node[sizes[NODES]];
            element_list = new element[sizes[ELEMENTS]];
            dirichlet_list = new condition[sizes[DIRICHLET]];
            neumann_list = new condition[sizes[NEUMANN]];
        }

        //Getters para los atributos arreglo
        node* getNodes(){
            return node_list;
        }
        element* getElements(){
            return element_list;
        }
        condition* getDirichlet(){
            return dirichlet_list;
        }
        condition* getNeumann(){
            return neumann_list;
        }

        //Método para obtener un nodo en particular
        node getNode(int i){
            return node_list[i];
        }

        //Método para obtener un elemento en particular
        element getElement(int i){
            return element_list[i];
        }

        //Método para obtener una condición en particular
        //(ya sea de Dirichlet o de Neumann)
        condition getCondition(int i, int type){
            if(type == DIRICHLET) return dirichlet_list[i];
            else return neumann_list[i];
        }

        //Métodos posiblemente a utilizar en un futuro
        /*void setNode(int i,int n,float r){
            node_list[i].setIntFloat(n,r);
        }*/
        /*void setElement(int i,int id,int n1,int n2){
            element_list[i].setIntIntInt(id,n1,n2);
        }*/
};
