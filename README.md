# COVID-19 Simulation 


<a href='https://github.com/vivibui/COVID-Simulation/blob/main/VivianBui-Simulations(submitted).pdf'><img src='https://img.shields.io/badge/Paper-PDF-red'></a>

Simulation to understand the effect of vaccination in mitigating COVID-19

## Questions 
• How does vaccination help reduce infections when all individuals have the same level of getting
infected? At which vaccination rate will we achieve herd immunity?
• How does vaccination help reduce infections in different vulnerable groups?
• How does vaccination help reduce the death rate in different vulnerable groups? 

## Setup 
The studying population size is 42000 people. There are three statuses a person might possibly have:
susceptible, infected, and recovered. To simplify our study, a recovered person will be inoculated against
the disease. Each simulation starts with patient Zero getting infected. As each day passes by, each
infected person will interact with ten different random people and spread the virus. Once the person gets
infected, it will take them 5 days to recover. The simulation stops when all infected people have
recovered and no further individuals get infected. 


