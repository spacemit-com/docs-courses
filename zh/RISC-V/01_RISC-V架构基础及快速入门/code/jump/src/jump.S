.section .text

// 跳转指令定义

.global jal_example
jal_example:
    add sp,sp,-8
    sd  ra,0(sp)
    jal ra, target_label # 跳转到 target_label
    ld  ra, 0(sp)
    add sp, sp,8
    ret                  # 返回

target_label:
    addi a0, zero, 1     # 成功跳转，返回 1
    ret

.global jalr_example
jalr_example:
    add  sp,sp,-8
    sd   ra,0(sp)
    la   t0, register_addr # 加载目标地址
    jalr t0       # 跳转到目标地址
    ld   ra, 0(sp)
    add  sp, sp,8
    ret                  # 返回

register_addr:
    addi a0, zero, 1     # 成功跳转，返回 1
    ret
