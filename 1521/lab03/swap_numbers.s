# Reads 10 numbers into an array
# printing 0 if they are in non-decreasing order
# or 1 otherwise.
# YOUR-NAME-HERE, DD/MM/YYYY

# Constants
ARRAY_LEN = 10

main:
	# Registers:
	#  - $t0: int i
	#  - $t1: temporary result
	#  - $t2: temporary result
	#  TODO: add your registers here

scan_loop__init:
	li	$t0, 0				# i = 0;
scan_loop__cond:
	bge	$t0, ARRAY_LEN, scan_loop__end	# while (i < ARRAY_LEN) {

scan_loop__body:
	li	$v0, 5				#   syscall 5: read_int
	syscall					#   
						#
	mul	$t1, $t0, 4			#   calculate &numbers[i] == numbers + 4 * i
	la	$t2, numbers			#
	add	$t2, $t2, $t1			#
	sw	$v0, ($t2)			#   scanf("%d", &numbers[i]);

	addi	$t0, $t0, 1			#   i++;
	j	scan_loop__cond			# }
scan_loop__end:


swap_init:
	li 	$t0, 1				#int i = 1
swap_cond:
	bge	$t0, ARRAY_LEN, swap_end	#while (i < ARRAY_LEN)
swap_body:
	mul	$t1, $t0, 4
	la	$t2, numbers
	add	$t2, $t2, $t1
	lw	$t3, ($t2)			#t4 = number[i]

	sub	$t2, $t2, 4			
	lw	$t4, ($t2)			#t5 = number[i - 1]

	bge	$t3, $t4, skip
	sw	$t3, ($t2)
	add	$t2, $t2, 4
	sw	$t4, ($t2)
	add 	$t0, $t0, 1
	j swap_cond

skip:
	add 	$t0, $t0, 1
	j swap_cond
swap_end:	

print_init:
	li 	$t0, 0
print_cond:
	bge	$t0, ARRAY_LEN, print_end
print_body:
	mul 	$t1, $t0, 4
	la	$t2, numbers
	add	$t2, $t2, $t1
	lw 	$a0, ($t2)
	li 	$v0, 1
	syscall
	li	$v0, 11				#   syscall 11: print_char
	li	$a0, '\n'			#
	syscall					#   printf("%c", '\n');
	addi $t0, $t0, 1
	j print_cond
print_end:

	li	$v0, 0
	jr	$ra				# return 0;

	.data
numbers:
	.word	0:ARRAY_LEN			# int numbers[ARRAY_LEN] = {0};