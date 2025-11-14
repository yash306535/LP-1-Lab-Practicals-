# ------------------------------------------
# Macro Processor Simulation (Pass 1 & Pass 2)
# ------------------------------------------

# Macro Definition Table (MDT)
macro_definition_table = {}

# Macro Name Table (MNT)
macro_name_table = {}

# ------------------------------------------
# PASS 1: Macro Definition Processing
# ------------------------------------------
def process_pass1(source_code):
    """
    Processes source code to build MNT and MDT.
    """
    mdt_index = 0
    macro_definition = []
    current_macro_name = None
    inside_macro = False

    for line in source_code:
        tokens = line.strip().split()

        if not tokens:
            continue

        # Start of macro definition
        if tokens[0] == 'MACRO':
            inside_macro = True
            continue

        # End of macro definition
        if inside_macro and tokens[0] == 'MEND':
            inside_macro = False
            # Store the macro in tables
            macro_definition_table[current_macro_name] = macro_definition[:]
            macro_name_table[current_macro_name] = mdt_index
            mdt_index += len(macro_definition)
            # Reset for next macro
            macro_definition = []
            current_macro_name = None
            continue

        # Inside a macro definition
        if inside_macro:
            # The first line after MACRO is the macro name + parameters
            if not current_macro_name:
                current_macro_name = tokens[0]
            # Add line to macro definition
            macro_definition.append(line.strip())


# ------------------------------------------
# PASS 2: Macro Expansion
# ------------------------------------------
def process_pass2(source_code):
    """
    Expands macros using the MNT and MDT built in Pass 1.
    """
    output = []
    inside_macro = False

    for line in source_code:
        tokens = line.strip().split()

        # Skip empty lines or macro definition lines
        if not tokens or tokens[0] == 'MACRO':
            inside_macro = True
            continue
        elif tokens[0] == 'MEND':
            inside_macro = False
            continue

        if inside_macro:
            continue

        macro_name = tokens[0]

        # If line contains a macro invocation
        if macro_name in macro_name_table:
            args = tokens[1:]
            macro_def = macro_definition_table[macro_name]

            # Expand macro
            for expanded_line in macro_def:
                temp_line = expanded_line
                for i, arg in enumerate(args):
                    temp_line = temp_line.replace(f"&ARG{i+1}", arg)
                output.append(temp_line)
        else:
            # Regular assembly instruction
            output.append(line.strip())

    return output


# ------------------------------------------
# DISPLAY TABLES
# ------------------------------------------
def display():
    print("\n===== PASS 1 OUTPUT =====")
    print("\nMacro Name Table (MNT):")
    for name, index in macro_name_table.items():
        print(f"  Macro Name: {name} | MDT Index: {index}")

    print("\nMacro Definition Table (MDT):")
    for name, definition in macro_definition_table.items():
        print(f"  Macro: {name}")
        for line in definition:
            print(f"    {line}")
    print("-----------------------------")


# ------------------------------------------
# MAIN PROGRAM
# ------------------------------------------
if __name__ == "__main__":
    # Input source code
    source_code = [
        "MACRO",
        "INCR &ARG1",
        "ADD &ARG1, ONE",
        "MEND",
        "MACRO",
        "DECR &ARG1",
        "SUB &ARG1, ONE",
        "MEND",
        "START",
        "INCR A",
        "DECR B",
        "END"
    ]

    # Pass 1: Build tables
    process_pass1(source_code)

    # Display MNT and MDT
    display()

    # Pass 2: Expand macros
    print("\n===== PASS 2 OUTPUT =====")
    expanded_code = process_pass2(source_code)
    for line in expanded_code:
        print(line)
