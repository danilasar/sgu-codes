.model small

	.stack 100h

	.data
	hello db "Hello, huy!$"

	HelloMacro macro 
 push ax
	lea dx, hello
	mov ah, 09h
	int 21h
	pop ax
endm
	
	.code 

start:

	mov AX, @data
	mov ds, ax 

HelloMacro

mov ax, 4c00h
	int 21h

end start
