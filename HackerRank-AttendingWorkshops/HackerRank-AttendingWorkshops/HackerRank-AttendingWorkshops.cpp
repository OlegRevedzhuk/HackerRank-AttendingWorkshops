//#include <bits/stdc++.h>

using namespace std;

struct Workshops {
	int start;
	int duration;
	int end;
};

struct Available_Workshops {
	static int n;
	Workshops* workshops = new Workshops[n];
};
//Implement the functions initialize and CalculateMaxWorkshops
Available_Workshops* initialize(int* startTime, int* duration, int n) {
	Available_Workshops * current = new Available_Workshops[n];

	for (int i{ 0 }; i < n; ++i) {
		current->workshops[i].start = startTime[i];
		current->workshops[i].duration = duration[i];
		current->workshops[i].end = startTime[i] + duration[i];
	}

	//next need to sort

	return current;
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
	return 0;
}
