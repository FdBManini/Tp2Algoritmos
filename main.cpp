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

void menu(FILE*,Nodo*[100][7]);
void IngresarDatos(int &, int &, int &);
void mostrar_Reservasttl(int &);
Nodo * Apilar(Nodo *, int);
void mostrar_lista(Nodo *,int &);
void test(int, int, int);


int main(){
    Nodo * ReservasV[100][7] = {NULL};
    FILE * reservaFile;
    reservaFile = fopen("RESERVAS.DAT","ab+"); //Ab+ para que el write no sobrescriba el archivo

    menu(reservaFile,ReservasV);
    fclose(reservaFile);
    return 0;
};

// Funciones principales
void Cargar_archivo(FILE* reservaFile) { //Escribe el archivo (Formato de guardado:Cod_ciudad + Cod_dia + Nodo)
    int Cod_ciudadTemp, Cod_diaTemp,dniTemp;
    int endLoop;

    while (endLoop != 0){
        IngresarDatos(Cod_ciudadTemp,Cod_diaTemp,dniTemp);

        fwrite(&Cod_ciudadTemp,sizeof(Cod_ciudadTemp),1,reservaFile);
        fwrite(&Cod_diaTemp,sizeof(Cod_diaTemp),1,reservaFile);
        fwrite(&dniTemp,sizeof(dniTemp),1,reservaFile);

        cout << "¿Desea continuar ? (0 para salir)"<< "\n";
        cin >> endLoop;
    };
};

void Procesar_archivo(FILE* reservaFile,Nodo * bReservasV[100][7]) {
    int Cod_ciudadTemp, Cod_diaTemp,dniTemp;
    Nodo * head = NULL;
    fseek(reservaFile,0, SEEK_SET);
    while (!feof(reservaFile)){ // lee hasta que llegue al final
        fread(&Cod_ciudadTemp,sizeof(Cod_ciudadTemp),1,reservaFile);
        fread(&Cod_diaTemp,sizeof(Cod_diaTemp),1,reservaFile);
        fread(&dniTemp,sizeof(dniTemp),1,reservaFile);
        test(Cod_ciudadTemp,Cod_diaTemp,dniTemp); // Muesta las variables que leyó

        head = bReservasV[Cod_ciudadTemp][Cod_diaTemp];
        bReservasV[Cod_ciudadTemp][Cod_diaTemp] = Apilar(head,dniTemp);
    };
};

void Emitir_reporte(Nodo * ReservasV[100][7]){ // Emite el reporte de la matriz
    int cantReservas = 0;
    for (int ciudadId = 0; ciudadId <= 99; ciudadId++){
        cout << "Reserva de la ciudad "<< ciudadId << "-------------------------------------------------------  \n";
        for (int diaId = 0; diaId <= 6; diaId++){
            cout << "-Reserva del dia-"<< diaId << "\n";
                if (ReservasV[ciudadId][diaId] == NULL){
                    cout << "\t No hay reservas" << "\n";
                } else{
                    mostrar_lista(ReservasV[ciudadId][diaId],cantReservas);
                };
        };
        mostrar_Reservasttl(cantReservas);
    };
};

void menu(FILE* reservaFile,Nodo * ReservasV[100][7]){
    int endLoop;
    while (endLoop != 0){
        cout << "\n¿Que desea hacer ?"<< "\n";
        cout << "1) Cargar datos "<< "\n";
        cout << "2) Procesar archivo "<< "\n";
        cout << "3) Emitir reporte"<< "\n";
        cout << "0) Salir"<< "\n";
        cin >> endLoop;

        switch (endLoop){
            case 1:
                    Cargar_archivo(reservaFile);
                break;
            case 2:
                    Procesar_archivo(reservaFile,ReservasV);
                break;
            case 3:
                    Procesar_archivo(reservaFile,ReservasV); // sino lo pongo acá tambien, va a estar null la matriz
                    Emitir_reporte(ReservasV);
                break;
            case 0: cout << "Se ha seleccionado salir"<< "\n"; break;
            default: cout << "No se ha seleccionado ninguno otro"<< "\n";break;
        };
    }
    
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

void mostrar_Reservasttl(int &cantReservas){ // Muesta la cantidad total de la lista
    cout << "(Cantidad de reservas total = "<< cantReservas << ")"<< endl;
    cantReservas = 0;
};

void mostrar_lista(Nodo *head, int &cantReservas ){// Mustra la lista 
    Nodo *temp = head; // crea un copia de la lista para recorrerla 
    cout << "\t";
    while (temp != NULL){
        cout << " Dni = " << temp->dni;
        temp = temp->sig;  //Va a la siguiente direccion 
        cantReservas++;
    };
    cout << "\n";
};

void test(int Cod_ciudadTemp, int Cod_diaTemp, int dniTemp){ //Para ver los valores leidos 
        cout << " Ciudad = "<< Cod_ciudadTemp << " ";
        cout << " Dia = "<< Cod_diaTemp << " ";
        cout << " Dni = "<< dniTemp << " ";
        cout << "\n";
};