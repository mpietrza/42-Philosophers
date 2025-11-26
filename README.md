# 42 Philosophers 🍝🧠

> Summary: A concurrency exercise implementing the classic "Dining Philosophers" problem in C. The project simulates philosophers who think, eat, and sleep while sharing forks (resources). The focus is on correct synchronization, timing, and graceful shutdown under different constraints.

---

## 📊 Repo Info
- Repository: mpietrza/42-Philosophers
- Primary languages: C (≈93.6%), Makefile (≈6.4%)
- Implementation located in the philo/ directory.

---

## 🏁 Project Goal
Simulate N philosophers around a table. Each philosopher repeatedly:
- Thinks
- Picks up two forks (one at a time)
- Eats for a specified time
- Puts down forks
- Sleeps for a specified time

Program must prevent deadlocks, correctly detect philosopher death (if starving longer than time_to_die), and print all actions with correct timestamps.

---

## ⚙️ Features
| Category            | Description |
|---------------------|-------------|
| Concurrency Model   | POSIX threads (pthread) — one thread per philosopher |
| Synchronization     | Mutexes to protect forks and printing |
| Timing Accuracy     | usleep / gettimeofday for timestamps |
| Graceful Shutdown   | Detect death and stop the simulation cleanly |
| Bonus (optional)    | Process-based implementation using semaphores and signals |

---

## 🔧 Build
```bash
cd philo
make          # Build the project (Makefile is in philo/)
make clean    # Remove object files
make fclean   # Remove object files and executables
make re       # Rebuild everything
```

The Makefile in philo/ should produce an executable (commonly named `philo`).

---

## 📂 Structure (actual files in philo/)
```
philo/
├── .vscode/
├── Makefile
├── actions.c
├── actions_eat.c
├── arg_check.c
├── atoi_secured.c
├── free_exit.c
├── init.c
├── monitoring.c
├── mtx_getters.c
├── mtx_setters.c
├── parse.c
├── philo.c
├── philo.h
├── routine.c
├── threads.c
├── utils.c
├── utils_itoa.c
└── utils_time.c
```

Key files:
- philo.h — shared types, structs, and prototypes
- philo.c / routine.c / threads.c — main simulation and thread handling
- actions*.c — eating/acting routines
- monitoring.c — death/monitor logic
- Makefile — build rules

---

## 🚀 Usage
```bash
# From repository root:
cd philo
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

# Example:
./philo 5 800 200 200 7
```

Arguments:
- number_of_philosophers: integer > 0
- time_to_die (ms): time before a philosopher dies if they don't start eating
- time_to_eat (ms)
- time_to_sleep (ms)
- number_of_times_each_philosopher_must_eat (optional): simulation ends when this is reached for all philosophers

Behavior expectations:
- Each action prints a timestamp (ms since start) and philosopher id.
- Printing is synchronized to avoid garbled output.
- Simulation stops immediately after a philosopher dies or when the optional eat-count goal is reached.

---

## 🧪 Testing & Debugging Tips
- Test small N first (2–5) before increasing.
- Use extreme timing values to test edge cases (very small time_to_die).
- Inspect logs and timestamps to verify timing behavior.
- Check for race conditions and resource leaks (valgrind / sanitizers).
- If implementing bonus (process) version, verify semaphore cleanup and signal handling.

---

## 🛠️ Error Handling
- Validate number and format of arguments; print usage on invalid input.
- Handle allocation failures with appropriate exits.
- Ensure mutexes are destroyed and threads joined before exit.
- Monitor loop should detect death and stop other threads reliably.

---

## 📌 Learning Outcomes
- Practical experience with threads and synchronization primitives.
- Understanding deadlocks, starvation, and strategies to avoid them.
- Timing-sensitive programming and coordinated shutdown of concurrent systems.
- Exposure to both thread- and process-based concurrency patterns (if bonus implemented).
