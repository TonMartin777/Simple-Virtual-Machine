import sys
import struct

# Translate instructions
OPCODES = {
    "HLT": 0x00, "PUSH": 0x01, "POP": 0x02, "ADD": 0x03, "SUB": 0x04,
    "SETI": 0x05, "JMP": 0x06, "PUSHR": 0x07, "POPR": 0x08, "BZ":  0x09,
    "BNZ": 0x0A, "LOAD": 0x0B, "STORE": 0x0C, "BEQ": 0x0D, "BNE": 0x0E,
    "BGT": 0x0F, "BLT": 0x10, "BGE": 0x11, "BLE": 0x12
}

def assemble(input_file, output_file):
    with open(input_file, 'r') as f:
        raw_lines = f.readlines()

    labels = {}         # Diccionario para guardar "nombre": byte_index
    cleaned_lines = []  # Stores code without comments
    current_byte = 0    # Instruction Pointer counter


    # First pass
    for line_num, line in enumerate(raw_lines, 1):
        # Ignore comments (; this is a comment)
        line = line.split(';')[0].strip()
        if not line:
            continue
        
        # If line ends with :, it's a Label
        if line.endswith(':'):
            label_name = line[:-1]
            labels[label_name] = current_byte
            continue

        cleaned_lines.append((line_num, line))

        # Parsing
        parts = line.split()
        instruction = parts[0].upper()

        if instruction in ["PUSH", "JMP", "BZ", "BNZ", "LOAD", "STORE", "BEQ", "BNE", "BGT", "BLT", "BGE", "BLE"]:
            current_byte += 5 # 1B opcode + 4B int
        elif instruction == "SETI":
            current_byte += 6 # 1B opcode + 1B reg + 4B int
        elif instruction in ["PUSHR", "POPR"]:
            current_byte += 2 # 1B opcode + 1B reg
        else: # 1B opcode
            current_byte += 1

    bytecode = bytearray()

    # Second pass
    for line_num, line in cleaned_lines:
        parts = line.split()
        instruction = parts[0].upper()

        if instruction not in OPCODES:
            print(f"Error in line {line_num}: Unknown Instruction '{instruction}'.")
            sys.exit(1)
        
        bytecode.append(OPCODES[instruction])
        
        try:
            if instruction in ["JMP", "BZ", "BNZ", "BEQ", "BNE", "BGT", "BLT", "BGE", "BLE"]:
                # If argument is a string, search in dictionary
                arg_str = parts[1]
                if arg_str in labels:
                    arg = labels[arg_str]
                else:
                    arg = int(arg_str)
                bytecode.extend(struct.pack('<i', arg))
                
            elif instruction in ["PUSH", "LOAD", "STORE"]:
                arg = int(parts[1])
                bytecode.extend(struct.pack('<i', arg))
                
            elif instruction == "SETI":
                reg = int(parts[1])
                val = int(parts[2])
                bytecode.append(reg)
                bytecode.extend(struct.pack('<i', val))
                
            elif instruction in ["PUSHR", "POPR"]:
                reg = int(parts[1])
                bytecode.append(reg)
        
        except KeyError:
            print(f"Error in line {line_num}: Label '{arg_str}' not defined.")
            sys.exit(1)
        
        except ValueError:
            print(f"Error in line {line_num}: Invalid argument.")
            sys.exit(1)

    # Write Bytes to the file
    with open(output_file, 'wb') as f:
        f.write(bytecode)
        
    print(f"Properly assembled: {output_file}.")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Use: python asm.py <file.asm> <file.bin>")
        sys.exit(1)
        
    assemble(sys.argv[1], sys.argv[2])