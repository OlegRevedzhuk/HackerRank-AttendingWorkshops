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
	//sorting by start date will group all the shops that overlap near each other
	//and allow for faster searching later on
	std::sort(current->workshops.begin(), current->workshops.end(), [](const auto& a, const auto& b) {
		return a.start < b.start; });

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

struct Solution {
	bool isSecondBranching{};
	int currentTime{};
	int classesAttended{};
	bool hasBeenAttended{};
	//bool isValidSchedule{};
	//size_t* bitFlagTracking{};
};

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

int CalculateMaxWorkshops(const Available_Workshops* currentWorkshops) {
	size_t numOfBranches{ static_cast<size_t>(currentWorkshops->n) };
	std::vector<Solution> solution{ {{false, -1, 0, false}, {false, 0, 0, false} } };  //going to use solutions[0] as an escape value since time = -1 is out of range.
	solution.reserve(numOfBranches + 1);

	size_t maxNumberOfShops{};
	while (solution.back().currentTime != -1) {
		if (solution.size() == numOfBranches + 1) {
			++solution.back().classesAttended;
			solution.back().hasBeenAttended = true;

			if (isValid(currentWorkshops, solution) && solution.back().classesAttended > maxNumberOfShops)
				maxNumberOfShops = solution.back().classesAttended;
			else if (solution.back().classesAttended - 1 > maxNumberOfShops)
				maxNumberOfShops = solution.back().classesAttended - 1;

			solution.pop_back();
			continue;
		}
		else if (!solution.back().isSecondBranching) {
			solution.back().isSecondBranching = true;
			solution.push_back({ false, solution.back().currentTime, solution.back().classesAttended, false});
			continue;
		}
		else if (!solution.back().hasBeenAttended) {
			solution.back().hasBeenAttended = true;
			if (!isValid(currentWorkshops, solution)) {
				solution.pop_back();
				continue;
			}
			else {
				//-2 because size is +1 from indexes and sol[0] is garbage.
				solution.push_back({ false, currentWorkshops->workshops[solution.size() - 2].end, solution.back().classesAttended + 1, false });
				continue;
			}
		}
		else
		{
			solution.pop_back();
		}
	}
	return maxNumberOfShops;
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
