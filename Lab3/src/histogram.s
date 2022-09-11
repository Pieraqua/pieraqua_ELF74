    MODULE ?histogram
    
    SECTION .text:CODE
    THUMB
    
    EXPORT EightBitHistogram
    
    
;Input: R0 -> width
;       R1 -> height
;       R2 -> starting address of image
;       R3 -> starting address of histogram 
;
;Output: R0 -> number of modified pixels
       
EightBitHistogram
    PUSH {R4, R5, LR}
    MUL R0, R1                  ;R0 = R0*R1 -> get img_size
    CMP R0, #65536              
    ITT GT                      ;If R0 > 64k
    MOVGT R0, #0                ;R0 = 0
    BLGT return                 ;return R0
    MOV R4, #0                  ;i = 0
    MOV R5, #0                  ;R5 = 0 (to clear hist)
clear_hist
    STR R5, [R3, R4]            ;hist[i] = 0
    ADD R4, #2                  ;i += 2
    CMP R4, #510                ;i == 255*2?
    BLE clear_hist
    MOV R4, #0                  ;i = 0
calc_hist
    LDRB R5, [R2, R4]            ;read a pixel in img
    LDR R1, [R3, R5]           ;read hist[pixel]
    ADD R1, #1                  ;hist[pixel]++
    STR R1, [R3, R5]            ;hist[i] = cont
    ADD R4, #2                  ;i += 2 (img pixel is type uint16_t)
    CMP R4, R0                  ;i > img_size?
    BLE calc_hist
    
return
    POP {R4, R5, PC}
    
    END