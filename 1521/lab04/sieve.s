# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
# Yinla Zhu

# Constants
ARRAY_LEN = 1000

main:

	# TODO: add your code here
	li	$t0, 2		#i = $t0
	la	$t1, prime

out_cond:
	bge	$t0, ARRAY_LEN, end
out_body:
	mul $t3, $t0, 1
	add $t2, $t3, $t1
	lb 	$t6, 0($t2)
	bne $t6, 1, jump
	li	$v0, 1
	move	$a0, $t0
	syscall
	li	$v0, 11				#   syscall 11: print_char
	li	$a0, '\n'			#
	syscall					#   printf("%c", '\n');
	mul 	$t4, $t0, 2
in_cond:
	bge	$t4, ARRAY_LEN, jump
in_body:
	add	$t5, $t4, $t1
	sb	$zero, 0($t5)
	add	$t4, $t4, $t0
	j in_cond
jump:
	addi $t0, $t0, 1
	j out_cond

end:

	li	$v0, 0
	jr	$ra			# return 0;

	.data
prime:
	.byte	1:ARRAY_LEN		# uint8_t prime[ARRAY_LEN] = {1, 1, ...};