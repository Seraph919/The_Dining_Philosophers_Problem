# The Dining Philosophers Problem

A classic synchronization problem in computer science, implemented in C using threads and mutexes.

## 📖 Problem Description

The Dining Philosophers Problem is a classic synchronization problem that illustrates the challenges of resource allocation and deadlock avoidance in concurrent programming. 

### The Scenario

Imagine a group of philosophers sitting at a round table with a bowl of spaghetti in the center. Between each pair of philosophers, there is a single fork. To eat, a philosopher needs two forks (the one on their left and the one on their right). 

The philosophers alternate between three states:
- **Thinking**: The philosopher is thinking and doesn't need any forks
- **Eating**: The philosopher has both forks and is eating
- **Sleeping**: The philosopher is resting after eating

### The Challenge

The challenge is to design a protocol that allows the philosophers to eat without:
1. **Deadlock**: A situation where all philosophers hold one fork and wait forever for the second one
2. **Starvation**: A situation where a philosopher never gets to eat because others always take the forks first

## 🏗️ Project Structure

This repository contains two implementations:

### `philo/` - Mandatory Part (Threads + Mutexes)
Implementation using POSIX threads (`pthread`) and mutexes for synchronization. Each philosopher is represented as a thread, and each fork is protected by a mutex.

### `philo_bonus/` - Bonus Part (Processes + Semaphores)
Implementation using processes and semaphores. Each philosopher runs as a separate process, providing better isolation.

### `printfd/`
Custom printf-like library used for formatted output.

## 🛠️ Compilation

### Compile the Mandatory Version
```bash
cd philo
make
```

### Compile the Bonus Version
```bash
cd philo_bonus
make
```

### Clean Build Files
```bash
make clean   # Remove object files
make fclean  # Remove object files and executables
make re      # Rebuild from scratch
```

## 🚀 Usage

### Command Format
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Description | Constraints |
|----------|-------------|-------------|
| `number_of_philosophers` | Number of philosophers (and forks) | 1-200 |
| `time_to_die` | Time in milliseconds before a philosopher dies if they don't eat | > 60ms |
| `time_to_eat` | Time in milliseconds a philosopher spends eating | > 60ms |
| `time_to_sleep` | Time in milliseconds a philosopher spends sleeping | > 60ms |
| `number_of_times_each_philosopher_must_eat` | (Optional) Simulation stops when all philosophers have eaten at least this many times | > 0 |

**Note**: All time values are in milliseconds and all arguments must be positive integers.

### Output Format

The program outputs state changes in the following format:
```
[timestamp_in_ms] [philosopher_id] [action]
```

Actions include:
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

## 📝 Examples

### Example 1: Basic Simulation
```bash
cd philo
./philo 5 800 200 200
```
- 5 philosophers
- Each philosopher must eat within 800ms or they die
- Eating takes 200ms
- Sleeping takes 200ms
- Runs indefinitely until a philosopher dies

### Example 2: Limited Meals
```bash
cd philo
./philo 4 410 200 200 3
```
- 4 philosophers
- Each philosopher must eat within 410ms or they die
- Eating takes 200ms
- Sleeping takes 200ms
- Simulation stops when all philosophers have eaten 3 times

### Example 3: Tight Timing (Challenging)
```bash
cd philo
./philo 4 310 200 100
```
- Very tight timing where philosophers must eat quickly to avoid dying

### Example 4: Single Philosopher
```bash
cd philo
./philo 1 800 200 200
```
- Special case: A single philosopher with only one fork (cannot eat, will die)

## 🔍 Implementation Details

### Key Features

1. **Data Race Prevention**: All shared data is protected by mutexes
2. **Deadlock Avoidance**: 
   - Even-numbered philosophers start eating slightly delayed
   - Philosophers with odd IDs pick up forks in a different order
3. **Death Monitoring**: A separate monitoring thread checks if any philosopher has died
4. **Precise Timing**: Custom sleep function ensures accurate timing
5. **Thread-Safe Logging**: All output is synchronized to prevent message interleaving

### Synchronization Strategy

- Each fork is protected by a mutex
- Philosophers acquire forks in a specific order to prevent deadlock
- A global mutex protects shared state (death flag, meal counter)
- The monitoring thread periodically checks if any philosopher has exceeded their time to die

### Race Condition Handling

The implementation carefully handles several race conditions:
- Checking and updating the "philosopher died" flag
- Reading and writing the last meal timestamp
- Incrementing meal counters
- Printing state changes

## ⚠️ Common Pitfalls

1. **Data Races**: Accessing shared variables without proper mutex protection
2. **Deadlock**: All philosophers grabbing one fork and waiting for the second
3. **Timing Issues**: Not accounting for the time it takes to grab forks
4. **Death Detection**: Not checking frequently enough if a philosopher should have died

## 🧪 Testing

### Test for No Death (Should run successfully)
```bash
./philo 5 800 200 200 7
```

### Test Death Detection (Should detect death)
```bash
./philo 4 310 200 100
```

### Test with Many Philosophers
```bash
./philo 200 800 200 200
```

## 📚 Resources

To learn more about the Dining Philosophers Problem:
- [Wikipedia - Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- Edsger Dijkstra's original paper on concurrent programming

## 👤 Author

Created as part of the 42 School curriculum by asoudani.

## 📄 License

This project is part of the 42 School curriculum.
