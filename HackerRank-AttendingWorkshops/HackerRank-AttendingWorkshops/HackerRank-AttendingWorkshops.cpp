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
		return a.end < b.end; });

	return current;
}

/*
int calculateClassesAttended(size_t bitFlagsForSolution) {
	unsigned int count = 0;
	while (bitFlagsForSolution) {
		count += bitFlagsForSolution & 1;
		bitFlagsForSolution >>= 1;
	}
	return count;
}
*/
/*
struct Solution {
	bool isSecondBranching{};
	int currentTime{};
	int classesAttended{};
	bool hasBeenAttended{};
	//bool isValidSchedule{};
	//size_t* bitFlagTracking{};
};
*/
/*
bool isValid(const Available_Workshops* currentWorkshops, const std::vector<Solution> &solution) {
	int currentTime{ 0 };
	for (size_t i{ 1 }; i < solution.size(); ++i) {
		if (!solution[i].hasBeenAttended)
			continue;
		else if (currentWorkshops->workshops[i - 1].start < currentTime) {
			return false;
		}
		else {
			currentTime = currentWorkshops->workshops[i - 1].end;
		}
	}
	return true;
}
*/

size_t CalculateMaxWorkshops(const Available_Workshops* currentWorkshops) {
	size_t lastEnd{ static_cast<size_t>(std::max_element(currentWorkshops->workshops.begin(), currentWorkshops->workshops.end(), [](const auto& a, const auto& b) {
		return a.end < b.end; })->end) };
	size_t currentTime{ 0 };
	size_t maxNumShops{ 0 };

	for (size_t i{ 1 }; i <= lastEnd; ++i) {
		for (int j{ 1 }; j <= i - currentTime; ++j) {
			const auto found{ std::find_if(currentWorkshops->workshops.begin(), currentWorkshops->workshops.end(), [=](const auto& a) {
				return a.end == i && a.duration == j; }) };
			if (found != currentWorkshops->workshops.end()) {
				currentTime = found->end;
				++maxNumShops;
				break;
			}
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
	/* testing sort

	for (const auto& a : ptr->workshops)
		std::cout << a.start << ' ';
	std::cout << '\n';
	*/
	cout << CalculateMaxWorkshops(ptr) << endl;

	//not in original problem, but dynamically allocated should be deleted
	//delete ptr; delete start_time; delete duration;

	return 0;
}
