;  ##############################################
;   Copyright (c) 2010 Cyrbil, http://cyrbil.tk
;  ##############################################
;   Permission is hereby granted, free of charge, to any person obtaining
;   a copy of this software and associated documentation files (the
;   "Software"), to deal in the Software without restriction, including
;   without limitation the rights to use, copy, modify, merge, publish,
;   distribute, sublicense, and/or sell copies of the Software, and to
;   permit persons to whom the Software is furnished to do so, subject to
;   the following conditions:
;   
;   The above copyright notice and this permission notice shall be
;   included in all copies or substantial portions of the Software.
;   
;   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
;   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
;   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
;   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
;   LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
;   OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
;   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
;   
;   

; This file is an exercice that I've made at Supinfo.
; It's only a square that's bounce into wall
; I've challenged the exercise by using minimum of code. (under 100 lines !)
; I put it here as educational purpose.


org 100h
; set video mode    
mov ax, 3     ; text mode 80x25, 16 colors, 8 pages (ah=0, al=3)
int 10h       ; do it!
; cancel blinking and enable all 16 colors:
mov ax, 1003h
mov bx, 0
int 10h
; set segment register:
mov ax, 0b800h
mov ds, ax 
; write loading and load border
mov bx, 0x0F            ; page number / colors
mov cx, 33              ; message size. 
mov dx, 0x0a0a          ; column/row starting
mov bp, offset data     ; pointeur to string
mov ax, 1301h           ; write mode
int 10h                 ; write!
mov bx, 0x1d0           ; page number / colors
mov cx, 0x780           ; message size. 
mov dx, 0               ; column/row starting
mov bp, offset data + 33; pointeur to string
int 10h                 ; write!
;load page
mov ax, 0x501           ; change page / set active page 1
int 10h                 ; go!
;initialise data
mov bl, 1111_1010b      ; colors
mov cx, 1               ; message size (one char)
mov bp, offset data2 + 1; pointeur to string (espace)
mov ah, 13h             ; write mode
mov dx, 0x620           ; column/row starting
mov [0xfff], 0          ; vector direction
main:; main loop
    ;printing part
        int 10h                 ; write!    
    ;colision part
        cmp dh, 1               ; cmp with up border
        ja col1                 ; if under, jump
            cmp [0xfff],3       ; else cmp direction with top left
            jne col01           ; if not top left, jump
                mov [0xfff], 2  ; else change direction
                jmp col2        ; jump after
            col01: 
                mov [0xfff], 1  ; change direction
                jmp col2
        col1: cmp dh, 22        ; cmp with down border
        jb col2                 ; if above, jump
            cmp [0xfff],2       ; else cmp direction with down left
            jne col11           ; if not down left, jump
                mov [0xfff], 3  ; else change direction
                jmp col2        ; jump after
            col11: 
                mov [0xfff], 0  ; change direction      
        col2: cmp dl, 1         ; cmp with left border
        ja col3                 ; if to the right, jump
            cmp [0xfff], 3      ; else cmp direction
            jne col21           ; if not top left, jump
                mov [0xfff], 0  ; else change direction
                jmp col3        ; jump after
            col21:
                mov [0xfff], 1  ; change direction
                jmp modifpos 
        col3: cmp dl, 78        ; cmp with right border
        jb modifpos             ; if to the left, jump
            cmp [0xfff], 0      ; else cmp direction
            jne col31           ; if not top right, jump
                mov [0xfff], 3  ; else change direction
                jmp modifpos    ; jump after
            col31:
                mov [0xfff], 2  ; change direction
    ;modify coord depend of vector
    modifpos:
        cmp [0xfff], 0          ; cmp vector with top-left
        jne pos1                ; if 
            add dx, 0xff01      ; change cursor position
            jmp end             ; jump to the end
        pos1: cmp [0xfff], 1    ; else cmp with top right
        jne pos2
            add dx, 0x0101      ; change cursor position
            jmp end 
        pos2: cmp [0xfff], 2    ; else cmp with down-left
        jne pos3
            add dx, 0x00ff      ; change cursor position
            jmp end
        pos3: sub dx, 0x0101    ; else (down right) change cursor position
     end:    
     ;compteur update part
        mov di, 0x1088          ; address of 1st number (0 at initial state)
        compt: call compteur    ; call procedure         
jmp main:
; recursive fonction to display frames
compteur proc
    mov si,[di]         ; add value in si
    inc si              ; increment
    cmp si, 0xD03A      ; si=0xD03A <=> si = "10"
    jne then            ; if si = 10{
        mov [di],0xD030 ;   push 0 to write
        sub di, 2       ;   change address
        call compteur   ;   recall function
    then:               ; }
    cmp si, 0xD0CE      ; else{
    jne write           ;  if egal to new number
        mov si, 0xD031  ;  push 1 to write
    write:              ;}
    mov [di], si        ;write value 
    ret
compteur endp
; data, border and text, easy to display, change and very fast method
data db "Loading Graphics, Please Wait ...ЩЭЭЭAnimation V3.6ЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭ0 FramesЭЭЭЛКллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллК", 
     db "КллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллККллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллКШЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭЭМ"



