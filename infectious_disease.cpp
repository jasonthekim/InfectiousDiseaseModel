#include <iostream>
#include <string>
#include <random>
using namespace std;

class Person {

private:

	int state = 0;
	int infected = 0;

public:
	Person() {}

	string status_string() {

		if (state == 0) 
			return "susceptible";
		
		if (state == -1) 
			return "recovered";

		if (state == -2) 
			return "not susceptible";
		
		if (state > 0) {
			string sick = "sick (" + to_string(state) + " to go)";
			return sick;
		}

		return "undefined";
	}


	void update() {
		if (infected == 1) {
			state--;
			if (state == 0)
				state = -1;
			if (state == -2)
				state = -1;
		}
		status_string();
	}


	void infect(int n) {
		if (state == 0) {
			state = n;
			infected = 1;
		}
	}

	void vaccinate() {
		state = -2;
	}

	bool is_stable() {

		if (state <= -1) 
			return true;
		else return false;
	}

	int check_state() {
		return state;
	}

};


class Population {
private:

	vector<Person> population;

public:

	Population(int npeople) {
		population.resize(npeople);
	}

	void random_infection() {
		int prone_person = rand() % population.size();
		population[prone_person].infect(5);
	}

	int count_infected() {
		int count = 0;
		for (int i = 0; i < population.size(); i++) {
			if (population[i].check_state() > 0) {
				count++;
			}
		}

		return count;
	}

	void update() {
		for (int i = 0; i < population.size(); i++) {
			population[i].update();
		}
	}

	string display() {

		string str;

		for (int i = 0; i < population.size(); i++) {

			// ? for susceptible
			if (population[i].check_state() == 0) {
				str = str + "? ";
			}
			// + for infected
			if (population[i].check_state() > 0) {
				str = str + "+ ";
			}
			// - for recovered
			if (population[i].check_state() == -1) {
				str = str + "- ";
			}
			// x for vaccinated 
			if (population[i].check_state() == -2) {
				str = str + "x ";
			}
		}
		return str;
	}

	void set_probability_of_transfer(float probability) {

		float contagion_right = (float)rand() / (float)RAND_MAX;

		if (contagion_right < probability) {
			for (int i = population.size() - 1; i > 0; i--) {
				if (population[i].check_state() > 0) {
					if (i != population.size() - 1) {
						if (population[i + 1].check_state() == 0) {
							population[i + 1].infect(5);
						}
					}
				}
			}
		}

		float contagion_left = (float)rand() / (float)RAND_MAX;

		if (contagion_left < probability) {
			for (int i = 0; i < population.size(); i++) {
				if (population[i].check_state() > 0) {
					if (i != 0) {
						if (population[i - 1].check_state() == 0) {
							population[i - 1].infect(5);
						}
					}
				}
			}
		}

	}

	void set_probability_of_vaccination(float vaccprob) {

		int vaxxed_people = vaccprob * population.size();

		for (int i = 0; i < vaxxed_people; i++) {
			int vaccinated_person = rand() % population.size();
			population[vaccinated_person].vaccinate();
		}
	}

	void contagion_of_random_people(float probability) {
		for (int i = 0; i < population.size(); i++) {
			if (population[i].check_state() > 0) {
				for (int j = 0; j < 6; j++) {
					int random_person = rand() % population.size();

					float contagion_chance = (float)rand() / (float)RAND_MAX;

					if (contagion_chance < probability) {
						if (population[random_person].check_state() == 0) {
							population[random_person].infect(5);
						}
					}
				}
			}
		}
	}

};


int main() {

	int pop_size = 30;
	srand(time(0));

	Person joe;

	float transmission_prob = .3;
	float vaccination_prob = .85;

	Population population(pop_size);
	
	int step = 1;
	int day = 1;
	
	for (; ; day++) {

		joe.update();
		float bad_luck = (float)rand() / (float)RAND_MAX;
		if (bad_luck > .95) {
			joe.infect(5);
		}

		if (joe.is_stable()) {
			break;
		}
	}

	population.set_probability_of_vaccination(vaccination_prob);
	population.random_infection();

	cout << "Size of Population:" << endl;
	cout << "In step " << step << " # sick:   " << population.count_infected() << " :  "
		<< population.display() << endl;

	for (step = 2; ; step++) {
		population.update();
		population.contagion_of_random_people(transmission_prob);
		cout << "In step " << step << " # sick:   " << population.count_infected() << " :  "
			<< population.display() << endl;

		if (population.count_infected() == 0) {
			break;
		}
	}

	cout << step;
	return 0;
}
