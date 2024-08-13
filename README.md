# Philosophers
## Summary
42's version of the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem). This project involves multithreading and concurrent programming using the pthread API, with mutexes used to avoid deadlocks and race conditions. It is also a good exercise in C optimization, as we need to manage CPU usage as efficiently as possible to ensure the survival of our philosophers.

📈 **Final grade: 100/100**

## 📌 Guidelines
Philosophers sit around a table, with a big plate of spaghetti at its center. Each philosopher represents a thread. 

They each have one fork, however because **two** forks are needed to eat they will need to borrow their neighbor's fork to eat. Of course, if they borrow a neighbor's fork, the neighbor can't use the fork. 

The processes / threads (i.e., individual philosophers) must communicate to know the state of the forks and of the other philosophers at all times. 

Given the right parameters, philosophers keep repeating their cycle virtually forever, unless a maximum number of times each philosopher must eat before the simulation ends is given.

**Program parameters:**

* **number_of_philosophers:** The number of philosophers (also the number of forks).
* **time_to_die** (in milliseconds):  If a philosopher didn’t start eating 'time_to_die' milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
* **time_to_eat** (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
* **time_to_sleep** (in milliseconds): The time a philosopher will spend sleeping.
* **number_of_times_each_philosopher_must_eat** _(optional argument)_: If all philosophers have eaten at least this parametrized times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

## ⚙️ Usage
Clone the repository:
```
git clone git@github.com:mpeterson114/philosophers_42.git
```

Enter into the directory and run the command ```make```. 

Then run the executable with the following parameters (last argument is optional): 
```<number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <[number_of_times_each_philosopher_must_eat]>```


**Example 1** (no philosopher should die and the program should run continuously):
```
./philo 4 410 200 200
```

**Example 2** (1 philosopher should die):
```
./philo 4 310 200 100
```

**Example 3** (no philosopher should die and the program should exit once every philosopher has eaten 7 times):
```
./philo 5 800 200 200 7
```

