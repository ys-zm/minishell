A simplified version of bash, written together with Francesco Aru (thank you for the collab).
Our shell behaves like the bash (Unix OS X version) as much as possible in the way it parses, executes commands, handles errors, manages environment variables.

---

## Compiling: 

1. `make` creates the executable named "minishell" 

2. `make clean` removes object files
   
3. `make fclean` removes object files and the executable
   
4. `make re` calls `fclean` followed by `all`  

---

## Usage:
```
./minishell
```
