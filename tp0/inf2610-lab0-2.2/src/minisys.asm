; Voir: linux/arch/x86/syscalls/syscall_64.tbl
; pour la liste complete des appels systemes
;
; Documentation NASM: http://www.nasm.us/doc/nasmdoc3.html
;
; Definitions de constantes :
; db=char, dw=short, dd=int, dq=long
;
; Etiquettes (equivalent a #define)
sys_write       equ    1
sys_exit        equ    60
stdout          equ    1

SECTION .data
; Voir: man ascii
msg             db     0x0A,"INF2610-TP0",0x0A
msg_len         equ    $-msg
fmt             db     "%d",0x0A,0

; Voir: man nanosleep
; struct timespec delay
delay   dq 0
        dq 1000000

SECTION .text
global  _start

_start:
    ;
    ; Convention d'appel systeme Linux x86_64
    ;
    ; parametres: rdi, rsi, rdx, r10, r8, r9
    ; numero de l'appel systeme: rax
    ; valeur de retour: rax
    ;

    ;
    ; Ecrire msg sur la sortie standard
    ;
    ; prototype: int sys_write(unsigned int fd,
    ;                          const char *buf,
    ;                          size_t count)
    ;
    mov     rdi, stdout     ; argument 1
    mov     rsi, msg        ; argument 2
    mov     rdx, msg_len    ; argument 3
    mov     rax, sys_write  ; appel systeme dans rax
    syscall                 ; interruption logicielle

    ; TODO: Pause avec nanosleep
    ;
    ; prototype: sys_nanosleep(struct timespec *delay,
    ;                          struct timespec *remain)
    ;
    sleep 10
    ;
    ; Terminaison du processus
    ;
    ; prototype: sys_exit(int status)
    ;
    xor     rdi, rdi      ; remise a zero
    mov     rax, sys_exit ; appel systeme dans rax
    syscall               ; interruption logicielle
