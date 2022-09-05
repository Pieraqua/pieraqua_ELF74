    MODULE ?histogram
    
    SECTION .text:CODE
    THUMB
    
    
;Input: R0 -> width
;       R1 -> height
;       R2 -> starting address of image
;       R3 -> starting address of histogram 
EightBitHistogram
    PUSH {R4, R5, LR}
    MUL R0, R1                  ;R0 = R0*R1 -> get img_size
    CMP R0, #65536              
    ITT GT                      ;If R0 > 64k
    MOVGT R0, #0                ;R0 = 0
    BGT return                  ;return R0
    MOV R4, #0                  ;i = 0
    MOV R5, #0                  ;R5 = 0
clear_hist
    STR R5, [R3, R4]            ;hist[i] = 0
    ADD R4, #1                  ;i += 1
    CMP R4, #255                ;R5 == 255?
    BLT clear_hist
    MOV R4, #0                  ;i = 0
calc_hist
    LDR R5, [R3, R4]            ;cont = hist[i]
    ADD R5, #1                  ;cont++
    STR R5, [R3, R4]            ;hist[i] = cont
    ADD R4, #2                  ;i += 2 (img -> uint16_t)
    CMP R4, R0                  ;i > img_size?
    BLT calc_hist
    
return
    POP {R4, R5, PC}
    
    END