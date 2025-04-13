
main:
	li $v0, 4
	la $a0, output
	syscall

	li $v0,0
	jr $ra

	.data

output:
	.asciiz "Well, this was a MIPStake!\n"