

/////////////////////////////////////////////////
//					       					   //
//	Author: Vivian Bui		       			   //	
//	Project: Covid-19    		       		   //
// 	SDS322 - Fall 2022 		       			   //
//					       					   //
/////////////////////////////////////////////////

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
            string risk; 
		
			int days_sick = 5; 
			int ID; 
		
			int CHANCE_VACCINE_FAIL = 10;

			int CHANCE_INFECTED_LOW = 10;
			int CHANCE_INFECTED_MED = 15;
			int CHANCE_INFECTED_HIGH = 30;  

			int DEATH_LOW = 5; 
			int DEATH_MED = 8;
			int DEATH_HIGH = 12; 

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
            string getRisk() { return risk; } 
	    	int getDaySick() { return days_sick; }
            int getId() { return ID; }
            

            //------------------SETTERS------------------
            void setStatus(string newstatus) { status = newstatus; }
            void setID(int newID) { ID = newID; }
            void setRisk(string newrisk) { risk = newrisk; }     
	
            //------------------METHODS------------------

            // Get infected 
            void chanceToInfected() 
            {
                int chance = random()%100;
                int CHANCE_INFECTED; 

			// Set infection rate based on risk level 
				if (getRisk() == "low")
				{
					CHANCE_INFECTED = CHANCE_INFECTED_LOW; 
				}
				else if (getRisk() == "medium") 
				{
					CHANCE_INFECTED = CHANCE_INFECTED_MED;
				}
				else { CHANCE_INFECTED = CHANCE_INFECTED_HIGH; }        
		
			// Run probability
				if (chance<CHANCE_INFECTED && getStatus() == "susceptible")
						{
							setStatus("infected");
						}
        	}
	
			// Decease Rate 
			void deceaseRate()
			{
				int chance = random()%100;
				int CHANCE_DECEASED;

				// Set decease rate based on risk level
				if (getRisk() == "low") 
				{
					CHANCE_DECEASED = DEATH_LOW; 
				}
				else if (getRisk() == "medium") 
				{
					CHANCE_DECEASED = DEATH_MED;
				}
				else { CHANCE_DECEASED = DEATH_HIGH; }

				// Run probability
				if (chance < CHANCE_DECEASED) 
				{
					setStatus("deceased");
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
				if (getDaySick() == 1)
					{
						deceaseRate();
					}
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
        int population_size = 1200; 
		double  percentage_vaccinated = 0.20;  
	
		list <int> vaccination_id;
		list <int> high_risk;
		list <int> med_risk;    	
	
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

                // set person Zero to be infected and high-risk  
                if (i == 0)
                {
                    personByID.setStatus("infected");
		    		personByID.setRisk("high");
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
			return vaccinated_size;   
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
		
		// Return number of deceased people
		int CountDeceased() 
		{
			int countDeceased = 0; 
			for (auto &p : persons) 
			{
				if (p.getStatus() == "deceased")
				{
					countDeceased ++;
				}
			}
			return countDeceased; 
		}
		
		// Return number of high-risk people 
		int CountHigh() 
		{
			int countHigh = 0;
			for (auto &p : persons) 
			{
			if (p.getRisk() == "high")
			{
				countHigh ++;
			}

			}
			return countHigh; 
		}

	
		// Return number of med-risk people 
		int CountMed()
		{
			int countMed = 0;
			for (auto &p : persons) 
			{
			if (p.getRisk() == "medium")
			{
				countMed ++;
			}
			}
			return countMed; 
		}

	
		// Return number of low-risk people 
		int CountLow() 
		{
			int countLow = 0; 
			for (auto &p : persons)
			{
			if (p.getRisk() == "low")
			{
				countLow ++;
			}
			}
			return countLow; 
		} 
	
	
		// Randomize % received vaccination (apart from patient Zero)  
		void vaccinated()
		{
			// Get random and unique list of ID    
			while (vaccination_id.size() < vaccinated_size())
			{
				int randomID = random()%persons.size();  // exclude patient Zero from vaccination 
				if (randomID != 0) { vaccination_id.push_back(randomID); } 
				else {
					//while (randomID == 0)
					//{
					int randomID = random()%persons.size();
					//}
					vaccination_id.push_back(randomID);
				} 
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
		
		
		// Randomly selected people with High-risk (need to include patient Zero) 
		void high_risk_func() 
		{
			int stop = (persons.size()/3)-1;
			// Get random and unique list of ID 
			while (high_risk.size() < stop) // one third of the pop size & exclude Zero 
			{
				int randomID = random()%persons.size() + 1; 
				high_risk.push_back(randomID);				
				// Sort list 
				high_risk.sort(); 
				// Get only unique value from list 
				high_risk.unique();
					
			}
				
			// Base on the ID in the collected list 
			// set risk status to High 
			for (auto j : high_risk)     
			{
				Person &high_person = getPerson(j);
				high_person.setRisk("high");
			}
							
		}

		
		// Randomly selected people with Medium-risk 
		void med_risk_func() 
		{
			int stop = persons.size()/3;
			// Get random and unique list of ID 
			while (CountMed() < stop)
			{
				int randomID = random()%persons.size();
				med_risk.push_back(randomID);
				// Sort list 
				med_risk.sort();
				// Get only unique value from list 
				med_risk.unique(); 
			

				// Base on the ID in the collected list 
				// set risk status to Medium 
				for (auto i : med_risk) 
				{
					Person &med_person = getPerson(i);
					if (med_person.getRisk() != "high") 
					{
						med_person.setRisk("medium");
					}
				}

				CountMed();
			}
		}


		// Randomly selected people with Low-risk 
		void low_risk_func() 
		{
			for (auto &p : persons) 
			{
				if (p.getRisk() == "") 
				{
					p.setRisk("low"); 	
				}
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


// INITIALIZE FUNCTIONS 
int countInfectedByGroup(string group_name, Population &population); 
int countDeceasedByGroup(string group_name, Population &population);


int main() 
{

    // INITIALIZE 
    srand(time(NULL));
    int day_count = 0; 
    Population population; 

    // SET VULNERABILITY LEVELS 
    population.high_risk_func(); 
    population.med_risk_func();
    population.low_risk_func();

    // INTRODUCTION MESSAGE 
    cout << "\n" << endl; 
    cout << "INTRO MESSAGE" << endl;
    cout << "The total number of high-risk people is: " << population.CountHigh() << endl; 
    cout << "The total number of medium-risk people is: " << population.CountMed() << endl;
    cout << "The total number of low-risk people is: " << population.CountLow() << endl; 
    cout << "Patient Zero vulnerability status is: " << population.getPerson(0).getRisk() << endl;    
    cout << "\n" << endl;

    // FORMATING 
    const char separator = ' ';
    const int dayWidth = 10; 
    const int allWidth = 20;
    
    cout << left  << setw(dayWidth) << setfill(separator) << "Day";
    cout << left  << setw(allWidth) << setfill(separator) << "Vaccinated";
    cout << left  << setw(allWidth) << setfill(separator) << "Susceptible";
    cout << left  << setw(allWidth) << setfill(separator) << "Infected"; 
    cout << left  << setw(allWidth) << setfill(separator) << "Recovered";
    cout << left  << setw(allWidth) << setfill(separator) << "Deceased"; 
    cout << left  << setw(allWidth) << setfill(separator) << "High-risk";
    cout << left  << setw(allWidth) << setfill(separator) << "Medium-risk";
    cout << left  << setw(allWidth) << setfill(separator) << "Low-risk" << endl;   
    
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
        cout << left << setw(allWidth) << setfill(separator) << population.CountInoculated();
		cout << left << setw(allWidth) << setfill(separator) << population.CountDeceased();
		
		// Call function to count infected by group  						 
    	cout << left << setw(allWidth) << setfill(separator) << countInfectedByGroup("high", population);
        cout << left << setw(allWidth) << setfill(separator) << countInfectedByGroup("medium", population);
		cout << left << setw(allWidth) << setfill(separator) << countInfectedByGroup("low", population) << endl; 
    }
    
    // MAIN INFO  
    cout << "\n" << endl;
    cout << "--------------------------------" << endl;
    cout << "Total population size: " << population.size() << endl; 
    cout << "Percentage of people received vaccines: " << population.getPercentage() << endl; 
    cout << "Total number of interactions per person: " << population.getInteraction() << endl;
    cout << "\n" << endl; 
    cout << "Deceased people by group: " << endl;
    cout << "High-risk: " << countDeceasedByGroup("high", population) << endl;
    cout << "Medium-risk: " << countDeceasedByGroup("medium", population) << endl;
    cout << "Low-risk: " << countDeceasedByGroup("low", population) << endl;    
    cout << "\n" << endl; 

    return 0; 
}


// FUNCTION: Count infected people by group 
int countInfectedByGroup(string group_name, Population &population) 
{ 
	int count = 0; 
	for (int i=0; i<population.size(); i++)
	{
		Person &p = population.getPerson(i);
		if (p.getRisk() == group_name && p.getStatus() == "infected")
		{
			count++;
		}
	}
	return count; 
}


// FUNCTION: Count deceased people by group
int countDeceasedByGroup(string group_name, Population &population)
{
	int count = 0; 
	for (int i=0; i<population.size(); i++)
	{
		Person &p = population.getPerson(i);
		if (p.getRisk() == group_name && p.getStatus() == "deceased")
		{
			count++;
		}
	}
	return count;
} 
