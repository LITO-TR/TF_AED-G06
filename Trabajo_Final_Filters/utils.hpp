#ifndef UTILS_HPP
#define UTILS_HPP
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "BlockChain.hpp"

static bool csvToDataSet(std::string _URL, std::map<std::string, std::vector<Register*>>& _container) {

	std::ifstream archive(_URL);
	std::string regToDifferentGetLine = ",";
	regToDifferentGetLine.push_back('"');
	if (archive.is_open()) {
		std::string titlesLine, valuesLine;
		std::getline(archive, titlesLine);
		std::string title;
		std::stringstream titleStream(titlesLine);
		std::vector<std::string> titles;
		while (std::getline(titleStream, title, ',')) titles.push_back(title);
		int indx = 0;
		while (std::getline(archive, valuesLine)) {
			std::string aux;
			bool extendWord = false;
			std::string word;
			std::stringstream stream(valuesLine);
			int titleIndx = 0;
			Register* nReg = new Register();
			while (std::getline(stream, word, ','))
			{
				if (!extendWord && word.front() == '"') {
					extendWord = true;
					aux = word;
					continue;
				}
				else if (extendWord) {
					aux += word;
					if (word.back() == '"') {
						extendWord = false;
						aux = "";
					}
					else {
						continue;
					}
				}
				switch (titleIndx++)
				{
				case 0:
					nReg->sRank(word);
					break;
				case 1:
					nReg->sName(word);
					break;
				case 2:
					nReg->sPlatform(word);
					break;
				case 3:
				{
					if (_container.count(word) == 0)
					{
						_container.insert(std::make_pair(word, std::vector<Register*>()));
					}
					nReg->sYear(word);
				}
				break;
				case 4:
					nReg->sGenre(word);
					break;
				case 5:
					nReg->sPublisher(word);
					break;
				case 6:
					nReg->sNA_sales(word);
					break;
				case 7:
					nReg->sEU_sales(word);
					break;
				case 8:
					nReg->sJP_sales(word);
					break;
				case 9:
					nReg->sOther_sales(word);
					break;
				case 10:
					nReg->sGlobal_sales(word);
					break;

				default:
					break;
				}
			}
			_container[nReg->gYear()].push_back(nReg);
		}

		archive.close();
		return true;
	}
	return false;

}

#endif // !UTILS_HPP