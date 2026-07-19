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

        if instruction in ["PSH", "JMP", "BZ", "BNZ", "LOAD", "STORE"]:
            current_byte += 5 # 1B opcode + 4B int
        elif instruction == "SET":
            current_byte += 6 # 1B opcode + 1B reg + 4B int
        elif instruction in ["GET", "STR"]:
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
            if instruction in ["JMP", "BZ", "BNZ"]:
                # Si el parámetro es un texto (etiqueta), buscamos su byte en el diccionario
                arg_str = parts[1]
                if arg_str in labels:
                    arg = labels[arg_str]
                else:
                    arg = int(arg_str) # Por si seguimos queriendo usar números a mano
                bytecode.extend(struct.pack('<i', arg))
                
            elif instruction in ["PSH", "LOAD", "STORE"]:
                arg = int(parts[1])
                bytecode.extend(struct.pack('<i', arg))
                
            elif instruction == "SET":
                reg = int(parts[1])
                val = int(parts[2])
                bytecode.append(reg)
                bytecode.extend(struct.pack('<i', val))
                
            elif instruction in ["GET", "STR"]:
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
        print("Use: python asm.py <archivo.asm> <archivo.bin>")
        sys.exit(1)
        
    assemble(sys.argv[1], sys.argv[2])