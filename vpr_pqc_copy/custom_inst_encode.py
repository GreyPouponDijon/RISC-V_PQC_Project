#!/usr/bin/env python3

ABI_REGS = {
    "zero": 0, "ra": 1, "sp": 2, "gp": 3, "tp": 4,
    "t0": 5, "t1": 6, "t2": 7,
    "s0": 8, "fp": 8, "s1": 9,
    "a0": 10, "a1": 11, "a2": 12, "a3": 13, "a4": 14, "a5": 15,
    "a6": 16, "a7": 17,
    "s2": 18, "s3": 19, "s4": 20, "s5": 21, "s6": 22, "s7": 23,
    "s8": 24, "s9": 25, "s10": 26, "s11": 27,
    "t3": 28, "t4": 29, "t5": 30, "t6": 31,
}

for i in range(32):
    ABI_REGS[f"x{i}"] = i

RV32E_MAX_REG = 15

OPCODES = {
    "CUSTOM_0": 0x0B,
    "CUSTOM_1": 0x2B,
    "CUSTOM_2": 0x5B,
    "CUSTOM_3": 0x7B,
}

INSTR_DB = {
    "rol64i_l": {
        "opcode": OPCODES["CUSTOM_0"],
        "funct3": 0x4,
        "funct2": 0,
    },
    "rol64i_h": {
        "opcode": OPCODES["CUSTOM_0"],
        "funct3": 0x5,
        "funct2": 1,
    },
    "load64": {
        "opcode": OPCODES["CUSTOM_0"],
        "funct3": 0x5,
    }
}

def parse_reg(reg_name, rv32e=True):
    reg_name = reg_name.strip().lower()
    if reg_name not in ABI_REGS:
        raise ValueError(f"Unknown register: {reg_name}")

    reg = ABI_REGS[reg_name]
    if rv32e and reg > RV32E_MAX_REG:
        raise ValueError(f"Register {reg_name} (x{reg}) is invalid on RV32E")
    return reg

def encode_custom(imm, funct2, rs2, rs1, funct3, rd, opcode):
    if not (0 <= imm <= 0x3F):
        raise ValueError(f"imm out of range for 6 bits: {imm}")
    if not (0 <= funct2 <= 0x1):
        raise ValueError(f"funct2 out of range for 1 bit: {funct2}")
    if not (0 <= rs2 <= 0x1F):
        raise ValueError(f"rs2 out of range: {rs2}")
    if not (0 <= rs1 <= 0x1F):
        raise ValueError(f"rs1 out of range: {rs1}")
    if not (0 <= funct3 <= 0x7):
        raise ValueError(f"funct3 out of range: {funct3}")
    if not (0 <= rd <= 0x1F):
        raise ValueError(f"rd out of range: {rd}")
    if not (0 <= opcode <= 0x7F):
        raise ValueError(f"opcode out of range: {opcode}")

    return (
        ((imm    & 0x3F) << 26) |
        ((funct2 & 0x01) << 25) |
        ((rs2    & 0x1F) << 20) |
        ((rs1    & 0x1F) << 15) |
        ((funct3 & 0x07) << 12) |
        ((rd     & 0x1F) <<  7) |
        ((opcode & 0x7F) <<  0)
    )

def encode_custom_load64(rd1, rd2, rs1, rs2, funct3, opcode, funct2=0):
    if not (0 <= rd1 <= 0x1F):
        raise ValueError(f"rd1 out of range: {rd1}")
    if not (0 <= rd2 <= 0x1F):
        raise ValueError(f"rd2 out of range: {rd2}")
    if not (0 <= rs1 <= 0x1F):
        raise ValueError(f"rs1 out of range: {rs1}")
    if not (0 <= rs2 <= 0x1F):
        raise ValueError(f"rs2 out of range: {rs2}")
    if not (0 <= funct3 <= 0x7):
        raise ValueError(f"funct3 out of range: {funct3}")
    if not (0 <= funct2 <= 0x3):
        raise ValueError(f"funct2 out of range: {funct2}")
    if not (0 <= opcode <= 0x7F):
        raise ValueError(f"opcode out of range: {opcode}")

    return (
        ((rd2    & 0x1F) << 27) |
        ((funct2 & 0x03) << 25) |
        ((rs2    & 0x1F) << 20) |
        ((rs1    & 0x1F) << 15) |
        ((funct3 & 0x07) << 12) |
        ((rd1    & 0x1F) <<  7) |
        ((opcode & 0x7F) <<  0)
    )

def assemble_line(line, rv32e=True):
    line = line.split("#", 1)[0].strip()
    if not line:
        return None

    parts = line.replace(",", " ").split()
    if len(parts) != 5:
        raise ValueError(f"Expected: mnemonic rd, rs1, rs2, imm\nGot: {line}")

    mnemonic = parts[0]

    if mnemonic not in INSTR_DB:
        raise ValueError(f"Unknown mnemonic: {mnemonic}")

    spec = INSTR_DB[mnemonic]

    if mnemonic == "load64":
        if len(parts) != 5:
            raise ValueError(f"Expected: load64 rd1, rd2, rs1, rs2\nGot: {line}")

        _, rd1_s, rd2_s, rs1_s, rs2_s = parts

        rd1 = parse_reg(rd1_s, rv32e=rv32e)
        rd2 = parse_reg(rd2_s, rv32e=rv32e)
        rs1 = parse_reg(rs1_s, rv32e=rv32e)
        rs2 = parse_reg(rs2_s, rv32e=rv32e)

        return encode_custom_load64(
            rd1=rd1,
            rd2=rd2,
            rs1=rs1,
            rs2=rs2,
            funct3=spec["funct3"],
            opcode=spec["opcode"],
            funct2=0,
        )

    else:
        if len(parts) != 5:
            raise ValueError(f"Expected: mnemonic rd, rs1, rs2, imm\nGot: {line}")

        _, rd_s, rs1_s, rs2_s, imm_s = parts

        rd  = parse_reg(rd_s, rv32e=rv32e)
        rs1 = parse_reg(rs1_s, rv32e=rv32e)
        rs2 = parse_reg(rs2_s, rv32e=rv32e)
        imm = int(imm_s, 0)

        return encode_custom(
            imm=imm,
            funct2=spec["funct2"],
            rs2=rs2,
            rs1=rs1,
            funct3=spec["funct3"],
            rd=rd,
            opcode=spec["opcode"],
        )

def main():
    asm = str(input("Insert instruction to encode: "))
    word = assemble_line(asm, rv32e=True)
    print(f"{asm}")
    print(f"0x{word:08x}")
    print(f'.4byte 0x{word:08x}')



if __name__ == "__main__":
    main()
    
