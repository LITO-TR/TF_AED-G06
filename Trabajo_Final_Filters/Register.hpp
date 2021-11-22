#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <string>
#include <iostream>

using namespace std;

int myStoi(string _element) {
	try
	{
		return std::stoi(_element);
	}
	catch (const std::exception&)
	{
		return 0;
	}
}

float myStof(string _element) {
	try
	{
		return std::stof(_element);
	}
	catch (const std::exception&)
	{
		return 0;
	}
}

class Register {
	long   rank;
	string name;
	string plataform;
	string year;
	string genre;
	string publisher;
	float NA_sales, EU_sales, JP_sales;
	float Other_sales, Global_sales;

public:
	Register(long rank = 0, string name = "", string plataform = "", string year = "", string genre = "",
		string publisher = "", float NA_sales = 0.0, float EU_sales = 0.0, float JP_sales = 0.0,
		float Other_sales = 0.0, float Global_sales = 0.0)
		:rank(rank), name(name), plataform(plataform), publisher(publisher), year(year), genre(genre),
		NA_sales(NA_sales), EU_sales(EU_sales), JP_sales(JP_sales), Other_sales(Other_sales),
		Global_sales(Global_sales) {}

	~Register() {};

	void operator =(const Register& _other) {
		rank = _other.rank;
		name = _other.name;
		plataform = _other.plataform;
		year = _other.year;
		genre = _other.genre;
		publisher = _other.publisher;
		NA_sales = _other.NA_sales;
		EU_sales = _other.EU_sales;
		JP_sales = _other.JP_sales;
		Other_sales = _other.Other_sales;
		Global_sales = _other.Global_sales;
	}

	bool operator ==(const Register& _other) {
		return this->rank == _other.rank;
	}

	bool operator <(const Register& _other) {
		return this->rank < _other.rank;
	}

	bool operator <=(const Register& _other) {
		return this->rank <= _other.rank;
	}

	bool operator >(const Register& _other) {
		return this->rank > _other.rank;
	}

	bool operator >=(const Register& _other) {
		return this->rank >= _other.rank;
	}

	int operator -(const Register& _other) {
		return this->rank - _other.rank;
	}

	friend ostream& operator<<(ostream& os, const Register& r) {
		os << "rank: " << r.rank << "\n";
		os << "name: " << r.name << "\n";
		os << "plataform: " << r.plataform << "\n";
		os << "year: " << r.year << "\n";
		os << "genre: " << r.genre << "\n";
		os << "publisher: " << r.publisher << "\n";
		os << "NA_sales: " << r.NA_sales << "\n";
		os << "EU_sales: " << r.EU_sales << "\n";
		os << "JP_sales: " << r.JP_sales << "\n";
		os << "Other_sales: " << r.Other_sales << "\n";
		os << "Global_sales: " << r.Global_sales << "\n";
		return os;
	}

	void sRank(string _rank) { rank = myStoi(_rank); }
	void sRank(int _rank) { rank = _rank; }
	void sName(string _name) { name = _name; }
	void sPlatform(string _plataform) { plataform = _plataform; }
	void sYear(string _year) { year = _year; }
	void sGenre(string _genre) { genre = _genre; }
	void sPublisher(string _publisher) { publisher = _publisher; }
	void sNA_sales(string _NA_sales) { NA_sales = myStof(_NA_sales); }
	void sEU_sales(string _EU_sales) { EU_sales = myStof(_EU_sales); }
	void sJP_sales(string _JP_sales) { JP_sales = myStof(_JP_sales); }
	void sOther_sales(string _Other_sales) { Other_sales = myStof(_Other_sales); }
	void sGlobal_sales(string _Global_sales) { Global_sales = myStof(_Global_sales); }

	long& gRank() { return rank; }
	string& gName() { return name; }
	string& gPlatform() { return plataform; }
	string& gYear() { return year; }
	string& gGenre() { return genre; }
	string& gPublisher() { return publisher; }
	float& gNA_sales() { return NA_sales; }
	float& gEU_sales() { return EU_sales; }
	float& gJP_sales() { return JP_sales; }
	float& gOther_sales() { return Other_sales; }
	float& gGlobal_sales() { return Global_sales; }
};

#endif // !REGISTER_HPP