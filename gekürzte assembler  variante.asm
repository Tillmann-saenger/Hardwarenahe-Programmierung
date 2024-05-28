.data
LED_PIN: .word 10
C3_GPIO: .word 0x60004000

.text
    .global app_main
    app_main:
        lw a0, C3_GPIO
        lw a1, LED_PIN
        
        # Pin On
        li t0, 1           #setzten von bit 1
        sll t0,t0,a1	   #bitschift (BIT(x))
        sw t0, 32(a0)	   #enable von pin
    toggle_led:                  
        lw t4, 4(a0)       #led an/aus
        xor t4, t4, t0     #xor zum tggeln der an/aus zustände
        sw t4, 4(a0)       #abspeichern von berechnung (toggle)
        li t5, 0           #init loop
        li t6, 1000000     #100000 durchläufe (je nach takt -> delay)
    loop:
        addi t5, t5, 1     #hochzählen um 1
        blt t5, t6, loop   #zurückspringen <= 1000000
        j toggle_led       #toggle led wenn durchgänge erreicht