
main: #t0 number
	#t1 i
	li $v0, 4
	la $a0, enter 	#printf("Enter a number: ");
	syscall		

	li $v0, 5
	syscall		#scanf("%d", &number);
	move $t0, $v0

	li $t1, 1

loop:
	bge $t1, $t0, end
	li $t2, 7
	div $t1, $t2
	mfhi $t3
	beq $t3, $zero, if_body
	li $t2, 11
	div $t1, $t2
	mfhi $t3
	beq $t3, $zero, if_body
	add $t1, $t1, 1
	j loop
if_body:
	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall
	add $t1, $t1, 1
	j loop

end:


	li $v0,0 #return 0
	jr $ra

	.data
enter: .asciiz "Enter a number: "
