#include "dataset.hpp"

int main() {
	DataSet data;
	data.readFromCSV("dataset.csv");
	//data.test();
	//std::cin.get();
	std::cout << "-> presione enter para continuar!!\n";
	std::cin.get();

	bool loop = true;
	while (loop)
	{
		int opcion = 0;

		std::cout << "\n" << "Filtros" << "\n";

		std::cout << "1.- Igual a" << "\n";
		std::cout << "2.- Inicia con" << "\n";
		std::cout << "3.- Finaliza con" << "\n";
  		std::cout <<"4.- Esta contenido en" << "\n";
		std::cout << "5.- No esta contenido en" << "\n";
		

		std::cout << "Seleccione una opcion: "; std::cin >> opcion;

		system("cls");

		switch (opcion)
		{
		case 1:
			data.igual_a();
   
			break;
		case 2:
			data.inicia_con();

			break;
		case 3:
			data.finaliza_con();
			break;
		case 4:
			
			break;
		case 5:
		
			break;
		}

		std::cout << "-> presione enter para continuar!!\n";
		system("pause>0");
		system("cls");

	}
	return 0;
}

