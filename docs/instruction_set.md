# Ephedra Assembler Instruction Set

Ephedra instructions are 4 bytes in length. An instruction in EASM 
can be represented as follows:

|            28 |         22 |         16 |           0 |
|--------------:|-----------:|-----------:|------------:|
| ```<instruction>``` | ```<operand1>``` | ```<operand2>``` | ```<immediate>``` |

## Instruction Table

|                                C - Code | Instruction | Operand1 | Operand2 | Immediate |
|----------------------------------------:|-------------|----------|----------|-----------|
| ```r1 = r1 + r2;```                     | add         | r1       | r2       |           |
| ```r1 = r1 + i;```                      | add         | r1       |          | i         |
| ```debug_print(); return 0;```          | hcf         |          |          |           |
| ```goto lbl;```                         | jmp         |          |          | lbl       |
| ```r1 = (uint8_t)*r2;```                | lb          | r1       | r2       |           |
| ```r1 = (uint8_t)*i;```                 | lb          | r1       |          | i         |
| ```r1 = i;```                           | li          | r1       |          | i         |
| ```r1 = (uint16_t)*r2;```               | lw          | r1       | r2       |           |
| ```r1 = (uint16_t)*i;```                | lw          | r1       |          | i         |
| ```r1 = r2;```                          | mov         | r1       | r2       |           |
| ```r1 = *(uint16_t*)SP; SP += 2;```     | pop         | r1       |          |           |
| ```SP -= 2; *((uint16_t*)SP) = r1;```   | push        | r1       |          |           |
| ```*((uint8_t*)r1) = (uint8_t)*r2;```   | sb          | r1       | r2       |           |
| ```*((uint8_t*)r1) = (uint8_t)*i;```    | sb          | r1       |          | i         |
| ```*((uint16_t*)r1) = (uint16_t)*r2;``` | sw          | r1       | r2       |           |
| ```*((uint16_t*)r1) = (uint16_t)*i;```  | sw          | r1       |          | i         |
| ```r1 = r1 - r2;```                     | sub         | r1       | r2       |           |
| ```r1 = r1 - i;```                      | sub         | r1       |          | i         |
