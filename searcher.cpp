
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#undef foreach
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/key_extractors.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
using namespace boost::multi_index;
#define foreach Q_FOREACH
#include <time.h>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
using namespace boost;

struct Rec {
	std::string name, surname, pid, dob;
	struct ByName {}; struct BySurname {}; struct ByPid {}; struct ByDob {}; struct ByKey {};
};

typedef boost::multi_index_container<Rec,
	indexed_by<
	ordered_non_unique<
	tag<Rec::ByName>, member<Rec, std::string, &Rec::name>
	>,
	ordered_non_unique<
	tag<Rec::BySurname>, member<Rec, std::string, &Rec::surname>
	>,
	ordered_non_unique<
	tag<Rec::ByPid>, member<Rec, std::string, &Rec::pid>
	>,
	ordered_non_unique<
	tag<Rec::ByDob>, member<Rec, std::string, &Rec::dob>
	>,
	ordered_non_unique<
	tag<Rec::ByKey>, composite_key<
	Rec,
	member<Rec, std::string, &Rec::name>,
	member<Rec, std::string, &Rec::surname>
	>
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
		getline(ip, pid, ',');
		getline(ip, lname, ',');
		getline(ip, fname, ',');
		getline(ip, dob, ',');
		rec.push_back({fname, lname, pid, dob});
	}
	std::cout << rec.size();

	ip.close();


	Store1 store1; {
		for (int i = 0; i < rec.size(); i++) {
			store1.insert(rec[i]);

		}
	}

	
	std::string find_id;
	std::cout << "\nEnter name: " << std::flush;
	std::cin >> find_id;
	std::cout << "Enter surname: " << std::flush;
	std::string find_id1;
	std::cin >> find_id1;
	clock_t tStart = clock();
	int counter = 0;

	Store1::index<Rec::ByKey>::type::iterator it0, it1;
	tie(it0, it1) = store1.get<Rec::ByKey>().equal_range(make_tuple(find_id, find_id1));
	while (it0 != it1) { 
		std::cout << "Name:" << (*it0).name << std::endl;;
		std::cout << "Surname:" << (*it0).surname << std::endl;;
		std::cout << "DOB:" << (*it0).dob << std::endl;;
		std::cout << "PID:" << (*it0).pid << std::endl;;
		std::cout << "------------------" << std::endl;
		counter++;
		++it0; 
	}
	printf("Amount of entries: %i \n", counter);
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	return 0;


}