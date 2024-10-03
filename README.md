# Infectious Disease Simulation

This C++ project simulates the spread of an infectious disease within a population, with a focus on analyzing how different vaccination rates and contagion probabilities affect disease transmission. The model explores herd immunity thresholds and infection dynamics over time.

## Project Overview

The simulation models individual infection, recovery, and vaccination dynamics using two core classes:
- **Person**: Represents an individual, their infection status, and recovery/vaccination state.
- **Population**: Applies the Person class to simulate the spread of disease across an entire population.

The goal is to understand how variables such as contagion rate and vaccination coverage influence disease spread, with particular attention to the impact of herd immunity.

### Key Features
- Simulates individual and population-level infection and recovery.
- Randomized infection spread based on adjustable contagion probabilities.
- Supports vaccination of a percentage of the population.
- Visual display of infection states: infected, recovered, susceptible, or vaccinated.
- Investigates herd immunity by simulating populations with varying vaccination rates.

### How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/InfectiousDiseaseSimulation.git
