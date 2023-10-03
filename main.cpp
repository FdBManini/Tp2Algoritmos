#include <iostream>
#include <stdio.h>

using namespace std;

struct Nodo{
    int dni;
    Nodo * sig;
};

void Cargar_archivo(FILE*);
void Procesar_archivo(FILE*,Nodo*[100][7]);
void Emitir_reporte(Nodo* [100][7]);
void IngresarDatos(int &, int &, int &);
void mostrar_Reservasttl(int &);
Nodo * Apilar(Nodo *, int);
void mostrar_lista(Nodo *);
//Formato de guardado:Cod_ciudad + Cod_dia + Nodo
void test(int, int, int);


int main(){
    Nodo * ReservasV[100][7] = {NULL};
    FILE * reservaFile;
    reservaFile = fopen("RESERVAS.DAT","ab+"); //Ab+ para que el write no sobrescriba el archivo

    //Cargar_archivo(reservaFile);
    Procesar_archivo(reservaFile,ReservasV);
    fclose(reservaFile);
    Emitir_reporte(ReservasV);

    return 0;
};

// Funciones principales
void Cargar_archivo(FILE* reservaFile) {
    int Cod_ciudadTemp, Cod_diaTemp,dniTemp;
    int endLoop;

    while (endLoop != -1){
        IngresarDatos(Cod_ciudadTemp,Cod_diaTemp,dniTemp);

        fwrite(&Cod_ciudadTemp,sizeof(Cod_ciudadTemp),1,reservaFile);
        fwrite(&Cod_diaTemp,sizeof(Cod_diaTemp),1,reservaFile);
        fwrite(&dniTemp,sizeof(dniTemp),1,reservaFile);

        cout << "¿Desea continuar ? (-1 para salir)"<< "\n";
        cin >> endLoop;
    };
};

void Procesar_archivo(FILE* reservaFile,Nodo * bReservasV[100][7]) {
    int Cod_ciudadTemp, Cod_diaTemp,dniTemp;
    Nodo * head = NULL;
    while (!feof(reservaFile)){ // lee hasta que llegue al final
        fread(&Cod_ciudadTemp,sizeof(Cod_ciudadTemp),1,reservaFile);
        fread(&Cod_diaTemp,sizeof(Cod_diaTemp),1,reservaFile);
        fread(&dniTemp,sizeof(dniTemp),1,reservaFile);
        //test(Cod_ciudadTemp,Cod_diaTemp,dniTemp);

        head = bReservasV[Cod_ciudadTemp][Cod_diaTemp]; 
        bReservasV[Cod_ciudadTemp][Cod_diaTemp] = Apilar(head,dniTemp);
    };
};

void Emitir_reporte(Nodo * ReservasV[100][7]){
    int cantReservas = 0;
    for (int ciudadId = 0; ciudadId <= 99; ciudadId++){
        cout << "Reserva de la ciudad "<< ciudadId << "-------------------------------------------------------  \n";
        for (int diaId = 0; diaId <= 6; diaId++){
            cout << "-Reserva del dia-"<< diaId << "\n";
                if (ReservasV[ciudadId][diaId] == NULL){
                    cout << "\t No hay reserva" << "\n";
                } else{
                    mostrar_lista(ReservasV[ciudadId][diaId]);
                    cantReservas++;
                };
        };
        mostrar_Reservasttl(cantReservas);
    };
};

//Funciones extras 
Nodo * Apilar(Nodo *head, int dni){
    Nodo * Newnode = new Nodo;
    Newnode->dni = dni;
    
    Newnode->sig = head;
    head = Newnode;
    return head;
};


void IngresarDatos(int &Cod_ciudadTemp, int &Cod_diaTemp,int &dniTemp){  // Le paso los parametros por referencia asi es más corta la otra función
    cout << "Ingrese al codigo de la ciudad (0 al 99)"<< "\n";
    cin >> Cod_ciudadTemp;
    cout << "Ingrese al codigo del dia ? (0 al 6)"<< "\n";
    cin >> Cod_diaTemp;
    cout << "Ingrese el dni"<< "\n";
    cin >> dniTemp;
};

void mostrar_Reservasttl(int &cantReservas){
    cout << "(Cantidad de reservas total = "<< cantReservas << ")"<< endl;
    cantReservas = 0;
};

void mostrar_lista(Nodo *head){// Mustra la lista 
    Nodo *temp = head; // crea un copia de la lista 
    cout << "\t";
    while (temp != NULL){
        cout << " Dni = " << temp->dni;
        temp = temp->sig; // temp = (*temp).sig;  //Va a la siguiente direccion  
    };
    cout << "\n";
};

void test(int Cod_ciudadTemp, int Cod_diaTemp, int dniTemp){ //Para ver los valores leidos
        cout << " Ciudad = "<< Cod_ciudadTemp << "\n";
        cout << " Dia = "<< Cod_diaTemp << "\n";
        cout << " Dni = "<< dniTemp << "\n";
};