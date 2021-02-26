  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.
    .global time2string
    .global hexasc
    .global delay
    .global enable_interrupt
    .data
    .text
    
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm


 #convert decimal value to ASCII code   
hexasc: 
 	 
 	andi $a0, $a0, 15	# set all but the four LSB to 0
 	sltiu $t0,$a0, 10 	# if argument is less than 10, add 48
 	beq $t0, $0, else	# if argument > 10, $t0 == 0, go to else label
 	nop			 
 	addi $v0, $a0, 48
 	j endif
 	nop
else:	
 	addi $v0, $a0, 55	
 	jr $ra
 	nop
endif:
 	jr $ra
 	nop
 	
# delay

delay: 	
	
	move $t0, $a0 		# fetch argument ms
	li $t1, 0 		# int i = 0
	li $t2, 10650		# constant

while:	
	ble $t0,$zero, exit	# if ms <= 0, exit
	nop
	j subtract
	nop
	
subtract:	
	addi $t0, $t0, -1
	li $t1, 0
	j for
	nop
for:			
	
	bge $t1, $t2, while	# while constant > int i 
	nop
	addi $t1, $t1, 1	
	j for
	nop
exit: 

	jr $ra
	nop
	
	


# output time as string 		
time2string:

	PUSH $s0
	PUSH $s1
	PUSH $s2
	PUSH $s3
	PUSH $s4
	PUSH $ra
	
	move $s4, $a0
	la $t0, mytime 
	
	lb $s0, 1($t0)		# Load minute byte
	lb $s2, 0($t0)		# Load second byte
	
	move $s1, $s0		# Make copy of minute byte
	srl $s0, $s0, 4		# MS minute digit 
	andi $s1, $s1, 0xF	# LS seconds digit 
	
	move $s3, $s2		# Make copy of second byte
	srl $s2, $s2, 4		# MS seconds digit 
	andi $s3, $s3, 0xF	# LS seconds digit 	
	
	move $a0, $s0		
	jal hexasc
	nop
	move $s0, $v0
	
	move $a0, $s1
	jal hexasc 
	nop
	move $s1, $v0		# Convert digits to ASCII code
	
	move $a0, $s2 
	jal hexasc
	nop
	move $s2, $v0
	
	move $a0, $s3
	jal hexasc 
	nop
	move $s3, $v0
	
	li $t0, 0x3A		# Colon
	li $t1, 0		# Null 

	sb $s0, 0($s4)		# Minute digit 1
	sb $s1, 1($s4)		# Minute digit 2
	sb $t0, 2($s4)		# Colon
	sb $s2, 3($s4) 		# Second digit 1
	sb $s3, 4($s4)		# Second digit 2
	sb $t1, 5($s4)		# Null byte 
	
	POP $ra
	POP $s4
	POP $s3
	POP $s2
	POP $s1
	POP $s0	

	jr $ra
	nop

enable_interrupt:
	ei
	jr	$ra
	nop

