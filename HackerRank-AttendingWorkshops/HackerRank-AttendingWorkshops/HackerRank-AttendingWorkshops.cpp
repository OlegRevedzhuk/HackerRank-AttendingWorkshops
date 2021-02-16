//#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#include <algorithm>
#include <vector>

struct Workshops {
	int start;
	int duration;
	int end;
};

struct Available_Workshops {
	int n;
	std::vector<Workshops> workshops;
};
//Implement the functions initialize and CalculateMaxWorkshops
Available_Workshops * initialize(int* startTime, int* duration, int n) {
	Available_Workshops * current = new Available_Workshops;
	current->n = n;
	current->workshops.reserve(n);

	for (int i{ 0 }; i < n; ++i) {
		current->workshops.push_back({ startTime[i], duration[i], startTime[i] + duration[i]});
	}
	//sorting by start date will group all the shops that overlap near each other
	//and allow for faster searching later on
	std::sort(current->workshops.begin(), current->workshops.end(), [](const auto& a, const auto& b){
																			return a.start < b.start; });

	return current;
}

//next is the CalculateMaxWorkshops function

int main(int argc, char *argv[]) {
	int n; // number of workshops
	cin >> n;
	// create arrays of unknown size n
	int* start_time = new int[n];
	int* duration = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> start_time[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> duration[i];
	}

	Available_Workshops * ptr;
	ptr = initialize(start_time, duration, n);
	//testing sort
	for (const auto& a : ptr->workshops)
		std::cout << a.start << ' ';
	std::cout << '\n';
	//cout << CalculateMaxWorkshops(ptr) << endl;
	
	//not in original problem, but dynamically allocated should be deleted
	//delete ptr; delete start_time; delete duration;

	return 0;
}
