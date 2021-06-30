#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

#include "defns.h"

#define MAX_LEN 512
#define MAX_POS -1
#define MIN_POS -2
#define ALL_YEARS 1000

using namespace std;

int lines_count(ifstream &file) {
	string line;
	int count = 0;
	while (!file.eof()) {
		getline(file, line);
		count++;
	}
	file.seekg(0, ios_base::beg);
	return count;
}

string *split(string s, char c, int max_len) {
	string *arr = new string[max_len];
	int k=0;
	arr[0] = "";
	for (int i=0; i < s.size(); i++) {
		if (s[i] == c) {
			k++;
			arr[k] = "";
		} else {
			arr[k] += s[i];
		}
	}
	return arr;
}

// This function converts a string, that represents certain amount of
// money in USD to an integer value
// Examples: .25K => 250, 10M => 10000000
int convert_toint(string amount) {
	if (amount == "")
		return 0;
	double k = stod(amount);
	char c = amount[amount.size() - 1];
	if (c == 'K')
		return (int)(k * 1000);
	else if (c == 'M')
		return (int)(k * 1000000);
	return (int)k;
}

bool is_corr_location(string s) {
	string table[] = {
		"BF", "BO", "BU", "CA", "CH", "EQ", "GF", "IW", "LS", "MH", "OT", "OU", "PH", "PS", "SC", "TE", "UT", "VE"
	};
	for (int i=0; i < 18; i++) {
		if (table[i] == s)
			return true;
	}
	return false;
}

bool is_corr_event_type(string s) {
	string table[] = {
		"Astronomical Low Tide",
		"Avalanche",
		"Blizzard",
		"Coastal Flood",
		"Cold",
		"Debris Flow",
		"Dense Fog",
		"Dense Smoke",
		"Drought",
		"Dust Devil",
		"Dust Storm",
		"Excessive Heat",
		"Extreme Cold",
		"Wind Chill",
		"Flash Flood",
		"Flood",
		"Frost",
		"Freeze",
		"Funnel Cloud",
		"Freezing Fog",
		"Hail",
		"Heat",
		"Heavy Rain",
		"Heavy Snow",
		"High Surf",
		"High Wind",
		"Hurricane",
		"Typhoon",
		"Ice",
		"Storm ",
		"Lake-Effect",
		"Snow",
		"Lakeshore",
		"Flood",
		"Lightning",
		"Marine Hail",
		"Marine High Wind",
		"Marine Strong Wind",
		"Marine Thunderstorm Wind",
		"Rip Current",
		"Seiche",
		"Sleet",
		"Storm Surge",
		"Tide",
		"Strong Wind",
		"Thunderstorm Wind",
		"Tornado",
		"Tropical Depression",
		"Tropical Storm",
		"Tsunami",
		"Volcanic Ash",
		"Waterspout",
		"Wildfire",
		"Winter Storm",
		"Winter Weather"
	};
	for (int i=0; i < 56; i++) {
		if (table[i] == s)
			return true;
	}
	return false;
}

struct storm_event *read_storms(ifstream &file, int n) {
	struct storm_event *events = new struct storm_event[n];

	string line;
	getline(file, line); // Skip the first line
	for (int i=0; i < n; i++) {
		getline(file, line);
		string *fields = split(line, ',', MAX_LEN);

		int j=0;
		events[i].event_id = convert_toint(fields[j]);
		j++;
		events[i].state = fields[j];
		j++;
		events[i].year = convert_toint(fields[j]);
		j++;
		events[i].month_name = fields[j];
		j++;
		if (is_corr_event_type(fields[j]))
			events[i].event_type = fields[j];
		j++;
		events[i].cz_type = fields[j][0];
		j++;
		events[i].cz_name = fields[j];
		j++;
		events[i].injuries_direct = convert_toint(fields[j]);
		j++;
		events[i].injuries_indirect = convert_toint(fields[j]);
		j++;
		events[i].deaths_direct = convert_toint(fields[j]);
		j++;
		events[i].deaths_indirect = convert_toint(fields[j]);
		j++;
		events[i].damage_property = convert_toint(fields[j]);
		j++;
		events[i].damage_crops = convert_toint(fields[j]);
	}
	return events;
}

