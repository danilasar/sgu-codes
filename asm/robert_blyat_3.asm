.model small
.stack 100h

.data
	hueta db "mat ebal vashu$"
	str_size equ 14

	.code
  start:
  	mov ax, @data
		mov ds, ax
		xor ax, ax

		lea si, hueta
		mov cx, str_size
		call_hueta:
			call output_stringi
		loop call_hueta
		mov ax, 4c00h
		int 21h

		proc output_stringi
			lodsb
			xor ah, ah
			mov dx, ax
			xor ax, ax
			mov ah, 02h
			int 21h
			ret
		output_stringi endp

    end start
