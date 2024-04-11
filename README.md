# Fourth Interpreter
Welcome to my fourth interpreter!

## About 

## Installation

## Build Status
<<<<<<< HEAD
[![FORTH](https://github.com/davidludington/Forth/actions/workflows/cmake.yml/badge.svg)]
=======
[![FORTH](https://github.com/davidludington/Forth/actions/main/.github/workflows/cmake.yml/badge.svg)](https://github.com/davidludington/Forth/actions/main/.github/workflows/cmake.yml)
>>>>>>> d9411e2e7ada69ef8915e3f35d5ad937f2c90f07

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

| Operator | Manipulation | Description | 
|----------|----------|----|
| `+`   | `(n1 n2 — (n1 + n2))` | pops the top two values off of the stack and pushes the sum of those valeus  |
| `-`   | `(n1 n2 — (n1 - n2))` | Subtracts the top two numbers on the stack and puts the result on the top of the stack  |
| `*`   | `(n1 n2 — (n1 * n2))` | Multiplies the top two numbers on the stack and puts the result on the top of the stack  |
| `/`   | `(n1 n2 — (n1 / n2))`| Divides the top two numbers on the stack and puts the result on the top of the stack  |

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
| `drop`   | `n n -> n` | Discards the top stack item |
| `swap`   | `n1 n2 -> n2 n1` | Swaps the top two numbers on the stack |
| `over`   | `n1 n2 -> n1 n2 n1` | Duplicates the second number on the stack and puts it on the top |
| `rot`   | `n1 n2 n3 -> n3 n1 n2` | Rotates the top three numbers of the stack |
| `2dup`   | `n n -> n n n n` | Duplicates the top two numbers on the stack |
| `2drop`   | `n n n -> n` | Drops the top two numbers on the stack |
| `2swap`   | `n1 n2 n3 n4 -> n3 n4 n1 n2` | Swaps the top two pairs of numbers on the stack |
| `2over`   | `n1 n2 n3 n4 -> n1 n2 n3 n4 n1 n2` | Duplicates the second pair of numbers on the stack and puts them on the top |
|`/mod`| `( n1 n2 — rem quot )`|Divides; returns remainder and quotient|
|`mod`|`(n1 n2 — rem)`|Divides; returns remainder only|


## Comparisons
| Symbol|Description|
|:---:|:---:|
| `=` | equals; pops top two values off stack, compares, then pushes `1` if they are equal or `0` if they are not equal |
| `<>` | not-equals; pops top two values off stack, compares, then pushes `1` if they are not equal or `0` if they are equal |
|`<`|less than; pops top two values off stack, compares, then pushes `1` if the item second to the top is less than the top item or pushes `0` if the second item to to the top is greater than the top
|`>` |greater than; pops top two values off stack, compares, then pushes `1` if the item second to the top is greater than the top item or pushes `0` if the second item to to the top is less than the top| 
|`<=`|less than; pops top two values off stack, compares, then pushes `1` if the item second to the top is less than or equal the top item or pushes `0` if the second item to to the top is greater than the top
|`>=` |greater than; pops top two values off stack, compares, then pushes `1` if the item second to the top is greater than or equla to the top item or pushes `0` if the second item to to the top is less than the top| 
|`0=`|  equal to zero; pops off top value, compares to zero, then pushes `1` on the stack if the top item equals 0 or it pushes `0` if the top is not equal to 0 | 
|`0<`| less than zero; pops off top value, compares to zero, then pushes `1` on the stack if the top item is less than  0 or it pushes `0` if the top is greater than 0|
|`0>`| greater than zero; pops off top value, compares to zero, then pushes `1` on the stack if the top item is greater than  0 or it pushes `0` if the top is less than 0 |


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
