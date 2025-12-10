.section .text

# RV32I Arithmetic Operations (19 commands)
.global addi_example
addi_example:
    addi a0, a0, 10       # Add immediate 10 to a0 and store result in a0
    ret

.global slti_example
slti_example:
    slti a0, a0, 5        # Set a0 to 1 if a0 < 5, else 0
    ret

.global sltiu_example
sltiu_example:
    sltiu a0, a0, 5       # Unsigned comparison: Set a0 to 1 if a0 < 5, else 0
    ret

.global andi_example
andi_example:
    andi a0, a0, 0xFF     # Perform bitwise AND of a0 and 0xFF, store in a0
    ret

.global ori_example
ori_example:
    ori a0, a0, 0x1       # Perform bitwise OR of a0 and 0x1, store in a0
    ret

.global xori_example
xori_example:
    xori a0, a0, 0x7FF    # Perform bitwise XOR of a0 and 0x7FF, store in a0
    ret

.global slli_example
slli_example:
    slli a0, a0, 3        # Shift a0 left by 3 bits, store in a0
    ret

.global srli_example
srli_example:
    srli a0, a0, 3        # Logical right shift a0 by 3 bits, store in a0
    ret

.global srai_example
srai_example:
    srai a0, a0, 3        # Arithmetic right shift a0 by 3 bits, store in a0
    ret

.global lui_example
lui_example:
    lui a0, 0x12345       # Load immediate 0x12345 into upper 20 bits of a0
    ret

.global auipc_example
auipc_example:
    auipc a0, 0x100       # Add current PC and immediate shifted left 12 bits, store in a0
    ret

.global add_example
add_example:
    add a0, a0, a1        # Add a0 and a1, store result in a0
    ret

.global sub_example
sub_example:
    sub a0, a0, a1        # Subtract a1 from a0, store result in a0
    ret

.global slt_example
slt_example:
    slt a0, a0, a1        # Set a0 to 1 if a0 < a1, else 0
    ret

.global sltu_example
sltu_example:
    sltu a0, a0, a1       # Unsigned comparison: Set a0 to 1 if a0 < a1, else 0
    ret

.global and_example
and_example:
    and a0, a0, a1        # Perform bitwise AND of a0 and a1, store in a0
    ret

.global or_example
or_example:
    or a0, a0, a1         # Perform bitwise OR of a0 and a1, store in a0
    ret

.global xor_example
xor_example:
    xor a0, a0, a1        # Perform bitwise XOR of a0 and a1, store in a0
    ret

.global nop_example
nop_example:
    nop                   # No operation
    ret

# RV64I Arithmetic Operations (14 commands)
.global addiw_example
addiw_example:
    addiw a0, a0, 4       # Add immediate 4 to lower 32 bits of a0, sign-extend to 64 bits
    ret

.global slliw_example
slliw_example:
    slliw a0, a0, 4       # Shift lower 32 bits of a0 left by 4 bits, sign-extend to 64 bits
    ret

.global srliw_example
srliw_example:
    srliw a0, a0, 4       # Logical right shift lower 32 bits of a0 by 4 bits, sign-extend to 64 bits
    ret

.global sraiw_example
sraiw_example:
    sraiw a0, a0, 4       # Arithmetic right shift lower 32 bits of a0 by 4 bits, sign-extend to 64 bits
    ret

.global addw_example
addw_example:
    addw a0, a0, a1       # Add lower 32 bits of a0 and a1, sign-extend to 64 bits
    ret

.global subw_example
subw_example:
    subw a0, a0, a1       # Subtract lower 32 bits of a1 from a0, sign-extend to 64 bits
    ret

.global sll_example
sll_example:
    sll a0, a0, a1        # Logical left shift a0 by the amount specified in a1
    ret

.global srl_example
srl_example:
    srl a0, a0, a1        # Logical right shift a0 by the amount specified in a1
    ret

.global sra_example
sra_example:
    sra a0, a0, a1        # Arithmetic right shift a0 by the amount specified in a1
    ret

.global sllw_example
sllw_example:
    sllw a0, a0, a1       # Logical left shift lower 32 bits of a0 by a1, sign-extend to 64 bits
    ret

.global srlw_example
srlw_example:
    srlw a0, a0, a1       # Logical right shift lower 32 bits of a0 by a1, sign-extend to 64 bits
    ret

.global sraw_example
sraw_example:
    sraw a0, a0, a1       # Arithmetic right shift lower 32 bits of a0 by a1, sign-extend to 64 bits
    ret

