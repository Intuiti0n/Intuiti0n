# Convert instructions to .hex file and check the outcome

We have to review the instructions, convert to opcodes and generate the .hex file

Note: check website for more info:

http://what-when-how.com/8051-microcontroller/explaining-the-intel-hex-file/

Hex file starts with :10000000 (last 2 zeros might belong to a valid instruction)

:**10**000000 Indicates that this line has 10**H**(HEXADECIMAL) bytes = 16 bytes (max).
<br/>
:10**0000**00 This is **CSEG AT**, which indicates where the **PC** should check the next instruction.
<br/>
:100000**00** If this value is equal to **00** means that there are more lines to read besides this one.
<br/> 
If this value is **01** (check last line of code printscreen img) means this is the last line we have to read.
<br/>

The values **0B**, **B9** and **FF** are checksum values and are used as a way to verify existing error in each line of code. (more info later on)

inserir 2 imagens
![hex example file](./pictures/image.png)
![code example file](./pictures/image.png)

Tasks:
1. Check instruction
2. Instructions can have 0,1,2 or 3 operands
Examples:
NOP
CLR A
MOV A, #03H
CJNE A, #03H, LABEL

So we have to separate the string into its parts.
1st part is the operation
2nd part, if there is one, are the operands.


3. See conversion exerciseVer exercício de conversão 
010H  hexadecimal
010   octal
10    decimal
10B   binary


4. Jumps have offsets, that are variable according to the size of the specific instruction
JZ
JNZ
JB
JNB
JMP
SJMP
AJMP
LJMP
CALL
ACALL

5.String write order:
1ºEscrever ‘:’;
5ºEscrever XX -Tamanho da linha em bytes (hexadecimal), máximo é 10h=16 bytes, 32 dígitos
2ºEscrever EEEE -Endereço do cseg at…(0000h por defeito)
3ºEscrever 00 se não for END a 1ª instrução. Escrever 01 se for na linha do end. (TT)
4ºEscrever opcodes das instruções. Criar contador, máximo de bytes é 16. (counter==16?)
6ºEscrever CC, checksum, resulta de 01h + NOT(02h + 00h + 00h + 04h + FFh + FFh) Soma de 1 com a soma dos bytes em hexa existentes na linha.


Tratamento do ficheiro com as instruções:
Ler o ficheiro. Converter tudo para maiúsculas. (feito)
Ler linha a linha, detetar instruções e converter para opcodes.


