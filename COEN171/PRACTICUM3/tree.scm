; vi:ai:lisp:sm
; an empty node is represented as an empty list
; a nonempty node is represented as a list with three elements:
; - the first element is the integer data
; - the second element is the left child
; - the third element is the right child

; Returns true if the integer data is found in the tree, and false otherwise.
(define (member? t x)
    (cond
        ((null? t) #f)
        ((< x (car t)) (member? (cadr t) x))
        ((> x (car t)) (member? (caddr t) x))
        (else #t)))

; Returns a tree that is the result of inserting the integer into the tree.
(define (insert t x)
    (cond
        ((null? t) (list x '() '()))
        ((< x (car t)) (list (car t) (insert (cadr t) x) (caddr t)))
        ((> x (car t)) (list (car t) (cadr t) (insert (caddr t) x)))
        (else t)))

; Inserts values in a list into a tree
(define (fold func val lst)
    (if (null? lst) val (fold func (func val (car lst)) (cdr lst))))

(define (build lst)
    (fold (lambda (t v) (insert t v)) '() lst))

; Returns the maximum out of tree
(define (maximum t)
    (cond
        ((null? t) #f)
        ((null? (caddr t)) (car t))
        (else (maximum (caddr t)))))