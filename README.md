<div align=center>
    <font size="20">
        <b>SIC</b>
    </font>
</div>
<div align=center>
    <font size=15>
        <b>Simple Interpreter in C++</b>
    </font>
</div>

##### SIC is A simple interpreter implemented in C++
- **Setup**
In the workspace folder
```shell
make
```
The executable can be found at ./bin/SIC
- **Features:**
    - **Dynamic** types
    - **Script** mode & **Calculator** mode
    - Support **while** loop and **if** command
    - Support **functions**
    - Support **comments**
    - Support **variables**
    - Support **()** and **\<SPACE>** in expression calculation 
    - **Error Handling**: indicate where a syntax error or a calculation error occurs.
- **Grammar**:
    - To define or assign a variable, use keyword "**let**" at the beginning of a line.
    - To **define** a function, use keyword "**def**" at the beginning of a line, and add keyword "**enddef**" after the definition.
    - To **define** or **call** a function, demonstrate its parameter/argument list with **[]** instead of ().
    - To use a **while** loop, put the loop condition right after the keyword "**while**" **without** (), and add keyword "**endwhile**" after the loop body to demonstrate that the loop is ended.
    - To use a **if** command, put the condition right after the keyword "**if**" **without** (), and add keyword "**endif**" to demonstrate that the body is ended.
    - To **output** a value of a variable or an instant expression, use keyword "**print**" and put the output content after it.
    - To add a **comment** which will be **ignored** by the interpreter, put character '**#**' at the beginning of a line.
- **Examples**:
[test.sic](test.sic)
```
# variable definition & assignment
let x = 1
let x = x+1

# print
print x * (2+1)
# Output: 6

# while loop
let f_i = 1
let f_i_1 = 1
let i = 2
let n = 40
while i < n
    let f_i = f_i + f_i_1
    let f_i_1 = f_i - f_i_1
    let i = i + 1
    # Fibonacci sequence
endwhile
print f_i
# Output: 102334155

# if
if i == 40
    print 40
    # Output: 40
endif

# function
def Fibonacci[n]
    if n == 1
        return 1
    endif
    if n == 2
        return 1
    endif
    let x = n-1
    let y = n-2
    return Fibonacci[x] + Fibonacci[y]
enddef
print Fibonacci[10]
# Output: 55
```
- **Modes**:
    - **Script** mode:
        - Activated when passed a script file as an argument in the terminal.
        - Exit when the script finishes.
    - **Calculator** mode:
        - Activated when no file is assigned.
        - Receive input from terminal as expression, and print the result instantly.
- **Unsupported yet**:
    - Processing string type
    - Handling expressions as function arguments
