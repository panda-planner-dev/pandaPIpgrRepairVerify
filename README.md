
# HTN Prefix Encoding

This repository contains code to solve the following problems by compiling them to HTN planning problems:
* Plan and Goal Recognition (PGR) – i.e., the problem to identify the goal and next steps of an observed agent based on a sequence of actions the agent has executed. In our case, we use HTN models to describe the agents' behavior.
* Plan Repair in the context on HTN planning – i.e., to find a new solution that fulfill certain properties given the execution of the first solution failed.
* Verification of HTN plans – i.e., to decide whether or not a given sequence of actions is a solution for a given HTN planning problem. It needs two files as input.

More technically, the implemented transformation restricts the set of solutions to an HTN planning problem to the subset of solutions that start with a certain prefix (or – in case of partially observable PGR – includes a certain prefix).

The different approaches have been presented in the following publications, which provide a more detailed description of the respective problems and how they are solved. If you use the code, please cite the respective paper:

    @inproceedings{Hoeller22verify,
      author    = {Daniel H{\"{o}}ller and Julia Wichlacz and Pascal Bercher and Gregor Behnke},
      title     = {Compiling {HTN} Plan Verification Problems into {HTN} Planning Problems},
      booktitle = {Proceedings of the 32nd International Conference on Automated Planning and Scheduling (ICAPS)},
      publisher = {{AAAI} Press},
      pages     = {145-150},
      year      = {2022}
    }

    @inproceedings{Hoeller20repair,
      author    = {Daniel H{\"{o}}ller and Pascal Bercher and Gregor Behnke and Susanne Biundo},
      title     = {{HTN} Plan Repair via Model Transformation},
      booktitle = {Proceedings of the 43rd German Conference on Artificial Intelligence (KI)},
      publisher = {Springer},
      pages     = {88--101},
      year      = {2020}
    }

    @inproceedings{Hoeller18pgr,
      author    = {Daniel H{\"{o}}ller and Gregor Behnke and Pascal Bercher and Susanne Biundo},
      title     = {Plan and Goal Recognition as {HTN} Planning},
      booktitle = {Proceedings of the 30th IEEE International Conference on Tools with Artificial Intelligence (ICTAI)},
      publisher = {IEEE Computer Society},
      pages     = {466--473},
      year      = {2018}
    }

The general process is the same for solving all these problems:
* The HTN model needs to be grounded using the PANDA grounder
* You need to provide a second file with the prefix to enforce (i.e., the observed actions of the agent, the plan to repair, or the solution to verify)
* The transformation creates a new problem file using the format used by PANDA to represent its input
* This file must be passed to a planner that supports this format as its input (e.g., a planner from the PANDA framework)

A more detailed description of the command line input is printed when the executable is started without parameters.

So far, the approach has been used by the TOAD system (see [1]).
 1. Daniel Höller. Translating Totally Ordered HTN Planning Problems to Classical Planning Problems Using Regular Approximation of Context-Free Languages. In: Proceedings of the 31st International Conference on Automated Planning and Scheduling (ICAPS). AAAI Press, 2021.