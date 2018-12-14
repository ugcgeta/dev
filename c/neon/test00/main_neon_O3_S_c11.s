	.arch armv6
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu neon
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
	add	r3, r2, #16
	add	ip, r1, #16
	cmp	r2, ip
	cmpcc	r1, r3
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, lr}
	add	lr, r0, #16
	movcs	ip, #1
	movcc	ip, #0
	cmp	r2, lr
	cmpcc	r0, r3
	movcs	r3, #1
	movcc	r3, #0
	tst	ip, r3
	beq	.L2
	and	r4, r0, #7
	rsb	r4, r4, #0
	ands	r4, r4, #15
	beq	.L10
	ldrb	r3, [r1]	@ zero_extendqisi2
	ldrb	ip, [r0]	@ zero_extendqisi2
	cmp	r4, #1
	add	r3, r3, ip
	strb	r3, [r2]
	beq	.L11
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	ldrb	ip, [r0, #1]	@ zero_extendqisi2
	cmp	r4, #2
	add	r3, r3, ip
	strb	r3, [r2, #1]
	beq	.L12
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	ldrb	ip, [r0, #2]	@ zero_extendqisi2
	cmp	r4, #3
	add	r3, r3, ip
	strb	r3, [r2, #2]
	beq	.L13
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	ldrb	ip, [r0, #3]	@ zero_extendqisi2
	cmp	r4, #4
	add	r3, r3, ip
	strb	r3, [r2, #3]
	beq	.L14
	ldrb	r3, [r1, #4]	@ zero_extendqisi2
	ldrb	ip, [r0, #4]	@ zero_extendqisi2
	cmp	r4, #5
	add	r3, r3, ip
	strb	r3, [r2, #4]
	beq	.L15
	ldrb	r3, [r1, #5]	@ zero_extendqisi2
	ldrb	ip, [r0, #5]	@ zero_extendqisi2
	cmp	r4, #6
	add	r3, r3, ip
	strb	r3, [r2, #5]
	beq	.L16
	ldrb	r3, [r1, #6]	@ zero_extendqisi2
	ldrb	ip, [r0, #6]	@ zero_extendqisi2
	cmp	r4, #7
	add	r3, r3, ip
	strb	r3, [r2, #6]
	beq	.L17
	ldrb	r3, [r1, #7]	@ zero_extendqisi2
	ldrb	ip, [r0, #7]	@ zero_extendqisi2
	cmp	r4, #8
	add	r3, r3, ip
	strb	r3, [r2, #7]
	beq	.L18
	ldrb	r3, [r1, #8]	@ zero_extendqisi2
	ldrb	ip, [r0, #8]	@ zero_extendqisi2
	cmp	r4, #9
	add	r3, r3, ip
	strb	r3, [r2, #8]
	beq	.L19
	ldrb	r3, [r1, #9]	@ zero_extendqisi2
	ldrb	ip, [r0, #9]	@ zero_extendqisi2
	cmp	r4, #10
	add	r3, r3, ip
	strb	r3, [r2, #9]
	beq	.L20
	ldrb	r3, [r1, #10]	@ zero_extendqisi2
	ldrb	ip, [r0, #10]	@ zero_extendqisi2
	cmp	r4, #11
	add	r3, r3, ip
	strb	r3, [r2, #10]
	beq	.L21
	ldrb	r3, [r1, #11]	@ zero_extendqisi2
	ldrb	ip, [r0, #11]	@ zero_extendqisi2
	cmp	r4, #12
	add	r3, r3, ip
	strb	r3, [r2, #11]
	beq	.L22
	ldrb	r3, [r1, #12]	@ zero_extendqisi2
	ldrb	ip, [r0, #12]	@ zero_extendqisi2
	cmp	r4, #13
	add	r3, r3, ip
	strb	r3, [r2, #12]
	beq	.L23
	ldrb	r3, [r1, #13]	@ zero_extendqisi2
	ldrb	ip, [r0, #13]	@ zero_extendqisi2
	cmp	r4, #15
	add	r3, r3, ip
	strb	r3, [r2, #13]
	bne	.L24
	ldrb	ip, [r1, #14]	@ zero_extendqisi2
	ldrb	r5, [r0, #14]	@ zero_extendqisi2
	mov	lr, #113
	mov	r3, r4
	add	ip, ip, r5
	strb	ip, [r2, #14]
.L4:
	rsb	r8, r4, #128
	mov	r6, #112
	mov	ip, #7
.L3:
	add	r5, r1, r4
	cmp	ip, #8
	add	ip, r2, r4
	mov	r9, r5
	add	r4, r0, r4
	vld1.8	{q8}, [r9]!
	vld1.64	{d18-d19}, [r4:64]
	mov	r7, ip
	vadd.i8	q8, q8, q9
	add	fp, r5, #32
	vst1.8	{q8}, [r7]!
	add	r10, ip, #32
	vld1.8	{q8}, [r9]
	vldr	d18, [r4, #16]
	vldr	d19, [r4, #24]
	add	r9, ip, #48
	vadd.i8	q8, q8, q9
	vst1.8	{q8}, [r7]
	add	r7, r5, #48
	vld1.8	{q8}, [fp]
	vldr	d18, [r4, #32]
	vldr	d19, [r4, #40]
	add	fp, r5, #80
	vadd.i8	q8, q8, q9
	vst1.8	{q8}, [r10]
	add	r10, r5, #64
	vld1.8	{q8}, [r7]
	vldr	d18, [r4, #48]
	vldr	d19, [r4, #56]
	add	r7, ip, #64
	vadd.i8	q8, q8, q9
	vst1.8	{q8}, [r9]
	add	r9, ip, #80
	vld1.8	{q8}, [r10]
	vldr	d18, [r4, #64]
	vldr	d19, [r4, #72]
	add	r10, r5, #96
	vadd.i8	q8, q8, q9
	vst1.8	{q8}, [r7]
	add	r7, ip, #96
	vldr	d18, [r4, #80]
	vldr	d19, [r4, #88]
	vld1.8	{q8}, [fp]
	vadd.i8	q8, q8, q9
	vst1.8	{q8}, [r9]
	vld1.8	{q8}, [r10]
	vldr	d18, [r4, #96]
	vldr	d19, [r4, #104]
	vadd.i8	q8, q8, q9
	vst1.8	{q8}, [r7]
	bne	.L5
	vldr	d18, [r4, #112]
	vldr	d19, [r4, #120]
	add	r5, r5, #112
	add	ip, ip, #112
	vld1.8	{q8}, [r5]
	vadd.i8	q8, q8, q9
	vst1.8	{q8}, [ip]
.L5:
	cmp	r8, r6
	add	r3, r3, r6
	rsb	lr, r6, lr
	ldmeqfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, pc}
	add	lr, r3, lr
	add	lr, r0, lr
	add	ip, r1, r3
	add	r0, r0, r3
	add	r2, r2, r3
.L6:
	ldrb	r1, [r0], #1	@ zero_extendqisi2
	ldrb	r3, [ip], #1	@ zero_extendqisi2
	cmp	r0, lr
	add	r3, r3, r1
	strb	r3, [r2], #1
	bne	.L6
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L10:
	mov	r6, #128
	mov	r8, r6
	mov	lr, r6
	mov	ip, #8
	mov	r3, r4
	b	.L3
.L2:
	sub	ip, r1, #1
	add	lr, r0, #127
	sub	r1, r2, #1
	sub	r2, r0, #1
.L8:
	ldrb	r0, [r2, #1]!	@ zero_extendqisi2
	ldrb	r3, [ip, #1]!	@ zero_extendqisi2
	cmp	r2, lr
	add	r3, r3, r0
	strb	r3, [r1, #1]!
	bne	.L8
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L11:
	mov	lr, #127
	mov	r3, r4
	b	.L4
.L24:
	mov	lr, #114
	mov	r3, #14
	b	.L4
.L15:
	mov	lr, #123
	mov	r3, r4
	b	.L4
.L14:
	mov	lr, #124
	mov	r3, r4
	b	.L4
.L13:
	mov	lr, #125
	mov	r3, r4
	b	.L4
.L12:
	mov	lr, #126
	mov	r3, r4
	b	.L4
.L23:
	mov	lr, #115
	mov	r3, r4
	b	.L4
.L22:
	mov	lr, #116
	mov	r3, r4
	b	.L4
.L21:
	mov	lr, #117
	mov	r3, r4
	b	.L4
.L20:
	mov	lr, #118
	mov	r3, r4
	b	.L4
.L19:
	mov	lr, #119
	mov	r3, r4
	b	.L4
.L18:
	mov	lr, #120
	mov	r3, #8
	b	.L4
.L17:
	mov	lr, #121
	mov	r3, r4
	b	.L4
.L16:
	mov	lr, #122
	mov	r3, r4
	b	.L4
	.size	add, .-add
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 400
	@ frame_needed = 0, uses_anonymous_args = 0
	str	lr, [sp, #-4]!
	sub	sp, sp, #404
	add	r0, sp, #16
	mov	r1, #18
	mov	r2, #128
	bl	memset
	mov	r2, #128
	add	r0, sp, #144
	mov	r1, #52
	bl	memset
	vldr	d18, [sp, #16]
	vldr	d19, [sp, #24]
	vldr	d16, [sp, #144]
	vldr	d17, [sp, #152]
	vadd.i8	q8, q8, q9
	vst1.64	{d16-d17}, [sp:64]
	ldr	r1, [sp]
	ldr	r0, .L31
	vldr	d20, [sp, #32]
	vldr	d21, [sp, #40]
	vstr	d16, [sp, #272]
	vstr	d17, [sp, #280]
	vldr	d18, [sp, #160]
	vldr	d19, [sp, #168]
	vldr	d16, [sp, #176]
	vldr	d17, [sp, #184]
	vadd.i8	q9, q9, q10
	vldr	d20, [sp, #48]
	vldr	d21, [sp, #56]
	vstr	d18, [sp, #288]
	vstr	d19, [sp, #296]
	vadd.i8	q8, q8, q10
	vldr	d18, [sp, #192]
	vldr	d19, [sp, #200]
	vldr	d20, [sp, #64]
	vldr	d21, [sp, #72]
	vstr	d16, [sp, #304]
	vstr	d17, [sp, #312]
	vadd.i8	q9, q9, q10
	vldr	d16, [sp, #208]
	vldr	d17, [sp, #216]
	vldr	d20, [sp, #80]
	vldr	d21, [sp, #88]
	vstr	d18, [sp, #320]
	vstr	d19, [sp, #328]
	vadd.i8	q8, q8, q10
	vldr	d18, [sp, #224]
	vldr	d19, [sp, #232]
	vldr	d20, [sp, #96]
	vldr	d21, [sp, #104]
	vstr	d16, [sp, #336]
	vstr	d17, [sp, #344]
	vadd.i8	q9, q9, q10
	vldr	d16, [sp, #240]
	vldr	d17, [sp, #248]
	vldr	d20, [sp, #112]
	vldr	d21, [sp, #120]
	vstr	d18, [sp, #352]
	vstr	d19, [sp, #360]
	vadd.i8	q9, q8, q10
	vldr	d16, [sp, #256]
	vldr	d17, [sp, #264]
	vstr	d18, [sp, #368]
	vstr	d19, [sp, #376]
	vldr	d18, [sp, #128]
	vldr	d19, [sp, #136]
	vadd.i8	q8, q8, q9
	vstr	d16, [sp, #384]
	vstr	d17, [sp, #392]
	bl	printf
	mov	r0, #0
	add	sp, sp, #404
	@ sp needed
	ldr	pc, [sp], #4
.L32:
	.align	2
.L31:
	.word	.LC0
	.size	main, .-main
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%08X\012\000"
	.ident	"GCC: (Raspbian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",%progbits
