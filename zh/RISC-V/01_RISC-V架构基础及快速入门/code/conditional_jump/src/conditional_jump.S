.section .text

// 条件跳转指令定义

.global beq_example
beq_example:
    beq a0, a1, equal_label
    li a0, 0            // 不相等返回 0
    ret
equal_label:
    li a0, 1            // 相等返回 1
    ret

.global bne_example
bne_example:
    bne a0, a1, not_equal_label
    li a0, 0            // 相等返回 0
    ret
not_equal_label:
    li a0, 1            // 不相等返回 1
    ret

.global blt_example
blt_example:
    blt a0, a1, less_label
    li a0, 0            // 不小于返回 0
    ret
less_label:
    li a0, 1            // 小于返回 1
    ret

.global bltu_example
bltu_example:
    bltu a0, a1, less_unsigned_label
    li a0, 0            // 不小于（无符号）返回 0
    ret
less_unsigned_label:
    li a0, 1            // 小于（无符号）返回 1
    ret

.global bge_example
bge_example:
    bge a0, a1, greater_equal_label
    li a0, 0            // 小于返回 0
    ret
greater_equal_label:
    li a0, 1            // 大于等于返回 1
    ret

.global bgeu_example
bgeu_example:
    bgeu a0, a1, greater_equal_unsigned_label
    li a0, 0            // 小于（无符号）返回 0
    ret
greater_equal_unsigned_label:
    li a0, 1            // 大于等于（无符号）返回 1
    ret

.global bgt_example
bgt_example:
    bgt a0, a1, greater_label
    li a0, 0            // 不大于返回 0
    ret
greater_label:
    li a0, 1            // 大于返回 1
    ret

.global bgtu_example
bgtu_example:
    bgtu a0, a1, greater_unsigned_label
    li a0, 0            // 不大于（无符号）返回 0
    ret
greater_unsigned_label:
    li a0, 1            // 大于（无符号）返回 1
    ret

.global ble_example
ble_example:
    ble a0, a1, less_equal_label
    li a0, 0            // 大于返回 0
    ret
less_equal_label:
    li a0, 1            // 小于等于返回 1
    ret

.global bleu_example
bleu_example:
    bleu a0, a1, less_equal_unsigned_label
    li a0, 0            // 大于（无符号）返回 0
    ret
less_equal_unsigned_label:
    li a0, 1            // 小于等于（无符号）返回 1
    ret

