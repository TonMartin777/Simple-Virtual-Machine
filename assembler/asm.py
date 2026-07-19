import sys
import struct

# Translate instructions
OPCODES = {
    "HLT": 0x00, "PSH": 0x01, "POP": 0x02, "ADD": 0x03, "SUB": 0x04,
    "SET": 0x05, "JMP": 0x06, "GET": 0x07, "STR": 0x08, "BZ":  0x09,
    "BNZ": 0x0A, "LOAD": 0x0B, "STORE": 0x0C
}

def assemble(input_file, output_file):
    with open(input_file, 'r') as f:
        lines = f.readlines()

    bytecode = bytearray() # Byte by byte

    for line_num, line in enumerate(lines, 1):
        # Ignore comments (; this is a comment)
        line = line.split(';')[0].strip()
        if not line:
            continue

        # Parsing
        parts = line.split()
        instruction = parts[0].upper()

        if instruction not in OPCODES:
            print(f"Error in line {line_num}: Unknown instruction '{instruction}'")
            sys.exit(1)

        # Add Opcode Byte
        opcode = OPCODES[instruction]
        bytecode.append(opcode)

        try:
            # OPCODE, arg (4B)
            if instruction in ["PSH", "JMP", "BZ", "BNZ", "LOAD", "STORE"]:
                arg = int(parts[1])
                bytecode.extend(struct.pack('<i', arg))
            

            # OPCODE, reg (1B), val (4B)
            elif instruction == "SET":
                reg = int(parts[1])
                val = int(parts[2])
                bytecode.append(reg)
                bytecode.extend(struct.pack('<i', val))
            
            # OPCODE, reg (1B)
            elif instruction in ["GET", "STR"]:
                reg = int(parts[1])
                bytecode.append(reg)
                            
        except IndexError:
            print(f"Error in line {line_num}: Not enough parameters '{instruction}'.")
            sys.exit(1)
        
        except ValueError:
            print(f"Error in line {line_num}: Invalid argument (must be a number).")
            sys.exit(1)

    # Write Bytes to the file
    with open(output_file, 'wb') as f:
        f.write(bytecode)
        
    print(f"Properly assembled: {output_file}.")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Use: python asm.py <archivo.asm> <archivo.bin>")
        sys.exit(1)
        
    assemble(sys.argv[1], sys.argv[2])