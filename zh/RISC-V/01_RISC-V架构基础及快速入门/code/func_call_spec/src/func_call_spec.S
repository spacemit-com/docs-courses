.section .text

.global add
add:
    add a0, a0, a1   # a0 = x + y
    ret              # 返回结果存储在 a0

.global multiply
multiply:
    fmul.s fa0, fa0, fa1  # fa0 = x * y
    ret                   # 返回结果存储在 fa0