	.arch armv6
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.align	2
	.global	add
	.type	add, %function
add:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	add	r3, r2, #4
	stmfd	sp!, {r4, r5, r6, lr}
	add	lr, r1, #4
	cmp	r2, lr
	cmpcc	r1, r3
	add	r4, r0, #4
	movcs	lr, #1
	movcc	lr, #0
	orr	ip, r0, r1
	cmp	r2, r4
	cmpcc	r0, r3
	movcs	r3, #1
	movcc	r3, #0
	orr	ip, r2, ip
	and	r3, r3, lr
	tst	ip, #3
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r3, #0
	beq	.L2
	sub	r5, r0, #4
	sub	ip, r1, #4
	add	r6, r2, #128
.L3:
	ldr	r1, .L10
	ldr	r0, [ip, #4]!
	ldr	r4, [r5, #4]!
	mov	lr, r1
	ldr	r3, .L10+4
	and	r1, r1, r0
	and	lr, lr, r4
	eor	r0, r0, r4
	add	r1, r1, lr
	and	r3, r3, r0
	eor	r3, r3, r1
	str	r3, [r2], #4
	cmp	r2, r6
	bne	.L3
	ldmfd	sp!, {r4, r5, r6, pc}
.L2:
	sub	r3, r1, #1
	sub	ip, r2, #1
	sub	r1, r0, #1
	add	lr, r0, #127
.L5:
	ldrb	r0, [r1, #1]!	@ zero_extendqisi2
	ldrb	r2, [r3, #1]!	@ zero_extendqisi2
	cmp	r1, lr
	add	r2, r2, r0
	strb	r2, [ip, #1]!
	bne	.L5
	ldmfd	sp!, {r4, r5, r6, pc}
.L11:
	.align	2
.L10:
	.word	2139062143
	.word	-2139062144
	.size	add, .-add
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 384
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, lr}
	sub	sp, sp, #388
	mov	r1, #18
	mov	r2, #128
	mov	r0, sp
	bl	memset
	add	r0, sp, #128
	mov	r1, #52
	mov	r2, #128
	bl	memset
	sub	r5, sp, #4
	add	r4, sp, #124
	add	ip, sp, #256
.L13:
	ldr	r2, .L16
	ldr	r1, [r4, #4]!
	ldr	lr, [r5, #4]!
	mov	r0, r2
	ldr	r3, .L16+4
	and	r2, r2, r1
	and	r0, r0, lr
	eor	r1, r1, lr
	add	r2, r2, r0
	and	r3, r3, r1
	eor	r3, r3, r2
	str	r3, [ip], #4
	add	r3, sp, #384
	cmp	ip, r3
	bne	.L13
	ldr	r1, [sp, #256]
	ldr	r0, .L16+8
	bl	printf
	mov	r0, #0
	add	sp, sp, #388
	@ sp needed
	ldmfd	sp!, {r4, r5, pc}
.L17:
	.align	2
.L16:
	.word	2139062143
	.word	-2139062144
	.word	.LC0
	.size	main, .-main
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%08X\012\000"
	.ident	"GCC: (Raspbian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",%progbits
