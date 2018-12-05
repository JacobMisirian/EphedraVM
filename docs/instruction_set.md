# Ephedra Assembler Instruction Set

Ephedra instructions are 4 bytes in length. An instruction in EASM 
can be represented as follows:

|            28 |         22 |         16 |           0 |
|--------------:|-----------:|-----------:|------------:|
| <instruction> | <operand1> | <operand2> | <immediate> |
|               |            |            |             |
|               |            |            |             |
  
