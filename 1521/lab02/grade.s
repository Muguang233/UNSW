
main:
	#t0 mark
	li $v0, 4
	la $a0, o1	
	syscall
	li $v0, 5
	syscall		
	move $t0, $v0
	
	blt $t0,50, if_less_50
	blt $t0,65, if_less_65
	blt $t0,75, if_less_75
	blt $t0,85, if_less_85
	b else


if_less_50:
	li $v0, 4
	la $a0, fl	
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall
	b end
if_less_65:
	li $v0, 4
	la $a0, ps	
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall
	b end
if_less_75:
	li $v0, 4
	la $a0, cr	
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall
	b end
if_less_85:
	li $v0, 4
	la $a0, dn	
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall
	b end
else:
	li $v0, 4
	la $a0, hd	
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall
	b end
end:
	#li $v0,0 #return 0
	jr $ra
	
.data

o1: .asciiz "Enter a mark: "
fl: .asciiz "FL"
ps: .asciiz "PS"
cr: .asciiz "CR"
dn: .asciiz "DN"
hd: .asciiz "HD"