struct fatality_event *read_fatalities(ifstream &file, int n) {
	struct fatality_event *fatalities = new struct fatality_event[n];

	string line;
	getline(file, line); // Skip the first line
	for (int i=0; i < n; i++) {
		getline(file, line);
		string *fields = split(line, ',', MAX_LEN);

		int j=0;
		fatalities[i].event_id = convert_toint(fields[j]);
		j++;
		fatalities[i].fatality_type = fields[j][0];
		j++;
		fatalities[i].fatality_date = fields[j];
		j++;
		fatalities[i].fatality_age = convert_toint(fields[j]);
		j++;
		fatalities[i].fatality_sex = fields[j][0];
		j++;
		if (is_corr_location(fields[j]))
			fatalities[i].fatality_location = fields[j];
		j++;
	}
	return fatalities;
}

void print_fields(storm_event *event) {
	if (event->event_id != 0)
		cout << "\t\tEvent Id: " << event->event_id << endl;
	if (event->state != "")
		cout << "\t\tState: " << event->state << endl;
	if (event->year != 0)
		cout << "\t\tYear: " << event->year << endl;
	if (event->month_name != "")
		cout << "\t\tMonth: " << event->month_name << endl;
	if (event->event_type != "")
		cout << "\t\tEvent Type: " << event->event_type << endl;
	if (event->cz_type != '\0')
		cout << "\t\tCounty/Parish/Marine: " << event->cz_type << endl;
	if (event->cz_name != "")
		cout << "\t\tCounty/Parish/Marine Name: " << event->cz_name << endl;
	// if (event->injuries_direct != 0)
		cout << "\t\tInjuries Direct: " << event->injuries_direct << endl;
	// if (event->injuries_indirect != 0)
		cout << "\t\tInjuries Indirect: " << event->injuries_indirect << endl;
	// if (event->deaths_direct != 0)
		cout << "\t\tDeaths Direct: " << event->deaths_direct << endl;
	// if (event->deaths_indirect != 0)
		cout << "\t\tDeaths Indirect: " << event->deaths_indirect << endl;
	// if (event->damage_property != 0)
		cout << "\t\tDamage to Property: $" << event->damage_property << endl;
	// if (event->damage_crops != 0)
		cout << "\t\tDamage to Crops: $" << event->damage_crops << endl;
	cout << endl;
}

void print_fields(fatality_event *event) {
	if (event->fatality_type != '\0')
		cout << "\t\t\tFatality Type: " << event->fatality_type << endl;
	if (event->fatality_date != "")
		cout << "\t\t\tFatality Date: " << event->fatality_date << endl;
	if (event->fatality_age != 0)
		cout << "\t\t\tFatality Age: " << event->fatality_age << endl;
	if (event->fatality_sex != '\0')
		cout << "\t\t\tFatality Sex: " << event->fatality_sex << endl;
	if (event->fatality_location != "" && (int)event->fatality_location[0] != 13)
		cout << "\t\t\tFatality Location: '" << event->fatality_location << "'" << endl;
	cout << endl;
}

int count_storms(annual_storm *storms, int length) {
	int sum = 0;
	for (int i=0; i < length; i++)
		sum += storms[i].no_storms;
	return sum;
}

int count_fatalities(annual_storm *storms, int length) {
	int sum = 0;
	for (int i=0; i < length; i++)
		sum += storms[i].no_fatalities;
	return sum;
}

deaths_and_damages *get_dmgs(annual_storm *storms, enum damage_type dmg_type, int length, int sum) {
	int i, j, k=0;
	struct deaths_and_damages *dmgs = new struct deaths_and_damages[sum];
	for (i=0; i < length; i++) {
		for (j=0; j < storms[i].no_storms; j++) {
			if (dmg_type == property)
				dmgs[k].factor = storms[i].storm_events[j].damage_property;
			else if (dmg_type == crops)
				dmgs[k].factor = storms[i].storm_events[j].damage_crops;
			dmgs[k].year = storms[i].storm_events[j].year;
			dmgs[k].index = j;
			k++;
		}
	}
	return dmgs;
}

