# Fourt Interpreter
Welcome to my fourth interpreter!

### How to add numbers to the stack
Separate the numbers with a space

```
1 2 3
```
`Output`:
```
1 2 3 <-Top
```
## Operations

| Operator | Description | 
|----------|----------|
| `+`   | Adds the top two numbers on the stack and puts the result on the top of the stack  |
| `-`   | Subtracts the top two numbers on the stack and puts the result on the top of the stack  |
| `*`   | Multiplies the top two numbers on the stack and puts the result on the top of the stack  |
| `/`   | Divides the top two numbers on the stack and puts the result on the top of the stack  |

### Usage
```
1 2 +
```
`Output`:
```
3 <-Top
```

## Stack Manipulation

| Word | Manipulation | Description | 
|----------|----------|----------|
| `dup`   | `n -> n n` | Duplicates the top number on the stack |
| `drop`   | `n n -> n` | Drops the top number on the stack |
| `swap`   | `n1 n2 -> n2 n1` | Swaps the top two numbers on the stack |
| `over`   | `n1 n2 -> n1 n2 n1` | Duplicates the second number on the stack and puts it on the top |
| `rot`   | `n1 n2 n3 -> n3 n1 n2` | Rotates the top three numbers of the stack |
| `2dup`   | `n n -> n n n n` | Duplicates the top two numbers on the stack |
| `2drop`   | `n n n -> n` | Drops the top two numbers on the stack |
| `2swap`   | `n1 n2 n3 n4 -> n3 n4 n1 n2` | Swaps the top two pairs of numbers on the stack |
| `2over`   | `n1 n2 n3 n4 -> n1 n2 n3 n4 n1 n2` | Duplicates the second pair of numbers on the stack and puts them on the top |

### Usage

### Usage
```
1 2 dup
```
`Output`:
```
1 2 2 <-Top
```

# Forth
