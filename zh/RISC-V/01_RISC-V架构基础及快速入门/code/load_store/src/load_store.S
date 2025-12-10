.section .text

// RV32I Load and Store Instructions
.global lh_example
lh_example:
    lh a0, 0(a0)            # Load 16-bit signed halfword from address a0 into a0
    ret                     # Return

.global lw_example
lw_example:
    lw a0, 0(a0)            # Load 32-bit word from address a0 into a0
    ret                     # Return

.global lbu_example
lbu_example:
    lbu a0, 0(a0)           # Load 8-bit unsigned byte from address a0 into a0
    ret                     # Return

.global lhu_example
lhu_example:
    lhu a0, 0(a0)           # Load 16-bit unsigned halfword from address a0 into a0
    ret                     # Return

.global sb_example
sb_example:
    sb a0, 0(a1)            # Store byte from a0 into address a1 + 0
    ret                     # Return

.global sh_example
sh_example:
    sh a0, 0(a1)            # Store halfword from a0 into address a1 + 0
    ret                     # Return

.global sw_example
sw_example:
    sw a0, 0(a1)            # Store word from a0 into address a1 + 0
    ret                     # Return

// RV64I Load and Store Instructions
.global ld64_example
ld64_example:
    ld a0, 0(a0)            # Load 64-bit value from address a0 into a0
    ret                     # Return

.global lw64_example
lw64_example:
    lw a0, 0(a0)            # Load 32-bit signed word from address a0 into a0
    ret                     # Return

.global lwu_example
lwu_example:
    lwu a0, 0(a0)           # Load 32-bit unsigned word from address a0 into a0
    ret                     # Return

.global lh64_example
lh64_example:
    lh a0, 0(a0)            # Load 16-bit signed halfword from address a0 into a0
    ret                     # Return

.global lhu64_example
lhu64_example:
    lhu a0, 0(a0)           # Load 16-bit unsigned halfword from address a0 into a0
    ret                     # Return

.global lb_example
lb_example:
    lb a0, 0(a0)            # Load 8-bit signed byte from address a0 into a0
    ret                     # Return

.global lbu64_example
lbu64_example:
    lbu a0, 0(a0)           # Load 8-bit unsigned byte from address a0 into a0
    ret                     # Return

.global sd_example
sd_example:
    sd a0, 0(a1)            # Store 64-bit value from a0 into address a1 + 0
    ret                     # Return

.global sw64_example
sw64_example:
    sw a0, 0(a1)            # Store 32-bit word from a0 into address a1 + 0
    ret                     # Return

.global sh64_example
sh64_example:
    sh a0, 0(a1)            # Store 16-bit halfword from a0 into address a1 + 0
    ret                     # Return

.global sb64_example
sb64_example:
    sb a0, 0(a1)            # Store 8-bit byte from a0 into address a1 + 0
    ret                     # Return

// Single-Precision Floating-Point Instructions
.global flw_example
flw_example:
    flw fa0, 0(a0)          # Load single-precision float from address a0 into fa0
    fmv.x.w a0, fa0         # Move float bits from fa0 to a0 as integer
    ret                     # Return (a0 holds the float bits)

.global fsw_example
fsw_example:
    fsw fa0, 0(a0)          # Store single-precision float from fa0 into address a0 + 0
    ret                     # Return

// Double-Precision Floating-Point Instructions
.global fld_example
fld_example:
    fld fa0, 0(a0)          # Load double-precision float from address a0 into fa0
    fmv.x.d a0, fa0         # Move double bits from fa0 to a0 as integer
    ret                     # Return (a0 holds the double bits)

.global fsd_example
fsd_example:
    fsd fa0, 0(a0)          # Store double-precision float from fa0 into address a0 + 0
    ret                     # Return

