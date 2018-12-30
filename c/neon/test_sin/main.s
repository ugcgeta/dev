	.arch armv5t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"main.c"
	.global	__aeabi_fmul
	.text
	.align	2
	.global	testFloat
	.syntax unified
	.arm
	.type	testFloat, %function
testFloat:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]	@ float
	str	r1, [fp, #-12]	@ float
	ldr	r1, [fp, #-12]	@ float
	ldr	r0, [fp, #-8]	@ float
	bl	__aeabi_fmul
	mov	r3, r0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	testFloat, .-testFloat
	.align	2
	.global	testSin
	.syntax unified
	.arm
	.type	testSin, %function
testSin:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]	@ float
	ldr	r0, [fp, #-8]	@ float
	bl	sinf
	mov	r3, r0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, pc}
	.size	testSin, .-testSin
	.global	__aeabi_i2f
	.global	__aeabi_f2d
	.section	.rodata
	.align	2
.LC0:
	.ascii	"%lf\012\000"
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, fp, lr}
	add	fp, sp, #8
	sub	sp, sp, #28
	str	r0, [fp, #-32]
	str	r1, [fp, #-36]
	ldr	r0, [fp, #-32]
	bl	__aeabi_i2f
	mov	r3, r0
	mov	r1, #1056964608
	mov	r0, r3
	bl	__aeabi_fmul
	mov	r3, r0
	str	r3, [fp, #-24]	@ float
	ldr	r3, .L7
	str	r3, [fp, #-20]	@ float
	ldr	r0, [fp, #-24]	@ float
	bl	testSin
	str	r0, [fp, #-16]	@ float
	ldr	r0, [fp, #-16]	@ float
	bl	__aeabi_f2d
	mov	r3, r0
	mov	r4, r1
	mov	r2, r3
	mov	r3, r4
	ldr	r0, .L7+4
	bl	printf
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #8
	@ sp needed
	pop	{r4, fp, pc}
.L8:
	.align	2
.L7:
	.word	1045220557
	.word	.LC0
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",%progbits
