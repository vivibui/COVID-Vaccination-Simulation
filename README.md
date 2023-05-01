# COVID-19 Simulation 


<a href='https://github.com/vivibui/COVID-Simulation/blob/main/VivianBui-Simulations(submitted).pdf'><img src='https://img.shields.io/badge/Paper-PDF-red'></a>

Simulation to understand the effect of vaccination in mitigating COVID-19

## Questions  
• How does vaccination help reduce infections when all individuals have the same level of getting infected? At which vaccination rate will we achieve herd immunity?  
• How does vaccination help reduce infections in different vulnerable groups?  
• How does vaccination help reduce the death rate in different vulnerable groups?  
  
## Setup 
The studying population size is 42000 people. There are three statuses a person might possibly have: susceptible, infected, and recovered. To simplify our study, a recovered person will be inoculated against the disease. Each simulation starts with patient Zero getting infected. As each day passes by, each infected person will interact with ten different random people and spread the virus. Once the person gets infected, it will take them 5 days to recover. The simulation stops when all infected people have recovered and no further individuals get infected.  
  
## Methodology
### First Question 
We introduce a vaccine with a success rate of 90% to the population. We increment the proportion of the population that randomly receives vaccines to see the effect of vaccination in slowing down the infection. A person is classified as “vaccinated” if receives the vaccine. We report the results for five different scenarios where the proportion of the vaccinated population is 0%, 10%, 50%, 75%, and 95%. 
  
### Second Question 
We randomly classify the population into three vulnerable categories: highrisk, medium-risk, and low-risk. Each different risk level coordinates with the chances of how likely a person will be infected. The higher the risk, the more a person is prone to infection. In the simulation, the infected rate is set at 10%, 15%, and 30% for low, medium, and high risk respectively. To simplify the study, all subjects in the population will be divided into the three mentioned groups, with an equal number of people across all vulnerable categories. We report the results for three different scenarios where the proportion of the vaccinated population is 0%, 50%, and 75%.  
  
### Third Question
We introduce the “deceased” status in the next question. The death rate will be varied by vulnerable categories and is set at 5%, 8%, and 12% respectively for low, medium, and high risk. Once an infected person reaches their fifth day of being sick, they will be randomly considered either “recovered” or “deceased” the next day depending on the assigned death rate. Similar to question two, we report the results at 0%, 50%, and 75% vaccination rates. 

