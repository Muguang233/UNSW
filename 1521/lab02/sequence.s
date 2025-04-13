
main:
	#$t0 start
	#$t1 stop
	#$t2 step
	li $v0, 4
	la $a0, enter1
	syscall

	li $v0, 5
	syscall
	move $t0, $v0

	li $v0, 4
	la $a0, enter2
	syscall

	li $v0, 5
	syscall
	move $t1, $v0

	li $v0, 4
	la $a0, enter3
	syscall

	li $v0, 5
	syscall
	move $t2, $v0
	blt $t1, $t0, if_1
	bgt $t1, $t0, if_2
if_1:
	blt $t2, $zero, loop_1
	j end

loop_1:
	move $t3, $t0
loop_1_body:
	blt $t3, $t1, end
	li $v0, 1
	move $a0, $t3
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall
	add $t3, $t3, $t2
	j loop_1_body
if_2:
	bgt $t2, $zero, loop_2
	j end
loop_2:
	move $t3, $t0
loop_2_body:
	bgt $t3, $t1, end
	li $v0, 1
	move $a0, $t3
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall
	add $t3, $t3, $t2
	j loop_2_body
end:
	li $v0, 0
	jr $ra
	

	.data

enter1: .asciiz "Enter the starting number: "
enter2: .asciiz "Enter the stopping number: "
enter3: .asciiz "Enter the step size: "