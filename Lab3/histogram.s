    MODULE ?histogram
    
    SECTION .text:CODE
    THUMB
    
;Entrada: R0 -> width
;         R1 -> height
;         R2 -> start address of image
;         R3 -> start address of histogram     

EightBitHistogram
    PUSH {R4, R5, LR}
    MUL R0, R1                  ;Get Image Size
    CMP R0, #64000              ;if R0 > 64k
    ITT GT
    MOVGT R0, #0                ;R0 = 0
    BGT return                  ;return
    B R2                        ;
return
    POP {R4, R5, PC} 
    BLR
    END