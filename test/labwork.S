  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.globl delay
.globl time2string
.globl hexasc

.macro	PUSH reg	# NOTERA ATT H�R IFNNS INGA PARANTESER RUNT reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
  
.data
  
.text

hexasc:
 	andi	$a0, $a0, 0xf	# maskera de 4 LSB

	
	addi	$t0, $0, 10
	slt	$t1, $a0, $t0	# Om a0 < t0 (10) blir t1 1, dvs. 1 ger siffror och 0 ger bokstäver  

	beq	$t1, $0, bokst	# OM t1 == 0 gå till bokstäver, annars fortsätt raden nedan
	nop
	
	addi	$v0, $a0, 0x30	# Addera return värdet med 48 (ASCII 0 börjar på 48)
 	jr $ra
 	nop
 	
 	bokst:
 		addi	$v0, $a0, 0x37	# Addera return värdet med 55 (ASCII A börjar på 55 + minst 10)
 		jr	$ra
 		nop
 		
 		
delay:
	addi	$t1, $0, 400	# detta jämförs med i i for loop nedan (500 för $a0 = 1000 ger 1 sekund delay) STARTA OM 
	while:
	
		slt	$t2, $0, $a0	# 0 < $a0 (0 < ms ger $t2 = 1)
		beq	$t2, 0, done
		nop
		addi	$a0, $a0, -1
		addi	$t0, $0, 0	# i = 0
	for:
		beq	$t0, $t1, while
		nop
		addi	$t0, $t0, 1
		j	for
		nop
	
	done:
		jr	$ra
		nop

		
#delay:
#	jr $ra
	
	
time2string:

	
	PUSH	$ra
	PUSH	$s0
	PUSH	$s1
	
	move	$s0, $a0		# Spara addressen i $s0
	move	$s1, $a1		# Spara tids innehållet i $s1
	
	andi	$a0, $s1, 0xf000	# Vänstra minut siffran
	srl	$a0, $a0, 12		# Förskjut till 4 LSB
	jal	hexasc
	nop
	sb	$v0, 0($s0)
	addi	$s0, $s0, 1		# Öka på index med 1

	andi	$a0, $s1, 0xf00		# Högra minut siffran
	srl	$a0, $a0, 8
	jal	hexasc
	nop
	sb	$v0, 0($s0)
	addi	$s0, $s0, 1


	addi	$t0, $0, 0x3A		# Lägg :
	sb	$t0, 0($s0)
	addi	$s0, $s0, 1
	
	
	andi	$a0, $s1, 0xf0		# Vänstra sekund siffran
	srl	$a0, $a0, 4
	jal	hexasc
	nop
	sb	$v0, 0($s0)
	addi	$s0, $s0, 1
	
	
	andi	$a0, $s1, 0xf		# Högra sekund siffran
	jal	hexasc
	nop
	sb	$v0, 0($s0)
	addi	$s0, $s0, 1
	
	addi	$t1, $0, 0x00		# Lägg till NULL
	sb	$t1, 0($s0)		# PROBLEM: det var t0 istället för t1, t0 är då :!!!!
	addi	$s0, $0, 1
	
	
	POP	$s1
	POP	$s0
	POP	$ra
	
	jr	$ra
	nop

