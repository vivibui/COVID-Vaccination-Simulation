// Vivian Bui
// Midterm 
// kb43323

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <iomanip>
#include <bits/stdc++.h>
#include <list> 

using std::cin;
using std::vector;
using std::cout;
using std::endl;
using std::string;

using namespace std;

class Person
{
        private:
            string status = "susceptible";
            int days_sick = 5; 
            int ID; 
	    
	    int CHANCE_INFECTED = 10; 
	    int CHANCE_VACCINE_FAIL = 10;
        public: 
            Person(){}
        
            Person (int PersonID, string currentStatus)
            {
                    srand(time(NULL));
                    int ID = PersonID;
                    string status = currentStatus;
            }

            //------------------GETTERS------------------
            string getStatus() { return status; }
            int getDaySick() { return days_sick; }
            int getId() { return ID; }
            

            //------------------SETTERS------------------
            void setStatus(string newstatus) { status = newstatus; }
            void setID(int newID) { ID = newID; }
            

            //------------------METHODS------------------

            // Get infected 
            void chanceToInfected() 
            {
                    int chance = random()%100;
                    if (chance<CHANCE_INFECTED && getStatus() == "susceptible")
                    {
                        setStatus("infected");
                    }
            }
            
	    // When vaccine does not effective
	    void vaccineNotEffective()
   	    {
		int chance = random()%100;
		if (chance < CHANCE_VACCINE_FAIL && getStatus() == "vaccinated")
		{
			setStatus("susceptible");		
		}
	    }

            // Update status
            void updateStatus() 
            {
                if (getDaySick() == 0)
                {
                    setStatus("recovered");
                }
                if (getStatus() == "infected")
                {
                    days_sick --; 
                }

            }
};


class Population
{
    private:
        vector<Person> persons; 

    public: 
	int max_interaction = 10;
        int population_size = 42000; 
	double  percentage_vaccinated = 0.50;  
	list <int> vaccination_id;
	
        Population()
        {   
            srand(time(NULL));
            string personByID;
            
            
            // Intialize population:
            for (int i = 0; i < population_size; i++)
            {
                personByID = std::to_string(i); 
                
                Person personByID;
                personByID.setID(i);

                // set person Zero to be infected 
                if (i == 0)
                {
                    personByID.setStatus("infected");
                }
                persons.push_back(personByID);
            }

        }


        //------------------GETTERS------------------
        Person &getPerson(int ID) {return persons[ID];} 
        double  getPercentage(){return percentage_vaccinated;}
	int getInteraction(){return max_interaction;}
        
        //------------------METHODS------------------
        // Add person (to be used out of the class)
        void add(Person &person)
        {
            persons.push_back(person); 
        };
        
        
        // Return size of the population (to be used out of the class)
        int size()
        {
            return persons.size();
        };


	// Return size of the population that is vaccinated
	int vaccinated_size() 
	{
	    int vaccinated_size = persons.size()*getPercentage();
	    return vaccinated_size; // exclude patient Zero   
	};
	 	

        // Return number of sick people
        int CountSick()
        {
            int countSick = 0; 
            
            for (auto &p: persons)
            {
                if (p.getStatus() == "infected")
                {
                    countSick ++;
                }
            }
            return countSick; 
        }
		

        // Return number of well people
        int CountWell()
        {
            int countWell = 0; 
            for (auto &p: persons)
            {
                if (p.getStatus() == "susceptible")
                {
                    countWell ++;
                }
            }
            return countWell; 
        }


        // Return number of inoculated  people
        int CountInoculated()
        {
            int countInoculated = 0; 
            for (auto &p: persons)
            {
                if (p.getStatus() == "recovered")
                {
                    countInoculated ++;
                }
            }
            return countInoculated; 
        }

	
	// Return number of vaccinated people
	int CountVaccinated() 
	{
	    int countVaccinated = 0;
	    for (auto &p: persons) 
	    {
		if (p.getStatus() == "vaccinated")
		{
			countVaccinated ++;
		}
	    }
	    return countVaccinated;
	}
	

	// Randomize % received vaccination (apart from patient Zero)  
	void vaccinated()
	{
		// Get random and unique ID   
		while (vaccination_id.size() < vaccinated_size()) 
		{
			int randomID = random()%persons.size(); // random starts from 1 to pop size 
            if (randomID != 0)
            {
			    vaccination_id.push_back(randomID); 
            }
            else { vaccination_id.push_back(1);} // if randomID is Person Zero, set to ID = 1 
			// Sort list 
			vaccination_id.sort();
			// Get only unique value from list 
			vaccination_id.unique();   
		}

		// Base on the ID on vaccination list 
		// set status of people to vaccinated 
		for (auto i : vaccination_id) 
		{
			Person &vaccine_person = getPerson(i);
			vaccine_person.setStatus("vaccinated");
		}
	}        


        // Simulation
        void simulation()
        {
            // Loop through each person in the population to update status
            for (int i = 0; i < persons.size(); i++)
            {   
                Person &each_person = getPerson(i);		
               
                // add interactions per person
                if (each_person.getStatus() == "infected")
                {
                for (int j = 0; j < max_interaction; j++)
                    {   
                        int randomID = random()%persons.size();
                        Person &random_person = getPerson(randomID); 
                        // if the person is vaccinated, see if vaccination fails 
			if (random_person.getStatus() == "vaccinated")
			{
				random_person.vaccineNotEffective();
			}
			// if the vaccines fail, or if the person is not vaccinated
			// see if they will be infected 
			random_person.chanceToInfected();

                    }
                }

                each_person.updateStatus(); 

            }
        }    
};


int main() 
{

    // INITIALIZE 
    srand(time(NULL));
    int day_count = 0; 
    Population population; 
    int max_infected = 0;
    int max_day = 0; 

    // FORMATING 
    const char separator = ' ';
    const int dayWidth = 10; 
    const int allWidth = 25;
    
    cout << left  << setw(dayWidth) << setfill(separator) << "Day";
    cout << left  << setw(allWidth) << setfill(separator) << "Vaccinated";
    cout << left  << setw(allWidth) << setfill(separator) << "Susceptible";
    cout << left  << setw(allWidth) << setfill(separator) << "Infected";
    cout << left  << setw(allWidth) << setfill(separator) << "Recovered" << endl;  

    // VACCINE 
    population.vaccinated();

    // MAIN LOOP 
    while (population.CountSick() > 0) 
    {
        day_count ++; 
	population.simulation(); 
        // Output 
        cout << left << setw(dayWidth) << setfill(separator) << day_count;
        cout << left << setw(allWidth) << setfill(separator) << population.CountVaccinated(); 
	cout << left << setw(allWidth) << setfill(separator) << population.CountWell();
        cout << left << setw(allWidth) << setfill(separator) << population.CountSick();
        cout << left << setw(allWidth) << setfill(separator) << population.CountInoculated() << endl; 
	if (population.CountSick() > max_infected) { max_infected = population.CountSick(); 
	max_day = day_count; }  
   }
    
    // MAIN INFO 
    cout << "--------------------------------" << endl;
    cout << "Total population size: " << population.size() << endl; 
    cout << "Percentage of people received vaccines: " << population.getPercentage() << endl; 
    cout << "Total number of interactions per person: " << population.getInteraction() << endl;
    
    cout << day_count << " " << max_infected << " " << max_day << endl;
    cout << "\n" << endl; 
    
    return 0; 
}

