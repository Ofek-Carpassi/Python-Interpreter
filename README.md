# 🔧 Python Interpreter

Welcome to the Python Interpreter repository, a code that was written as part of the Magshimim Cyber Program. The interpreter is written in C++ and can interpret a subset of the Python language. The code had five steps:
1. Basic structure.
2. Types.
3. Variables.
4. Lists.
5. Variables manipulation.

I was able to finish 4 - which means you can now create and manipulate variables including lists, call methods on lists, and print their values. The code supports deep copying of variables and nested data structures.
I was able to finish the first three steps in the span of the 4 hours we worked on the project in class and the rest in an hour at home.

## Features

- **Basic Structure**: The interpreter has a basic structure to handle input and output.
- **Types**: Supports basic types such as integers, booleans, strings, and lists.
- **Variables**: Allows creating variables, assigning values to them, and printing their values.
- **Lists**: Supports creating, nesting, and manipulating lists with methods.
- **Methods**: Implement list methods like the append.
- **Deep Copying**: Variables are properly deep-copied to avoid reference issues.

## Usage

To use the interpreter, follow these steps:

1. **Clone the repository**:
    ```sh
    git clone https://github.com/yourusername/python-interpreter.git
    cd python-interpreter
    ```

2. **Open the solution in Visual Studio**:
    Open the `Python Interpreter.sln` file in Visual Studio.

3. **Build the project**:
    Build the project using the `Debug` or `Release` configuration.

4. **Run the interpreter**:
    Run the project. You will see a welcome message and a prompt (`>>>`) where you can enter your commands.

5. **Commands**:
    - **Create a variable**: `x = 5`
    - **Print a variable**: `x`
    - **Reassign a variable**: `x = 10`
    - **Create a list**: `x = [1, 2, "hello", True]`
    - **Append to a list**: `x.append(3)`
    - **Quit the interpreter**: `quit()`

## Example

```sh
Welcome to Magshimim Python Interpreter version 1.0 by Ofek Carpassi
>>> x = 5
>>> x
5
>>> y = "Hello"
>>> y
'Hello'
>>> z = [1, 2, 3]
>>> z
[1, 2, 3]
>>> z.append(4)
>>> z
[1, 2, 3, 4]
>>> quit()