deaths_and_damages *get_deaths(annual_storm *storms, int length, int sum) {
	int i, j, k = 0;
	struct deaths_and_damages *deaths_arr = new struct deaths_and_damages[sum];
	for (i=0; i < length; i++) {
		for (j=0; j < storms[i].no_storms; j++) {
			deaths_arr[k].factor = storms[i].storm_events[j].deaths_direct + storms[i].storm_events[j].deaths_indirect;
			deaths_arr[k].year = storms[i].year;
			deaths_arr[k].index = j;
			// cout << "Index: " << j << "Factor: " << deaths_arr[k].factor << endl;
			k++;
		}
	}
	return deaths_arr;
}

storm_event *find_event(deaths_and_damages &object, annual_storm *storms, int length) {
	for (int i=0; i < length; i++) {
		if (storms[i].year == object.year)
			return &storms[i].storm_events[object.index];
	}
	cerr << "Unable to find the event " << object.year << " " << object.index << endl;
	return NULL;
}

void find_fatality_events(deaths_and_damages &object, annual_storm *storms, int length) {
	int last_id = -1;
	for (int i=0; i < length; i++) {
		if (storms[i].year == object.year && last_id != storms[i].storm_events[object.index].event_id) {
			storm_event event = storms[i].storm_events[object.index];
			last_id = event.event_id;
			int found = 0;
			for (int j=0; j < storms[i].no_fatalities; j++) {
				if (storms[i].fatality_events[j].event_id == event.event_id) {
					if (found == 0) {
						found++;
						cout << "\t\tEvent Id: " << event.event_id << endl;
					}
					print_fields(&storms[i].fatality_events[j]);
				}
			}
			return;
		}
	}
	cerr << "Unable to find the event " << object.year << " " << object.index << endl;
}

int compare_factors(deaths_and_damages &obj1, deaths_and_damages &obj2, annual_storm *storms, int length) {
	if (obj1.factor > obj2.factor)
		return 1;
	else if (obj1.factor == obj2.factor) {
		if (obj1.year > obj2.year)
			return 1;
		else if (obj1.year == obj2.year) {
			storm_event *event1 = find_event(obj1, storms, length);
			storm_event *event2 = find_event(obj2, storms, length);
			if (event1->event_id > event2->event_id)
				return 1;
			else
				return -1;
		} else {
			return -1;
		}
	} else {
		return -1;
	}
}

