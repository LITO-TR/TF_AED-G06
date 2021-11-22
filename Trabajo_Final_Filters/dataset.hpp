#ifndef DATASET_HPP
#define DATASET_HPP

#include <iostream>
#include <map>

#include "Timer.hpp"
#include "Register.hpp"
#include "utils.hpp"
#include "BlockChain.hpp"
#include "filters.hpp"

class DataSet {

	//blockchain
	BlockChain<std::vector<Register*>> blockchain;

	//filters
	PublisherFilter publisherFilter;
	NameFilter nameFilter;
	StartWithFilter startWithFilter;
	EndWithFilter endWithFilter;
	EqualsToFilter equalsToFilter;
	//timer
	Timer timer;
public:
	DataSet() :startWithFilter("New"),endWithFilter("Activision"),equalsToFilter("Activision")  {
		srand(time(NULL));
	}
	/*DataSet() :endWithFilter("Activision") {
		srand(time(NULL));
	}
	DataSet() :equalsToFilter("Activision") {
		srand(time(NULL));
	}*/

	bool readFromCSV(std::string URL) {
		timer.restart();
		std::cout << "-> Leyendo registros desde " << URL << "\n";

		std::map<std::string, std::vector<Register*>> container;
		timer.start();
		bool response = csvToDataSet(URL, container);
		timer.end();

		std::cout
			<< "-> "
			<< ((response) ? "Registros leidos" : "Error en la lectura de registros")
			<< " en "
			<< timer.count()
			<< "s\n";

		if (response) {

			std::cout << "-> Creando Blockchain " << URL << "\n";
			timer.restart();
			timer.start();
			for (auto& _pair : container) {
				auto block = blockchain.insert(_pair.second);
				auto list = _pair.second;
				for (auto& elementList : list) {
					publisherFilter.insert(elementList, block);
					nameFilter.insert(elementList, block);
					startWithFilter.insert(elementList, block);
					endWithFilter.insert(elementList,block);
					equalsToFilter.insert(elementList,block);
				}
			}
			timer.end();
			std::cout
				<< "-> blockchain creada en "
				<< timer.count()
				<< "s\n";
		}

		return response;
	}

	void igual_a() {
		timer.restart();
		timer.start();
		std::cout << "busqueda inicializada \n";
		auto sws = equalsToFilter.searchAll();
		for(auto& sw: sws){
			std::cout << sw.data << "\n";
		};
		timer.end();
		std::cout
			<< "-> busqueda finalizada en "
			<< timer.count()
			<< "s\n";

	}
	void inicia_con() {
		timer.restart();
		timer.start();
		std::cout << "busqueda inicializada \n";
		auto sws = startWithFilter.searchAll();
		
		
		for(auto& sw: sws){
			std::cout << sw.data << "\n";
		};
		timer.end();
		std::cout
			<< "-> busqueda finalizada en "
			<< timer.count()
			<< "s\n";

	}
	void finaliza_con() {
		timer.restart();
		timer.start();
		std::cout << "busqueda inicializada \n";
		auto sws = endWithFilter.searchAll();
		for(auto& sw: sws){
			std::cout << sw.data << "\n";
		};
		timer.end();
		std::cout
			<< "-> busqueda finalizada en "
			<< timer.count()
			<< "s\n";

	}

};

#endif // !DATASET_HPP