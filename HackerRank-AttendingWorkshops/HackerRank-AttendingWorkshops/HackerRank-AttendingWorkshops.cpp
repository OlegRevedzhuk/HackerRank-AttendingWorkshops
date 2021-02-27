//#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#include <algorithm>
#include <cmath>
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
		current->workshops.push_back({ startTime[i], duration[i], startTime[i] + duration[i] });
	}
	//got a hint from discussion to try and sort by end date.
	std::sort(current->workshops.begin(), current->workshops.end(), [](const auto& a, const auto& b) {
		return b.end < a.end; });

	return current;
}

size_t CalculateMaxWorkshops(Available_Workshops* currentWorkshops) {
	auto& shops{ currentWorkshops->workshops };
	size_t lastEnd{ static_cast<size_t>(std::max_element(shops.begin(), shops.end(), [](const auto& a, const auto& b) {
		return a.end < b.end; })->end) };
	size_t maxNumShops{ 0 };
	size_t currentTime{ 0 };

	for (size_t i{ 1 }; i <= lastEnd; ++i) {
		const auto found{ std::find_if(shops.rbegin(), shops.rend(), [=](const auto& a) {
				return a.end == i && a.start >= currentTime; }) };
		if (found != shops.rend()) {
			++maxNumShops;
			currentTime = found->end;
		}
	}
	return maxNumShops;
}

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
	
	cout << CalculateMaxWorkshops(ptr) << endl;

	//not in original problem, but dynamically allocated should be deleted
	delete ptr; delete start_time; delete duration;

	return 0;
}
