

main:
	#t0 number
	#t1 i
	li $v0, 4
	la $a0, o 	#printf("Enter a number: ");
	syscall		

	li $v0, 5
	syscall		#scanf("%d", &number);
	move $t0, $v0

	li $t1, 1

loop_body:
	bgt $t1, $t0, loop_end
	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall
	add $t1, $t1, 1
	j loop_body

	
loop_end:
	li $v0,0 #return 0
	jr $ra


	.data
o: .asciiz "Enter a number: "