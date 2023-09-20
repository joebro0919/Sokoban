		xdef		_set_video_base

base		equ		8

_set_video_base:
		link		a6,#0
		move.l		base(a6),d1
		lsr.l		#8,d1
		move.l		#$ffff8201,a0
		movep.w		d1,(a0)
	
		unlk		a6
		rts
