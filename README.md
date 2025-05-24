<div align=center>
    <font size="70">
        <b>SIC</b>
    </font>
</div>
<div align=center>
    <font size=50>
        <b>Simple Interpreter in C++</b>
    </font>
</div>

##### [SIC](https://github.com/wkj2333666/SIC) is a simple interpreter implemented in C++
- **Development platform**: Win11 amd64
- **Setup**:  
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
    - **Operators**:
        - \+ for **add**
        - \- for **subtraction** and **negative mark**
        - \* for **multiplication**
        - /  for **division**
        - // for **integer division** in C++
        - %  for **modulo**
        - ^  for **exponential** operation
        - =  for **assignment**
        - == for **equal** comparison
        - != for **not equal** comparison
        - \> for **greater than** comparison
        - <  for **less than** comparison
        - \>= for **grater than or equal to** comparison
        - <= for **less than or equal to** comparison
    - Arithmetical **priority**:
        Listing **from high to low**:
        - **negative mark**
        - ^ exponential operator
        - \* / // % multiplication relevant operator
        - \+ \- add and subtraction operator
        - == != > < >= <= comparison operator
        - = assignment operator
- **Modes**:
    - **Script** mode:
        - Activated when passed a script file as an argument in the terminal.
        - Exit when the script finishes or a syntax error occurs.
    - **Calculator** mode:
        - Activated when no file is assigned.
        - Receive input from terminal as expression, and print the result instantly.
        - Keep running after catching exceptions.
        - Exit when receive EOF.
```shell
# Script mode:
bin/SIC script_test.sic

# Calculator mode:
bin/SIC
```
- **Examples**:
All test examples can be found in **./test**  
[script_test.sic](test/script_test.sic)
```SIC
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
[calculator_test.in](test/calculator_test.in)
```
1
-2 +3
(1-9)*8
2+6/5
0.1+0.2
5//2
5 % 2
2^3
2^3.3
-1.1^3
1 == 1
1 > 1
1<=1
1 != 1
1+
(2+3
()))20+2
1/0
1//0
-1.1^1.1

hello world
```
[calculator_test.ans](test/calculator_test.ans)
```
1
1
-64
3.200000
0.300000
2
1
8.000000
9.849155
-1.331000
1
0
1
0
Expected digit, got: "", at 2
Lacking right parenthesis
Extra right parenthesis
inf
Divided by 0!
nan

Expected digit, got: "h", at 0
```
- **Unsupported yet**:
    - Processing **string** type.
    - Handling **expressions** as function **arguments**.
    - **Chinese characters**. This also may cause **exception report** to be ineffective in **Calculator** mode.
    - Add **negative mark** to an **expression**
```SIC
# error examples:

print "Hello World!"
# error!

def add[a, b]
    return a+b
enddef

print add[1+1, 1]
# error, but you can do this by:
let x = 1+1
print add[x, 1]

let 变量 = 1
print 变量
# error

print -(1+1)
# error, but you can do this by:
print -1 * (1+1)
```
