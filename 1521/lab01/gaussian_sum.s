
main:

	# $t0 n1
	# $t1 n2
	li $v0, 4
	la $a0, out1	#printf("Enter first number: ");
	syscall

	li $v0, 5
	syscall		#scanf
	move $t0, $v0

	li $v0, 4
	la $a0, out2	#printf("Enter second number: ");
	syscall 

	li $v0, 5
	syscall		#scanf
	move $t1, $v0

	sub $t2, $t1, $t0
	add $t2,$t2, 1
	add $t3, $t0, $t1
	mul $t3, $t3,$t2
	div $t3, $t3,2

	li $v0, 4
	la $a0, f1	
	syscall 
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 4
	la $a0, f2	
	syscall 
	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 4
	la $a0, f3	
	syscall 
	li $v0, 1
	move $a0, $t3
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall

	li $v0,0 #return 0
	jr $ra

	.data

out1:
	.asciiz "Enter first number: "
out2:
	.asciiz "Enter second number: "
f1:
	.asciiz "The sum of all numbers between "
f2:
	.asciiz " and "
f3:
	.asciiz " (inclusive) is: "

