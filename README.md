# AbstractVM

AbstractVM is a 42 project. You have to do a virtual machine capable of interpreting pseudo-ASM basic.

![Alt text](/ressource/note.png?raw=true "note")


### Installing

Just git clone and run `make`.

```
git clone  https://github.com/jloro/AbstractVM.git
```

And run `./avm or ./avm file`.


## Instructions

The VM can read instructions from 2 different way :
> From the standard input. To do that, execute `./avm`, then write your code. You must end with `;;` to indicate that you have finish writing.

> From a file. Just execute `./avm yourFile`.


- Comments : Comments start with a ’;’ and finish with a newline.

- Push &#120011; : Pushes the value &#120011; at the top of the stack. The value &#120011; must have one ofthe following form:
  - int8(&#120003;): Creates an 8-bit integer with value &#120003;.
  - int16(&#120003;): Creates a 16-bit integer with value &#120003;.
  - int32(&#120003;): Creates a 32-bit integer with value &#120003;.
  - float(&#120015;): Creates a float with value &#120015;.
  - double(&#120015;): Creates a double with value &#120015;.
 
 - Pop : Unstacks the value from the top of the stack.
 
 - Dump : Displays each value of the stack, from the most recent one to the oldest one.
 
 - Assert &#120011; : Asserts that the value at the top of the stack is equal to the one passedas parameter for this instruction. The value &#120011; has the same form that push.
 
 - Add : Unstacks the first two values on the stack, adds them together and stacks the result.
 
 - Sub : Unstacks the first two values on the stack, subtracts them, then stacks the result.
 
 - Mul : Unstacks the first two values on the stack, multiplies them, then stacks the result.
 
 - Div : Unstacks the first two values on the stack, divides them, then stacks the result.
 
 - Mod : nstacks the first two values on the stack, calculates the modulus, thenstacks the result.
 
 - Print : Asserts that the value at the top of the stack is an 8-bit integer then interprets it as an ASCII value and displays the corresponding character on the standard output.
 
 - Exit : Terminate the execution of the current program.
 

### Examples

```
$>./avm
push int32(2)
push int32(3)
add
dump
exit
;;
5
$>
```

```
$>cat FirstExample.avm
; -------------
; exemple.avm -
; -------------

push int32(42)
push int32(33)

add

push float(44.55)

mul

push double(42.42)
push int32(42)

dump

pop

assert double(42.42)

exit
$>./avm FirstExample.avm
42
42.42
3341.25
$>
```

## Authors

* **Jules Loro** - [jloro](https://github.com/jloro)