void insertion_sort(deaths_and_damages *arr, int n, annual_storm *storms, int length) {
	int i, j;
	deaths_and_damages key;
	for (i=1; i < n; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && compare_factors(arr[j], key, storms, length) >= 0) {   // The main comp 
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

void merge(deaths_and_damages *arr, int l, int m, int r, annual_storm *storms, int length) {
	int n1 = m - l + 1;
	int n2 = r - m;
	deaths_and_damages *L = new deaths_and_damages[n1], *R = new deaths_and_damages[n2];
 
	int i, j;
	for (i=0; i < n1; i++)
		L[i] = arr[l + i];
	for (j=0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	i=0;
	j=0;
	int k=l;

	while (i < n1 && j < n2) {
		if (compare_factors(L[i], R[j], storms, length) <= 0) {   // The main comp
			arr[k] = L[i];
			i++;
		} else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
 
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void merge_sort(deaths_and_damages *arr, int l, int r, annual_storm *storms, int length) {
	if (l >= r)
		return;
	int m = l + (r - l) / 2;
	merge_sort(arr, l, m, storms, length);
	merge_sort(arr, m+1, r, storms, length);
	merge(arr, l, m, r, storms, length);
}

int find_min_factor(deaths_and_damages *arr, int length) {
	int min = 0;
	for (int i=0; i < length; i++) {
		if (arr[i].factor < min || min == 0)
			min = arr[i].factor;
	}
	return min;
}

int find_max_factor(deaths_and_damages *arr, int length) {
	int max = 0;
	for (int i=0; i < length; i++) {
		if (arr[i].factor > max)
			max = arr[i].factor;
	}
	return max;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		cerr << "Not enough command line arguments" << endl;
		exit(1);
	}

	// Parse the data from given files
	int n = atoi(argv[1]);
	struct annual_storm *storms = new struct annual_storm[n];
	for (int i=0; i < n && (i + 2) < argc; i++) {
		storms[i].year = atoi(argv[i + 2]);
		// cout << "Handling year " << to_string(storms[i].year) << endl;

		ifstream file("Data/details-" + to_string(storms[i].year) + ".csv");
		storms[i].no_storms = lines_count(file) - 1;
		storms[i].storm_events = read_storms(file, storms[i].no_storms);
		file.close();

		file.open("Data/fatalities-" + to_string(storms[i].year) + ".csv");
		storms[i].no_fatalities = lines_count(file) - 1;
		storms[i].fatality_events = read_fatalities(file, storms[i].no_fatalities);
		file.close();
	}

	// Handle the queries
	int q;
	string query, full_query;
	cin >> q;
	for (int i=0; i < q; i++) {
		full_query = "";
		cin >> query;
		full_query += query + " ";
		if (query == "select") {
			cin >> query;
			full_query += query + " ";
			int k, year;
			enum damage_type dmg_type;
			enum sorting_type sorting;
			int qtype = 1; // 
			if (query == "max") {
				k = MAX_POS;
			} else if (query == "min") {
				k = MIN_POS;
			} else {
				k = convert_toint(query); // stoi ?
			}

			cin >> query;
			full_query += query + " ";
			if (query == "all") {
				year = ALL_YEARS;
			} else {
				year = convert_toint(query);
			}

			cin >> query;
			full_query += query + " ";
			if (query == "fatality") {
				qtype = 2;
			} else if (query == "damage_property") {
				dmg_type = property;
			} else if (query == "damage_crops") {
				dmg_type = crops;
			}

			cin >> query;
			full_query += query + " ";
			if (query == "insertion") {
				sorting = insertion;
			} else if (query == "merge") {
				sorting = merge_sorting;
			}

			struct deaths_and_damages *arr;
			int sum;
			sum = count_storms(storms, n);
			// cout << "Getting damages and deaths..." << endl;
			if (qtype == 1) {
				// sum = count_storms(storms, n);
				arr = get_dmgs(storms, dmg_type, n, sum);
				// arr = (deaths_and_damages *)dmgs;
			}
			else if (qtype == 2) {
				// sum = count_fatalities(storms, n);
				arr = get_deaths(storms, n, sum);
				// arr = (deaths_and_damages *)deaths_arr;
			}

			// for (int i=0; i < sum; i++)
			// 	cout << "Index: " << arr[i].index << " Factor: " << arr[i].factor << endl;

			// cout << "DEBUG: sorting stage" << endl;
			if (sorting == insertion)
				insertion_sort(arr, sum, storms, n);
			else if (sorting == merge_sorting)
				merge_sort(arr, 0, sum - 1, storms, n);

			if (k == MAX_POS)
				k = find_max_factor(arr, sum);
			else if (k == MIN_POS)
				k = find_min_factor(arr, sum);
			// Output for the query
			cout << "Query: " << full_query << endl;
			int last_year = 0, last_id = 0, last_index = 0;
			for (int i=0; i < sum; i++) {
				if (arr[i].factor == k && (arr[i].year == year || year == ALL_YEARS)) {
					if (last_year != arr[i].year) {
						cout << "\t" << arr[i].year << endl;
						last_year = arr[i].year;
					}
					if (qtype == 1) {
						storm_event *event = find_event(arr[i], storms, n);
						if (last_id != event->event_id) {
							last_id = event->event_id;
							print_fields(event);
						}
					}
					else if (qtype == 2 && arr[i].index != last_index) {
						last_index = arr[i].index;
						find_fatality_events(arr[i], storms, n);
					}
				}
			}

		}
	}
}