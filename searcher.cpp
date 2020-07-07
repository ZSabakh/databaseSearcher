#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/key_extractors.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
using namespace boost;
#undef foreach
using namespace boost::multi_index;
#define foreach Q_FOREACH

struct Rec {
	std::string name, surname, pid, dob;
	struct ByName {}; struct BySurname {}; struct ByPid {}; struct ByDob {};
};

typedef boost::multi_index_container<Rec,
	indexed_by<
	ordered_non_unique<
	tag<Rec::ByName>, member<Rec, std::string, &Rec::name>
	>,
	ordered_non_unique<
	tag<Rec::BySurname>, member<Rec, std::string, &Rec::surname>
	>,
	ordered_unique<
	tag<Rec::ByPid>, member<Rec, std::string, &Rec::pid>
	>,
	ordered_non_unique<
	tag<Rec::ByDob>, member<Rec, std::string, &Rec::dob>
	>
	>
> Store1;

int main() {

	std::ifstream ip("");
	//Any comma separated value file or any other data file should be specified (data type can be set up below with getline char delimiters.
	if (!ip.is_open()) {
		std::cout << "ERROR" << std::endl;
	}

	std::string fname;
	std::string lname;
	std::string pid;
	std::string dob;
	std::vector<Rec> rec;
	
	while (ip.good()) {		
		getline(ip, fname, ',');
		getline(ip, lname, ',');
		getline(ip, pid, ',');
		getline(ip, dob, ',');
		rec.push_back({fname, lname, pid, dob});
	}


	ip.close();


	Store1 store1; {
		for (int i = 0; i < rec.size(); i++) {
			store1.insert(rec[i]).second;
			store1.insert(rec[i]).second;
		}
	}

	
	std::string find_id;
	std::cout << "Enter name: " << std::flush;
	std::cin >> find_id;
	std::cout << "Enter surname: " << std::flush;
	std::string find_id1;
	std::cin >> find_id1;

	typedef Store1::index<Rec::ByName>::type List;
	typedef Store1::index<Rec::BySurname>::type List1;

	const List& ls = store1.get<Rec::ByName>();
	const List1& ls1 = store1.get<Rec::BySurname>();

	List::const_iterator it = ls.find(find_id);
	List1::const_iterator it1 = ls1.find(find_id1);


	if (it != ls.end() && it1 != ls1.end()) {
		std::cout << "NAME:" << (*it).name << std::endl;
		std::cout << "SURNAME:" << (*it).surname << std::endl;
		std::cout << "DOB:" << (*it).dob << std::endl;
		std::cout << "PID:" << (*it).pid << std::endl;
		std::cout << '\n' << std::endl;
	}
	return 0;


}