# Single Precision Floating-Point Arithmetic (11 commands)
.global fadd_s_example
fadd_s_example:
    fadd.s fa0, fa0, fa1  # Add single-precision floating-point numbers in fa0 and fa1, store in fa0
    ret

.global fsub_s_example
fsub_s_example:
    fsub.s fa0, fa0, fa1  # Subtract single-precision floating-point number in fa1 from fa0, store in fa0
    ret

.global fmul_s_example
fmul_s_example:
    fmul.s fa0, fa0, fa1  # Multiply single-precision floating-point numbers in fa0 and fa1, store in fa0
    ret

.global fdiv_s_example
fdiv_s_example:
    fdiv.s fa0, fa0, fa1  # Divide single-precision floating-point number in fa0 by fa1, store in fa0
    ret

.global fsqrt_s_example
fsqrt_s_example:
    fsqrt.s fa0, fa0       # Compute square root of single-precision floating-point number in fa0, store in fa0
    ret

.global fmin_s_example
fmin_s_example:
    fmin.s fa0, fa0, fa1  # Compute minimum of two single-precision floating-point numbers in fa0 and fa1, store in fa0
    ret

.global fmax_s_example
fmax_s_example:
    fmax.s fa0, fa0, fa1  # Compute maximum of two single-precision floating-point numbers in fa0 and fa1, store in fa0
    ret

.global fmadd_s_example
fmadd_s_example:
    fmadd.s fa0, fa0, fa1, fa2 # Fused multiply-add: fa0 = fa0 * fa1 + fa2
    ret

.global fmsub_s_example
fmsub_s_example:
    fmsub.s fa0, fa0, fa1, fa2 # Fused multiply-subtract: fa0 = fa0 * fa1 - fa2
    ret

.global fnmsub_s_example
fnmsub_s_example:
    fnmsub.s fa0, fa0, fa1, fa2 # Negative fused multiply-subtract: fa0 = -(fa0 * fa1 - fa2)
    ret

.global fnmadd_s_example
fnmadd_s_example:
    fnmadd.s fa0, fa0, fa1, fa2 # Negative fused multiply-add: fa0 = -(fa0 * fa1 + fa2)
    ret

# Double Precision Floating-Point Arithmetic (11 commands)
.global fadd_d_example
fadd_d_example:
    fadd.d fa0, fa0, fa1  # Add double-precision floating-point numbers in fa0 and fa1, store in fa0
    ret

.global fsub_d_example
fsub_d_example:
    fsub.d fa0, fa0, fa1  # Subtract double-precision floating-point number in fa1 from fa0, store in fa0
    ret

.global fmul_d_example
fmul_d_example:
    fmul.d fa0, fa0, fa1  # Multiply double-precision floating-point numbers in fa0 and fa1, store in fa0
    ret

.global fdiv_d_example
fdiv_d_example:
    fdiv.d fa0, fa0, fa1  # Divide double-precision floating-point number in fa0 by fa1, store in fa0
    ret

.global fsqrt_d_example
fsqrt_d_example:
    fsqrt.d fa0, fa0       # Compute square root of double-precision floating-point number in fa0, store in fa0
    ret

.global fmin_d_example
fmin_d_example:
    fmin.d fa0, fa0, fa1  # Compute minimum of two double-precision floating-point numbers in fa0 and fa1, store in fa0
    ret

.global fmax_d_example
fmax_d_example:
    fmax.d fa0, fa0, fa1  # Compute maximum of two double-precision floating-point numbers in fa0 and fa1, store in fa0
    ret

.global fmadd_d_example
fmadd_d_example:
    fmadd.d fa0, fa0, fa1, fa2 # Fused multiply-add: fa0 = fa0 * fa1 + fa2
    ret

.global fmsub_d_example
fmsub_d_example:
    fmsub.d fa0, fa0, fa1, fa2 # Fused multiply-subtract: fa0 = fa0 * fa1 - fa2
    ret

.global fnmsub_d_example
fnmsub_d_example:
    fnmsub.d fa0, fa0, fa1, fa2 # Negative fused multiply-subtract: fa0 = -(fa0 * fa1 - fa2)
    ret

.global fnmadd_d_example
fnmadd_d_example:
    fnmadd.d fa0, fa0, fa1, fa2 # Negative fused multiply-add: fa0 = -(fa0 * fa1 + fa2)
    ret

