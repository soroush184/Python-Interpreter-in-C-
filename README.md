# Python Interpreter in C++

## Overview

This project is a Python-like interpreter implemented in C++. It parses and executes a subset of Python syntax, supporting basic variable management, arithmetic and logical operations, loops, conditional statements, and custom functions. It provides a way to evaluate Python-like code dynamically while implementing the logic and syntax handling in C++.

## Features

- **Python-Like Syntax Support**:
  - Handles Python-style variable assignments, `if-else` statements, `while` loops, and `Print` statements.
  - Evaluates mathematical and logical expressions.

- **Variable Management**:
  - Supports types similar to Python: `Int`, `Double`, and `Str` (Strings).
  - Dynamically stores and rewrites variable values during execution.

- **Expression Parsing**:
  - Converts and evaluates infix mathematical expressions using postfix notation.
  - Evaluates logical expressions with operators like `and`, `or`, `==`, `!=`, `<`, `<=`, `>`, `>=`.

- **Custom Built-In Functions**:
  - `Print`: Outputs variables, expressions, or strings.
  - `Size`: Calculates the size of strings.
  - `Type`: Identifies the type of a variable.
  - `Int` and `Double`: Type casting functions.

- **Control Flow**:
  - Implements `if-else` logic and while loops.
  - Uses a `goto` mechanism to manage loops and block indentation.

## How It Works

1. **Input Parsing**:
   - Accepts Python-like code through standard input.
   - Processes line by line to interpret commands or store them for later evaluation.

2. **Expression Evaluation**:
   - Arithmetic and logical expressions are evaluated using stack-based approaches.
   - Supports variable replacement, type casting, and advanced operations.

3. **Execution Flow**:
   - Loops and conditionals are handled with custom logic to mimic Python’s behavior.
   - Goto-based loop management ensures efficient handling of repeated code blocks.

## File Structure

- **Core Components**:
  - **Expression Evaluation**:
    - `rewrite`: Replaces variables with their values in expressions.
    - `postfix`: Converts infix to postfix expressions.
    - `doMath`: Computes mathematical results from postfix expressions.
    - `solveLogic`: Evaluates logical conditions.
  - **Variable Management**:
    - `variables`: Stores variable names, types, and values.
    - `save`: Parses and stores variable assignments dynamically.
  - **Built-In Functions**:
    - Functions like `toInt`, `toDouble`, `getSize`, and `getType` handle Python-style type casting and introspection.

- **Execution Control**:
  - Implements conditional (`if-else`) and looping (`while`) constructs.
  - Detects and prevents infinite loops.

## Example Input

```python
x = 10
y = 20
if (x < y):
    Print("x is less than y")
else:
    Print("x is greater than or equal to y")
while (x < y):
    Print(x)
    x = x + 2
Print("Done")
#
```

## Example Output

```text
x is less than y
10
12
14
16
18
Done
```

## Getting Started

1. **Compilation**:
   Use a C++ compiler to build the program:
   ```bash
   g++ -o python_interpreter Untitled-2.cpp
   ```

2. **Execution**:
   Run the program:
   ```bash
   ./python_interpreter
   ```

3. **Input**:
   - Enter Python-like code interactively.
   - End the program input with a `#` symbol.

## Limitations

- Only supports a subset of Python syntax and constructs.
- Indentation rules are simulated using underscores (`_`) for block management.

## Future Enhancements

- Extend support for more Python features like lists, dictionaries, and advanced control flow.
- Add error reporting for syntax and runtime errors.
- Support file-based input for larger Python scripts.
