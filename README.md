# Philosophers 🍝
## Summary
42's version of the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem). This project involves multithreading and concurrent programming using the pthread API, with mutexes used to avoid deadlocks and race conditions. It is also a good exercise in C optimization, as we need to manage CPU usage as efficiently as possible to ensure the survival of our philosophers.

📈 **Final grade: 100/100**

## Rules
The program takes the following parameters: 
```
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>
```

* number_of_philosophers: The number of philosophers (also the number of forks).
* time_to_die: (in milliseconds):  If a philosopher didn’t start eating 'time_to_die' milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
* time_to_eat: (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
* time_to_sleep: (in milliseconds): The time a philosopher will spend sleeping.
* number_of_times_each_philosopher_must_eat: (optional argument): If all philosophers have eaten at least this parametrized times, the simulation stops. If not specified, the simulation stops when a philosopher dies.


